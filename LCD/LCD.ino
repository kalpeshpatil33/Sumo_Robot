#include <LiquidCrystal.h>// include the library code
/**********************************************************/
char array1[] = " SunFounder               "; //the string to print on the LCD
char array2[] = "hello, world!             "; //the string to print on the LCD

int tim = 200; //the value of delay timef
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
int positionCounter1 = 0;
/*********************************************************/
void setup()
{
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  lcd.setCursor(15, 0); // set the cursor to column 15, line 0
}
/*********************************************************/
void loop()
{
  lcd.scrollDisplayLeft();
  lcd.print(array1[positionCounter1]); // Print a message to the LCD.
  delay(tim); //delay
  positionCounter1++;

  if (positionCounter1 > 15) {
    positionCounter1 = 0;
    lcd.clear();
    lcd.setCursor(15, 0); // set the cursor to column 15, line 0
  }
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