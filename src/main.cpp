#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
bool sending;

void setup()
{
    //Serial.begin(115200);
    Serial1.begin(115200, SERIAL_8N1, 44, 43);
    Serial2.begin(115200, SERIAL_8N1, 18, 17);

    Wire.begin(8, 9);

    if (!bno.begin()) {
        Serial1.println("BNO055 not found");
        while (1);
    }

    delay(1000);
    bno.setExtCrystalUse(true);
}



float distance = 0.0;
char id = 'A';
float heading = 0.0;
void loop()
{
    if (Serial1.available()) {
        String cmd = Serial1.readStringUntil('\n');
        cmd.trim();

        if (cmd == "START") {
            sending = true;
        }
    }




    if(Serial2.available()) {
        String received = Serial2.readStringUntil('\n');
        received.trim();
        

        distance = received.toFloat();
    }

    if (sending == true) {
        sensors_event_t event;
        bno.getEvent(&event);

        float ownheading = event.orientation.x;

        Serial1.print(id);
        Serial1.print(",");
        Serial1.print(distance, 2);
        Serial1.print(",");
        Serial1.println(heading);

        Serial1.println(ownheading, 2);

        delay(100);
    }
}