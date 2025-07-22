const int trigPin = D1;  
const int echoPin = D2; 
const int buttonPin = D3;

float duration, distance;  

unsigned long previousMillis = 0;
const unsigned long interval = 10000;  // 10 seconds

bool alerted70 = false;
bool alerted80 = false;
bool alerted90 = false;
bool locked = false;

void setup() {  
	pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);  
	pinMode(buttonPin, INPUT_PULLUP);
	Serial.begin(9600);  
}  

void loop() {  

	if (Serial.available() > 0) {
		String input = Serial.readStringUntil('\n');
		input.trim();
		if (input.equalsIgnoreCase("reset")) {
			resetSystem();
		}
	}

	if (digitalRead(buttonPin) == LOW) {
		resetSystem();
		delay(300);
	}

	unsigned long currentMillis = millis();
	if (currentMillis - previousMillis >= interval && !locked) {
		previousMillis = currentMillis;

		digitalWrite(trigPin, LOW);  
		delayMicroseconds(2);  
		digitalWrite(trigPin, HIGH);  
		delayMicroseconds(10);  
		digitalWrite(trigPin, LOW);  

		duration = pulseIn(echoPin, HIGH);  
		distance = (duration * 0.0343) / 2;  

		if (distance <= 22.8 && !alerted70) {
			Serial.println("Bin 70% full");
			alerted70 = true;
		}
		else if (distance <= 15.2 && !alerted80) {
			Serial.println("Bin 80% full");
			alerted80 = true;
		}
		else if (distance <= 7.6 && !alerted90) {
			Serial.println("Bin 90% full");
			alerted90 = true;
			locked = true;
		}
	}
}

void resetSystem() {
	alerted70 = false;
	alerted80 = false;
	alerted90 = false;
	locked = false;
	Serial.println("System reset.");
}