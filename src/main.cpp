#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#define CHAR_LIMIT 32

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 3, en = 2, d4 = 7, d5 = 8, d6 = 9, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String message;

//custon button character
byte open_button[] = {
  0x00,
  0x0E,
  0x11,
  0x11,
  0x11,
  0x11,
  0x0E,
  0x00
};
byte closed_button[] = {
  0x00,
  0x0E,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x0E,
  0x00
};

void show_on_lcd(String message){
  String line_1 = "";
  String line_2 = "";
  uint8_t new_line_index;
  lcd.clear();
  lcd.setCursor(0,0);
  if(message.length() > CHAR_LIMIT){
    lcd.print("Message was\ntoo long!");
  } else {
    new_line_index = message.indexOf('\n');
    if(new_line_index > 0){
      line_1 = message.substring(0, new_line_index);
      line_2 = message.substring(new_line_index+1, CHAR_LIMIT);
      lcd.print(line_1);
      lcd.setCursor(0,1);
      lcd.print(line_2);
    } else {
      lcd.print(message);
    }
  }
}

void receiveEvent(int howMany) {
  message = "";
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    message += c;
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println('\n' + message + '\n');
  show_on_lcd(message);
}

void setup() {
  //LCD setup
  lcd.begin(16, 2);
  lcd.print("Booting...");
  lcd.createChar(0, open_button);
  lcd.createChar(1, closed_button);
  //I2C setup
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  //Debug serial
  Serial.begin(9600);
}

void loop() {
  delay(100);
}

