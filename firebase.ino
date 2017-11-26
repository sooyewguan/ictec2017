#include <WiFiClientSecure.h>

const char *host = "iot-playground-f45eb.firebaseio.com";
const char *url = "/weather.json";
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char *fingerprint = "B8 4F 40 70 0C 63 90 E0 07 E8 7D BD B4 11 D0 4A EA 9C 90 F6";

void updateTemperature(char* value)
{
    if(WiFi.status() != WL_CONNECTED)
        return;
    // Use WiFiClientSecure class to create TLS connection
    WiFiClientSecure client;
    Serial.print("connecting to ");
    Serial.println(host);
    if (!client.connect(host, httpsPort))
    {
        Serial.println("connection failed");
        return;
    }

    if (client.verify(fingerprint, host))
    {
        Serial.println("certificate matches");
    }
    else
    {
        Serial.println("certificate doesn't match");
    }

    String data = "{\"temperature\":" + String(value) + "}";

    client.println("PATCH " + (String)url + " HTTP/1.1");
    client.println("Host: " + (String)host);
    client.println("User-Agent: ESP8266/1.0");
    client.println("Content-Type: application/json;");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);
    client.println("Connection: close");
    client.println();
}