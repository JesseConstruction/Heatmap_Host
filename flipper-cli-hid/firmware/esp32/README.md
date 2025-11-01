# ESP32 USB HID Firmware

This firmware turns an ESP32-S2/S3 into a WiFi-enabled USB HID keyboard.

## Hardware Requirements

- **ESP32-S2** or **ESP32-S3** (required for native USB support)
- USB-A cable for connection to target computer
- WiFi network

**Recommended boards:**
- ESP32-S3 DevKit (~$8 on AliExpress)
- ESP32-S2 Mini
- Any ESP32-S2/S3 with USB port

## Features

- Receives commands via MQTT over WiFi
- Emulates USB HID keyboard
- Supports text typing, special keys, and key combinations
- Status reporting
- Auto-reconnect for WiFi and MQTT

## Setup

### 1. Install Arduino IDE

Download from: https://www.arduino.cc/en/software

### 2. Add ESP32 Board Support

1. Open Arduino IDE
2. File → Preferences
3. Add to "Additional Board Manager URLs":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Tools → Board → Boards Manager
5. Search "esp32" and install "esp32" by Espressif

### 3. Install Required Libraries

Tools → Manage Libraries, install:
- **PubSubClient** by Nick O'Leary
- **ArduinoJson** by Benoit Blanchon

### 4. Configure WiFi and MQTT

Edit `config.h`:
```cpp
#define WIFI_SSID "YourWiFiSSID"
#define WIFI_PASSWORD "YourWiFiPassword"
#define MQTT_BROKER "broker.hivemq.com"
#define DEVICE_ID "default"
```

### 5. Upload Firmware

1. Connect ESP32 via USB
2. Tools → Board → ESP32 Arduino → ESP32S3 Dev Module (or your board)
3. Tools → USB Mode → "USB-OTG (TinyUSB)"
4. Tools → Port → Select your ESP32 port
5. Click Upload

### 6. Test

After uploading, the ESP32 will:
1. Connect to WiFi
2. Connect to MQTT broker
3. Act as USB keyboard when plugged into target computer

Monitor serial output (115200 baud) for status.

## Troubleshooting

**ESP32 not detected as USB device:**
- Ensure you're using ESP32-S2 or S3 (S1 doesn't have native USB)
- Check USB Mode is set to "USB-OTG (TinyUSB)"
- Try a different USB cable (some are power-only)

**WiFi connection fails:**
- Check SSID and password in config.h
- Ensure 2.4GHz WiFi (ESP32 doesn't support 5GHz)

**MQTT not connecting:**
- Check broker address
- Public brokers like HiveMQ are rate-limited, consider running your own

## Running Your Own MQTT Broker

For production use, run a local MQTT broker:

```bash
# Using Docker
docker run -d -p 1883:1883 eclipse-mosquitto

# Then update config.h
#define MQTT_BROKER "192.168.1.100"  // Your broker IP
```
