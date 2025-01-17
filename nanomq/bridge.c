#include "include/bridge.h"
#include "nng/mqtt/mqtt_client.h"
#include "nng/nng.h"
#include "nng/protocol/mqtt/mqtt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/nanomq.h"

static void
fatal(const char *func, int rv)
{
	fprintf(stderr, "%s: %s\n", func, nng_strerror(rv));
}

nng_msg *
bridge_publish_msg(const char *topic, uint8_t *payload, uint32_t len, bool dup,
    uint8_t qos, bool retain)
{
	int rv;

	// create a PUBLISH message
	nng_msg *pubmsg;
	nng_mqtt_msg_alloc(&pubmsg, 0);
	nng_mqtt_msg_set_packet_type(pubmsg, NNG_MQTT_PUBLISH);
	nng_mqtt_msg_set_publish_dup(pubmsg, dup);
	nng_mqtt_msg_set_publish_qos(pubmsg, qos);
	nng_mqtt_msg_set_publish_retain(pubmsg, retain);
	nng_mqtt_msg_set_publish_payload(pubmsg, payload, len);
	nng_mqtt_msg_set_publish_topic(pubmsg, topic);

	debug_msg("publish to '%s'", topic);

	return pubmsg;
}

// Disconnect message callback function
static void
disconnect_cb(nng_pipe p, nng_pipe_ev ev, void *arg)
{
	debug_msg("disconnected");
}

typedef struct {
	nng_socket * sock;
	conf_bridge *config;
} bridge_param;

// Connack message callback function
static void
bridge_connect_cb(nng_pipe p, nng_pipe_ev ev, void *arg)
{
	// Connected succeed
	bridge_param *param = arg;
	nng_msg *     msg;

	nng_mqtt_msg_alloc(&msg, 0);
	nng_mqtt_msg_set_packet_type(msg, NNG_MQTT_SUBSCRIBE);

	nng_mqtt_topic_qos *topic_qos =
	    nng_mqtt_topic_qos_array_create(param->config->sub_count);
	for (size_t i = 0; i < param->config->sub_count; i++) {
		nng_mqtt_topic_qos_array_set(topic_qos, i,
		    param->config->sub_list[i].topic,
		    param->config->sub_list[i].qos);
	}
	nng_mqtt_msg_set_subscribe_topics(
	    msg, topic_qos, param->config->sub_count);

	nng_mqtt_topic_qos_array_free(topic_qos, param->config->sub_count);

	// Send subscribe message
	nng_sendmsg(*param->sock, msg, NNG_FLAG_NONBLOCK);
}

static bridge_param bridge_arg;

int
bridge_client(nng_socket *sock, conf *config)
{
	int        rv;
	nng_dialer dialer;
	if ((rv = nng_mqtt_client_open(sock)) != 0) {
		fatal("nng_mqtt_client_open", rv);
		return rv;
	}
	nng_socket_set(*sock, NANO_CONF, config, sizeof(conf));
	conf_bridge  *bridge_conf = &config->bridge;

	if ((rv = nng_dialer_create(&dialer, *sock, bridge_conf->address))) {
		fatal("nng_dialer_create", rv);
		return rv;
	}

	// create a CONNECT message
	/* CONNECT */
	nng_msg *connmsg;
	nng_mqtt_msg_alloc(&connmsg, 0);
	nng_mqtt_msg_set_packet_type(connmsg, NNG_MQTT_CONNECT);
	nng_mqtt_msg_set_connect_keep_alive(connmsg, bridge_conf->keepalive);
	nng_mqtt_msg_set_connect_proto_version(connmsg, bridge_conf->proto_ver);
	nng_mqtt_msg_set_connect_clean_session(connmsg, bridge_conf->clean_start);
	if (bridge_conf->clientid) {
		nng_mqtt_msg_set_connect_client_id(connmsg, bridge_conf->clientid);
	}
	if (bridge_conf->username) {
		nng_mqtt_msg_set_connect_user_name(connmsg, bridge_conf->username);
	}
	if (bridge_conf->password) {
		nng_mqtt_msg_set_connect_password(connmsg, bridge_conf->password);
	}

	bridge_arg.config = bridge_conf;
	bridge_arg.sock   = sock;

	nng_dialer_set_ptr(dialer, NNG_OPT_MQTT_CONNMSG, connmsg);
	nng_mqtt_set_connect_cb(*sock, bridge_connect_cb, &bridge_arg);
	nng_mqtt_set_disconnect_cb(*sock, disconnect_cb, connmsg);

	nng_dialer_start(dialer, NNG_FLAG_NONBLOCK);
	return 0;
}