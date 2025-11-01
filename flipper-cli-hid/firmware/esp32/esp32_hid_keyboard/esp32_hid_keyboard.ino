/*
 * ESP32-S2/S3 USB HID Keyboard via MQTT
 *
 * Receives keyboard commands over WiFi/MQTT and executes them as USB HID keyboard
 *
 * Hardware: ESP32-S2 or ESP32-S3 (required for native USB HID)
 *
 * Author: Generated with ❤️
 * License: See LICENSE file (eMoGPLol™️)
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "USB.h"
#include "USBHIDKeyboard.h"
#include "config.h"

// Global objects
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
USBHIDKeyboard keyboard;

// State tracking
unsigned long lastReconnectAttempt = 0;
unsigned long lastStatusReport = 0;
bool wifiConnected = false;
bool mqttConnected = false;

// Function prototypes
void setupWiFi();
void reconnectMQTT();
void mqttCallback(char* topic, byte* payload, unsigned int length);
void handleCommand(JsonDocument& doc);
void typeText(const char* text);
void pressKey(uint8_t key);
void pressKeyCombo(const char* combo);
void sendStatus();
uint8_t getKeyCode(const char* keyName);

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n\n====================================");
  Serial.println("ESP32 USB HID Keyboard via MQTT");
  Serial.println("====================================\n");

  // Initialize USB HID Keyboard
  keyboard.begin();
  USB.begin();
  Serial.println("✓ USB HID Keyboard initialized");

  // Connect to WiFi
  setupWiFi();

  // Setup MQTT
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);
  mqttClient.setBufferSize(512);

  Serial.println("\n✓ Setup complete!");
  Serial.println("Waiting for commands...\n");
}

void loop() {
  // Maintain WiFi connection
  if (WiFi.status() != WL_CONNECTED) {
    if (wifiConnected) {
      Serial.println("✗ WiFi connection lost!");
      wifiConnected = false;
    }
    setupWiFi();
  } else {
    wifiConnected = true;
  }

  // Maintain MQTT connection
  if (!mqttClient.connected()) {
    if (mqttConnected) {
      Serial.println("✗ MQTT connection lost!");
      mqttConnected = false;
    }

    unsigned long now = millis();
    if (now - lastReconnectAttempt > MQTT_RECONNECT_INTERVAL) {
      lastReconnectAttempt = now;
      reconnectMQTT();
    }
  } else {
    mqttConnected = true;
    mqttClient.loop();
  }

  // Send periodic status updates
  if (mqttConnected) {
    unsigned long now = millis();
    if (now - lastStatusReport > STATUS_REPORT_INTERVAL) {
      lastStatusReport = now;
      sendStatus();
    }
  }

  delay(10);
}

void setupWiFi() {
  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long startAttempt = millis();
  while (WiFi.status() != WL_CONNECTED &&
         millis() - startAttempt < WIFI_CONNECT_TIMEOUT) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✓ WiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    wifiConnected = true;
  } else {
    Serial.println("\n✗ WiFi connection failed!");
    wifiConnected = false;
  }
}

void reconnectMQTT() {
  Serial.print("Connecting to MQTT broker: ");
  Serial.println(MQTT_BROKER);

  String clientId = "ESP32-HID-";
  clientId += String(random(0xffff), HEX);

  if (mqttClient.connect(clientId.c_str())) {
    Serial.println("✓ MQTT connected!");

    // Subscribe to command topic
    mqttClient.subscribe(MQTT_TOPIC_CMD);
    Serial.print("✓ Subscribed to: ");
    Serial.println(MQTT_TOPIC_CMD);

    mqttConnected = true;
    sendStatus();
  } else {
    Serial.print("✗ MQTT connection failed, rc=");
    Serial.println(mqttClient.state());
    mqttConnected = false;
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("← Message received on topic: ");
  Serial.println(topic);

  // Parse JSON
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, payload, length);

  if (error) {
    Serial.print("✗ JSON parse error: ");
    Serial.println(error.c_str());
    return;
  }

  // Check device ID
  const char* deviceId = doc["device_id"];
  if (deviceId && strcmp(deviceId, DEVICE_ID) != 0) {
    Serial.println("  Ignoring: device_id mismatch");
    return;
  }

  // Handle command
  handleCommand(doc);
}

void handleCommand(JsonDocument& doc) {
  const char* type = doc["type"];
  const char* payload = doc["payload"];
  int delay_ms = doc["delay"] | 0;

  if (!type || !payload) {
    Serial.println("✗ Invalid command: missing type or payload");
    return;
  }

  Serial.print("→ Executing command: ");
  Serial.print(type);
  Serial.print(" = ");
  Serial.println(payload);

  // Apply delay if specified
  if (delay_ms > 0) {
    Serial.print("  Waiting ");
    Serial.print(delay_ms);
    Serial.println("ms...");
    delay(delay_ms);
  }

  // Execute command
  if (strcmp(type, "type") == 0) {
    typeText(payload);
  } else if (strcmp(type, "key") == 0) {
    uint8_t keyCode = getKeyCode(payload);
    if (keyCode > 0) {
      pressKey(keyCode);
    } else {
      Serial.println("✗ Unknown key name");
    }
  } else if (strcmp(type, "combo") == 0) {
    pressKeyCombo(payload);
  } else {
    Serial.println("✗ Unknown command type");
  }
}

void typeText(const char* text) {
  keyboard.print(text);
  Serial.println("✓ Text typed");
}

void pressKey(uint8_t key) {
  keyboard.press(key);
  delay(50);
  keyboard.releaseAll();
  Serial.println("✓ Key pressed");
}

void pressKeyCombo(const char* combo) {
  // Parse combo like "CTRL+ALT+DELETE"
  Serial.print("  Parsing combo: ");
  Serial.println(combo);

  String comboStr = String(combo);
  comboStr.toUpperCase();

  // Simple implementation - extend as needed
  if (comboStr.indexOf("CTRL") >= 0) keyboard.press(KEY_LEFT_CTRL);
  if (comboStr.indexOf("ALT") >= 0) keyboard.press(KEY_LEFT_ALT);
  if (comboStr.indexOf("SHIFT") >= 0) keyboard.press(KEY_LEFT_SHIFT);
  if (comboStr.indexOf("GUI") >= 0 || comboStr.indexOf("WIN") >= 0) {
    keyboard.press(KEY_LEFT_GUI);
  }

  // Check for special keys
  if (comboStr.indexOf("DELETE") >= 0) keyboard.press(KEY_DELETE);
  else if (comboStr.indexOf("ENTER") >= 0) keyboard.press(KEY_RETURN);
  else if (comboStr.indexOf("TAB") >= 0) keyboard.press(KEY_TAB);
  else if (comboStr.indexOf("ESC") >= 0) keyboard.press(KEY_ESC);

  delay(100);
  keyboard.releaseAll();
  Serial.println("✓ Key combo pressed");
}

uint8_t getKeyCode(const char* keyName) {
  String key = String(keyName);
  key.toUpperCase();

  // Special keys mapping
  if (key == "ENTER" || key == "RETURN") return KEY_RETURN;
  if (key == "TAB") return KEY_TAB;
  if (key == "BACKSPACE") return KEY_BACKSPACE;
  if (key == "DELETE") return KEY_DELETE;
  if (key == "ESC" || key == "ESCAPE") return KEY_ESC;
  if (key == "SPACE") return ' ';
  if (key == "UP") return KEY_UP_ARROW;
  if (key == "DOWN") return KEY_DOWN_ARROW;
  if (key == "LEFT") return KEY_LEFT_ARROW;
  if (key == "RIGHT") return KEY_RIGHT_ARROW;
  if (key == "HOME") return KEY_HOME;
  if (key == "END") return KEY_END;
  if (key == "PAGEUP") return KEY_PAGE_UP;
  if (key == "PAGEDOWN") return KEY_PAGE_DOWN;

  // Single character
  if (key.length() == 1) {
    return key[0];
  }

  return 0;
}

void sendStatus() {
  JsonDocument doc;
  doc["device_id"] = DEVICE_ID;
  doc["status"] = "online";
  doc["wifi_connected"] = wifiConnected;
  doc["mqtt_connected"] = mqttConnected;
  doc["wifi_rssi"] = WiFi.RSSI();
  doc["uptime"] = millis() / 1000;

  char buffer[256];
  serializeJson(doc, buffer);

  mqttClient.publish(MQTT_TOPIC_STATUS, buffer);
  Serial.print("→ Status sent: ");
  Serial.println(buffer);
}
