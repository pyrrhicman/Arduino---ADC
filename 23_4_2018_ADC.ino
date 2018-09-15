
#include <LiquidCrystal.h>

#define LED1 0
#define SAMPLE_DELAY 800
const int rs = 9, en = 8, d4 = 5, d5 = 6, d6 = 3, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int analogPin = 9;
unsigned int readedValue = 0; 
unsigned int savedValue=0;
int lightPresent = 0.0;
const byte interruptPin = 2;
volatile byte state = LOW;

void setup() {
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1,HIGH);
  lcd.begin(16, 2);
  lcd.setCursor(3,0);
  lcd.print("LCD TEST");
  digitalWrite(LED1,LOW);
  delay(1000);
  digitalWrite(LED1,HIGH);
  lcd.clear();
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), button, CHANGE);
  savedValue = analogRead(analogPin); 
}

void loop() 
{
  readedValue = analogRead(analogPin);  
  lightPresent = readedValue ; //MAX = 1024 MIN = 0
  lightPresent = lightPresent / 10.24 ;
  lcd.print("Luettu: ");
  lcd.print(readedValue);
  lcd.print(" ");
  lcd.print(lightPresent);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Saved: ");
  lcd.print(savedValue);
  
    if(readedValue<=savedValue)
    {
       digitalWrite(LED1,LOW);
       lcd.print(" Dark");
    }
    else if((readedValue -50)>savedValue)
    {
       digitalWrite(LED1,HIGH); 
       lcd.print(" Light");
    }
    
  delay(SAMPLE_DELAY);
  lcd.clear();
}

void button() {
  savedValue = readedValue;  
}
