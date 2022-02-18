#include <LiquidCrystal_I2C.h>
#include "AccelStepper.h" 
#include <Wire.h>   // standardowa biblioteka Arduino
#include <LcdBarGraphRobojax.h>


byte lcdNumCols = 16; // -- number of columns in the LCD
byte lcdLine = 2; // -- number of line in the LCD
LiquidCrystal_I2C lcd(0x27, 16,2);  // Ustawienie adresu ukladu na 0x27
LcdBarGraphRobojax lbg(&lcd, 12, 0, 0);  // -- creating 16 character long bargraph starting at char 0 of line 0 (see video)
LcdBarGraphRobojax lbg2(&lcd, 12, 0, 1);
AccelStepper stepper(1, 2, 3);  // 1 = Easy Driver interface
                                  // Nano Pin 2 connected to STEP pin of Easy Driver
                                  // Nano Pin 3 connected to DIR pin of Easy Driver
AccelStepper stepper2(1, 5, 6);  // 1 = Easy Driver interface
                                  // Nano Pin 5 connected to STEP pin of Easy Driver
                                  // Nano Pin 6 connected to DIR pin of Easy Driver                                

AccelStepper stepper3(1, 8, 9);  // 1 = Easy Driver interface
                                  // Nano Pin 8 connected to STEP pin of Easy Driver
                                  // Nano Pin 9 connected to DIR pin of Easy Driver  

AccelStepper stepper4(1, 11, 12);  // 1 = Easy Driver interface
                                  // Nano Pin 11 connected to STEP pin of Easy Driver
                                  // Nano Pin 12 connected to DIR pin of Easy Driver                                  
                                  
// Variables to store current, previous and move position
int val=0;
int val2=0;
int val11 = 0;
int val22 = 0;
int previous = 0;
int previous2 = 0;
int long newval = 0; 
int long newval2 = 0;

void setup() {
lcd.begin();   // Inicjalizacja LCD 2x16
  
  lcd.backlight(); // zalaczenie podwietlenia 
  lcd.setCursor(0,0); // Ustawienie kursora w pozycji 0,0 (pierwszy wiersz, pierwsza kolumna)

  stepper.setMaxSpeed(2400);  // Set speed fast enough to follow pot rotation
  stepper.setAcceleration(2400);  //  High Acceleration to follow pot rotation  
  stepper2.setMaxSpeed(2400);  // Set speed fast enough to follow pot rotation
  stepper2.setAcceleration(2400);  //  High Acceleration to follow pot rotation 
  stepper3.setMaxSpeed(2400);  // Set speed fast enough to follow pot rotation
  stepper3.setAcceleration(2400);  //  High Acceleration to follow pot rotation  
  stepper4.setMaxSpeed(2400);  // Set speed fast enough to follow pot rotation
  stepper4.setAcceleration(2400);  //  High Acceleration to follow pot rotation 
}

void loop() {

 // lbg.clearLine(1);// clear line 1 to display fresh voltage value
  int inpuValue = analogRead(A0);
  val=inpuValue;
  if ((val > previous+6) || (val < previous-6)) 
  {  // Check that a move of the pot is at least > or < than 6
    newval = map(val, 0, 1023, 0, 33400);  // Map value (1600 = 1 stepper shaft rotation), 33400 to rowne cztery obroty
    stepper.runToNewPosition(newval);  // Move stepper to new position
    stepper3.runToNewPosition(newval);  // Move stepper to new position
    previous = val;  // save current value into variable previous
  }
  // -- draw bar graph from the analog value read
  lbg.drawValue( inpuValue, 1024);
  // -- do some delay: frequent draw may cause broken visualization
  float voltage = inpuValue * (100.0 / 1023.0);
  lcd.setCursor (12,0); //
  lcd.print(voltage); // print
  lcd.setCursor (15,0); //  
  lcd.print("%");   
  delay(100);

  

// lbg2.clearLine(1);// clear line 1 to display fresh voltage value
  int inpuValue2 = analogRead(A1);
  val2=inpuValue2;
  if ((val2 > previous2+6) || (val2 < previous2-6)) {  // Check that a move of the pot is at least > or < than 6
    newval2 = map(val2, 0, 1023, 0, 33400);  // Map value (1600 = 1 stepper shaft rotation), 33400 to rowne cztery obroty
    stepper2.runToNewPosition(newval2);  // Move stepper to new position
    stepper4.runToNewPosition(newval2);  // Move stepper to new position
    previous2 = val2;  // save current value into variable previous
  }
  
  // -- draw bar graph from the analog value read
  lbg2.drawValue( inpuValue2, 1024);
  // -- do some delay: frequent draw may cause broken visualization
  float voltage2 = inpuValue2 * (100.0 / 1023.0);
  lcd.setCursor (12,1); //
  lcd.print(voltage2); // print
  lcd.setCursor (15,1); //  
  lcd.print("%");   
  delay(100);
  
     
  }
