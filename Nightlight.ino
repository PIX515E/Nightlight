/*
Created by: PIX515E
Last Edited: 5/5/2013 3:31 PM CST
I have no notes on this project and don't remember it's purpose.
This is why we leave //COMMENTS kids...

After a quick glance it looks like a nightlight that can be programmed to
a specific color or preset color and displays how long it has been on via LCD.
...or something...
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int BTNS = A0;
const int POT = A1;

const int LED_R = 6;
const int LED_G = 9;
const int LED_B = 10;
const int BkLight = 13;

int BTN_Val = 0;
int old_BTN_Val = 0;
int button = 0;
int POT_Val = 0;
int old_POT_Val = 0;

unsigned long currentMillis = 0;
unsigned long objectiveMillis = 0;
unsigned long timerReset = 0;
unsigned long currentTime = 0;
unsigned long t = 0;

unsigned int interval = 5000;

int s = 0;
int m = 0;
int h = 0;

int i = 0;

int scroll = 0;

int state = 0;

int brt_R0 = 0;
int brt_G0 = 0;
int brt_B0 = 0;

byte timer1[8] = {
  B01110,
  B11011,
  B00100,
  B01010,
  B00100,
  B11011,
  B01110,
};

byte timer2[8] = {
  B01111,
  B01110,
  B00100,
  B01010,
  B00100,
  B01110,
  B11110,
};

byte timer3[8] = {
  B00011,
  B00111,
  B00110,
  B01010,
  B01100,
  B11100,
  B11000,
};

byte timer4[8] = {
  B00000,
  B00110,
  B00111,
  B11011,
  B11100,
  B01100,
  B00000,
};

byte timer5[8] = {
  B00000,
  B00100,
  B01110,
  B11011,
  B01110,
  B00100,
  B00000,
};

byte timer6[8] = {
  B00000,
  B01100,
  B11100,
  B11011,
  B00111,
  B00110,
  B00000,
};

byte timer7[8] = {
  B11000,
  B11100,
  B01100,
  B01010,
  B00110,
  B00111,
  B00011,
};

byte timer8[8] = {
  B11110,
  B01110,
  B00100,
  B01010,
  B00100,
  B01110,
  B01111,
};

void red() {
  analogWrite(LED_R, 255);
  analogWrite(LED_G, 0);
  analogWrite(LED_B, 0);
}

void green() {
  analogWrite(LED_R, 0);
  analogWrite(LED_G, 255);
  analogWrite(LED_B, 0);
}

void blue() {
  analogWrite(LED_R, 0);
  analogWrite(LED_G, 0);
  analogWrite(LED_B, 255);
}

void white() {
  analogWrite(LED_R, 255);
  analogWrite(LED_G, 255);
  analogWrite(LED_B, 255);
}

void black() {
  analogWrite(LED_R, 0);
  analogWrite(LED_G, 0);
  analogWrite(LED_B, 0);
}

void timer() {
  currentMillis = millis();
  currentTime = (2^32-1)-timerReset+currentMillis-(2^32-1);
  t = currentTime/1000;
  s = t % 60;
  m = (t/60) % 60;
  h = t/3600;
  lcd.setCursor(0, 1);
  if (button == 0) {
    i++;
  } else {
    i++;
    delay(100);
  }
  if (i > 7) {
    i = 0;
  }
  lcd.write(byte(i));
  lcd.print(" ");
  if (h > 9) {
    lcd.print(h);
    lcd.print("h| ");
  }
  else {
    lcd.print(h);
    lcd.print(" h| ");
  }
  if (m > 9) {
    lcd.print(m);
    lcd.print("m| ");
  }
  else {
    lcd.print(m);
    lcd.print(" m| ");
  }
  if (s > 9 ) {
    lcd.print(s);
    lcd.print("s] ");
  }
  else {
    lcd.print(s);
    lcd.print(" s] ");
  }
}

void upTime() {
  currentMillis = millis();
  for (scroll = 36; scroll > 24; scroll--) {
    buttonSelect();
    if (button > 0 || state == 0) {
      break;
    }
    if (button == 0 && state == 1) {
      lcd.setCursor(-1*scroll, 0);
      lcd.print(" ");
      lcd.print("Up Time Is:");
      lcd.print("                ");
      timer();
      delay(100);
    }
  }
  for (scroll = 0; scroll < 16; scroll++) {
    buttonSelect();
    if (button > 0 || state == 0) {
      break;
    }
    if (button == 0 && state == 1) {
      lcd.setCursor(scroll, 0);
      lcd.print(" ");
      lcd.print("Up Time Is:");
      lcd.print("                ");
      timer();
      delay(100);
    }
  }
}

void buttonSelect() {
  currentMillis = millis();
  BTN_Val = analogRead(BTNS);
  BkLight_Switch();
  if (old_BTN_Val < 100) {
    if (BTN_Val < 100) {
      if (currentMillis > objectiveMillis) {
        button = 0;
      }
    }
    if ((BTN_Val >= 825 && BTN_Val <= 845)) {
      state = 1 - state;
    }
    if (currentMillis <= objectiveMillis) {
      if (BTN_Val >= 680 && BTN_Val <= 700) {
        objectiveMillis = currentMillis + interval;
        button = 1;
      }
      if (BTN_Val >= 635 && BTN_Val <= 655) {
        objectiveMillis = currentMillis + interval;
        button = 2;
      }
      if (BTN_Val >= 585 && BTN_Val <= 605) {
        objectiveMillis = currentMillis + interval;
        button = 3;
      }
      if (BTN_Val >= 500 && BTN_Val <= 520) {
        objectiveMillis = currentMillis + interval;
        button = 4;
      }
    }
  }
  old_BTN_Val = BTN_Val;
}

void BkLight_Switch() {
  currentMillis = millis();
  if (BTN_Val > 100) {
    objectiveMillis = currentMillis + interval;
    if (currentMillis <= objectiveMillis) {
      digitalWrite(BkLight, HIGH);
    }
  }
  if (currentMillis > objectiveMillis) {
    digitalWrite(BkLight, LOW);
  }
}

void potCheck() {
  currentMillis = millis();
  if (old_POT_Val != POT_Val) {
    objectiveMillis = currentMillis + interval;
  }
  old_POT_Val = POT_Val;
}

void modeOff() {
  digitalWrite(BkLight, LOW);
  black();
  lcd.clear();
  t = 0;
  s = 0;
  m = 0;
  h = 0;
  i = 0;
  scroll = 0;
  currentMillis = millis();
  objectiveMillis = 0;
  timerReset = currentMillis;
}

void setup() {
  lcd.createChar(0, timer1);
  lcd.createChar(1, timer2);
  lcd.createChar(2, timer3);
  lcd.createChar(3, timer4);
  lcd.createChar(4, timer5);
  lcd.createChar(5, timer6);
  lcd.createChar(6, timer7);
  lcd.createChar(7, timer8);
  pinMode(BkLight, OUTPUT);
  pinMode(BTNS, INPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {
  currentMillis = millis();
  buttonSelect();
  if (state != 1) {
    modeOff();
  }
  if (state == 1) {
    POT_Val = analogRead(POT);
    POT_Val = map(POT_Val, 0, 1023, 0, 255);
    switch (button) {
      case 1:
      brt_R0 = POT_Val;
      lcd.setCursor(0, 0);
      lcd.print("Red!            ");
      analogWrite(LED_G, 0);
      analogWrite(LED_B, 0);
      analogWrite(LED_R, brt_R0);
      timer();
      potCheck();
      break;
      case 2:
      brt_G0 = POT_Val;
      lcd.setCursor(0, 0);
      lcd.print("Green!          ");
      analogWrite(LED_R, 0);
      analogWrite(LED_B, 0);
      analogWrite(LED_G, brt_G0);
      timer();
      potCheck();
      break;
      case 3:
      brt_B0 = POT_Val;
      lcd.setCursor(0, 0);
      lcd.print("Blue!           ");
      analogWrite(LED_R, 0);
      analogWrite(LED_G, 0);
      analogWrite(LED_B, brt_B0);
      timer();
      potCheck();
      break;
      case 4:
      brt_R0 = POT_Val;
      brt_G0 = POT_Val;
      brt_B0 = POT_Val;
      lcd.setCursor(0, 0);
      lcd.print("White!          ");
      analogWrite(LED_R, brt_R0);
      analogWrite(LED_G, brt_G0);
      analogWrite(LED_B, brt_B0);
      timer();
      potCheck();
      break;
      default:
      analogWrite(LED_R, brt_R0);
      analogWrite(LED_G, brt_G0);
      analogWrite(LED_B, brt_B0);
      upTime();
      break;
    }
  }
}
