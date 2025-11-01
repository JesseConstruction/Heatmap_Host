# CLI Reference

Complete reference for the `hid-cli` command-line interface.

## Installation

```bash
cd cli
npm install
```

## Configuration

Create `.env` file:

```bash
cp .env.example .env
```

Edit `.env`:

```env
MQTT_BROKER=mqtt://broker.hivemq.com
MQTT_TOPIC_CMD=hid-device/command
MQTT_TOPIC_STATUS=hid-device/status
DEVICE_ID=default
```

## Commands

### `type` - Type Text

Type a string on the remote computer.

**Syntax:**
```bash
npm start -- type <text> [options]
```

**Options:**
- `-d, --delay <ms>` - Delay before typing (milliseconds)

**Examples:**
```bash
# Type simple text
npm start -- type "Hello World"

# Type with delay
npm start -- type "Delayed message" --delay 2000

# Type special characters
npm start -- type "user@example.com"
```

### `key` - Press Special Key

Press a single special key (Enter, Tab, etc.).

**Syntax:**
```bash
npm start -- key <keyname> [options]
```

**Options:**
- `-d, --delay <ms>` - Delay before key press

**Supported Keys:**
- `ENTER`, `RETURN`
- `TAB`
- `BACKSPACE`
- `DELETE`
- `ESC`, `ESCAPE`
- `SPACE`
- `UP`, `DOWN`, `LEFT`, `RIGHT`
- `HOME`, `END`
- `PAGEUP`, `PAGEDOWN`
- Single characters: `A`, `B`, `1`, `2`, etc.

**Examples:**
```bash
# Press Enter
npm start -- key ENTER

# Press Tab
npm start -- key TAB

# Press Escape after 1 second
npm start -- key ESC --delay 1000
```

### `combo` - Key Combination

Press a combination of keys simultaneously.

**Syntax:**
```bash
npm start -- combo "<keys>" [options]
```

**Options:**
- `-d, --delay <ms>` - Delay before combo

**Modifier Keys:**
- `CTRL`
- `ALT`
- `SHIFT`
- `GUI`, `WIN` (Windows key)

**Format:** Separate keys with `+`

**Examples:**
```bash
# Ctrl+Alt+Delete
npm start -- combo "CTRL+ALT+DELETE"

# Alt+Tab
npm start -- combo "ALT+TAB"

# Windows+R (Run dialog)
npm start -- combo "GUI+R"

# Ctrl+Shift+Escape (Task Manager)
npm start -- combo "CTRL+SHIFT+ESC"
```

### `status` - Check Device Status

Query the status of connected devices.

**Syntax:**
```bash
npm start -- status
```

**Output:**
```json
{
  "device_id": "default",
  "status": "online",
  "wifi_connected": true,
  "mqtt_connected": true,
  "wifi_rssi": -45,
  "uptime": 3600
}
```

**Example:**
```bash
npm start -- status
# Listening for device status...
# Device Status: { device_id: 'default', status: 'online', ... }
```

### `script` - Execute Script File

*(Not yet implemented)*

Execute a series of commands from a file.

**Planned syntax:**
```bash
npm start -- script <file>
```

## Advanced Usage

### Multiple Devices

To target specific devices, set different `DEVICE_ID` values:

**Device config.h:**
```cpp
#define DEVICE_ID "office-pc"
```

**CLI .env:**
```env
DEVICE_ID=office-pc
```

### Custom MQTT Broker

**Run your own broker:**
```bash
docker run -d -p 1883:1883 eclipse-mosquitto
```

**Update .env:**
```env
MQTT_BROKER=mqtt://192.168.1.100:1883
```

### Custom Topics

Change MQTT topics for isolation:

```env
MQTT_TOPIC_CMD=myproject/commands
MQTT_TOPIC_STATUS=myproject/status
```

Update firmware `config.h` to match.

## Programmatic Usage

You can also use the CLI programmatically in Node.js:

```javascript
const mqtt = require('mqtt');

const client = mqtt.connect('mqtt://broker.hivemq.com');

client.on('connect', () => {
  const command = {
    device_id: 'default',
    type: 'type',
    payload: 'Hello from code!',
    delay: 0,
    timestamp: Date.now()
  };

  client.publish('hid-device/command', JSON.stringify(command));
});
```

## Message Format

### Command Message

**Topic:** `hid-device/command`

**Payload (JSON):**
```json
{
  "device_id": "default",
  "type": "type|key|combo",
  "payload": "command-specific-data",
  "delay": 0,
  "timestamp": 1234567890
}
```

### Status Message

**Topic:** `hid-device/status`

**Payload (JSON):**
```json
{
  "device_id": "default",
  "status": "online|offline",
  "wifi_connected": true,
  "mqtt_connected": true,
  "wifi_rssi": -45,
  "uptime": 3600
}
```

## Error Handling

The CLI will exit with status codes:

- `0` - Success
- `1` - Error (connection failed, invalid command, etc.)

**Example:**
```bash
npm start -- type "Hello" || echo "Command failed!"
```

## Tips

### Shell Escaping

When using special characters, quote your strings:

```bash
# Good
npm start -- type "It's working!"

# Bad (shell interprets the apostrophe)
npm start -- type It's working!
```

### Delays

Use delays when the target system needs time to process:

```bash
# Open Run dialog, wait, then type command
npm start -- combo "GUI+R" --delay 0
sleep 1
npm start -- type "notepad" --delay 0
sleep 0.5
npm start -- key ENTER
```

### Testing

Test commands locally first:

```bash
# Connect ESP32 to your own computer
# Run commands and verify they work
# Then deploy to target computer
```
