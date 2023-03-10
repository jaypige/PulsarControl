
#include "pinMapping.h"
#include "serialCommunication.h"

int i = 0;
int start = 0;
String message;


void setup() {
  Serial.begin(9600);
  pinMode(TEMP_2_PIN, INPUT);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENABLE, OUTPUT);

  
  pinMode(H1, OUTPUT);
  pinMode(H2,OUTPUT);
  pinMode(H3,OUTPUT);


  // Thermocouples
  pinMode(TC1,INPUT);
  pinMode(TC2, INPUT);

  // Thermoresistors
  pinMode(TEMP_2_PIN, INPUT);
  pinMode(TEMP_3_PIN, INPUT);
  pinMode(TEMP_4_PIN, INPUT);
}


void loop() {

  while(!start){
    if (Serial.available() > 0) {
      if(Serial.read()!='q'){
      delay(50);
      start=1;
      break;
      }
    }
  }

  int* commandStatePointer = receiveData(Serial, commandState);


  for(int i =0;i<4;i++){
    commandState[i] = commandStatePointer[i];
  }
  analogWrite(H1,(400*commandState[0])/400);
  analogWrite(H2,(400*commandState[1])/400);
  analogWrite(H3,(400*commandState[2])/400);
  analogWrite(STEP,commandState[2]/100);
  digitalWrite(ENABLE,1);
  digitalWrite(H1,1);


  sendState(Serial, commandState, false);

  // feedBackState[0] += 1;
  // feedBackState[1] +=2;
  // feedBackState[2] +=3;
  // feedBackState[3] +=4;

  sendState(Serial, feedBackState,true);
  delay(1000);
}
