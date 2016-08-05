#include <LiquidCrystal.h>
#include <Keypad.h>


const byte NUM_CANDIDATES = 4;
const byte LCD_RS = 2;
const byte LCD_E = 3;
const byte LCD_D4 = 4;
const byte LCD_D5 = 5;
const byte LCD_D6 = 6;
const byte LCD_D7 = 7;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {8, 9, 14, 15}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {16, 17, 18, 19}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
String vote;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 4);

}
char key;
char message[NUM_CANDIDATES];
int pref;

void loop()
{
  while (!Serial.find("enable")) {
    lcd.clear();
    lcd.print ("Wait for enable");

  }
  lcd.clear();
  lcd.print("Enabled");
  delay(1000);
  lcd.clear();

  // Vote for president

  lcd.print("President");
  delay(1000);
  pref = 1;
  while (pref <= NUM_CANDIDATES + 1) //Since pref starts at 1
  { 
    enter_again:
    if (pref != NUM_CANDIDATES + 1) {
      lcd.clear();
      lcd.print("#");
      lcd.print(pref);
      lcd.print(" preference");
      lcd.setCursor(0, 2);
      key = customKeypad.getKey();
      if (key)
      { 
        // Check if the character has been previously entered
        for (int i = 0; i < pref; i++) {
          if (key == message[i])
          {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Invalid choice");
            lcd.setCursor(0, 1);
            lcd.print("Please choose");
            lcd.setCursor(0, 2);
            lcd.print("again.");
            delay(1500);
            goto enter_again; // Don't kill me.
          }
        }

        if (key == 'C')
        {
          for (int i = 0; i < NUM_CANDIDATES; i++)
            message[i] = '0';
          pref = 1;
          lcd.clear();
          continue;
        }
        else if (key == 'D')
        {
          for (; pref <= NUM_CANDIDATES; pref++)
            message[pref - 1] = 'n';
          continue;
        }
        message[pref - 1] = key;
        lcd.print(key);
        pref++;
        delay(1000);


      }
    }
    else if (pref == NUM_CANDIDATES + 1) //All votes for the ballot have been cast
    {
      lcd.setCursor(0, 0);
      for (int i = 0; i < NUM_CANDIDATES; i++) { // Show your preference
        lcd.print(i + 1);
        lcd.print(">");
        lcd.print(message[i]);
        lcd.print("|");
      }
      lcd.setCursor(0, 2); //Print confirm prompt
      lcd.print("C to cancel");
      lcd.setCursor(0, 3);
      lcd.print("D to confirm");
      key = customKeypad.getKey();
      if (key)
      {
        if (key == 'C')
        {
          for (int i = 0; i < NUM_CANDIDATES; i++)
            message[i] = '0'; //Reset the cote
          pref = 1; // Reset to preference 1
          lcd.clear();
          continue;
        }
        else if (key == 'D')
        {
          for (int i = 0; i < NUM_CANDIDATES; i++)
            Serial.print(message[i]);
          for (int i = 0; i < NUM_CANDIDATES; i++)
            message[i] = '0';
          break;
        }
        lcd.clear();
      }
    }
  }
  Serial.print("\n");
  delay(1000);
  lcd.clear();
}


