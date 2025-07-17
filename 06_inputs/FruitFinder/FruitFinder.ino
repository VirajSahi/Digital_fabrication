long result;
int analog_pin = A3;
int tx_pin = 4;

String currentFruit = "";

void setup() {
  pinMode(tx_pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  result = tx_rx();
  
  String newFruit = detectFruit(result);

  if (newFruit != currentFruit) {
    currentFruit = newFruit;
    Serial.println("Fruit detected: " + currentFruit);
  }

  delay(250); // Avoid spamming
}

long tx_rx() {
  int read_high;
  int read_low;
  int diff;
  long int sum = 0;
  int N_samples = 100;

  for (int i = 0; i < N_samples; i++) {
    digitalWrite(tx_pin, HIGH);
    read_high = analogRead(analog_pin);
    delayMicroseconds(100);
    digitalWrite(tx_pin, LOW);
    read_low = analogRead(analog_pin);
    diff = read_high - read_low;
    sum += diff;
  }
  return sum;
}

// ⚠️ Replace these ranges with your real measured values
String detectFruit(long val) {
  if (val < 4280) return "Zucchini";
  else if (val < 4600) return "Kiwi";
  else if (val < 4760) return "Banana";
  else if (val < 5040) return "Pear";
  else return "Apple";
}