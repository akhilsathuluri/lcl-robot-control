#ifndef SOME_HEADER_FILE_GUARD 
#define SOME_HEADER_FILE_GUARD

#include <Arduino.h>
#include <SCServo.h>

class smlbus {
    public:
        int ids[15];
        int positions[15];
        int writepositions[15];
        int writespeeds[15];
        int writeaccels[15];
        int motorlength;
        void getAllIds();
        void writePosition();
        void getPositions();
        void setupSmbl();
        void disenableToruqe(int status);
    
        SMSBL sms;

};

void setupSmbl ();
void getPositions ();
void timLueth();
void traditionalRecording();


#endif