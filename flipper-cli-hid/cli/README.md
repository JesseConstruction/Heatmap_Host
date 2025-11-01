# HID CLI - Command Line Interface

Node.js CLI for sending keyboard commands to remote devices over MQTT.

## Installation

```bash
npm install
```

## Configuration

```bash
cp .env.example .env
```

Edit `.env` with your settings:
- `MQTT_BROKER` - MQTT broker URL
- `DEVICE_ID` - Target device identifier
- Topics for commands and status

## Usage

```bash
# Type text
npm start -- type "Hello World"

# Press special key
npm start -- key ENTER

# Key combination
npm start -- combo "CTRL+ALT+DELETE"

# Check device status
npm start -- status
```

## Full Documentation

See: [../docs/CLI_REFERENCE.md](../docs/CLI_REFERENCE.md)
