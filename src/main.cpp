#include <Arduino.h>
#include "SMBL.h"
#include "lclrobot.h"
#include <Adafruit_NeoPixel.h>

#include <SCServo.h>

#define PIN       26
#define NUMPIXELS  7
#define Record_Button_Pin 5
#define Play_Button_Pin 6
#define OnOff_Button_Pin 4
#define brightness 10


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500

SMSBL sm;

lclrobot lcl;


typedef enum
{
    Idle,
    Recording,
    ProcessRecording,
    Play,
    Standby,
    Eempty,
    Akhil
} eSystemState;

eSystemState curretnState;

// void set_idle_led(){
//   pixels.clear();
//   pixels.setBrightness(brightness);
//   //pixels.setPixelColor(0, pixels.Color(167, 173, 0,10));
//   pixels.setPixelColor(0, 167, 173, 0);
//   pixels.setBrightness(brightness);
//   pixels.show();
// }

// Display buffer like
void like_buffer(int r, int g, int b, int loops=1, int delay_val=DELAYVAL, int brightness_val=brightness){
  // trying to make the LEDs to make a buffer like motion
  for (int j = 0; j < loops; j++){
    for (int i = 1; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(r,g,b));
    pixels.setBrightness(brightness_val);
    pixels.show();
    delay(delay_val);
    }
  }
}

void set_idle_led(){
  // Then clear and show that the robot is ready
  pixels.clear();
  pixels.setPixelColor(0, 167, 173, 0);
  pixels.setBrightness(brightness);
  pixels.show();  
}

void set_memory_led(){
  
  for(int i=1; i<NUMPIXELS; i++) {

    pixels.setPixelColor(i, pixels.Color(0, 101, 189));
    pixels.setBrightness(brightness);
    pixels.show();
    //delay(DELAYVAL);
  }
}

void set_recording_led(){
  pixels.setBrightness(brightness);
  for(int i=1; i<NUMPIXELS; i++) {

    pixels.setPixelColor(i, pixels.Color(162, 173, 0));
    pixels.setBrightness(brightness);
    pixels.show();
    //delay(DELAYVAL);
  }
}

void set_off_led(){
  pixels.clear();
  pixels.show();
}

void set_playing_led(){
  pixels.clear();
  // While playing show a buffering motion
  like_buffer(255, 165, 0);
  pixels.clear();
  for(int i=1; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(227, 114, 34));
    pixels.setBrightness(brightness);
    pixels.show();
  }
}

void recordingbutton(){
  
  delay(100);

  if (digitalRead(Record_Button_Pin)&& digitalRead(Play_Button_Pin)){
    if(curretnState == Idle || curretnState == Eempty){
        curretnState = Akhil;
        delay(1000);
        return;
    }
  }
  if (digitalRead(Record_Button_Pin)){
    //Serial.println("Recordinterrupt");
    if(curretnState == Idle || curretnState == Eempty){
      lcl.recordingbutton =1;
      curretnState = Recording;
      delay(100);
      return;
    }
    else if (curretnState == Recording){
      lcl.recordingbutton = 0;
      return;
    }
    
  }
  if (digitalRead(OnOff_Button_Pin)){
    if(curretnState == Standby) {
      curretnState = Eempty;
      set_idle_led();
      Serial.println("Emptymode");
      delay(1000);
      return;
    }
    if(curretnState == Eempty || curretnState == Idle) 
    {
      curretnState = Standby;
      Serial.println("Standby");
      set_off_led();
      delay(1000);
      return;
    }
  }
  if (digitalRead(Play_Button_Pin)){
    //Serial.println("Playinterrupt");
    if(curretnState == Idle){
      curretnState = Play;
      set_playing_led();
      Serial.println("Start Play");
      // Enable the Torque
      lcl.smblb.disenableToruqe(1);
      lcl.playProgram();
      lcl.smblb.disenableToruqe(0);
      Serial.println("End Play");
      curretnState = Idle;
      return;
      // Disable the Torque
    }
    
  }
}




void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  delay(1000);
  pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
  pinMode(Record_Button_Pin, INPUT_PULLDOWN);
  pinMode(Play_Button_Pin, INPUT_PULLDOWN);
  pinMode(OnOff_Button_Pin, INPUT_PULLDOWN);
  lcl.setup();
  attachInterrupt(digitalPinToInterrupt(Record_Button_Pin), recordingbutton, RISING);
  attachInterrupt(digitalPinToInterrupt(Play_Button_Pin), recordingbutton, RISING);
  attachInterrupt(digitalPinToInterrupt(OnOff_Button_Pin), recordingbutton, RISING);
  //attachInterrupt(digitalPinToInterrupt(Play_Button_Pin), playbutton, RISING);
  curretnState = Eempty;
  pixels.begin();
  Serial.println("Setup_abgeschlossen");

}

void loop()
{  
  switch(curretnState){
    case Standby:{
      //Serial.print("Standby");
      set_off_led();
      break;
    }
    case Idle:
    {
      set_memory_led();
      //Serial.println("Hallo");
      lcl.smblb.getPositions();
        // Copy data Here
        for (int i=0; i<lcl.smblb.motorlength; i++){
           
           Serial.print(lcl.smblb.positions[i]);
           Serial.print(" ");
        }
        Serial.println();
      break;
    }
    case Recording:
    {
      set_recording_led();
      Serial.println("Start Recording");
      lcl.timluethrecord();
      curretnState=Idle;
      break; 
    }
    case ProcessRecording:
    {
      Serial.println("Hallo");
      break;
    }
    case Play:
    {
      Serial.println("Hallo");
      break;
    }
    case Eempty:
    {
      lcl.iteration=0;
      break;
    }
    case Akhil:
    {
      s16 A[] = {3626, 1364, 3204, 891,2850};
      s16 B[] = {2721, 1914, 2629, 891,2850};

      u16 Speeds[]  = {750,10,10,10,10};
      u8 accels[]  = {100,100,100,100,100};

      u8 ids[] = {1,2,3,4,5};

      
      for (int g=0;g<3;g++){

     /* for (int i=0; i<lcl.smblb.motorlength; i++){
           
           lcl.smblb.sms.WritePosEx(lcl.smblb.ids[i], A[i], 8, 100);
           //Serial.print(lcl.smblb.positions[i]);
           //Serial.print(" ");

        }*/
       lcl.smblb.sms.SyncWritePosEx(ids, 5, A, Speeds, accels);
        delay(5000);
     /* for (int i=0; i<lcl.smblb.motorlength; i++){
           
           lcl.smblb.sms.WritePosEx(lcl.smblb.ids[i], B[i], 8, 100);
           //Serial.print(lcl.smblb.positions[i]);
           //Serial.print(" ");

        }*/
               lcl.smblb.sms.SyncWritePosEx(ids, 5, B, Speeds, accels);

        delay(5000);
      }
      lcl.smblb.disenableToruqe(0);
      curretnState = Idle;
      break;
    }
  }
  //Serial.println("Hallo");
  delay(10);  
}

