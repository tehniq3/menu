/* menu and value
 * base sketch: Arduino IDE -> Example -> Basic => Button
 * original changes by Nicu FLORICA (niq_ro)
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>  // https://github.com/tehniq3/used_library

// Set the LCD address to ox3F or 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);
  
#define sw0 13 // D13 - pin for menu
#define sw1 14 // A0 - pin for increase the value 
#define sw2 12 // D12 - pin for decrease the value

byte starebuton0, starebuton1, starebuton2;             // the current reading from the input pin
byte citirestarebuton0, citirestarebuton1, citirestarebuton2;   // 

byte ultimastarebuton0 = HIGH;   // the previous reading from the input pin
byte ultimastarebuton1 = HIGH; 
byte ultimastarebuton2 = HIGH; 

unsigned long ultimtpdebounce0 = 0;  // the last time the output pin was toggled
unsigned long ultimtpdebounce1 = 0; 
unsigned long ultimtpdebounce2 = 0; 

unsigned long tpdebounce = 50;    // the debounce time; increase if the output flickers

byte meniu = 0;
int valoare = 0;

void setup() {
  lcd.begin(); // initialize the LCD
  lcd.clear(); // clear the screen
  lcd.backlight(); // Turn on the blacklight and print a message.
  lcd.setCursor(0,0);
  lcd.print("   Test meniu    ");
  lcd.setCursor(0,1);
  lcd.print("sw: Nicu FLORICA");

  pinMode(sw0, INPUT);
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  digitalWrite(sw0, HIGH);
  digitalWrite(sw1, HIGH);
  digitalWrite(sw2, HIGH);  

   delay(3000);
   lcd.clear();
   Serial.begin(9600);
   Serial.println(" ");Serial.println(" ");Serial.println(" ");
   Serial.println("------------------------------------------");    
   Serial.println("test");
}

void loop() {

buton0();
buton1();
buton2();

  lcd.setCursor(0,0);
  lcd.print("Meniu:");

  lcd.setCursor(2,1);
  lcd.print(meniu);

  lcd.setCursor(8,0);
  lcd.print("Valoare:");
  
  lcd.setCursor(10,1);
  if (valoare >= 0) lcd.print(" ");
  lcd.print(valoare);
  

ultimastarebuton0 = citirestarebuton0;
ultimastarebuton1 = citirestarebuton1;
ultimastarebuton2 = citirestarebuton2;
}  // end main loop

void buton0()
{
  // button reading
citirestarebuton0 = digitalRead(sw0);  // read the state of the switch into a local variable: 
  if (citirestarebuton0 != ultimastarebuton0) // If the switch changed, due to noise or pressing:
  {
    ultimtpdebounce0 = millis();  // reset the debouncing timer
  }
  if ((millis() - ultimtpdebounce0) > tpdebounce) 
  {
    if (citirestarebuton0 != starebuton0) // if the button state has changed
    {
      starebuton0 = citirestarebuton0;         
      if (starebuton0 == LOW) // only toggle the LED if the new button state is LOW
      {
        Serial.println("sw0 pushed");
        meniu = meniu + 1;
        valoare = 0;
        if (meniu > 9) meniu = 0;
      }
    }
  }
}

void buton1()
{
  // button reading
citirestarebuton1 = digitalRead(sw1);  // read the state of the switch into a local variable: 
  if (citirestarebuton1 != ultimastarebuton1) // If the switch changed, due to noise or pressing:
  {
    ultimtpdebounce1 = millis();  // reset the debouncing timer
  }
  if ((millis() - ultimtpdebounce1) > tpdebounce) 
  {
    if (citirestarebuton1 != starebuton1) // if the button state has changed
    {
      starebuton1 = citirestarebuton1;         
      if (starebuton1 == LOW) // only toggle the LED if the new button state is LOW
      {
        Serial.println("sw1 pushed");
        valoare = valoare + 1;
        if (valoare > 9) valoare = -9;
      }
    }
  }
}

void buton2()
{
  // button reading
citirestarebuton2 = digitalRead(sw2);  // read the state of the switch into a local variable: 
  if (citirestarebuton2 != ultimastarebuton2) // If the switch changed, due to noise or pressing:
  {
    ultimtpdebounce2 = millis();  // reset the debouncing timer
  }
  if ((millis() - ultimtpdebounce2) > tpdebounce) 
  {
    if (citirestarebuton2 != starebuton2) // if the button state has changed
    {
      starebuton2 = citirestarebuton2;         
      if (starebuton2 == LOW) // only toggle the LED if the new button state is LOW
      {
        Serial.println("sw2 pushed");
        valoare = valoare - 1;
        if (valoare < -9) valoare = 9;
      }
    }
  }
}
