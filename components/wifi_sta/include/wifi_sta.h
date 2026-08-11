#ifndef WIFI_STA_H
#define WIFI_STA_H

#include "esp_err.h"

#define WIFI_STA_CONNECTED_BIT BIT0
#define WIFI_STA_IPV4_OBTAINED_BIT BIT1
#define WIFI_STA_IPV6_OBTAINED_BIT BIT2

/**
 * @brief initialize the wifi in station mode
 * 
 * sets up the wifi interface and connect to a wifi network.
 */

esp_err_t wifi_sta_init(EventGroupHandle_t event_group);

/**
 * @brief disable wifi
 */
esp_err_t wifi_sta_stop(void);


/**
 * @brief attempt to reconnect to wifi
 */
esp_err_t wifi_sta_reconnect(void);

#endif // WIFI_STA_H