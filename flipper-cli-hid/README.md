# Flipper Zero / ESP32 CLI Input Device

Send keyboard input from a CLI interface over the internet to an offline computer using low-power devices.

## Architecture

### Option 1: ESP32 USB HID (Recommended for simplicity)
```
[CLI] → [MQTT Broker] → [ESP32 + WiFi] → [USB HID] → [Offline Computer]
```

### Option 2: Flipper Zero + WiFi Dev Board
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
- **ESP32**: Use Arduino IDE or PlatformIO (see `firmware/esp32/README.md`)
- **Flipper Zero**: Copy script to Flipper (see `firmware/flipper/README.md`)

### 4. Run CLI
```bash
npm start -- type "Hello from the internet!"
```

## Hardware Requirements

### Option 1: ESP32 (Recommended)
- ESP32 Dev Board with USB (~$8)
- USB-A cable
- WiFi network

### Option 2: Flipper Zero
- Flipper Zero
- WiFi Dev Board for Flipper
- USB-C cable

## Project Structure

```
flipper-cli-hid/
├── cli/                    # Node.js CLI interface
├── firmware/
│   ├── esp32/             # ESP32 Arduino firmware
│   └── flipper/           # Flipper Zero Bad USB scripts
└── docs/                  # Documentation
```

## Future Features

- UID code transmission (separate feature branch)
- WebSocket alternative to MQTT
- Encrypted communication
- Multi-device support
