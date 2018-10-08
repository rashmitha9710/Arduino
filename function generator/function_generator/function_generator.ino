#include <LiquidCrystal.h>

int count = 0;
//int sine = 13;
//int squ = 12;
//int tri = 11;
int button = A1;
int pot1 = A0;
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

void setup()
{
  if (digitalRead(button) == HIGH)
  {

    //pinMode(sine, OUTPUT);
    //pinMode(squ, OUTPUT);
    //pinMode(tri, OUTPUT);
    pinMode(button, INPUT);
    pinMode(pot1, INPUT);
    //lcd.print("hello, world!");
    lcd.clear();
    lcd.begin(16, 2);

    lcd.setCursor(0, 0);
    lcd.print("PRESS BUTTON TO PROCEED");
    lcd.setCursor(0, 1);
    lcd.print("PROCEED");

    delay(10000);
    lcd.begin(16, 2);
    lcd.noDisplay();

    PORTD = 0;
    DDRD = 255;
  }
}

void loop()
{

  byte buttonState = digitalRead(button);
  float freq = analogRead(pot1) * 0.01;


  if (buttonState == LOW) {
    delay(100);
    count++;
  }
  switch (count)
  { case 1: {

        //digitalWrite(sine, HIGH);
        // digitalWrite(squ, LOW);
        // digitalWrite(tri, LOW);
        for (int i = 0; i < 360; i++)
        {
          if (buttonState == LOW)
            break;
          int m = 127 + 127 * sin(i * 3.1415 / 180);
          PORTD = m;
          delay(freq);
        }

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(">>SINE");  //displaying sine wave in LCD
        // lcd.clear();
        lcd.display();
        lcd.setCursor(0, 1);
        lcd.print(freq);    //
        lcd.print("kHz");


        lcd.display();



        break;
      }
    case 2: {
        //digitalWrite(squ, HIGH);
        // digitalWrite(sine, LOW);
        // digitalWrite(tri, LOW);
        for (int i = 0; i < 360; i++)
        {
          if (buttonState == LOW)
            break;
          PORTD = 0;
          delay (freq);
          PORTD = 255;
          delay (freq);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(">>SQUARE");

        lcd.display();
        lcd.setCursor(0, 1);
        lcd.print(freq);
        lcd.print("kHz");

        lcd.display();



        break;
      }

    case 3: {
        //digitalWrite(tri, HIGH);
        //digitalWrite(squ, LOW);
        //digitalWrite(sine, LOW);


        for (int i = 0; i <= 255; i = i + 1)
        {
          if (buttonState == LOW)
            break;
          PORTD = i;
          delay(freq);
        }
        for (int i = 255; i >= 0; i = i - 1)
        {
          if (buttonState == LOW)
            break;
          PORTD = i;
          delay(freq);
        }
        //lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(">>TRIANGLE");

        lcd.display();
        lcd.setCursor(0, 1);
        lcd.print(freq);
        lcd.print("KHz");
        lcd.display();
        break;
      }

    default : {
        if (count >= 4)
          count = 1;
      }
  }
}



