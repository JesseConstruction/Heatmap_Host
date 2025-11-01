# Arduino Portenta H7 USB HID Firmware

This firmware turns an Arduino Portenta H7 into a WiFi-enabled USB HID keyboard.

## Hardware Requirements

- **Arduino Portenta H7** (any variant)
- USB-C cable for connection to target computer
- WiFi network (2.4GHz or 5GHz supported)

## Features

- Receives commands via MQTT over WiFi
- Emulates USB HID keyboard
- Supports text typing, special keys, and key combinations
- Status reporting with device info
- Auto-reconnect for WiFi and MQTT
- Dual-core ARM Cortex-M7 + M4 processor
- Built-in WiFi (Murata 1DX module)

## Setup

### 1. Install Arduino IDE

Download from: https://www.arduino.cc/en/software

### 2. Add Portenta Board Support

1. Open Arduino IDE
2. File → Preferences
3. Add to "Additional Board Manager URLs":
   ```
   https://downloads.arduino.cc/packages/package_mbed_index.json
   ```
4. Tools → Board → Boards Manager
5. Search "portenta" and install "Arduino Mbed OS Portenta Boards"

### 3. Install Required Libraries

Tools → Manage Libraries, install:
- **PubSubClient** by Nick O'Leary
- **ArduinoJson** by Benoit Blanchon

The USB HID libraries are included with the Portenta board package.

### 4. Configure WiFi and MQTT

Edit `config.h`:
```cpp
#define WIFI_SSID "YourWiFiSSID"
#define WIFI_PASSWORD "YourWiFiPassword"
#define MQTT_BROKER "broker.hivemq.com"
#define DEVICE_ID "portenta-default"
```

### 5. Upload Firmware

1. Connect Portenta H7 via USB to your computer
2. Open `portenta_h7_hid_keyboard.ino`
3. Tools → Board → Arduino Mbed OS Portenta Boards → Arduino Portenta H7 (M7 core)
4. Tools → Port → Select Portenta port (usually "Arduino Portenta H7")
5. Click Upload
6. Wait for "Done uploading"

### 6. Test

After uploading, the Portenta will:
1. Connect to WiFi (LED should indicate activity)
2. Connect to MQTT broker
3. Act as USB keyboard when plugged into target computer

Monitor serial output (115200 baud) for status.

## LED Indicators

The Portenta H7 has RGB LEDs that can indicate status:
- **WiFi connecting**: Blinking blue (if implemented)
- **WiFi connected**: Solid blue
- **MQTT connected**: Solid green
- **Error**: Red

*(LED status code can be added to firmware if desired)*

## Troubleshooting

### Portenta not detected as USB device

- Ensure firmware uploaded to **M7 core** (not M4)
- Check USB-C cable (must support data, not just power)
- Try double-pressing reset button to enter bootloader mode
- Check Device Manager / System Info for USB device

### WiFi connection fails

- Check SSID and password in config.h
- Portenta supports both 2.4GHz and 5GHz WiFi
- Check WiFi signal strength (Portenta antenna is internal)
- Try moving closer to router for testing

### MQTT not connecting

- Check broker address and port
- Public brokers like HiveMQ are rate-limited, consider running your own
- Check firewall settings
- Monitor serial output for specific error codes

### Upload fails

- Double-tap reset button to enter bootloader mode
- Unplug other USB devices
- Try a different USB port
- Update board package to latest version

## Serial Monitor Output

Expected output after successful boot:

```
====================================
Portenta H7 USB HID Keyboard via MQTT
====================================

✓ USB HID Keyboard initialized
Connecting to WiFi: YourNetwork
.....
✓ WiFi connected!
IP address: 192.168.1.100
Signal strength (RSSI): -45 dBm
Connecting to MQTT broker: broker.hivemq.com
✓ MQTT connected!
✓ Subscribed to: hid-device/command

✓ Setup complete!
Waiting for commands...

→ Status sent: {"device_id":"portenta-default","device_type":"portenta-h7",...}
```

## Running Your Own MQTT Broker

For production use, run a local MQTT broker:

```bash
# Using Docker
docker run -d -p 1883:1883 eclipse-mosquitto

# Then update config.h
#define MQTT_BROKER "192.168.1.100"  // Your broker IP
```

## Advanced Configuration

### Changing Device ID

Each device should have a unique ID:

```cpp
#define DEVICE_ID "portenta-office-1"
```

This allows controlling multiple devices independently.

### Security

For production deployments:

1. **Use TLS/SSL for MQTT**
   - Configure broker with SSL certificates
   - Use `WiFiSSLClient` instead of `WiFiClient`

2. **Use authentication**
   - Add username/password to MQTT connection
   - Store credentials securely

3. **Network isolation**
   - Put HID devices on separate VLAN
   - Use firewall rules

## Performance

The Portenta H7 is significantly more powerful than needed for this application:

- **Processor**: Dual-core ARM Cortex-M7 @ 480MHz + M4 @ 240MHz
- **RAM**: 8 MB SDRAM + 1 MB SRAM
- **Flash**: 16 MB (external) + 2 MB (internal)

This means it can easily handle:
- Multiple simultaneous connections
- Complex command parsing
- Future features (UID transmission, encryption, etc.)
- Running additional tasks concurrently

## Power Consumption

The Portenta H7 is not the most power-efficient option:

- **Active mode**: ~300-500 mA @ 5V
- **With WiFi active**: Can peak higher

For battery-powered deployments, consider:
- ESP32-S3 (much lower power)
- Implementing sleep modes
- Using the M4 core for low-power tasks

## Next Steps

- Test with your target computer
- Configure your own MQTT broker
- Customize device ID
- Consider adding LED status indicators
- Plan for UID transmission feature (future branch)

## Comparison: Portenta H7 vs ESP32

| Feature | Portenta H7 | ESP32-S3 |
|---------|-------------|----------|
| **Price** | ~$100 | ~$8 |
| **Processor** | Dual ARM M7+M4 | Single Xtensa |
| **WiFi** | Built-in | Built-in |
| **USB HID** | Native | Native |
| **Power** | Higher | Lower |
| **Best for** | Professional, future expansion | Cost-sensitive, simple |

The Portenta H7 is overkill for this application but offers:
- Better build quality
- More headroom for features
- Professional-grade reliability
- Arduino ecosystem support
