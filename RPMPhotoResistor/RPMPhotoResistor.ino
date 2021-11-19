const int photoPin = 27;
const int maxSamples = 5;
const int bounceThreshold = 10000; // us
const int lightThreshold = 30;

enum {
  IDLE, PASSING, DEBOUNCING, COUNTING, DEBUGGING
} state = IDLE;

int last_v, curr_v, idx = 0;
unsigned long curr_t, last_t, delta_t, period, rpm, sample[maxSamples];

void setup() {
  Serial.begin(115200);
  pinMode(photoPin, INPUT);
}

void loop() {
  curr_t = micros();
  curr_v = analogRead(photoPin);
  switch (state) {
    case DEBUGGING:
      Serial.printf("%d\n", curr_v); return;
    case IDLE:
      if (curr_v >= lightThreshold) state = PASSING; return;
    case PASSING:
      if (curr_v < lightThreshold) state = DEBOUNCING; return;
    case DEBOUNCING:
      delta_t = curr_t - last_t;
      if (delta_t < bounceThreshold) { state = IDLE; return; }
      state = COUNTING;
    case COUNTING:
      last_t = curr_t;
      sample[idx++] = delta_t;

      if (idx < maxSamples) { state = IDLE; return; }

      for (idx = 0; idx < maxSamples; ++idx) period += sample[idx];
      period /= maxSamples;
      idx = 0;
      break;
  }
  rpm = 6e7/period;
  Serial.printf("rpm:%d,", rpm);
  Serial.printf("\n");
}
