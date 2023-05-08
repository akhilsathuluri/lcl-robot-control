#ifndef lclrobot_h
#define lclrobot_h

#include <Arduino.h>
#include "SMBL.h"

class lclrobot {
    public:
        int name;
        smlbus smblb;
        void setup();
        void timluethrecord();
        void traditionalProgramming();
        s16 positionarray[15][6000];
        s16 veloarray[15][6000];
        void playProgram();

        int recordingbutton;
        int iteration;
};

#endif //lclrobot_h