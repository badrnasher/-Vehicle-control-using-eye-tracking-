#include "Arduino.h"
#include "BluetoothSerial.h"
#include "string.h"

BluetoothSerial SerialBT;

const int Enable_A = 22;
const int Enable_B = 23;
const int inputA1 = 16;
const int inputA2 = 17;
const int inputB1 = 18;
const int inputB2 = 19;
// const char* Ip = "S";

const int frequency = 500;
const int resolution = 8;
const int pwm_channel_ENB = 0;
const int pwm_channel_ENA = 1;
int flag = 0;

void setup()
{
  definePin();

  Serial.begin(115200);
  SerialBT.begin("ESP32test123");
  Serial.println("The device started, now you can pair it with bluetooth!");
  Serial.print("Start fuck...");


}

void motorSpeed(int SpeedENA, int SpeedEnB){
  ledcWrite(pwm_channel_ENA, SpeedENA);
  ledcWrite(pwm_channel_ENB, SpeedEnB);
}


void definePin(){
  pinMode(Enable_A, OUTPUT);
  pinMode(Enable_B, OUTPUT);
  pinMode(inputA1, OUTPUT);
  pinMode(inputA2, OUTPUT);
  pinMode(inputB1, OUTPUT);
  pinMode(inputB2, OUTPUT);

  ledcSetup(pwm_channel_ENA, frequency, resolution);
  ledcSetup(pwm_channel_ENB, frequency, resolution);

  ledcAttachPin(Enable_A, pwm_channel_ENA);
  ledcAttachPin(Enable_B, pwm_channel_ENB);
}

void moveCar(int direction){
  switch(direction)
    {
      case 1: //ileri
        
        digitalWrite(inputA1, HIGH);
        digitalWrite(inputA2, LOW);
        digitalWrite(inputB1 , HIGH);
        digitalWrite(inputB2, LOW);  
        
        if (flag== 1){
          for (int i = 255; i >= 0; --i){
            motorSpeed(i, i);
            delay(2);
          }
        }        


        break;
    
      case 2: //geri
        
        digitalWrite(inputA1, LOW);
        digitalWrite(inputA2, HIGH);
        digitalWrite(inputB1, LOW);
        digitalWrite(inputB2, HIGH);
        
        if (flag== 1){
          for (int i = 255; i >= 0; --i){
            motorSpeed(i, i);
            delay(2);
          }
        }   

        break;
    
      case 3: //sağ

        digitalWrite(inputA1, HIGH);
        digitalWrite(inputA2, LOW); 
        digitalWrite(inputB1, LOW);
        digitalWrite(inputB2, HIGH);

        if (flag== 1){
          for (int i = 225; i >= 0; --i){
            motorSpeed(i, i);
            delay(2);
          }
        }


        break;
    
      case 4: //sol

        digitalWrite(inputA1, LOW);
        digitalWrite(inputA2, HIGH); 
        digitalWrite(inputB1, HIGH);
        digitalWrite(inputB2, LOW);

        if (flag== 1){
          for (int i = 225; i >= 0; --i){
            motorSpeed(i, i);
            delay(2);
          }
        }

        break;
  
      case 5: //dur
        motorSpeed(0, 0);
        break;
    
      default: //dur
        motorSpeed(0, 0);
        break;
    }
  
}


void loop(){
  flag = 0;
  
  if (SerialBT.available()) {
    //Serial.write(SerialBT.read());
    String Ip = SerialBT.readString();
    Serial.println(Ip);
  
     if (Ip == "F" || Ip == "FF"){
    flag = 1;
    Serial.println("move forward");    
    moveCar(1);
  }
  else  if (Ip == "B"|| Ip == "BB"){
    flag = 1;
    Serial.println("move backward");
    moveCar(2);
  }
  else  if (Ip == "L"|| Ip == "LL"){
    flag = 1;
    Serial.println("move left");
    moveCar(4);
  }
  else  if (Ip == "R"|| Ip == "RR"){
    flag = 1;
    Serial.println("move right");
    moveCar(3);
  }
  else  if (Ip == "S"|| Ip == "SS"){
    flag = 1;
    Serial.println("stop");
    moveCar(5);
  }
  else {
    flag = 1;
    moveCar(5);
  } 
  }
 

}