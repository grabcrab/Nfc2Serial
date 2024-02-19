#include <Arduino.h>

#include "leds.h"
#include "nfc.h"

#define BOOT_DELAY_MS           3000  
#define PRINT_INTERVAL_MS       750
#define STATUS_LED_DELAY_MS     100
#define LOOP_DELAY_MS           1

unsigned long lastPrinted = 0;

void setup(void)
{
    Serial.begin(115200);  
    initLeds();
    ledAmber(LED_ON);
    ledGreen(LED_ON);
    Serial.println("*** NFC 2 SERIAL Reader ***");
    delay(BOOT_DELAY_MS);
    ledAmber(LED_OFF);
    ledGreen(LED_OFF);
}

void loopPrint(bool nfcConnected)
{
    if (millis() - lastPrinted < PRINT_INTERVAL_MS) return;
    String s = "[CONNECTED]";
    if (nfcConnected)
    {
        ledGreen(LED_ON);
    }
    else 
    {
        s = "[NOT CONNECTED]";
        ledGreen(LED_ON);
        delay(STATUS_LED_DELAY_MS );
        ledGreen(LED_OFF);
    }
    
    Serial.printf("<<<NFC_2_SERIAL_READER %s>>>\r\n", s.c_str());
    lastPrinted = millis();
}

void loop(void)
{
    bool nfcConnected = nfcProcess();
    loopPrint(nfcConnected);   
    delay(LOOP_DELAY_MS);
}



