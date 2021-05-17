#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#define WIFI_SSID "Redmi Note 7"
#define WIFI_PASSWORD "test1234"

#define FIREBASE_AUTH "HXJV8k0JBzQJ2t97d96CSEM4Xh3HUVWGQb7jMvet"
#define FIREBASE_HOST "keretaapi-6ad27-default-rtdb.asia-southeast1.firebasedatabase.app" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
FirebaseData fbdo;
const int potensio = A0;
int nilaipot = 0;

void setup()
{
    Serial.begin(9600);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
}

void loop()
{
    nilaipot = analogRead(potensio);
    Firebase.setInt(fbdo, "/nilai", nilaipot);
    delay(500);
}
