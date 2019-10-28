/*
    This sketch sends data via HTTP GET requests to data.sparkfun.com service.

    You need to get streamId and privateKey at data.sparkfun.com and paste them
    below. Or just customize this script to talk to other HTTP servers.

*/

#include <ESP8266WiFi.h>

// HIER SSID UND PASSWORT EINSETZEN
const char* ssid     = "......";
const char* password = "......";

const char* host = "192.168.4.1";
const int telnetPort = 23;

WiFiClient client;



void setup() {
  pinMode(D1, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);

  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(BUILTIN_LED, HIGH);
    delay(250);
    digitalWrite(BUILTIN_LED, LOW);
    delay(250);
    Serial.print(".");
  }
  digitalWrite(BUILTIN_LED, LOW);
  Serial.println("");
  Serial.println("Mit WLAN verbunden.");
  Serial.println("IP-Addresse: ");
  Serial.println(WiFi.localIP());

  Serial.print("Verbinde mit ");
  Serial.print(host);
  Serial.print(":");
  Serial.print(telnetPort);
  Serial.print("...");
  // Use WiFiClient class to create TCP connections
  if (!client.connect(host, telnetPort)) {
    Serial.println("Verbindung fehlgeschlagen");
    return;
  }
  else
  {
    Serial.println("verbunden!");
  }
}

int buttonState = digitalRead(D1);
int previousState = -1;

/* Tipps und Tricks:

      einen Eingang einlesen: digitalRead(D1)
      die interne LED setzen: digitalWrite(BUILTIN_LED, HIGH) // aus!!
                              digitalWrite(BUILTIN_LED, LOW)   // an!!
      eine Zeile über TELNET senden:
                              client.println("Hallo Welt!");
      überprüfen, ob eine TELNET-Verbindung besteht:
                              client.connected()
*/

void loop() {
  // Hier muss die Funktionalität hin :)


  // Alle Rückgaben von TELNET auf die serielle Konsole ausgeben
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
}
