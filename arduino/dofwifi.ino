#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

#include <Servo.h>

Servo leftAnkle;
Servo rightAnkle;
Servo leftHip;
Servo rightHip;
Servo leftAknee;
Servo leftBknee;
Servo rightAknee;
Servo rightBknee;

const uint8_t leftAnkleServo = D8;
const uint8_t leftAkneeServo = D9;
const uint8_t leftBkneeServo = D10;
const uint8_t leftHipServo = D11;

const uint8_t rightAnkleServo = D4;
const uint8_t rightAkneeServo = D5;
const uint8_t rightBkneeServo = D6;
const uint8_t rightHipServo = D7;


int leftAnklePos = 47;
int leftAkneePos = 93;
int leftBkneePos = 93;
int leftHipPos = 93;


int rightAnklePos = 130;
int rightAkneePos = 90;
int rightBkneePos = 90;
int rightHipPos = 90;

const char* ssid = "";
const char* password = "";

const char *mqtt_broker = "172.16.0.101";
const int mqtt_port = 1883;

DynamicJsonDocument doc(1024);

WiFiClient espClient;
PubSubClient client(espClient);

void wifiConnect() {
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting to "); Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}


void writePosition()                                  
{
  Serial.println("writePosition");
  Serial.println(leftAnklePos);
  Serial.print(", ");
  Serial.print(rightAnklePos);

  leftAnkle.write(leftAnklePos);
  leftAknee.write(leftAkneePos);
  leftBknee.write(leftBkneePos);
  leftHip.write(leftHipPos);

  rightHip.write(rightHipPos);
  rightAknee.write(rightAkneePos);
  rightBknee.write(rightBkneePos);
  rightAnkle.write(rightAnklePos);

  delay(1000);
}

void callback(String topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  Serial.println();

  if (topic == "dofIn") {
    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }

    leftAnklePos = doc["ankleLeftValue"];
    leftHipPos = doc["hipLeftValue"];
    leftAkneePos = doc["kneeLeftAValue"];
    leftBkneePos = doc["kneeLeftBValue"];

    rightAnklePos = doc["ankleRightValue"];
    rightHipPos = doc["hipRightValue"];
    rightAkneePos = doc["kneeRightAValue"];
    rightBkneePos = doc["kneeRightBValue"];

    writePosition();
  }

}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");

      client.subscribe("dofIn");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println(" ");
  Serial.println("Init...");

  wifiConnect();

  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);


  leftAnkle.attach(leftAnkleServo);
  leftAknee.attach(leftAkneeServo);
  leftBknee.attach(leftBkneeServo);
  leftHip.attach(leftHipServo);

  rightAnkle.attach(rightAnkleServo);
  rightAknee.attach(rightAkneeServo);
  rightBknee.attach(rightBkneeServo);
  rightHip.attach(rightHipServo);

  writePosition();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();
}
