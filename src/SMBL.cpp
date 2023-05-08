#include "SMBL.h"


void smlbus::getAllIds(){
    motorlength = 0;
    for (int i = 1; i<15;i++){
        int ID = sms.Ping(i);
        if(ID!=-1){
            Serial.print("Servo ID:");
            Serial.println(ID, DEC);
            ids[motorlength] = i;
            motorlength++;
        }
    }
    Serial.print("Following number of motors were found");
    Serial.println(motorlength);
}

void smlbus::getPositions(){
    // loop over the Motors
    for (int i=0; i<motorlength;i++){
        s16 pos = sms.ReadPos((u8)ids[i]);        
            //Serial.println(pos, DEC);
            positions[i] = (int) pos;
       
    }
    // read from the Motors and write to array
}

void smlbus::setupSmbl () {
    Serial1.begin(115200);
    sms.pSerial = &Serial1;
    smlbus::getAllIds();
}

void smlbus::writePosition(){
    for (int i=0; i<motorlength;i++){
        sms.WritePosEx((u8)ids[i],(s16) writepositions[i], (u16) writespeeds[i], (u8) writeaccels[i] );
    }
}

void smlbus::disenableToruqe(int status){
    for (int i=0; i<motorlength;i++){
        sms.EnableTorque((u8)ids[i],(u8) status);
       // sms.WritePosEx((u8)ids[i],(s16) writepositions[i], (u16) writespeeds[i], (u8) writeaccels[i] );
    }
}
