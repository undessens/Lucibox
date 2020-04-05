/*
 *        LUCIBOX
 *        github.com/undessens/lucibox
 * 
 *        Author : Aurelien Conil
 *        github.com/aurelienconil
 */

  #include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
// touch includes
#include <MPR121.h>
#include <Wire.h>
#define MPR121_ADDR 0x5C
#define MPR121_INT 4

//NEOPIXEL
#define PIN            12
#define NUMPIXELS      12
#define MAXLUMINOSITY  1 

#define ANALOGIN 1    // Nombre de potentiometre
#define DIGITALIN 1   // Nombre de boutons
#define DIGITALOUT 4  // Nombre de leds
#define ANALOG_THRESH 10 


// ------------   POTENTIOMETRE --------------
int analogValue[ANALOGIN];
int analogPin[] = { A0, A1, A2,A3,A4,A5 };

// ------------   BOUTONS  ------------------
int digitalinValue[DIGITALIN];
int digitalinPin[] =  { 2,3,5,6,7,8 ,9};


// ------------   LEDS  --------------------
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB +  NEO_KHZ800);
int digitaloutValue[DIGITALOUT];
int pixelsColor[NUMPIXELS][3];
boolean pixelsOn[NUMPIXELS];
int digitaloutPin[] = {};

//-------------- COLORS --------------------
int globalR, globalG, globalB;
boolean isWaiting = true;



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
  
  //LED WS2812 INIT
   //SET defaulut color
  for(int i=0; i<4; i++){
    setColorNeoPixel(i*3, 2);
    setColorNeoPixel(i*3 + 1, 3);
    setColorNeoPixel(i*3 + 2, 7);
  }
  
  pixels.begin();
  for (int i= 0; i<DIGITALOUT; i++){
     setNeoPixel(i, 0,0,0);
  }
  pixels.show();
  setColor(0);
  pinMode(digitaloutPin[0], OUTPUT );
  pinMode(digitaloutPin[1], OUTPUT );

 //TOUCH SENSOR INIT
  if(!MPR121.begin(MPR121_ADDR)) Serial.println("error setting up MPR121");
  MPR121.setInterruptPin(MPR121_INT);
  MPR121.setTouchThreshold(255);
  MPR121.setReleaseThreshold(50);
   
   

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
    //Serial.println("Touch on touch: "+String(i)); 
  }

  if(MPR121.isNewRelease(i)){
    sendMessage(i + 30,0);
    //Serial.println("release on touch: "+String(i)); 
    //Serial.println("...");
  }

  
}

  
  
  // Serial receive message
  while(Serial.available()>2){
    
    int channel = (Serial.read()) ;
    int finalvalue = (Serial.read()) ;
    char end_of_line = Serial.read();
    
    if(end_of_line == 13 ){
      
         switch(channel){
             case 0:
                   setOneNeoPixel( finalvalue, 0, 25, 25);
              break;
             case 1:
                   //digitalWrite(digitaloutPin[1], finalvalue>0);
                   //setNeoPixel(1, 0, 0, finalvalue);
                break; 
            case 2: 
                   setColorNeoPixel(0,finalvalue);
                break;
           case 3:
                   setColorNeoPixel(1, finalvalue);
              break;
             case 4:
                   setColorNeoPixel(2,finalvalue);
                break; 
            case 5: 
                   setColorNeoPixel(3, finalvalue);
                break;
             case 6:
                   setColorNeoPixel(4,finalvalue);
              break;
             case 7:
                   setColorNeoPixel(5, finalvalue);
                break; 
            case 8: 
                   setColorNeoPixel(6, finalvalue);
                break;
            case 9:
                   setColorNeoPixel(7, finalvalue);
              break;
             case 10:
                   setColorNeoPixel(8,finalvalue);
                break; 
            case 11: 
                   setColorNeoPixel(9,finalvalue);
                break;
            case 12: 
                   setColorNeoPixel(10,finalvalue);
                break;
            case 13: 
                   setColorNeoPixel(11,finalvalue);
                break;
            case 14:
                 break;
            
          
             

             
             }


      
       
    }
   
   

    
  }

  if(!Serial){
      setWaveNeoPixel();
    }

    
  // Don't forget to update the LEDS when serial is over
  pixels.show();
  
  
  
  delay(5);
  
  
}


void sendMessage(int address, int value){

// Normal way to send a message

 Serial.print(char(address) );
 if(value ==14) value = 13;
 Serial.print(char(value));
 Serial.print(char(14));

}

void setNeoPixel(int channel, int r, int v, int b){

  int finalr, finalv, finalb;

  finalr = r*MAXLUMINOSITY;
  finalv = v*MAXLUMINOSITY;
  finalb = b*MAXLUMINOSITY;

  pixels.setPixelColor(NUMPIXELS-(channel+1), pixels.Color(finalr,finalv,finalb));
  
}

void setColorNeoPixel(int channel,int colorIndex){

  isWaiting = false;
  int finalr ;
  int finalg ;
  int finalb ;
  
  
  // if colorIndex is 1 or 0 : set On or Off
  if(colorIndex<2 && channel<NUMPIXELS){

       if(colorIndex==1) {
        pixelsOn[channel] = true;
       }else{
        pixelsOn[channel] = false;
       }

  }
  else{
   //if colorIndex >=0, set color
  
    switch( colorIndex){
        //RED
        case 2: finalr = 0; finalg = 25; finalb = 0;
          break;
        //LIGHT WHITE
        case 3: finalr = 2; finalg = 2; finalb = 2;
          break;
        //MEDIUM WHITE
        case 4: finalr = 30; finalg = 30; finalb = 30;
          break;
        //BLUE
        case 5: finalr = 0; finalg = 0; finalb = 25;
          break;
        // YELLOW
        case 6: finalr = 12; finalg = 12; finalb = 0;
          break;
       // GREEN
        case 7: finalr = 25; finalg = 0; finalb = 0;
          break;
    }

    pixelsColor[channel][0] = finalr;
    pixelsColor[channel][1] = finalg;
    pixelsColor[channel][2] = finalb;

  }

  //Finally draw pixel
  int mult = 0;
  if(pixelsOn[channel]) mult = 1;
  
  finalr = pixelsColor[channel][0] * mult;
  finalg = pixelsColor[channel][1] * mult;
  finalb = pixelsColor[channel][2] * mult;

   pixels.setPixelColor(NUMPIXELS-(channel+1), pixels.Color(finalr,finalg,finalb));


  
  
}

void setOneNeoPixel(int channel, int r, int v, int b ){

isWaiting = false;

for(int i=0; i<NUMPIXELS; i++){
  setNeoPixel(i, 0, 0, 0);
}

// Effect of filling bar
//for(int i=0; i<(channel+1); i++){
//  setNeoPixel(i, r, v, b);
//}

// Effect one pixel
 setNeoPixel(channel, r, v, b);


  
}

void setBarNeoPixel(int channel, int r, int v, int b ){

isWaiting = false;

for(int i=0; i<NUMPIXELS; i++){
  setNeoPixel(i, 0, 0, 0);
}

// Effect of filling bar
for(int i=0; i<(channel+1); i++){
  setNeoPixel(i, r, v, b);
}




  
}

void setWaveNeoPixel(){

  float freq = 0.4;
  float modulation = ( sin(freq*(millis()/1000.0f)*2*PI))/2.0 + 0.5;
  float finalR = globalR*modulation;
  float finalG = globalG*modulation;
  float finalB = globalB*modulation;
  
  for(int i=0; i<NUMPIXELS; i++){
  setNeoPixel(i, finalR, finalG, finalB);
  }

  
}

void setColor(int module){

isWaiting = true;

switch(module){

  case 0:
    globalR = 12;
    globalG = 12;
    globalB = 12;
  break;
  case 1:
    globalR = 12; //BLeu
    globalG = 0;
    globalB = 0;
  break;
  case 2:
    globalR = 0;
    globalG = 12; //Red
    globalB = 0;
  break;
  case 3:
    globalR = 0;
    globalG = 0;
    globalB = 12;
  break;
  case 4:
    globalR = 12;
    globalG = 12;
    globalB = 0;
  break;

  

}
}
