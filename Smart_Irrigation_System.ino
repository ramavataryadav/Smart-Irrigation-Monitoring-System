#include <DHT.h>
#include <ESP8266WiFi.h>

String apiKey = "T1RBOG3QPCPOAYH0";     //  Enter your Write API key here
const char* server = "api.thingspeak.com";
const char *ssid =  "Redmi Note 8 Pro";     // Enter your WiFi Name
const char *pass =  "12345678"; // Enter your WiFi Password

#define DHTPIN 0 //d3         // GPIO Pin where the dht11 is connected

DHT dht(DHTPIN, DHT11);

WiFiClient client;


const int moisturePin = A0;             // moisteure sensor pin

const int motorPin = 5;//d1

unsigned long interval = 10000;

unsigned long previousMillis = 0;

unsigned long interval1 = 1000;

unsigned long previousMillis1 = 0;

float moisturePercentage;              //moisture reading

float h;                  // humidity reading

float t;                  //temperature reading


void setup()

{

  Serial.begin(115200);

  delay(10);

  pinMode(motorPin, OUTPUT);

  digitalWrite(motorPin, LOW); // keep motor off initally

  dht.begin();

  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)

  {

    delay(500);

    Serial.print(".");              // print ... till not connected

  }

  Serial.println("");

  Serial.println("WiFi connected");

}


void loop()

{

  unsigned long currentMillis = millis(); // grab current time


  h = dht.readHumidity();     // read humiduty

  t = dht.readTemperature();     // read temperature


  if (isnan(h) || isnan(t))

  {

    Serial.println("Failed to read from DHT sensor!");

    return;

  }


  moisturePercentage = ( 100.00 - ( (analogRead(moisturePin) / 1023.00) * 100.00 ) );


  if ((unsigned long)(currentMillis - previousMillis1) >= interval1) {

    Serial.print("Soil Moisture is  = ");

    Serial.print(moisturePercentage);

    Serial.println("%");

    previousMillis1 = millis();

  }


if (moisturePercentage < 34) {

  digitalWrite(motorPin, HIGH);        // tun on motor
  sendEmailIFTTT(moisturePercentage,t,h);

}


if (moisturePercentage > 35) {

  digitalWrite(motorPin, LOW);          // turn off mottor
  sendEmailIFTTT(moisturePercentage,t,h);
  
}



if ((unsigned long)(currentMillis - previousMillis) >= interval) {


  sendThingspeak();           //send data to thing speak

  previousMillis = millis();

  client.stop();

}


}


void sendThingspeak() {

  if (client.connect(server, 80))

  {

    String postStr = apiKey;              // add api key in the postStr string

    postStr += "&field1=";

    postStr += String(moisturePercentage);    // add mositure readin

    postStr += "&field2=";

    postStr += String(t);                 // add tempr readin

    postStr += "&field3=";

    postStr += String(h);                  // add humidity readin

    postStr += "\r\n\r\n";


    client.print("POST /update HTTP/1.1\n");

    client.print("Host: api.thingspeak.com\n");

    client.print("Connection: close\n");

    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");

    client.print("Content-Type: application/x-www-form-urlencoded\n");

    client.print("Content-Length: ");

    client.print(postStr.length());           //send lenght of the string

    client.print("\n\n");

    client.print(postStr);                      // send complete string

    Serial.print("Moisture Percentage: ");

    Serial.print(moisturePercentage);

    Serial.print("%. Temperature: ");

    Serial.print(t);

    Serial.print(" C, Humidity: ");

    Serial.print(h);

    Serial.println("%. Sent to Thingspeak.");

  }
  
  void sendEmailIFTTT(float moisture, float temperature, float humidity) 
  {
	  WiFiClient client1;
	  const char* host1 = "maker.ifttt.com";
	  const char* eventName1 = "Moisture_sensor_data"; // your IFTTT event name
	  const char* key1 = "IF45TY34DFWE5";          // replace with your IFTTT key

	  String url = String("/trigger/") + eventName1 + "/with/key/" + key1 +
				   "?value1=" + moisture +
				   "&value2=" + temperature +
				   "&value3=" + humidity;

	  Serial.println("Sending email via IFTTT...");

	  if (client1.connect(host1, 80)) {
		client1.print(String("GET ") + url + " HTTP/1.1\r\n" +
					 "Host: " + host1 + "\r\n" +
					 "Connection: close\r\n\r\n");
		Serial.println("Email sent!");
	  } else {
		Serial.println("Failed to connect to IFTTT.");
	  }
}

}
