static unsigned long long id1 = 0x820017D1C0, id2 = 0x820017DEDA, id3 = 0x6006C457D;
int taka[3] = {0, 0, 0};
char naam[100];
int num, red=8, green=10;
void string(char *str1, char *str2);
unsigned long long last_id;

int ir_sensor = A0; // set the ouput mode in the Serial()!!!
//int buz = 10;

//... for RFID
#include <SoftwareSerial.h>
#include "RDM6300.h"

SoftwareSerial rdm_serial(11, 12);
RDM6300<SoftwareSerial> rdm(&rdm_serial);

int led_pin = 13;
//... for RFID

//... For servo
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
//... For servo


//... For LCD
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//... For LCD


//void GREETING(char *str, int len){
//  lcd.setCursor(15, 0);
//  for(int i=0; i<l6; i++){
//    lcd.write(str[i]);
//    delay(300);
////    lcd.scrollDisplayLeft();
//    // wait a bit:
//    
//  }
//  for(int i=16; i<len; i++){
//    lcd.write(str[i]);
//  delay(5000);
//  // clear the screen !!!!!!!!!!!!!!!
////  for(int i=0; i<16; i++){
////    lcd.scrollDisplayLeft();
////    // wait a bit:
////    delay(150);
////  }
//}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);    ///... For RFID then how to setup for 9600?
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  myservo.write(0);
//  pinMode(10, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
//  GREETING("ADAR EKTA BALlllllllllllllllll", 30);
//  lcd.clear();
}


int bal;


void loop() {
  Serial.println(analogRead(ir_sensor));//?
  bal = analogRead(ir_sensor) < 970;
//  Serial.println(bal);
  if(bal){
    myservo.write(90);  // lifts the barricade upwards
//    analogWrite(buz, HIGH);
//    delay(100);
//    analogWrite(buz, LOW);
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
  }
  else{
    digitalWrite(green, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("  Digital Toll  ");
    lcd.setCursor(0, 1);
    lcd.print(" Collecting Sys .");
    delay(500);
    lcd.clear();
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("     Please     ");
  lcd.setCursor(0, 1);
  lcd.print("  Scan Your ID  ");/////////////////////////////////////////////////////////////////////////////////////////////////
//  delay(2000);

  last_id = rdm.read();
  last_id = rdm.read();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning...");/////////////////////////////////////////////////////////////////////////////////////////////////
  delay(1000);
  if(last_id == id1){
    string(naam, "SHAN");
    num = 0;
  }
  else if(last_id == id2){
    string(naam, "ADNAN");
    num = 1;
  }
  else if(last_id == id3){
    string(naam, "Rahim");
    num = 2;
  }
  else{
    Serial.println("Unauthorized Access! Get out");/////////////////////////////////////////////////////////////////////
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Unauthorized  ");
    lcd.setCursor(0, 1);
    lcd.print("    Access!!    ");
// 
    delay(3000);
    while(1){
      
    }
//    analogWrite(buz, LOW);
    return;
  }
  Serial.println(naam);
  Serial.println("Scanning Completed!");
  lcd.clear();
  lcd.print("Scan Completed!");////////////////////////////////////////////////////////////////////////////////////////
  delay(2000);
  // can alarm a buzzer

  // display in the LCD

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Welcome!!!   ");//////////////////////////////////////////////////////////////////////////////////////////////////////
  delay(2000);
//  Serial.println(greetings);
//  GREETING(greetings, 33);


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ID : ");////////////////////////////////////////////////////////////////////////////////////////////////////////
  lcd.setCursor(5, 0);
  lcd.print(naam);////////////////////////////////////////////////////////////////////////////////////////////////////////

//  Serial.print("RFID: 0x");
//  rdm.print_int64(last_id);
//  Serial.println();

  taka[num] += 20;
  Serial.print("Name: ");
  Serial.println(naam);
//  lcd.print(naam);

  
  lcd.setCursor(0,1);          // start of the second row
  lcd.print("Bill : ");///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  lcd.setCursor(7, 1);
  lcd.print(taka[num]);
  Serial.print("Bill : ");/////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.print(taka[num]);
  lcd.setCursor(11, 1);
  lcd.print(" BDT");///////////////////////////////////////////////////////////////////////////////////////////////////////
  
  delay(2000);


  char greetings2[] = "Thank you for your Cooperation!";
  Serial.println(greetings2);
//  GREETING(greetings2, 31);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Thank You!   ");////////////////////////////////////////////////////////////////////////////////////////////////////
  delay(1000);


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    Opening    ");///////////////////////////////////////////////////////////////////////////////////////
  lcd.setCursor(0, 1);
  lcd.print("    Barrier    ");
  Serial.println("Opening Barrier ..... ");
  delay(1000);

  myservo.write(30); //  reaching the intitial position!!!
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Digital Toll  ");
  lcd.setCursor(0, 1);
  lcd.print(" Collecting Sys .");
  bal = analogRead(ir_sensor) < 970;
  while(bal){
    bal = analogRead(ir_sensor) < 970;
  }
  delay(500);
}


void string(char *str1, char *str2)
{
  char *p = str2;
  int i = 0;
  while(*p){
    str1[i++] = *p++;
  }
  str1[i] = '\0';
}

