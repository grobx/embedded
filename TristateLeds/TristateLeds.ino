#include "Arduino.h"

const int tristatePin = 2;

const int LEDPin = 4;
const int PWMFreq = 5000; /* 5 KHz */
const int PWMChannel = 0;
const int PWMResolution = 10;
const int MAX_DUTY_CYCLE = (int)(pow(2, PWMResolution) - 1);
int dutyCycle = MAX_DUTY_CYCLE;

void setup() {
  Serial.begin(115200);
  ledcSetup(PWMChannel, PWMFreq, PWMResolution);
  ledcAttachPin(LEDPin, PWMChannel);
  ledcWrite(PWMChannel, dutyCycle);
}

// accende un led
// poi li spegne entrambi
// ne accende un altro
// e nuovamente li spegne entrambi
// a ripetizione
void loop() {
  pinMode(tristatePin, OUTPUT);
  digitalWrite(tristatePin, HIGH);
  delay(1000);

  pinMode(tristatePin, INPUT);
  delay(1000);

  pinMode(tristatePin, OUTPUT);
  digitalWrite(tristatePin, LOW);
  delay(1000);

  pinMode(tristatePin, INPUT);
  delay(1000);
}
