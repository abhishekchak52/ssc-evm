#include <LiquidCrystal.h>
#include <Keypad.h>


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {6,7,8,9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10,11,12,13}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal lcd(14,15,16,17,18,19);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16,2);

}
String message;
bool enabled = false;
char enabler;

void loop() 
{
    // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    delay(100);
    enabler = Serial.peek();
    lcd.write(enabler);
    if(enabler == 'e')
      {
        Serial.readString();
        while(true)
        {
            char customKey = customKeypad.getKey();
              
            if (customKey)
            {   
                lcd.write(customKey);
                message.concat(customKey);
                if(message.length() == 4)
                {  
                  message.concat("\r\n");
                  Serial.write(message.c_str());
                  message = "";
                  lcd.clear();
                  
                  break;
                  
                }  
            }
     
        }
      }
      else
        Serial.readString();
  }
}

