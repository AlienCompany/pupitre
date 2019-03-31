#define _ESPLOGLEVEL_ 4

#include <Arduino.h>
#include "Util.h"
#include "Led.h"
#include "Sensor.h"
#include "Lcd.h"


//char* SERVER = "letterbox.notraly.fr";
//IPAddress SERVER(192,168,1,20);
//CommunicationService *communicationService ;
Lcd *lcd;
long time;
long oldTime = 0;

char ssid[] = "Livebox-32CC";               // your network SSID (name)
char pass[] = "547AEF16514955276FA6642371"; // your network password
int status = WL_IDLE_STATUS;                // the Wifi radio's status



void setup() {

}

void loop() {


}
