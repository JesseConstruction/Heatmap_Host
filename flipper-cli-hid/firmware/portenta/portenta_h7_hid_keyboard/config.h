#ifndef CONFIG_H
#define CONFIG_H

// WiFi Configuration
#define WIFI_SSID "YourWiFiSSID"
#define WIFI_PASSWORD "YourWiFiPassword"

// MQTT Configuration
#define MQTT_BROKER "broker.hivemq.com"
#define MQTT_PORT 1883
#define MQTT_TOPIC_CMD "hid-device/command"
#define MQTT_TOPIC_STATUS "hid-device/status"

// Device Configuration
#define DEVICE_ID "portenta-default"

// Timing
#define WIFI_CONNECT_TIMEOUT 20000  // 20 seconds
#define MQTT_RECONNECT_INTERVAL 5000  // 5 seconds
#define STATUS_REPORT_INTERVAL 30000  // 30 seconds

#endif
