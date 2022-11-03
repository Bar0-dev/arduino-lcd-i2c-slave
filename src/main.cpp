#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#define CHAR_LIMIT 32
#define CHAR_ON '+'
#define CHAR_OFF '-'

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 3, en = 2, d4 = 7, d5 = 8, d6 = 9, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String message;

//custon button character
// byte button_off[] = {
//   0x00,
//   0x0E,
//   0x11,
//   0x11,
//   0x11,
//   0x11,
//   0x0E,
//   0x00
// };
// byte button_on[] = {
//   0x00,
//   0x0E,
//   0x1F,
//   0x1F,
//   0x1F,
//   0x1F,
//   0x0E,
//   0x00
// };
byte button_off[] = {
  0x00,
  0x00,
  0x0E,
  0x0E,
  0x1F,
  0x1F,
  0x00,
  0x00
};
byte button_on[] = {
  0x00,
  0x00,
  0x00,
  0x0E,
  0x1F,
  0x1F,
  0x00,
  0x00
};

void show_on_lcd(String message){
  String line_1 = "";
  String line_2 = "";
  uint8_t new_line_index;
  lcd.setCursor(0,0);  
  if(message.length() > CHAR_LIMIT){
    lcd.print("Msg. too long!");
    return;
  }
  if(message.indexOf(CHAR_ON) != -1 || message.indexOf(CHAR_OFF) != -1){
    for(int i=0; i<16; i++){
      if(i==8){
        lcd.setCursor(0,1);
      }
      if(message.charAt(i) == CHAR_OFF){
        lcd.write(byte(0));
      }
      if(message.charAt(i) == CHAR_ON){
        lcd.write(byte(1));
      }
    }
    return;
  }
  if(message.indexOf('\n') != -1){
    new_line_index = message.indexOf('\n');
    line_1 = message.substring(0, new_line_index);
    line_2 = message.substring(new_line_index+1, CHAR_LIMIT);
    lcd.print(line_1);
    lcd.setCursor(0,1);
    lcd.print(line_2);
    return;
  }
  if(message.length()>16){
    line_1 = message.substring(0, new_line_index);
    line_2 = message.substring(new_line_index, CHAR_LIMIT);
    lcd.print(line_1);
    lcd.setCursor(0,1);
    lcd.print(line_2);
    return;
  }
  lcd.print(message);
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
  lcd.createChar(0, button_off);
  lcd.createChar(1, button_on);
  //I2C setup
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  //Debug serial
  Serial.begin(9600);
}

void loop() {
  delay(100);
}

