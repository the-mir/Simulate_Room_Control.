const int temperaturePin = A0;    // Analog pin for temperature sensor
const int lightPin = A1;         // Analog pin for light sensor
const int pirPin = 2;            // Digital pin for PIR sensor
const int fanPin = 3;            // Digital pin for fan
const int lightControlPin = 4;   // Digital pin for light control

const int fanThreshold = 20;     // Temperature threshold for turning on the fan
const int lightThreshold = 500;  // Light intensity threshold for turning on the light

void setup() {
  pinMode(fanPin, OUTPUT);
  pinMode(lightControlPin, OUTPUT);
  pinMode(pirPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int temperature = getTemperature();
  int lightIntensity = getLightIntensity();
  bool presence = detectPresence();

  if (temperature >= fanThreshold && presence) {
    turnOnFan();
  } else {
    turnOffFan();
  }

  if (lightIntensity <= lightThreshold && presence) {
    turnOnLight();
  } else {
    turnOffLight();
  }

  delay(1000); // Delay for 1 second
}

int getTemperature() {
  int reading = analogRead(temperaturePin);
  // Convert the analog reading to temperature in degrees Celsius
  float voltage = reading * 5.0 / 1023.0;
  float temperature = (voltage - 0.5) * 100;
  return int(temperature);
}

int getLightIntensity() {
  int reading = analogRead(lightPin);
  return reading;
}

bool detectPresence() {
  bool presence = digitalRead(pirPin);
  return presence;
}

void turnOnFan() {
  digitalWrite(fanPin, HIGH);
}

void turnOffFan() {
  digitalWrite(fanPin, LOW);
}

void turnOnLight() {
  digitalWrite(lightControlPin, HIGH);
}

void turnOffLight() {
  digitalWrite(lightControlPin, LOW);
}
