#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#define WIFI_SSID "Redmi Note 7"
#define WIFI_PASSWORD "test1234"

#define FIREBASE_AUTH "HXJV8k0JBzQJ2t97d96CSEM4Xh3HUVWGQb7jMvet"
#define FIREBASE_HOST "keretaapi-6ad27-default-rtdb.asia-southeast1.firebasedatabase.app" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
FirebaseData fbdo;

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

    lcd.begin();
    lcd.backlight();
}

void loop()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("nilai tekanan");
    if (Firebase.getInt(fbdo, "/nilai"))
    {
        if (fbdo.dataType() == "int")
        {
            Serial.println(fbdo.intData());
            lcd.setCursor(0, 1);
            lcd.print(fbdo.intData());
            lcd.print("      ");
        }
    }
    else
    {
        Serial.println(fbdo.errorReason());
        lcd.setCursor(0, 1);
        lcd.print(fbdo.errorReason());
        lcd.print("    ");
    }
    delay(500);
}
