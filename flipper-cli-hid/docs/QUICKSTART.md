# Quick Start Guide

Get up and running with the CLI HID input system in 10 minutes.

## Choose Your Hardware

### Option 1: ESP32 (Recommended)

**Pros:**
- Simple setup
- Cheap (~$8)
- All-in-one WiFi + USB HID

**Cons:**
- Need to buy hardware

### Option 2: Flipper Zero

**Pros:**
- Cool factor
- Multi-purpose device

**Cons:**
- More expensive
- Requires WiFi Dev Board
- More complex setup
- **Not currently fully implemented** (use ESP32 instead)

## Setup: ESP32 (Recommended Path)

### 1. Hardware

Buy an **ESP32-S2** or **ESP32-S3** development board:
- Must have native USB support (S2 or S3, not original ESP32)
- ~$8 on AliExpress, Amazon, etc.
- Example: "ESP32-S3 DevKit"

### 2. Install Arduino IDE

1. Download: https://www.arduino.cc/en/software
2. Install on your computer

### 3. Setup Arduino for ESP32

1. File → Preferences
2. Additional Board Manager URLs:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Tools → Board → Boards Manager
4. Search "esp32" and install

### 4. Install Libraries

Tools → Manage Libraries, install:
- PubSubClient
- ArduinoJson

### 5. Configure Firmware

Edit `firmware/esp32/esp32_hid_keyboard/config.h`:

```cpp
#define WIFI_SSID "YourWiFiName"
#define WIFI_PASSWORD "YourWiFiPassword"
#define MQTT_BROKER "broker.hivemq.com"  // Or your own
#define DEVICE_ID "my-device"
```

### 6. Upload Firmware

1. Connect ESP32 via USB to your computer
2. Open `firmware/esp32/esp32_hid_keyboard/esp32_hid_keyboard.ino`
3. Tools → Board → ESP32S3 Dev Module
4. Tools → USB Mode → "USB-OTG (TinyUSB)"
5. Tools → Port → Select ESP32 port
6. Click Upload button
7. Wait for "Done uploading"

### 7. Setup CLI

```bash
cd cli
npm install
cp .env.example .env
```

Edit `.env` if needed (default works with public broker).

### 8. Test!

**Connect ESP32 to target computer:**
- Unplug ESP32 from your computer
- Plug into the offline/target computer
- It should be recognized as a keyboard

**From CLI computer (with internet):**

```bash
# Type text
npm start -- type "Hello from the internet!"

# Press Enter
npm start -- key ENTER

# Key combination
npm start -- combo "CTRL+ALT+DELETE"

# Check device status
npm start -- status
```

## Troubleshooting

### ESP32 not detected as keyboard

- Make sure you have ESP32-S2 or S3 (not original ESP32)
- Check USB Mode is "USB-OTG (TinyUSB)"
- Try different USB cable
- Check serial monitor (115200 baud) for errors

### WiFi not connecting

- Check SSID/password in config.h
- ESP32 only supports 2.4GHz WiFi
- Check serial monitor for connection status

### MQTT not working

- Public brokers can be unreliable
- Consider running your own:
  ```bash
  docker run -d -p 1883:1883 eclipse-mosquitto
  ```
- Update `MQTT_BROKER` in config.h to your broker IP

### Commands not executing

- Check device ID matches in config.h and .env
- Monitor serial output on ESP32
- Ensure ESP32 is connected to both WiFi and target computer

## Next Steps

- Set up your own MQTT broker for reliability
- Create custom command scripts
- Build the UID feature (future branch)
- Experiment with Bad USB scripts on Flipper Zero

## Security Notes

⚠️ **This tool can control computers remotely**

- Use only on devices you own/have permission to access
- Secure your MQTT broker (authentication, encryption)
- Don't expose to public internet without proper security
- Change default device IDs
- Use private MQTT brokers for production

## Support

For issues, check:
1. Serial monitor output (ESP32 side)
2. CLI console output
3. MQTT broker logs
4. GitHub issues in the repo
