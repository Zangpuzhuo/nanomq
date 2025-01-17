# Configuration

## Introduction

The configuration files of NanoMQ Broker usually have the suffix .conf. You can find these configuration files in the etc directory.
| File                      | Description                   |
| ----------------------------- | ---------------------- |
| etc/nanomq.conf               | NanoMQ Configuration File        |
| etc/nanomq_bridge.conf        | NanoMQ Bridge File     |
| etc/nanomq_auth_username.conf | NanoMQ Authorization File  |
| etc/nanomq_web_hook.conf | NanoMQ Web Hook File  |
| etc/nanomq_gateway.conf       | NanoMQ Gateway File     |
| etc/nanomq_auth_http.conf     | NanoMQ HTTP Authentication File|

## Parameter Description

### nanomq.conf

| Name                  | Type    | Description                                                  |
| --------------------- | ------- | ------------------------------------------------------------ |
| url              | String  | Url of listener.                        |
| num_taskq_thread | Integer | Number of taskq threads used. |
| max_taskq_thread | Integer | Maximum number of taskq threads used. |
| parallel |Long  | Number of parallel.                                          |
| property_size |Integer  | Max size for a MQTT property. |
| msq_len | Integer | Queue length for resending messages. |
| qos_duration | Integer | The interval of the qos timer.                               |
| allow_anonymous | Boolean | Allow anonymous login.                                       |
| tls.enable | Boolean | Enable TLS listener(*default: false*).                                         |
| tls.url | String | URL of TLS listener. |
| tls.key | String | User's private PEM-encoded key. |
| tls.keypass | String | String containing the user's password. Only used if the private keyfile is password-protected. |
| tls.cert |String  | User certificate data.                                       |
| tls.cacert | String | User's PEM-encoded CA certificates.                          |
| tls.verify_peer | Boolean | Verify peer certificate.                                     |
| tls.fail_if_no_peer_cert | Boolean | Server will fail if the client does not have a certificate to send. |
| websocket.enable | Boolean | Enable websocket listener(*default: true*). |
| websocket.url | String  | URL of websocket listener. |
| websocket.tls_url |  String | URL of TLS over websocket listerner. |
| http_server.enable| Boolean | Enable http server listerner (*default: false*). |
| http_server.port | Integer | Port of http server. |
| http_server.username | String | User name of http server. |
| http_server.password | String | Password of http server. |
| http_server.auth_type | Enum | Http server authentication type (*default: basic*). |
| http_server.jwt.public.keyfile | String |public key file for *JWT*. |
| http_server.jwt.private.keyfile | String |private key file for *JWT*. |

### nanomq_bridge.conf

| Name                  | Type    | Description                                                  |
| --------------------- | ------- | ------------------------------------------------------------ |
| bridge.bridge_mode | Boolean | Enter MQTT bridge mode (default `false` ).                                  |
| bridge.address | String | Remote Broker address. |
| bridge.proto_ver | String | MQTT client version（3｜4｜5）. |
| bridge.clientid | String | MQTT client identifier. |
| bridge.keepalive | Integer | Interval of keepalive.                                       |
| bridge.clean_start | Boolean | Clean seeson.                                                |
| bridge.parallel | Long | Parallel of mqtt client. |
| bridge.username | String | Login user name. |
| bridge.password | String | Login password. |
| bridge.forwards | Array[String] | Array of forward topics.( *Use commas `,` to separate multiple topics* ) |
| bridge.mqtt.subscription.1.topic | String | First `Topic`.                               |
| bridge.mqtt.subscription.1.qos | Integer | First `Qos`.                       |
| bridge.mqtt.subscription.2.topic | String        | Second`Topic` ( *And so on* ).             |
| bridge.mqtt.subscription.2.qos   | Integer       | Second`Qos`( *And so on* ). |

### nanomq_auth_username.conf

| Name                  | Type    |  Description                                     |
| --------------- | -------- | ------------------------------- |
| auth.1.login    | String   | First Username.               |
| auth.1.password | String   | First Password.                 |
| auth.2.login    | String   | Second Username ( *And so on* ). |
| auth.2.password | String   | Second Password ( *And so on* ). |

### nanomq_web_hook.conf

| Name | Type | Description |
| ------ | -------- | -------- |
| web.hook.enable       | Boolean | Enable WebHook (default: `false`) |
| web.hook.url       | String | *Webhook URL* |
| web.hook.headers.\<Any\> | String | *HTTP Headers*<br>*Example:*<br>*1. web.hook.headers.content-type=application/json*<br> *2. web.hook.headers.accept=\** |
| web.hook.body.encoding_of_payload_field | Enum | *The encoding format of the payload field in the HTTP body*<br>Options: <br>plain \| base64 \| base62 |
| web.hook.ssl.cacertfile       | String | *PEM format file of CA's*. |
| web.hook.ssl.certfile       | String | *Certificate file to use, PEM format assumed.* |
| web.hook.ssl.keyfile       | String | *Private key file to use, PEM format assumed.* |
| web.hook.ssl.verify       | Boolean | *Turn on peer certificate verification*  (default: `false`). |
| web.hook.ssl.server_name_indication       | Boolean | *Verify server_name*  (default: `false`). |
| web.hook.pool_size | Integer | *Connection process pool size* (default: 32). |
| web.hook.rule.client.connack.\<No\>      | String  | Example: <br>*web.hook.rule.client.connack.1={"action": "on_client_connack"}* |
| web.hook.rule.client.disconnected.\<No\> | String  | *Example: <br/>web.hook.rule.client.disconnected.1={"action": "on_client_disconnected"}* |
| web.hook.rule.message.publish.\<No\>     | String  | Example: <br/>*web.hook.rule.message.publish.1={"action": "on_message_publish"}* <br>*web.hook.rule.message.publish.1={"action": "on_message_publish", "topic": "topic/1/2"}* <br>*web.hook.rule.message.publish.2 = {"action": "on_message_publish", "topic": "foo/#"}* |

### nanomq_gateway.conf

| Name                              | Type    | Description                                                  |
| --------------------------------- | ------- | ------------------------------------------------------------ |
| gateway.address                   | String  | Remote Broker address.                                       |
| gateway.proto_ver                 | String  | MQTT client version（3｜4｜5).                                |
| gateway.clientid                  | String  | MQTT client identifier.                                      |
| gateway.keepalive                 | Integer | Interval of keepalive.                                       |
| gateway.clean_start               | Boolean | Clean seeson.                                                |
| gateway.parallel                  | Long    | Parallel of mqtt client.                                     |
| gateway.username                  | String  | Login user name.                                             |
| gateway.password                  | String  | Login password.                                              |
| gateway.forward                   | String  | Forward topic.                                               |
| gateway.mqtt.subscription.topic   | String  | Mqtt subscribe topic.                                        |
| gateway.mqtt.subscription.qos     | Integer | Mqtt subscribe qos.                                          |
| gateway.zmq.sub.address           | String  | Remote ZMQ server subscribe address.                         |
| gateway.zmq.pub.address           | String  | Remote ZMQ server publish address.                           |
| gateway.zmq.sub_prefix            | String  | Remote ZMQ server subscribe prefix.                          |
| gateway.zmq.pub_prefix            | String  | Remote ZMQ server publish prefix.                            |

### nanomq_auth_http.conf

| Name                              | Type | Description                                                     | default                                                         |
| ----------------------------------- | -------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| auth.http.enable                    | Boolean  | Enable HTTP authentication                        | `false`                                                      |
| auth.http.auth_req.url              | String   | Specify the target URL of the authentication request. | `http://127.0.0.1:80/mqtt/auth`                              |
| auth.http.auth_req.method           | Enum     | Specify the request method of the authentication request.<br>(`POST`  , `GET`) | `POST`                                                       |
| auth.http.auth_req.headers.\<Any\>  | String   | Specify the data in the HTTP request header. `<Key>` Specify the field name in the HTTP request header, and the value of this configuration item is the corresponding field value. `<Key>` can be the standard HTTP request header field. User can also customize the field to configure multiple different request header fields. | `auth.http.auth_req.headers.content-type = application/x-www-form-urlencoded` <br/>`auth.http.auth_req.headers.accept = */*` |
| auth.http.auth_req.params           | String   | Specify the data carried in the authentication request. <br>When using the **GET** method, the value of `auth.http.auth_req.params` will be converted into `k=v` key-value pairs separated by `&` and sent as query string parameters. <br>When using the **POST** method, the value of `auth.http.auth_req.params` will be converted into `k=v` key-value pairs separated by `&` and sent in the form of Request Body. All placeholders will be replaced by run-time data , and the available placeholders are as follows:<br>`%u: Username`<br>`%c: MQTT Client ID`<br>`%a: Client's network IP address`<br>`%r: The protocol used by the client can be:mqtt, mqtt-sn, coap, lwm2m and stomp`<br>`%P: Password`<br>`%p: Server port for client connection`<br>`%C: Common Name in client certificate`<br>`%d: Subject in client certificate` | `clientid=%c,username=%u,password=%P`                        |
| auth.http.super_req.url             | String   | Specify the target URL for the superuser authentication request. | `http://127.0.0.1:80/mqtt/superuser`                         |
| auth.http.super_req.method          | String   | Specifies the request method of the super user authentication request.<br>(`POST`  , `GET`) | `POST`                                                       |
| auth.http.super_req.headers.\<Any\> | String   | Specify the data in the HTTP request header. `<Key>` Specify the field name in the HTTP request header, and the value of this configuration item is the corresponding field value. `<Key>` can be the standard HTTP request header field. User can also customize the field to configure multiple different request header fields. | `auth.http.super_req.headers.content-type = application/x-www-form-urlencoded`<br/>`auth.http.super_req.headers.accept = */*` |
| auth.http.super_req.params          | String   | Specify the data carried in the authentication request. <br>When using the **GET** method, the value of `auth.http.auth_req.params` will be converted into `k=v` key-value pairs separated by `&` and sent as query string parameters. <br>When using the **POST** method, the value of `auth.http.auth_req.params` will be converted into `k=v` key-value pairs separated by `&` and sent in the form of Request Body. All placeholders will be replaced by run-time data , and the available placeholders are the same as those of `auth.http.auth_req.params`. | `clientid=%c,username=%u`                                    |
| auth.http.acl_req.url               | String   | Specify the target URL for ACL verification requests. | `http://127.0.0.1:8991/mqtt/acl`                             |
| auth.http.acl_req.method            | String   | Specifies the request method for ACL verification requests.<br>(`POST`  , `GET`) | `POST`                                                       |
| auth.http.acl_req.headers.\<Any\>   | String   | Specify the data in the HTTP request header. `<Key>` Specify the field name in the HTTP request header, and the value of this configuration item is the corresponding field value. `<Key>` can be the standard HTTP request header field. User can also customize the field to configure multiple different request header fields. | `auth.http.super_req.headers.content-type = application/x-www-form-urlencoded`<br/>`auth.http.super_req.headers.accept = */*` |
| auth.http.acl_req.params            | String   | Specify the data carried in the authentication request. <br>When using the **GET** method, the value of `auth.http.auth_req.params` will be converted into `k=v` key-value pairs separated by `&` and sent as query string parameters. <br>When using the **POST** method, the value of `auth.http.auth_req.params` will be converted into `k=v` key-value pairs separated by `&` and sent in the form of Request Body. All placeholders will be replaced by run-time data , and the available placeholders are as follows:<br/>`%A: Permission to be verified, 1 means subscription, 2 means publish`<br>`%u: UserName`<br/>`%c: MQTT Client ID`<br/>`%a: Client network IP address`<br/>`%r: The protocol used by the client can be: mqtt, mqtt-sn, coap, lwm2m and stomp`<br/>`%m: Mount point`<br>`%t: Topic` | `access=%A,username=%u,clientid=%c,ipaddr=%a,topic=%t,mountpoint=%m` |
| auth.http.timeout                   | Integer  | HTTP request timeout. Any setting equivalent to `0s` means never timeout. | `5s`                                                         |
| auth.http.connect_timeout           | Integer  | Connection timeout for HTTP requests. Any setting value equivalent to `0s` means never time out. | `5s`                                                         |
| auth.http.ssl.cacertfile            | String   | CA certificate file path.                   | `etc/certs/ca.pem`                                           |
| auth.http.ssl.certfile              | String   | Client certificate file path. | `etc/certs/client-cert.pem`                                  |
| auth.http.ssl.keyfile               | String   | Client private key file path. | `etc/certs/client.key.pem`                                   |
