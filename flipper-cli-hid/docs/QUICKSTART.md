# Quick Start Guide

Get up and running with the CLI HID input system in 10 minutes.

## Choose Your Hardware

### Option 1: Arduino Portenta H7 (Recommended - Tested)

**Pros:**
- Professional-grade hardware
- Powerful dual-core processor
- Built-in WiFi (2.4GHz + 5GHz)
- Native USB HID support
- Runs Mbed OS (RTOS)
- Arduino ecosystem

**Cons:**
- Higher cost (~$100)
- Overkill for simple use case

### Option 2: ESP32 (Budget Option - Untested Draft)

**Pros:**
- Very cheap (~$8)
- All-in-one WiFi + USB HID
- Low power consumption

**Cons:**
- Need to buy hardware
- **Firmware untested**

### Option 3: Flipper Zero (Manual Mode Only)

**Pros:**
- Cool factor
- Multi-purpose device

**Cons:**
- Most expensive (~$199)
- Requires WiFi Dev Board (+$30)
- More complex setup
- **Not fully implemented** (manual Bad USB only)

## Setup: Portenta H7 (Recommended Path)

### 1. Hardware

You'll need:
- **Arduino Portenta H7** (any variant)
- USB-C cable (must support data transfer)
- WiFi network (2.4GHz or 5GHz)

### 2. Install Arduino IDE

1. Download: https://www.arduino.cc/en/software
2. Install on your computer

### 3. Setup Arduino for Portenta H7

1. File → Preferences
2. Additional Board Manager URLs:
   ```
   https://downloads.arduino.cc/packages/package_mbed_index.json
   ```
3. Tools → Board → Boards Manager
4. Search "portenta" and install "Arduino Mbed OS Portenta Boards"

### 4. Install Libraries

Tools → Manage Libraries, install:
- PubSubClient
- ArduinoJson

(USB HID libraries are included with Portenta board package)

### 5. Configure Firmware

Edit `firmware/portenta/portenta_h7_hid_keyboard/config.h`:

```cpp
#define WIFI_SSID "YourWiFiName"
#define WIFI_PASSWORD "YourWiFiPassword"
#define MQTT_BROKER "broker.hivemq.com"  // Or your own
#define DEVICE_ID "portenta-default"
```

### 6. Upload Firmware

1. Connect Portenta H7 via USB to your computer
2. Open `firmware/portenta/portenta_h7_hid_keyboard/portenta_h7_hid_keyboard.ino`
3. Tools → Board → Arduino Mbed OS Portenta Boards → Arduino Portenta H7 (M7 core)
4. Tools → Port → Select Portenta port
5. Click Upload button
6. Wait for "Done uploading"

### 7. Setup CLI

```bash
cd cli
npm install
cp .env.example .env
```

Edit `.env` if needed (default works with public broker).

### 8. Test!

**Connect Portenta H7 to target computer:**
- Unplug Portenta from your computer
- Plug into the offline/target computer via USB-C
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

**Monitor on Portenta:**
- Open Serial Monitor (115200 baud) while connected to your computer
- Should see WiFi connection, MQTT connection, and command execution logs

## Troubleshooting

### Portenta not detected as keyboard

- Ensure firmware was uploaded to **M7 core** (not M4)
- Check USB-C cable supports data transfer (not power-only)
- Try double-pressing reset button to enter bootloader
- Check Device Manager / System Info for USB HID device

### WiFi not connecting

- Check SSID/password in config.h
- Portenta supports both 2.4GHz and 5GHz WiFi
- Check serial monitor for connection status
- Move closer to router for testing

### MQTT not working

- Public brokers can be unreliable and rate-limited
- Consider running your own:
  ```bash
  docker run -d -p 1883:1883 eclipse-mosquitto
  ```
- Update `MQTT_BROKER` in config.h to your broker IP
- Check firewall isn't blocking port 1883

### Commands not executing

- Check device ID matches in config.h and .env
- Monitor serial output on Portenta (115200 baud)
- Ensure Portenta is connected to both WiFi and target computer
- Verify MQTT broker is accessible from Portenta's network

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
