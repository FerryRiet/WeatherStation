#include "Arduino.h"

#include <WiFi.h>
#include <HTTPClient.h>

#include "WiFiManager.h"

#include <GxEPD2_3C.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

// ESP32-C6 CS(SS)=16,SCL(SCK)=4,SDA(MOSI)=6,BUSY=21,RES(RST)=22,DC=23
#define CS_PIN (16)
#define BUSY_PIN (21)
#define RES_PIN (22)
#define DC_PIN (23)

GxEPD2_3C<GxEPD2_290_C90c,GxEPD2_290_C90c::HEIGHT> display(GxEPD2_290_C90c(/*CS=5*/ CS_PIN, /*DC=*/DC_PIN, /*RES=*/RES_PIN, /*BUSY=*/BUSY_PIN)); // GDEY0213Z98 122x250, SSD1680

//GxEPD2_3C<GxEPD2_213_Z98c, GxEPD2_213_Z98c::HEIGHT> display(GxEPD2_213_Z98c(/*CS=5*/ CS_PIN, /*DC=*/DC_PIN, /*RES=*/RES_PIN, /*BUSY=*/BUSY_PIN)); // GDEY0213Z98 122x250, SSD1680
//GxEPD2_3C<GxEPD2_420c_Z21,GxEPD2_420c_Z21::HEIGHT> display(GxEPD2_420c_Z21(/*CS=5*/ CS_PIN, /*DC=*/DC_PIN, /*RES=*/RES_PIN, /*BUSY=*/BUSY_PIN)); 

bool setupWiFi(){
   bool res;
    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;
 
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    res = wm.autoConnect("weather","rainyday"); // password protected ap

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    // wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

    if(!res) {
        Serial.println("Failed to connect");
        ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
    }
    return res ;
}

void setupDisplay() {
    pinMode(16, OUTPUT) ; // There are some errors on the gxdpd lib.
	pinMode(22, OUTPUT) ;
	pinMode(23, OUTPUT) ;

	display.init(115200, true, 20, false);
    display.fillScreen(GxEPD_WHITE);
    display.display();
}
void setup() {
    Serial.begin(115200);
    
    setupWiFi() ;
    setupDisplay() ;

    if ( WiFi.isConnected() )
        Serial.println("Wifi connected...yeey :)");

 
}

void loop() {


}