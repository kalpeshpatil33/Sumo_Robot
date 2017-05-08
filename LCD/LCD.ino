#include <LiquidCrystal.h>// include the library code
/**********************************************************/
char array1[] = " Bot Info               "; //the string to print on the LCD

int tim = 200; //the value of delay timef
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
int positionCounter1 = 0;
/*********************************************************/
void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  lcd.setCursor(15, 0); // set the cursor to column 15, line 0

  while (Serial.available() > 0)
    Serial1.read();

//  lcd.scrollDisplayLeft();
//  lcd.print(array1[positionCounter1]); // Print a message to the LCD.
//  delay(tim); //delay
//  positionCounter1++;

  lcd.clear();
  lcd.setCursor(15, 0);
  positionCounter1 = 0;
  while (positionCounter1 < 15) {
    lcd.scrollDisplayLeft();
    lcd.print(array1[positionCounter1]);
    delay(tim);
    positionCounter1++;
  }
}
/*********************************************************/
void loop()
{
  String in;
  if (Serial1.available() > 0) {
    in = Serial1.readStringUntil('\n');
    Serial.println(in);
  }
  int in_int = in.toInt();

  lcd.setCursor(0, 1);
  lcd.clear();
  switch (in_int) {
    case 1:
      Serial.println(in_int);
      lcd.print("I see you <3      ");
      break;
    case 2:
      lcd.print(" Let go back ..      ");
      break;
    case 3:
      lcd.print(" Left ...      ");
      break;
    case 4:
      lcd.print(" Right ...      ");
      break;
    case 5:
      lcd.print(" </3 :'(      ");
      break;
    case 6:
      lcd.print("Attack      ");
      break;
    case 7:
      lcd.print(" Hi ...     ");
      break;
    case 10:
      lcd.print("  </3 :'(    ");
      break;
    default:
      break;
  }


  //  lcd.print(in_int);
  delay(500);

  while (Serial.available() > 0)
    Serial1.read();

  //  lcd.setCursor(15, 0); // set the cursor to column 15, line 0
  //  for ( int positionCounter1 = 0; positionCounter1 < 26; positionCounter1++)
  //  {
  //    lcd.scrollDisplayLeft(); //Scrolls the contents of the display one space to the left.
  //    lcd.print(array1[positionCounter1]); // Print a message to the LCD.
  //    delay(tim); //wait for 500 ms
  //  }
  //  lcd.clear(); //Clears the LCD screen and positions the cursor in the upper-left corner.
  //  lcd.setCursor(15, 1); // set the cursor to column 15, line 1
  //  for (int positionCounter2 = 0; positionCounter2 < 26; positionCounter2++)
  //  {
  //    lcd.scrollDisplayLeft(); //Scrolls the contents of the display one space to the left.
  //    lcd.print(array2[positionCounter2]); // Print a message to the LCD.
  //    delay(tim); //wait for 500 ms
  //  }
  //  lcd.clear(); //Clears the LCD screen and positions the cursor in the upper-left corner.
}
/************************************************************/
