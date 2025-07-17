int hallPin = D2;
int N_samples = 100;

void setup() {
  Serial.begin(9600);
}

void loop() {
  long result = readHall();
  Serial.println(result);
}

long readHall() {
  long sum = 0;
  for (int i = 0; i < N_samples; i++) {
    sum += analogRead(hallPin);
  }
  return sum / N_samples;\
}