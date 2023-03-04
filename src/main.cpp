#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#define S_WIDTH 16
#define S_HEIGHT 2
#define S_ADDR 80
#define NUM_OF_DOTS 8

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

const int rs = 3, en = 2, d4 = 7, d5 = 8, d6 = 9, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void handleReceive(int numOfBytes){
  String request, cmd, parameters;
  int param_beg_index, param_end_index, par_del_index, par1, par2;
  while(Wire.available()){
    char c = Wire.read();
    request += c;
  }
  if(!request.indexOf('(') && !request.indexOf(')')) return;
  param_beg_index = request.indexOf('(');
  param_end_index = request.indexOf(')');
  cmd = request.substring(0,param_beg_index);
  parameters = request.substring(param_beg_index+1, param_end_index);
  if(cmd == "print") lcd.print(parameters);
  if(cmd == "clear") lcd.clear();
  if(cmd == "home") lcd.home();
  if(cmd == "setCursor") {
    par_del_index = parameters.indexOf(",");
    if(par_del_index){
      par1 = parameters.substring(0,par_del_index).toInt();
      par2 = parameters.substring(par_del_index+1).toInt();
      if(par1<S_WIDTH && par2<S_HEIGHT) lcd.setCursor(par1, par2);
    }
  }
  if(cmd == "write") lcd.write(parameters[0]);
  if(cmd == "cursor") lcd.cursor();
  if(cmd == "noCursor") lcd.noCursor();
  if(cmd == "blink") lcd.blink();
  if(cmd == "noBlink") lcd.noBlink();
  if(cmd == "display") lcd.display();
  if(cmd == "noDisplay") lcd.noDisplay();
  if(cmd == "scrollDisplayLeft") lcd.scrollDisplayLeft();
  if(cmd == "scrollDisplayRight") lcd.scrollDisplayRight();
  if(cmd == "autoscroll") lcd.autoscroll();
  if(cmd == "noAutoscroll") lcd.noAutoscroll();
  if(cmd == "leftToRight") lcd.leftToRight();
  if(cmd == "rightToLeft") lcd.rightToLeft();
}

void setup() {
  //LCD setup
  lcd.begin(S_WIDTH, S_HEIGHT);
  //i2c setup
  Wire.begin(S_ADDR);
  Wire.onReceive(handleReceive);
  //serial debug
  // Serial.begin(9600);
}

void loop() {

}

