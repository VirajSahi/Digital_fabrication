#define TX_PIN 6   // GPIO 6
#define RX_PIN 7   // GPIO 7

void setup() {
  Serial.begin(115200);
  pinMode(TX_PIN, OUTPUT);
  pinMode(RX_PIN, INPUT);
}

long senseCapacitance() {
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(10);

  unsigned long start = micros();
  digitalWrite(TX_PIN, HIGH);

  while (digitalRead(RX_PIN) == LOW) {
    if ((micros() - start) > 3000) break;
  }

  unsigned long duration = micros() - start;
  digitalWrite(TX_PIN, LOW);  // reset

  return duration;
}

void loop() {
  long reading = senseCapacitance();
  Serial.println(reading);
  delay(200);
}