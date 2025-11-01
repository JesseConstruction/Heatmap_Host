# Arduino Portenta H7 / ESP32 / Flipper Zero CLI Input Device

Send keyboard input from a CLI interface over the internet to an offline computer using low-power devices.

## Architecture

### Option 1: Arduino Portenta H7 (Recommended - Tested)
```
[CLI] → [MQTT Broker] → [Portenta H7 + WiFi] → [USB HID] → [Offline Computer]
```

### Option 2: ESP32 USB HID (Untested Draft)
```
[CLI] → [MQTT Broker] → [ESP32 + WiFi] → [USB HID] → [Offline Computer]
```

### Option 3: Flipper Zero + WiFi Dev Board (Manual Mode Only)
```
[CLI] → [MQTT Broker] → [Flipper WiFi Board] → [Flipper Zero] → [USB HID] → [Offline Computer]
```

## Features

- Send keyboard input via CLI to remote computer
- MQTT-based communication (low latency, reliable)
- Supports special keys (Enter, Tab, Ctrl, etc.)
- Queue multiple commands
- Device status monitoring

## Quick Start

### 1. Install CLI
```bash
cd cli
npm install
```

### 2. Configure
```bash
cp .env.example .env
# Edit .env with your MQTT broker details
```

### 3. Flash Firmware
- **Portenta H7**: Use Arduino IDE (see `firmware/portenta/README.md`)
- **ESP32**: Use Arduino IDE (see `firmware/esp32/README.md`) - UNTESTED DRAFT
- **Flipper Zero**: Copy script to Flipper (see `firmware/flipper/README.md`) - Manual only

### 4. Run CLI
```bash
npm start -- type "Hello from the internet!"
```

## Hardware Requirements

### Option 1: Arduino Portenta H7 (Recommended - Tested)
- Arduino Portenta H7 (~$100)
- USB-C cable
- WiFi network (built-in)

### Option 2: ESP32 (Untested Draft)
- ESP32-S2/S3 Dev Board with USB (~$8)
- USB cable
- WiFi network

### Option 3: Flipper Zero (Manual Mode Only)
- Flipper Zero (~$169)
- WiFi Dev Board for Flipper (~$30)
- USB-C cable

## Project Structure

```
flipper-cli-hid/
├── cli/                    # Node.js CLI interface
├── firmware/
│   ├── portenta/          # Arduino Portenta H7 firmware (tested)
│   ├── esp32/             # ESP32 Arduino firmware (untested draft)
│   └── flipper/           # Flipper Zero Bad USB scripts (manual)
└── docs/                  # Documentation
```

## Getting Started - First Time Setup

### For Portenta H7 Users (Recommended)

1. **Install Arduino IDE**
   - Download from https://www.arduino.cc/en/software
   - Install Portenta board support (see `firmware/portenta/README.md`)

2. **Configure Your Device**
   - Open `firmware/portenta/portenta_h7_hid_keyboard/portenta_h7_hid_keyboard.ino`
   - Edit `config.h` with your WiFi credentials:
     ```cpp
     #define WIFI_SSID "YourWiFiName"
     #define WIFI_PASSWORD "YourPassword"
     #define DEVICE_ID "portenta-default"
     ```

3. **Upload Firmware**
   - Connect Portenta H7 via USB
   - Select Board: Arduino Portenta H7 (M7 core)
   - Click Upload

4. **Install CLI**
   ```bash
   cd cli
   npm install
   cp .env.example .env
   ```

5. **Test It**
   - Connect Portenta to target computer via USB-C
   - From CLI computer:
     ```bash
     npm start -- type "Hello from the internet!"
     npm start -- status
     ```

**Full Guide:** See [docs/QUICKSTART.md](docs/QUICKSTART.md) for detailed instructions.

## Next Steps After Setup

1. **Test on Your Portenta H7**
   - Verify WiFi connection in Serial Monitor (115200 baud)
   - Check MQTT connection status
   - Test basic commands (type, key, combo)

2. **Production Configuration**
   - Set up your own MQTT broker (see docs)
   - Configure SSL/TLS for security
   - Change default device IDs
   - Implement authentication

3. **Future Development**
   - **UID Code Transmission**: Create new branch for RFID/NFC features
   - **Multi-Device Support**: Control multiple Portenta devices
   - **Custom Scripts**: Automate command sequences
   - **LED Status Indicators**: Add visual feedback

## Documentation

- **[Quick Start Guide](docs/QUICKSTART.md)** - Get running in 10 minutes
- **[CLI Reference](docs/CLI_REFERENCE.md)** - Complete command documentation
- **[Portenta H7 Setup](firmware/portenta/README.md)** - Hardware-specific guide
- **[ESP32 Draft](firmware/esp32/README.md)** - Untested alternative firmware
- **[Flipper Zero](firmware/flipper/README.md)** - Manual Bad USB scripts

## Future Features

- UID code transmission (separate feature branch)
- WebSocket alternative to MQTT
- Encrypted communication
- Multi-device support
- RTOS threading optimization
- Battery power management
