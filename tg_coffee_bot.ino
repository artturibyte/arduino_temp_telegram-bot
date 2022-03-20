#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include <OneWire.h>
#include <DallasTemperature.h>

//-------------------Dallas sensor setup
// GPIO
const int oneWireBus = 4;     
OneWire oneWire(oneWireBus); 
DallasTemperature sensors(&oneWire);
//--------------------------------------

// Replace with your network credentials
const char* ssid = "#####";
const char* password = '#####';

// Initialize Telegram BOT
#define BOTtoken "#####"  // your Bot Token (Get from Botfather)
const long utcOffsetInSeconds = 7200;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "#####"


  X509List cert(TELEGRAM_CERTIFICATE_ROOT);

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);


void setup() {
  Serial.begin(9600);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("connecting ...");
    delay(1000);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Bot started up", "");
  sensors.begin();
  timeClient.begin();
}

void loop() {
timeClient.update();
int aika = timeClient.getHours();
if (aika==6) {
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  String postData = "Hyvää huomenta, lämpötila ulkona on: " + String(temperatureC)+ " astetta, kello on:" + String(aika);
  bot.sendMessage(CHAT_ID, postData, "");
}
delay(3600000);
}
