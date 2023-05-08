#include "lclrobot.h"

void lclrobot::setup(){
    // Setup
    smblb.setupSmbl();
    recordingbutton =0;
    iteration =0;

}

void lclrobot::timluethrecord(){
    /******************* Record Data *******************/
    //int recording = 1;
    //int iteration =0;
    iteration=0;
    Serial.println("Started recording");
    while (recordingbutton == 1){
        // read data from all
        smblb.getPositions();
        // Copy data Here
        for (int i=0; i<smblb.motorlength; i++){
            positionarray[i][iteration] = smblb.positions[i];
           Serial.print(positionarray[i][iteration]);
           Serial.print(" ");
        }
        Serial.println();
        iteration++;
        delay(10);
        
        // Check if button is pressed again

        
    }
    /********************* Calculate Accelearations *****/

    

    /*********************Calculate Velocities **********/
    //calculate ableitung
    /*for (int i =0; i<15;i++){
        veloarray[i][0]=0;
    }
    s16 veloAkt=0;
    for (int i = 1; i<iteration;i++){
        for (int j=0;j<15;j++){
            veloAkt=positionarray[j][i]-positionarray[j-1][i-1];
            veloarray[j][i]=(s16)(veloAkt/0.01);
        }
    }*/
    //generate Array
    Serial.println("Recording ended");
    Serial.print(iteration);
    Serial.println(" Samples were recorded");
    

}

void lclrobot::traditionalProgramming(){

}

void lclrobot::playProgram(){
    Serial.print(iteration);
    Serial.println(" will be played");
    for (int i=0; i<iteration; i++){
       /* Serial.print(positionarray[0][i]);
        Serial.print(" ");
        Serial.println(positionarray[1][i]);*/
        for (int g=0; g<smblb.motorlength; g++){
            smblb.sms.WritePosEx(smblb.ids[g], positionarray[g][i], 800, 254); //舵机(ID1)以最高速度V=80(50*80步/秒)，加速度A=100(100*100步/秒^2)，运行至P1=4095位置
        }
        delay(10);
        /*Serial.print(" ");
        Serial.print(veloarray[0][iteration]);
        Serial.print(" ");
        Serial.println(veloarray[1][iteration]);*/
        //Serial.print(" ");
    }
}