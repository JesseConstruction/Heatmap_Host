#!/usr/bin/env node

require('dotenv').config();
const { program } = require('commander');
const mqtt = require('mqtt');
const chalk = require('chalk');

// Configuration from environment
const MQTT_BROKER = process.env.MQTT_BROKER || 'mqtt://broker.hivemq.com';
const MQTT_TOPIC_CMD = process.env.MQTT_TOPIC_CMD || 'hid-device/command';
const MQTT_TOPIC_STATUS = process.env.MQTT_TOPIC_STATUS || 'hid-device/status';
const DEVICE_ID = process.env.DEVICE_ID || 'default';

let client = null;

// Connect to MQTT broker
function connectMQTT() {
  return new Promise((resolve, reject) => {
    console.log(chalk.blue(`Connecting to MQTT broker: ${MQTT_BROKER}`));

    client = mqtt.connect(MQTT_BROKER, {
      clientId: `hid-cli-${Math.random().toString(16).slice(2, 8)}`,
      clean: true,
      connectTimeout: 4000,
      reconnectPeriod: 1000
    });

    client.on('connect', () => {
      console.log(chalk.green('✓ Connected to MQTT broker'));
      client.subscribe(MQTT_TOPIC_STATUS, (err) => {
        if (!err) {
          console.log(chalk.gray(`Subscribed to status topic: ${MQTT_TOPIC_STATUS}`));
        }
      });
      resolve(client);
    });

    client.on('error', (err) => {
      console.error(chalk.red('MQTT Error:'), err.message);
      reject(err);
    });

    client.on('message', (topic, message) => {
      if (topic === MQTT_TOPIC_STATUS) {
        try {
          const status = JSON.parse(message.toString());
          console.log(chalk.cyan('Device Status:'), status);
        } catch (e) {
          console.log(chalk.cyan('Device Status:'), message.toString());
        }
      }
    });
  });
}

// Send command via MQTT
function sendCommand(type, payload, delay = 0) {
  const command = {
    device_id: DEVICE_ID,
    type,
    payload,
    delay,
    timestamp: Date.now()
  };

  return new Promise((resolve, reject) => {
    const cmdStr = JSON.stringify(command);
    console.log(chalk.yellow('Sending command:'), cmdStr);

    client.publish(MQTT_TOPIC_CMD, cmdStr, { qos: 1 }, (err) => {
      if (err) {
        console.error(chalk.red('Failed to send command:'), err);
        reject(err);
      } else {
        console.log(chalk.green('✓ Command sent successfully'));
        resolve();
      }
    });
  });
}

// Program commands
program
  .name('hid-cli')
  .description('CLI for remote HID keyboard input via Flipper Zero or ESP32')
  .version('1.0.0');

program
  .command('type <text>')
  .description('Type text on remote computer')
  .option('-d, --delay <ms>', 'Delay before typing (ms)', '0')
  .action(async (text, options) => {
    try {
      await connectMQTT();
      await sendCommand('type', text, parseInt(options.delay));
      setTimeout(() => {
        client.end();
        process.exit(0);
      }, 1000);
    } catch (err) {
      console.error(chalk.red('Error:'), err.message);
      process.exit(1);
    }
  });

program
  .command('key <keyname>')
  .description('Send special key (ENTER, TAB, CTRL, etc.)')
  .option('-d, --delay <ms>', 'Delay before key press (ms)', '0')
  .action(async (keyname, options) => {
    try {
      await connectMQTT();
      await sendCommand('key', keyname.toUpperCase(), parseInt(options.delay));
      setTimeout(() => {
        client.end();
        process.exit(0);
      }, 1000);
    } catch (err) {
      console.error(chalk.red('Error:'), err.message);
      process.exit(1);
    }
  });

program
  .command('combo <keys>')
  .description('Send key combination (e.g., "CTRL+ALT+DELETE")')
  .option('-d, --delay <ms>', 'Delay before key combo (ms)', '0')
  .action(async (keys, options) => {
    try {
      await connectMQTT();
      await sendCommand('combo', keys.toUpperCase(), parseInt(options.delay));
      setTimeout(() => {
        client.end();
        process.exit(0);
      }, 1000);
    } catch (err) {
      console.error(chalk.red('Error:'), err.message);
      process.exit(1);
    }
  });

program
  .command('script <file>')
  .description('Execute a script file with multiple commands')
  .action(async (file) => {
    console.log(chalk.yellow('Script execution not yet implemented'));
    console.log(chalk.gray('Planned: Read commands from file and execute sequentially'));
    process.exit(1);
  });

program
  .command('status')
  .description('Check device status')
  .action(async () => {
    try {
      await connectMQTT();
      console.log(chalk.blue('Listening for device status...'));
      console.log(chalk.gray('Press Ctrl+C to exit'));

      // Keep connection alive
      setTimeout(() => {
        console.log(chalk.yellow('No status received after 10 seconds'));
        client.end();
        process.exit(0);
      }, 10000);
    } catch (err) {
      console.error(chalk.red('Error:'), err.message);
      process.exit(1);
    }
  });

// Handle graceful shutdown
process.on('SIGINT', () => {
  console.log(chalk.yellow('\nShutting down...'));
  if (client) {
    client.end();
  }
  process.exit(0);
});

program.parse();
