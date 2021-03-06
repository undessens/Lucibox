/*
 *        LUCIBOX
 *        github.com/undessens/lucibox
 * 
 *        Author : Aurelien Conil
 *        Casemate Fablab de Grenoble
 */

 #include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

//NEOPIXEL
#define PIN            2

#define NUMPIXELS      12
#define MAXLUMINOSITY  1


#define ANALOGIN 1    // Nombre de potentiometre
#define DIGITALIN 8   // Nombre de boutons
#define DIGITALOUT 12  // Nombre de leds
#define ANALOG_THRESH 10 

//--------------- NEOPIXEL ----------------
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB +  NEO_KHZ800);


// ------------   POTENTIOMETRE --------------
int analogValue[ANALOGIN];
int analogPin[] = { A0, A1, A2,A3,A4,A5 };

// ------------   BOUTONS  ------------------
int digitalinValue[DIGITALIN];
int digitalinPin[] =  { 3,4,5,6,7,8,9,10,11};

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

  pixels.begin();
  for (int i= 0; i<DIGITALOUT; i++){
     setNeoPixel(i, 0,0,0);
    
  }
  pixels.show();
  setColor(2);


   
      

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
  
  
  // Serial receive message
  while(Serial.available()>2){
    
    int channel = (Serial.read()) ;
    int value = (Serial.read()) ;
    int finalvalue = value*255;
    char end_of_line = Serial.read();

    //change Value because of led light power

    if(end_of_line == 13 ){
      
         switch(channel){
             case 0:
                   //setNeoPixel(0, 0,finalvalue,0);
                   //digitalWrite(digitaloutPin[0], finalvalue>0);
              break;
             case 1:
                   //digitalWrite(digitaloutPin[1], finalvalue>0);
                   //setNeoPixel(1, 0, 0, finalvalue);
                break; 
            case 2: 
                   // TRUC 
                break;
             case 11: 
                   setBarNeoPixel(value, globalR, globalG, globalB);
                break;
            case 12: 
                   setOneNeoPixel(value,globalR,globalG,globalB);
                break;
            case 13: 
                   setColor(value);
                break;


            
          
             

             
             }


     
     
     
    }

    
   
   

    
  }

  if(isWaiting){
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

/*
//debug way to send a message
Serial.print("ad: ");
Serial.print(address);
Serial.print(" - val: ");
Serial.println(value);
 */
}

void setNeoPixel(int channel, int r, int v, int b){

  int finalr, finalv, finalb;
//  if( r == 0 ){
//    finalr= digitaloutValue[channel];
//  }else{
//    digitaloutValue[channel] = r;
//    finalr = r;
//  }
//  
//  if( v == 0 ){
//    finalv= digitaloutValue[channel+1];
//  }else{
//    digitaloutValue[channel+1] = v;
//    finalv = v;
//  }
//  
//  if( b == 0 ){
//    finalb= digitaloutValue[channel+2];
//  }else{
//    digitaloutValue[channel+2] = b;
//    finalb = b;
//  }

  finalr = r*MAXLUMINOSITY;
  finalv = v*MAXLUMINOSITY;
  finalb = b*MAXLUMINOSITY;

  pixels.setPixelColor(NUMPIXELS-(channel+1), pixels.Color(finalr,finalv,finalb));
  


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



