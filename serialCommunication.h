int commandState[4] = {0,0,0,0};
int feedBackState[4] = {0,0,0,0};
char keyToHeader[4] = "fstm";



void sendState(HardwareSerial& serial, int state[], bool isFeedback){

    String typeOfData = "";
    if(isFeedback){
        typeOfData = 'y';

    }
    else
        typeOfData+='r';

    int i;
    int *p;
    for(i = 0; i<4;i++){
        serial.println(typeOfData + keyToHeader[i] + String(state[i]) + 'x');
    }
}


int* receiveData(HardwareSerial& serial, int state[]){


  const int MAX_VALUES = 5; // maximum number of values in the input string
  const int MAX_VALUE_LENGTH = 5; // maximum length of each value
  char* incomingData[30];
  String inputString  = "";
  
  if(serial.available() > 0) {


    while (serial.available()) {
      char incomingChar = Serial.read();
      if (incomingChar == 'x') {            
        inputString = ""; 
      } 
      else if(incomingChar=='q'){
        serial.flush();
      }
      else {
        inputString += incomingChar; 
      }

    for(int i =0; i< 4;i++){
      if(inputString[0]==keyToHeader[i]){
        state[i] = inputString.substring(1).toInt();
      }
    }
   }
  }
  return state;
}

int waitUntilStart(HardwareSerial& serial){

    while(true){
        if (serial.available() > 0) {        
            serial.println("ACKx");
            return 1;
        }
    }

}