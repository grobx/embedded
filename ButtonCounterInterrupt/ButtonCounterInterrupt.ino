#include <esp_task_wdt.h>

const int dMin = 10;      // ms
const int buttonPin = 2;
const int wdtTimeout = 3;
int ms0, msk, total = 0;

void count() {
    ms0 = millis();
    while (digitalRead(buttonPin) == LOW) esp_task_wdt_reset();
    msk = millis();
    if (msk - ms0 >= dMin) total++;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Configuring WDT...");
  esp_task_wdt_init(wdtTimeout, true); //enable panic so ESP32 restarts
  esp_task_wdt_add(NULL); //add current thread to WDT watch
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), count, FALLING);
}

void loop() {
  esp_task_wdt_reset();
  delay(1000);
  Serial.printf("Counter: %d\n", total);
}
