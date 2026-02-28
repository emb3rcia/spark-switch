//
// Created by ember on 2/28/26.
//

//made with help of ai as prototype, will be mostly rewritten when i get switch physically and can try the code

#include "webui.h"
#include "lwip/api.h"
#include "config.h"
#include <string.h>
#include <stdio.h>

void send_webpage(struct netconn *conn) {
    char *buf = (char *)pvPortMalloc(1024); // Tymczasowy bufor na fragmenty
    if (!buf) return;

    netconn_write(conn, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n", 44, NETCONN_COPY);
    netconn_write(conn, "<html><head><meta charset='UTF-8'><title>Switch Config</title></head><body>", 75, NETCONN_COPY);
    netconn_write(conn, "<h2>Konfiguracja spark-switch</h2><form method='POST'>", 54, NETCONN_COPY);

    snprintf(buf, 1024, "<b>Broker MQTT:</b> <input type='text' name='mqtt_ip' value='%s'><br><br>", CurrentConfig.mqtt_broker_ip);
    netconn_write(conn, buf, strlen(buf), NETCONN_COPY);

    netconn_write(conn, "<b>Port status:</b><br>", 23, NETCONN_COPY);
    for (int i = 1; i <= 5; i++) {
        const char *is_checked = (CurrentConfig.port_enabled[i]) ? "checked" : "";
        snprintf(buf, 1024, "P%d: <input type='checkbox' name='p%d' %s> ", i, i, is_checked);
        netconn_write(conn, buf, strlen(buf), NETCONN_COPY);
    }
    netconn_write(conn, "<br><br>", 8, NETCONN_COPY);

    netconn_write(conn, "<b>Active VLANs:</b><table border='1'><tr><th>VID</th><th>Mask</th><th>Action</th></tr>", 87, NETCONN_COPY);
    for (int i = 0; i < 15; i++) {
        if (CurrentConfig.vlans[i].is_active) {
            snprintf(buf, 1024, "<tr><td>%d</td><td>0x%02X</td><td><a href='/?del=%d'>Delete</a></td></tr>",
                     CurrentConfig.vlans[i].vid, CurrentConfig.vlans[i].port_mask, i);
            netconn_write(conn, buf, strlen(buf), NETCONN_COPY);
        }
    }
    netconn_write(conn, "</table><br>", 12, NETCONN_COPY);

    netconn_write(conn, "<b>Add VLAN:</b> VID: <input type='text' name='new_vid' size='4'> ", 65, NETCONN_COPY);
    netconn_write(conn, "Mask: <input type='text' name='new_mask' size='4' placeholder='np. 7'> ", 72, NETCONN_COPY);

    netconn_write(conn, "<br><br><input type='submit' value='Submit changes'></form></body></html>", 74, NETCONN_COPY);

    vPortFree(buf);
}

void StartWebUITask(void const * argument) {
    struct netconn *conn, *newconn;
    err_t err;

    conn = netconn_new(NETCONN_TCP);
    if (conn != NULL) {
        err = netconn_bind(conn, IP_ADDR_ANY, 80);
        if (err == ERR_OK) {
            netconn_listen(conn);

            for (;;) {
                err = netconn_accept(conn, &newconn);
                if (err == ERR_OK) {
                    struct netbuf *buf;
                    void *data;
                    u16_t len;

                    if (netconn_recv(newconn, &buf) == ERR_OK) {
                        netbuf_data(buf, &data, &len);

                        if (strncmp(data, "POST", 4) == 0) {
                            char *ip_ptr = strstr((char*)data, "mqtt_ip=");
                            if (ip_ptr) {
                                ip_ptr += 8;

                                char *end_ptr = strchr(ip_ptr, '&');
                                int ip_len = end_ptr ? (end_ptr - ip_ptr) : strlen(ip_ptr);

                                if (ip_len > 0 && ip_len < 16) {
                                    strncpy(CurrentConfig.mqtt_broker_ip, ip_ptr, ip_len);
                                    CurrentConfig.mqtt_broker_ip[ip_len] = '\0';
                                }
                            }

                            for (int i = 1; i <= 5; i++) {
                                char key[6];
                                snprintf(key, 10, "p%d=on", i);
                                uint8_t newState = (strstr(data, key) != NULL) ? 1 : 0;

                                if (newState != CurrentConfig.port_enabled[i]) {
                                    CurrentConfig.port_enabled[i] = newState;
                                    KSZ_WriteReg8((i << 12) | 0x0B04, newState ? 0x06 : 0x00);
                                }
                            }

                            char *v_vid = strstr(data, "new_vid=");
                            char *v_mask = strstr(data, "new_mask=");
                            if (v_vid && strlen(v_vid + 8) > 0) {
                                for (int i = 0; i < 15; i++) {
                                    if (!CurrentConfig.vlans[i].is_active) {
                                        CurrentConfig.vlans[i].vid = atoi(v_vid + 8);
                                        CurrentConfig.vlans[i].port_mask = atoi(v_mask + 9);
                                        CurrentConfig.vlans[i].is_active = 1;
                                        KSZ_SetVLAN(CurrentConfig.vlans[i].vid, CurrentConfig.vlans[i].port_mask, 1);
                                        break;
                                    }
                                }
                            }
                            Config_SaveToFlash();
                        }
                        if (strstr(data, "GET /?del=")) {
                            char *del_ptr = strstr(data, "del=") + 4;
                            int idx = atoi(del_ptr);
                            if (idx >= 0 && idx < 15) {
                                KSZ_SetVLAN(CurrentConfig.vlans[idx].vid, 0, 0);
                                CurrentConfig.vlans[idx].is_active = 0;
                                Config_SaveToFlash();
                            }
                        }

                        send_webpage(newconn);

                        netbuf_delete(buf);
                    }
                    netconn_close(newconn);
                    netconn_delete(newconn);
                }

            }
        }
    }
}