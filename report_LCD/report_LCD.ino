#include <LiquidCrystal.h>                  // include the library code

char array1[] = " Bot Info               "; // welcome string

int delay_t = 200; //the value of delay delay_tef
int positionCounter1 = 0; // for left moving animation

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);

void setup()
{
  Serial1.begin(115200);  // Xbee
  lcd.begin(16, 2);       // set up the LCD's number of columns and rows:
  lcd.clear();            // clear the LCD
  lcd.setCursor(15, 0);   // set the cursor to column 15, line 0

  // flush the buffer
  while (Serial1.available() > 0)
    Serial1.read();

  // print welcome string
  positionCounter1 = 0;
  while (positionCounter1 < 15) {
    lcd.scrollDisplayLeft();
    lcd.print(array1[positionCounter1]);
    delay(delay_t);
    positionCounter1++;
  }
}
/*********************************************************/
void loop()
{
  String in;
  if (Serial1.available() > 0) {
    // read the string from XBee 
    in = Serial1.readStringUntil('\n');
  }

  // convert the String to Int
  int in_int = in.toInt();

  lcd.setCursor(0, 1);
  lcd.clear();

  // print the respective string to LCD
  switch (in_int) {
    case 1:
      Serial.println(in_int);
      lcd.print(" Robot in front      ");
      break;
    case 2:
      lcd.print(" Go back ..      ");
      break;
    case 3:
      lcd.print(" Left ...      ");
      break;
    case 4:
      lcd.print(" Right ...      ");
      break;
    case 5:
      lcd.print(" Stop !      ");
      break;
    case 6:
      lcd.print("Attack      ");
      break;
    case 7:
      lcd.print(" Rotate 180   ");
      break;
    case 10:
      lcd.print("  Middle QTI int.  ");
      break;
    default:
      break;
  }

  //  lcd.print(in_int);
  delay(1000);

  // flush the buffer
  while (Serial1.available() > 0)
    Serial1.read();
}
/************************************************************/
