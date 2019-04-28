#include <Arduino.h>
#include <Timer.h>

void f1(){
    Serial.print((uint32_t )millis());
    Serial.println(": f1");
}

void f2(){
    Serial.print((uint32_t )millis());
    Serial.println(": f2");

}
void f3(){
    Serial.print((uint32_t )millis());
    Serial.println(": f3");

}

void setup() {
    Serial.begin(9600);
    Serial.print(millis());
    Serial.println(": Start");

    Timer::setInterval(2000, f2);
    Timer::setTimeOut(1000, f1);
    Timer::setInterval(2500, f3);

}

void loop() {

    Timer::check();

}