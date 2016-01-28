#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>    
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>w

//calib
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

#define STMPE_CS 8
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

#define RADIUS 30
//#define PENRADIUS 3
//int oldcolor, currentcolor;
//int pinz=0;  //0 if phone pad, 1 if pin pad
int xcoor;
int ycoor;

void setup(void) {
 
  Serial.begin(9600);
  
  tft.begin();

  if (!ts.begin()) {
    Serial.println("Couldn't start touchscreen controller");
    while (1);
  }
  Serial.println("Touchscreen Initiated");
  
  tft.fillScreen(ILI9341_BLACK);
 
  // select the current color 'red'
//  tft.drawCircle(0, 0, RADIUS, ILI9341_WHITE);
//  currentcolor = ILI9341_RED;
}

void loop() {
  numpad(1);  //0 for phone number, 1 for PIN

}

void numpad(int pinz){
  tft.setCursor(5,10);
  if(pinz==0){
    tft.setTextSize(2);
    tft.print("Enter Phone Number");
  }
  else{
    tft.setTextSize(3);
    tft.print("Choose a PIN");
  }
  // make the num selection circles
  printnumpad();

  if (ts.bufferEmpty()) {
    return;
  }
  ts.writeRegister8(STMPE_INT_STA, 0xFF);
  TS_Point p = ts.getPoint();
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
  xcoor=p.x;
  ycoor=p.y;
  Serial.print("Input!");
    //debounce
    
  /*if (! ts.bufferEmpty()) {
    return;
  }*/
/*
    while(p.z>15){
      p = ts.getPoint();
      //Serial.println("P of z is getting chekced");
      Serial.println(p.z);
      delay(50);
    }
 */ 
  int key;
  key = checkin(xcoor, ycoor);
  //tft.fillRect(0, 0, 300, 35, ILI9341_BLACK);
  
  Serial.println(key);
  delay(1000);
  
  //Serial.print("("); Serial.print(p.x);
  //Serial.print(", "); Serial.print(p.y);
  //Serial.println(")");
  //checkin();
  //delay(5000);
  //delay(5000);

}

int checkin(int xcoor, int ycoor){
  int key;
  if((xcoor<70)&&(ycoor<101)) {        //1
     //Serial.print("Going to choose 1");
     tft.fillCircle(40, 71, RADIUS, ILI9341_GREEN);
     //delay(200);
     tft.fillCircle(40, 71, RADIUS, ILI9341_BLACK);
     printnumpad();
     key=1;
     //Serial.print("Chose 1");
  }
  else if((xcoor>70)&&(xcoor<150)&&(ycoor<101)) {        //2
     tft.fillCircle(120, 71, RADIUS, ILI9341_GREEN);
     //delay(200);
     tft.fillCircle(120, 71, RADIUS, ILI9341_BLACK);
     printnumpad();
     key=2;
  }
  else if((xcoor>149)&&(ycoor<101)) {        //3
     tft.fillCircle(200, 71, RADIUS, ILI9341_GREEN);
     delay(200);
     tft.fillCircle(200, 71, RADIUS, ILI9341_BLACK);
     printnumpad();
     key=3;
  }
  else{
    key=300;
  }
  /*
  else if((xcoor<2346)&&(ycoor<98)) {        //4
     tft.fillCircle(40, 142, RADIUS, ILI9341_GREEN);
     delay(200);
     tft.fillCircle(40, 142, RADIUS, ILI9341_BLACK);
     printnumpad();
     key=4;
  }
  else if((xcoor<2346)&&(ycoor<98)) {        //5
   tft.fillCircle(120, 142, RADIUS, ILI9341_GREEN);
     delay(200);
     tft.fillCircle(120, 142, RADIUS, ILI9341_BLACK);
     printnumpad();
     key=5;
  }
  else if((xcoor<2346)&&(ycoor<98)) {        //6
     tft.fillCircle(200, 142, RADIUS, ILI9341_GREEN);
     delay(200);
     tft.fillCircle(200, 142, RADIUS, ILI9341_BLACK);
     printnumpad();
     key=6;
  }
  else if((xcoor<2346)&&(ycoor<98)) {        //7
     tft.fillCircle(40, 213, RADIUS, ILI9341_GREEN);
     delay(200);
     tft.fillCircle(40, 213, RADIUS, ILI9341_BLACK);
     printnumpad();
     key=7;
  }
  else if((xcoor<2346)&&(ycoor<98)) {        //8
     tft.fillCircle(120, 213, RADIUS, ILI9341_GREEN);
     delay(200);
     tft.fillCircle(120, 213, RADIUS, ILI9341_BLACK);
     printnumpad();
     key=8;
  }
  else if((xcoor<2346)&&(ycoor<98)) {        //9
     tft.fillCircle(200, 213, RADIUS, ILI9341_GREEN);
     delay(200);
     tft.fillCircle(200, 213, RADIUS, ILI9341_BLACK);
     printnumpad();
     key=9;
  }
  else if((xcoor<2346)&&(ycoor<98)) {        //X
     tft.fillCircle(40, 284, RADIUS, ILI9341_GREEN);
     delay(200);
     tft.fillCircle(40, 284, RADIUS, ILI9341_BLACK);
     printnumpad();
     key=0;
  }
  else if((xcoor<2346)&&(ycoor<98)) {        //0
     tft.fillCircle(120, 284, RADIUS, ILI9341_GREEN);
     delay(200);
     tft.fillCircle(120, 284, RADIUS, ILI9341_BLACK);
     printnumpad();
     key=0;
  }
  else if((xcoor<2346)&&(ycoor<98)) {        //E
     tft.fillCircle(200, 284, RADIUS, ILI9341_GREEN);
     delay(200);
     tft.fillCircle(200, 284, RADIUS, ILI9341_BLACK);
     printnumpad();
     key=0;
  }
  */
  //int key=7;
  return key;
}

void printnumpad(){
  tft.drawCircle(40, 71, RADIUS, ILI9341_WHITE);
  tft.setTextSize(4);
  tft.setCursor(32,58);
  tft.print("1");
  tft.drawCircle(120, 71, RADIUS, ILI9341_WHITE);
  tft.setCursor(112,58);
  tft.print("2");
  tft.drawCircle(200, 71, RADIUS, ILI9341_WHITE);   //3
  tft.setCursor(192,58);
  tft.print("3");
  tft.drawCircle(40, 142, RADIUS, ILI9341_WHITE);
  tft.setCursor(32,129);
  tft.print("4");
  tft.drawCircle(120, 142, RADIUS, ILI9341_WHITE);
  tft.setCursor(112,129);
  tft.print("5");
  tft.drawCircle(200, 142, RADIUS, ILI9341_WHITE);   //6
  tft.setCursor(192,129);
  tft.print("6");
  tft.drawCircle(40, 213, RADIUS, ILI9341_WHITE); 
  tft.setCursor(32,200);
  tft.print("7");
  tft.drawCircle(120, 213, RADIUS, ILI9341_WHITE);
  tft.setCursor(112,200);
  tft.print("8");
  tft.drawCircle(200, 213, RADIUS, ILI9341_WHITE);   //9
  tft.setCursor(192,200);
  tft.print("9");
  tft.drawCircle(40, 284, RADIUS, ILI9341_RED);
  tft.setCursor(32,271);
  tft.print("X");
  tft.drawCircle(120, 284, RADIUS, ILI9341_WHITE);
  tft.setCursor(112,271);
  tft.print("0");
  tft.drawCircle(200, 284, RADIUS, ILI9341_GREEN);
  tft.setCursor(192,271);
  tft.print("E");
}

void resetDisplay()
{
   //Setup Screen
  tft.fillScreen(ILI9341_BLACK);
  // origin = left,top landscape (USB left upper)
  tft.setRotation(1); 
  tft.setCursor(10,10);
  tft.setTextColor(0x000, 0xFFFF);
  tft.setTextSize(2);
}


