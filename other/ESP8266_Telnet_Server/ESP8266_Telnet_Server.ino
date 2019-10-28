/*
  WiFiTelnetToSerial - Example Transparent UART to Telnet Server for esp8266

  Copyright (c) 2015 Hristo Gochkov. All rights reserved.
  This file is part of the ESP8266WiFi library for Arduino environment.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <ESP8266WiFi.h>

// HIER SSID UND PASSWORT EINSETZEN
const char* ssid     = "....";
const char* password = "....";

// TCP-Server auf Port 23 starten
WiFiServer telnetServer(23);
WiFiClient serverClient;

// Die Funktion setup() wird genau einmal beim Starten des Programms
// ausgeführt.
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(BUILTIN_LED, LOW);

  // Öffne serielle Schnittstelle
  Serial.begin(115200);
  // Starte Access Point
  WiFi.disconnect();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  // Ausgabe auf serieller Schnittstelle
  Serial.print("\nAccess Point bereit: "); Serial.println(ssid);
  
  //Starte UART und den TELNET-Server
  telnetServer.begin();
  telnetServer.setNoDelay(true);

  // Ausgabe auf Schnittstelle
  Serial.print("Fertig! Mit 'telnet ");
  if (WiFi.getMode() == WIFI_AP)
    Serial.print(WiFi.softAPIP());
  else
    Serial.print(WiFi.localIP());

  Serial.println(" 23' verbinden!\n\n\n");
  pinMode(BUILTIN_LED, HIGH);
}

String line = "";

// Nach dem Setup wird immer wieder die Funktion loop() ausgeführt
// (in einer Endlos-Schleife)
void loop() {
  //Überprüfe, ob sich ein Benutzer verbinden will
  if (telnetServer.hasClient()) {
    // Ist niemand da?
    if (!serverClient || !serverClient.connected()) {
      if (serverClient) {
        serverClient.stop();
        Serial.println("Verbindung getrennt.");
      }
      serverClient = telnetServer.available();
      Serial.print("Neue Verbindung mit " );
      Serial.print(serverClient.remoteIP());
      Serial.print(":");
      Serial.println(serverClient.remotePort());
      serverClient.flush();  // clear input buffer, else you get strange characters
    }
    else
    {
      // Schon jemand da - Verbindung ablehnen!
      WiFiClient discardClient = telnetServer.available();
      discardClient.write("Sorry, leider schon voll!!\n");
      discardClient.flush();
      Serial.print("Verbindung mit " );
      Serial.print(discardClient.remoteIP());
      Serial.print(":");
      Serial.print(discardClient.remotePort());
      Serial.println(" abgelehnt.");
      discardClient.stop();
    }
  }

  // Sind neue Daten angekommen?
  if (serverClient.available())
  {
    // Wenn ja: alle Daten über TELNET annehmen...
    line = serverClient.readStringUntil('\r');
    serverClient.readStringUntil('\n');
    // ...und weiter verarbeiten

    serverClient.print("Empfangen: ");
    serverClient.println(line);
    serverClient.flush();

  }

  // Klitzekleine Pause, um seltsame Probleme mit dem Buffer
  // zu vermeiden
  delay(10);
}
