#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
//Defind Pin
  int fronttrig = 6;
  int frontecho = 7;
  int lefttrig = 9;
  int leftecho = 8;
  int righttrig = 11;
  int rightecho = 10;
  int pip = 12;
  int switch1 = 2;
  int switch2 = 13;
  int switch3 = 4;
  int switch4 = 5;
  int SPD = 3;
//Defind variable for code
  int frontdistance;
  int leftdistance;
  int rightdistance;
  int sw1 = 1;
  int sw2 = 1;
  int sw3 = 1;
  int sw4 = 1;
  int ttdis = 0;
  int start = 0;
//Defind variable to ref
  int reffront = 15;
  int refleft = 15;
  int refright = 15;
  int Automoto = 1;
  int swithmoto = 1;
  int mts = 0;
  int LCD = 0;
  int MLCD = 5;
  int speed = 110;
void setup() {
  Serial.begin(9600);  // Initialize serial communication to send data
  pinMode(fronttrig, OUTPUT);
  pinMode(frontecho, INPUT);
  pinMode(lefttrig, OUTPUT);
  pinMode(leftecho, INPUT);
  pinMode(righttrig, OUTPUT);
  pinMode(rightecho, INPUT);
  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);
  pinMode(switch3, INPUT_PULLUP);
  pinMode(switch4, INPUT_PULLUP);
  pinMode(SPD, OUTPUT);
  analogWrite(SPD, speed);
  lcd.begin();
}
void nxlcd() {
  LCD = (LCD + 1) % MLCD;
}
void chksw() {
  sw1 = digitalRead(switch1);
  sw2 = digitalRead(switch2);
  sw3 = digitalRead(switch3);
  sw4 = digitalRead(switch4);
}
int dischkft() {
  digitalWrite(fronttrig, LOW);
  delayMicroseconds(2);
  digitalWrite(fronttrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(fronttrig, LOW);
  // Read the time it takes for the pulse to return
  long frontduration = pulseIn(frontecho, HIGH);
  // Calculate distance in cm
  return frontduration * 0.034 / 2;
}
int dischklt() {
  //left ultrasonic sensor
  digitalWrite(lefttrig, LOW);
  delayMicroseconds(2);
  digitalWrite(lefttrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(lefttrig, LOW);
  long leftduration = pulseIn(leftecho, HIGH);
  return leftdistance = leftduration * 0.034 / 2;
}
int dischkrt() {
  //rightultrasonic sensor
  digitalWrite(righttrig, LOW);
  delayMicroseconds(2);
  digitalWrite(righttrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(righttrig, LOW);
  long rightduration = pulseIn(rightecho, HIGH);
  return rightdistance = rightduration * 0.034 / 2;
}
void loop() {
  analogWrite(SPD, speed);
  while (start == 0) {
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("Press any switch");
    lcd.setCursor(0, 1);
    lcd.print("    to start    ");
    while (1) {
      delay(100);
      chksw();
      if (sw1 == 1 || sw2 == 1 || sw3 == 1 || sw4 == 1) {
        break;
      }
    }
    start = 1;
    tone(pip,1000,200);
    delay(200);
  }
// Send a pulse to trigger the front ultrasonic sensor
  frontdistance = dischkft();
//left ultrasonic sensor
  leftdistance = dischklt();
//rightultrasonic sensor
  rightdistance = dischkrt();

//Switch process 
  chksw();
  if (sw1 == 1 || sw2 == 1 || sw3 == 1 || sw4 == 1) {
    if (sw1 == 1) { // set the ref distance with botton 1
      tone(pip, 500, 50);
      nxlcd();
    }
    else if (sw2 == 1 || sw3 == 1 || sw4 == 1) {
      if (LCD <= 1) {
        if (sw2 == 1) {
          Automoto = 0;
          if (mts == 4) {
          }
          else {
            Serial.println("q");
            mts = 4;
          }
        }
        else if (sw3 == 1) {
          Automoto = 0;
          if (mts == 2) {
          }
          else {
            Serial.println("e");
            mts = 2;
          }
        }
        else if (sw4 == 1) {
          Automoto = 0;
          if (mts == 3) {
          }
          else {
            Serial.println("b");
            mts = 3;
          }
        }
      }
      if (LCD == 2) {
        if (sw2 == 1) {
          refleft = leftdistance;
        }
        else if (sw3 == 1) {
          refright = rightdistance;
        }
        else if (sw4 == 1) {
          refleft = leftdistance;
          refright = rightdistance;
        }
        tone(pip, 300, 50);
      }
      if (LCD == 3) {
        if (sw2 == 1) {
          speed = speed - 10;
        }
        else if (sw3 == 1) {
          speed = speed + 10;
        }
        else if (sw4 == 1) {
          speed =  110;
        }
        if (speed <= 0) {
          speed = 0;
        } 
        else if (speed >= 250) {
          speed = 250;
        }
        tone(pip, 400, 50);
      }
      if (LCD == 4) {
        if (swithmoto == 1) {
          swithmoto = 0;
        }
        else {
          swithmoto = 1;
        }
        tone(pip, 300, 50);
      }
    }
  }
  else {
    Automoto = 1;
    if (swithmoto == 0) {
      Serial.println("s");
        mts = 0; // mts = 0 is stop
    }
  }

//Auto motive zone
  if (Automoto == 1 && swithmoto == 1) {
    if (frontdistance <= reffront) {
      if (mts == 0) {
      }
      else {
        Serial.println("s");
        mts = 0; // mts = 0 is stop
        tone(pip, 1500, 100);
      }
    }
    else if ((leftdistance >= refleft && rightdistance >= refright)) {
      if (mts == 0) {
      }
      else {
        Serial.println("s");
        mts = 0; // mts = 0 is stop
      }
    }
    else if (leftdistance < refleft || rightdistance < refright) {
      if (leftdistance < refleft && rightdistance >= refright) {
        if (mts == 2) {
        }
        else {
          Serial.println("r");
          mts = 2; // mts = 2 is turn right
        }
      }
      else if (leftdistance >= refleft && rightdistance < refright) {
        if (mts == 4) {
        }
        else {
          Serial.println("l");
          mts = 4; // mts = 4 is turn right
        }
      }
      else {
        if (mts == 1) {
        }
        else {
          Serial.println("f");
          mts = 1; // mts = 1 is go straight
        }
      }
    }
  }

//ทำ LCD
  lcd.clear();
  lcd.setCursor(0, 0); 
  switch (LCD) {
    case 0:
      lcd.print("Status :");
      lcd.setCursor(8, 0); 
      switch (mts) {
        case 0:
        lcd.print("Stop");
        break;
        case 1:
        lcd.print("Strait");
        break;
        case 2:
        lcd.print("Right");
        break;
        case 3:
        lcd.print("Back");
        break;
        case 4:
        lcd.print("Left");
        break;
      }
      lcd.setCursor(0, 1);
      lcd.print("Distance :");
      lcd.setCursor(10, 1);
      lcd.print(ttdis);
      break;
    case 1:
      lcd.print("Distance F :");
      lcd.setCursor(13, 0);
      lcd.print(frontdistance);
      lcd.setCursor(0, 1);
      lcd.print(" L :");
      lcd.setCursor(4, 1);
      lcd.print(leftdistance);
      lcd.setCursor(8, 1);
      lcd.print(" R :");
      lcd.setCursor(12, 1);
      lcd.print(rightdistance);
      break;
    case 2:
      lcd.print("-Dis L:");
      lcd.setCursor(7, 0);
      lcd.print(leftdistance);
      lcd.setCursor(11, 0);
      lcd.print("R:");
      lcd.setCursor(13, 0);
      lcd.print(rightdistance);
      lcd.setCursor(0, 1);
      lcd.print("-Ref L:");
      lcd.setCursor(7, 1);
      lcd.print(refleft);
      lcd.setCursor(11, 1);
      lcd.print("R:");
      lcd.setCursor(13, 1);
      lcd.print(refright);
      break;
    case 3:
      lcd.print("SetSpeed s2- s3+");
      lcd.setCursor(0, 1); 
      lcd.print("Speed :");
      lcd.setCursor(8, 1);
      lcd.print(speed);
      break;
    case 4:
      lcd.print("Press 234 switch");
      lcd.setCursor(0, 1);
      switch (swithmoto) {
        case 0:
          lcd.print("    to start    ");
          break;
        case 1:
          lcd.print("    to stop    ");
          break;
      }
      break;
  }
//Total Distance
  if (mts ==0) {
    }
    else if (mts ==1) {
      ttdis++;
    }
    else if (mts ==2) {
      ttdis++;
    }
    else if (mts ==3) {
    }
    else if (mts ==4) {
      ttdis++;
    }
//Small delay for stability
  delay(100);
}
