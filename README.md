# Smart-Irrigation-Monitoring-System
# Smart Irrigation System using ESP8266, DHT11, and Soil Moisture Sensor

This project is a simple smart irrigation system that monitors soil moisture, temperature, and humidity using an ESP8266 NodeMCU, a DHT11 sensor, and a soil moisture sensor. The system controls a water pump automatically and sends data to **ThingSpeak**. It also sends email alerts via **IFTTT** when moisture crosses critical thresholds.

## 📦 Components Used

- ESP8266 NodeMCU
- DHT11 Temperature & Humidity Sensor
- Soil Moisture Sensor
- Relay Module (to control motor/pump)
- Water Pump or Motor
- Jumper Wires
- Power Source

## 🛠️ Features

- ✅ Reads soil moisture, temperature, and humidity
- ✅ Controls a motor automatically based on soil moisture level
- ✅ Sends sensor data to [ThingSpeak](https://thingspeak.com/)
- ✅ Sends email alerts using [IFTTT](https://ifttt.com/)
- ✅ Non-blocking loop using `millis()` (no `delay()`)

## 🔌 Wiring

| Component        | ESP8266 Pin |
|------------------|-------------|
| Soil Moisture    | A0          |
| DHT11            | D3 (GPIO 0) |
| Relay (Motor)    | D1 (GPIO 5) |

> 📌 Note: Use a transistor and diode circuit or relay to safely drive the motor from ESP8266.

## 🌐 Configuration

### WiFi

Update the following lines with your Wi-Fi credentials:
```cpp
const char *ssid =  "Your_SSID";
const char *pass =  "Your_PASSWORD";

**ThingSpeak**

Replace with your ThingSpeak Write API Key:
String apiKey = "YOUR_THINGSPEAK_WRITE_API_KEY";

IFTTT
Set your IFTTT Webhook Event Name and Key:
const char* eventName1 = "Moisture_sensor_data";
const char* key1 = "YOUR_IFTTT_WEBHOOK_KEY";

## Irrigation Logic
If moisture < 34%: Turns motor ON and sends alert via IFTTT.

If moisture > 35%: Turns motor OFF and sends alert via IFTTT.

## Data Monitoring
You can visualize sensor readings in real-time via:

ThingSpeak Dashboard for graphs

Email notifications from IFTTT

## Future Improvements
Add hysteresis control to prevent frequent motor toggling

Use MQTT or Blynk for real-time remote control

Add OLED display for local readout

 ## 📄 License
This project is open-source and available under the MIT License.
