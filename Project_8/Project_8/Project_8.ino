#define SWITCHPIN 8

#define INTERVAL 6000

void setup() {
  Serial.begin(9600);
  for (uint8_t i = 2; i < 8; i++) {
    pinMode(i, OUTPUT);
    Serial.println("h");
  }

  pinMode(SWITCHPIN, INPUT);

}

void doAThing(uint8_t * led) {
  for (uint8_t i = 2; i < 8; i++) {
    Serial.println("h");
    digitalWrite(i, LOW);
  } 
  *led = 2;
}

void loop() {
  static uint32_t previousTime = 0;
  static uint32_t previousState = 0;
  static uint8_t led = 2;

  uint32_t currentTime = millis();

  Serial.println(currentTime - previousTime);
  if (currentTime - previousTime > INTERVAL) {
    previousTime = currentTime;
    digitalWrite(led, HIGH);
    Serial.print(led);
    Serial.println(" is HIGH");
    led++;
    
    if (led >= 8) led = 2;

  } 

  uint8_t switchState = digitalRead(SWITCHPIN);

  if (switchState != previousState) doAThing(&led);

  previousState = switchState;
}
