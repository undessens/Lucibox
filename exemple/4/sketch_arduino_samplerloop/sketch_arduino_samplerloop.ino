/*
 *        LUCIBOX
 *        github.com/undessens/lucibox
 * 
 *        Author : Aurelien Conil
 *        github.com/aurelienconil
 */
// touch includes
#include <MPR121.h>
#include <Wire.h>
#define MPR121_ADDR 0x5C
#define MPR121_INT 4
 

#define ANALOGIN 0    // Nombre de potentiometre
#define DIGITALIN 0   // Nombre de boutons
#define DIGITALOUT 4  // Nombre de leds
#define ANALOG_THRESH 10 




// ------------   POTENTIOMETRE --------------
int analogValue[ANALOGIN];
int analogPin[] = { A0, A1, A2,A3,A4,A5 };

// ------------   BOUTONS  ------------------
int digitalinValue[DIGITALIN];
int digitalinPin[] =  { 2,3,4,5,6,7,8 ,9};


// ------------   LEDS  --------------------
int digitaloutValue[DIGITALOUT];
int digitaloutPin[] = { 10, 11, 12 , 13};

void setup(){

  Serial.begin(38400);
  while(!Serial);
  Serial.print("Lucibox");
     
    
  for( int i=0 ;i<ANALOGIN ; i++){
    
    pinMode(analogPin[i], INPUT);
    analogValue[i] = analogRead(analogPin[i]);
  
  }
  
  for(int i=0 ; i<DIGITALIN ; i++ ){
    pinMode(digitalinPin[i], INPUT_PULLUP);
    digitalinValue[i] = digitalRead(digitalinPin[i]);
  }
  
  
 for(int i=0 ; i<DIGITALOUT ; i++ ){
    pinMode(digitaloutPin[i], OUTPUT );
    digitaloutValue[i] = LOW;
    digitalWrite(digitaloutPin[i], HIGH);
    digitalWrite(digitaloutPin[i], LOW);
  }

  if(!MPR121.begin(MPR121_ADDR)) Serial.println("error setting up MPR121");
  MPR121.setInterruptPin(MPR121_INT);
  MPR121.setTouchThreshold(40);
  MPR121.setReleaseThreshold(20);
   
   

}

void loop(){
  
  // READ analog pin and write to serial
  for (int i= 0; i<ANALOGIN; i++){
   
    
    int newValueAn = analogRead(analogPin[i]);

    //Send message if value is different
    if ( abs( newValueAn - analogValue[i]) > ANALOG_THRESH ){
     
      analogValue[i] = newValueAn;
      sendMessage(i, map(newValueAn, 0, 1024, 0, 255 )); 
      
    }

  }

  //READ digital pin and write to serial
  for (int i= 0; i<DIGITALIN; i++){
    int newValueDi = !digitalRead(digitalinPin[i]);  
    if( newValueDi != digitalinValue[i] ){
    
      digitalinValue[i] = newValueDi;
      int finalValue = 0;
      if (newValueDi) finalValue = 255;
      sendMessage(i + 20, newValueDi*255); 
  
    }

    
  }

  //UPDATE TOUCH SENSOR
 MPR121.updateTouchData();
for (int i=0; i < 12; i++){

  if(MPR121.isNewTouch(i)){
    sendMessage(i + 30, 255); 
  }

  if(MPR121.isNewRelease(i)){
    sendMessage(i + 30,0); 
  }

  
}

  
  
  // Serial receive message
  while(Serial.available()>2){
    
    int channel = (Serial.read()) ;
    int value = (Serial.read()) ;
    char end_of_line = Serial.read();
    
    if(end_of_line == 13 ){
      
         switch(channel){
             case 0:
                    digitalWrite(digitaloutPin[0], value);
              break;
             case 1:
                   digitalWrite(digitaloutPin[1], value);
                break; 
            case 2: 
                   digitalWrite(digitaloutPin[2], value);
                break;
            case 3: 
                   digitalWrite(digitaloutPin[3], value);
                break; 
            case 4: 
                 digitalWrite(digitaloutPin[4], value);
                break; 
            case 5: 
                digitalWrite(digitaloutPin[5], value);
                break; 
            
          
             

             
             }


      
       
    }
   
   

    
  }
  
  
  
  delay(5);
  
  
}


void sendMessage(int address, int value){

// Normal way to send a message

 Serial.print(char(address) );
 if(value ==14) value = 13;
 Serial.print(char(value));
 Serial.print(char(14));

}
