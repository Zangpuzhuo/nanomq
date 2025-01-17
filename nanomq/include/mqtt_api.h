#ifndef MQTT_API_H
#define MQTT_API_H
#include <conf.h>
#include <nng/mqtt/mqtt_client.h>
#include <nng/supplemental/tls/tls.h>
#include <nng/supplemental/util/options.h>
#include <nng/supplemental/util/platform.h>
#include <nng/protocol/mqtt/mqtt.h>

int nano_listen(nng_socket sid, const char *addr, nng_listener *lp, int flags, conf *conf);
int init_listener_tls(nng_listener l, conf_tls *tls);
#endif // MQTT_API_H