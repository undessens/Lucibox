/*
 *        LUCIBOX MACHINE 2 : looper 4 channel
 *        MOON LOOPSTATION
 *        github.com/undessens/lucibox
 *        
 *        Author : Aurelien Conil
 *        Casemate Fablab de Grenoble
 */

 #include "Adafruit_NeoPixel.h"

//NEOPIXEL
#define PIN            12

#define NUMPIXELS      12
#define MAXLUMINOSITY  0.1


#define ANALOGIN 3    // Nombre de potentiometre
#define DIGITALIN 10   // Nombre de boutons
#define DIGITALOUT 0  // Nombre de leds
#define ANALOG_THRESH 10 

//--------------- NEOPIXEL ----------------
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB +  NEO_KHZ800);
int digitaloutValue[DIGITALOUT];
int digitaloutPin[] = {};

// ------------   POTENTIOMETRE --------------
int analogValue[ANALOGIN];
int analogPin[] = { A0, A1, A2};

// ------------   BOUTONS  ------------------
int digitalinValue[DIGITALIN];
int digitalinPin[] =  { 2,3,4,5,6,7,8, 9, 10, 11};

// Others
/* When Led song mode is on, neo pixel are display the current song.
 *  No others leds are use. The current input is 0
 * When an other event happen ( 1 or more ), then the Led song mode stop
 * and every led are clear before execute the command.
 */
boolean led_song_mode = false;



void setup(){

    Serial.begin(38400);
    while(!Serial);
    
   
  
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
  pinMode(digitaloutPin[0], OUTPUT );
  pinMode(digitaloutPin[1], OUTPUT );

   
      

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

    //Check Led Song Mode
    if(led_song_mode & (channel>0)){
      setOneNeoPixel( -1, 0, 0, 0); //Clear; 
      led_song_mode = false;
    }

    if(!led_song_mode & (channel==0)){
      led_song_mode = true;
    }

    //change Value because of led light power

    if(end_of_line == 13 ){
      
         switch(channel){
             case 0:
                   setOneNeoPixel( value, 0, 25, 25);
              break;
             case 1:
                   //digitalWrite(digitaloutPin[1], finalvalue>0);
                   //setNeoPixel(1, 0, 0, finalvalue);
                break; 
            case 2: 
                   setNeoPixel(0,finalvalue,0 ,0);
                break;
           case 3:
                   setNeoPixel(1, finalvalue/3,finalvalue/3,finalvalue/3);
              break;
             case 4:
                   setNeoPixel(2,0,finalvalue, 0);
                break; 
            case 5: 
                   setNeoPixel(3, finalvalue,0,0);
                break;
             case 6:
                   setNeoPixel(4,finalvalue/3,finalvalue/3,finalvalue/3);
              break;
             case 7:
                   setNeoPixel(5, 0,finalvalue,0);
                break; 
            case 8: 
                   setNeoPixel(6, finalvalue,0 ,0);
                break;
            case 9:
                   setNeoPixel(7, finalvalue/3,finalvalue/3,finalvalue/3);
              break;
             case 10:
                   setNeoPixel(8, 0,finalvalue,0);
                break; 
            case 11: 
                   setNeoPixel(9,finalvalue,0,0);
                break;
            case 12: 
                   setNeoPixel(10,finalvalue/3,finalvalue/3,finalvalue/3);
                break;
            case 13: 
                   setNeoPixel(11,0,finalvalue,0);
                break;
            case 14:
                 break;

            
          
             

             
             }


     
     
     
    }
   
   

    
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
  finalr = r*MAXLUMINOSITY;
  finalv = v*MAXLUMINOSITY;
  finalb = b*MAXLUMINOSITY;

  pixels.setPixelColor(channel, pixels.Color(finalv,finalr,finalb));
  


}

void setOneNeoPixel(int channel, int r, int v, int b ){

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
