# Flipper Zero Bad USB Setup

This approach uses Flipper Zero's Bad USB functionality with the WiFi Dev Board for remote command execution.

## Hardware Requirements

- Flipper Zero
- WiFi Dev Board for Flipper Zero
- USB-C cable

## Architecture

```
MQTT Broker → WiFi Dev Board → Serial/GPIO → Flipper Zero → USB → Target Computer
```

## Current Status

⚠️ **This requires custom firmware on the WiFi Dev Board**

The WiFi Dev Board needs firmware to:
1. Connect to WiFi
2. Subscribe to MQTT topics
3. Send commands to Flipper via serial/GPIO
4. Trigger Bad USB scripts

## Alternative: Use ESP32 Instead

**Recommended:** Use the ESP32 firmware (see `../esp32/`) instead of Flipper Zero for this use case.

**Reasons:**
- Simpler setup
- Direct WiFi + USB HID in one device
- Cheaper (~$8 vs $169 + $30 for Flipper + WiFi board)
- No custom firmware needed

## Flipper Zero Bad USB Scripts (Manual Mode)

You can manually run Bad USB scripts on Flipper Zero without WiFi:

### 1. Create Script

On your computer, create `hello.txt`:

```
REM Hello World Bad USB Script
DELAY 1000
GUI r
DELAY 500
STRING notepad
ENTER
DELAY 1000
STRING Hello from Flipper Zero!
ENTER
```

### 2. Transfer to Flipper

1. Connect Flipper to computer via USB
2. Navigate to `SD Card/badusb/`
3. Copy `hello.txt` to this folder
4. Eject Flipper

### 3. Run Script

1. On Flipper: Apps → Bad USB
2. Select `hello.txt`
3. Connect Flipper to target computer
4. Press OK to execute

## Bad USB Script Commands

| Command | Description | Example |
|---------|-------------|---------|
| `REM` | Comment | `REM This is a comment` |
| `DELAY` | Wait (ms) | `DELAY 1000` |
| `STRING` | Type text | `STRING Hello World` |
| `ENTER` | Press Enter | `ENTER` |
| `GUI` | Windows/Cmd key | `GUI r` (Win+R) |
| `CTRL` | Ctrl key | `CTRL ALT DELETE` |
| `ALT` | Alt key | `ALT F4` |
| `SHIFT` | Shift key | `SHIFT TAB` |

## Future Development: WiFi Dev Board Firmware

To enable remote Bad USB via MQTT, we need to develop:

1. **ESP32 Firmware for WiFi Board** (WiFi Dev Board uses ESP32-S2)
   - MQTT client
   - Serial communication with Flipper
   - Command translation

2. **Flipper Application**
   - Listen for serial commands from WiFi board
   - Execute Bad USB payloads dynamically
   - Report status

This is a more complex setup than the standalone ESP32 approach.

## Recommendation

For now, **use the ESP32 firmware** (`../esp32/`) which provides the same functionality with less complexity.

Consider Flipper Zero for:
- Manual Bad USB penetration testing
- RFID/NFC emulation (future feature branch)
- Sub-GHz communication
- Other Flipper-specific features

But for simple "CLI → Internet → USB HID keyboard", ESP32 is the better choice.
