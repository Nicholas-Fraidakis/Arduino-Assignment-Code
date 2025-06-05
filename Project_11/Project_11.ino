// This code is a cleaned up version of the Arduino Textbook code with some extra responses :D
// Also it is a port for the Raspberry Pi Pico 2W
#include <LiquidCrystal.h>
LiquidCrystal lcd(D15, D14, D13, D12, D11, D10);

const int switchPin = D1;

void setup() {
  lcd.begin(16, 2);
  pinMode(switchPin,INPUT);
  lcd.print("Ask the");
  lcd.setCursor(0, 1);
  lcd.print("Crystal Ball!");
}

char *answers[] {
  "Yes",
  "Most likely",
  "Certainly",
  "Outlook good",
  "Unsure",
  "Ask again",
  "Doubtful",
  "No",
  "Definately Not",
  "Absolutely",
  "Quack"
};

void loop() {
  int switchState = digitalRead(switchPin);
  static int prevSwitchState = 0;

  if (switchState == prevSwitchState) return;

  int reply = random(sizeof(answers) / sizeof(answers[0]));
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("The ball says:");
  lcd.setCursor(0, 1);
  Serial.println("input");

  lcd.print(answers[reply]);

  prevSwitchState = switchState;
}