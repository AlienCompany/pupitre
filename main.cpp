#include <Arduino.h>
#include <Timer.h>

void f1(){
    Serial.println("f1");
}

void f2(){
    Serial.println("f2");

}

void f3(uint8_t v1, uint8_t v2, uint8_t v3){
    Serial.print("f3:");
    Serial.print(v1);
    Serial.print(",");
    Serial.print(v2);
    Serial.print(",");
    Serial.println(v3);

}
void f4(int v1, int v2, int v3, int v4){

    Serial.print("f4:");
    Serial.print(v1);
    Serial.print(",");
    Serial.print(v2);
    Serial.print(",");
    Serial.print(v3);
    Serial.print(",");
    Serial.println(v4);
}

void setup() {
    Serial.begin(115200);

    Timer::setTimeOut(100, f4 , 45,56,78,98);

}

void loop() {

    Timer::check();

}