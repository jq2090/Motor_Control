//library
#include "TractionControl.h"

//table
int sinTable[257] ={
127, 130, 133, 136, 139, 143, 146, 149, 152, 155, 158, 161, 164, 167, 170, 173, 
176, 179, 182, 184, 187, 190, 193, 195, 198, 200, 203, 205, 208, 210, 213, 215, 
217, 219, 221, 224, 226, 228, 229, 231, 233, 235, 236, 238, 239, 241, 242, 244, 
245, 246, 247, 248, 249, 250, 251, 251, 252, 253, 253, 254, 254, 254, 254, 254, 
255, 254, 254, 254, 254, 254, 253, 253, 252, 251, 251, 250, 249, 248, 247, 246, 
245, 244, 242, 241, 239, 238, 236, 235, 233, 231, 229, 228, 226, 224, 221, 219, 
217, 215, 213, 210, 208, 205, 203, 200, 198, 195, 193, 190, 187, 184, 182, 179, 
176, 173, 170, 167, 164, 161, 158, 155, 152, 149, 146, 143, 139, 136, 133, 130, 
127, 124, 121, 118, 115, 111, 108, 105, 102, 99, 96, 93, 90, 87, 84, 81, 
78, 75, 72, 70, 67, 64, 61, 59, 56, 54, 51, 49, 46, 44, 41, 39, 
37, 35, 33, 30, 28, 26, 25, 23, 21, 19, 18, 16, 15, 13, 12, 10, 
9, 8, 7, 6, 5, 4, 3, 3, 2, 1, 1, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 7, 8, 
9, 10, 12, 13, 15, 16, 18, 19, 21, 23, 25, 26, 28, 30, 33, 35, 
37, 39, 41, 44, 46, 49, 51, 54, 56, 59, 61, 64, 67, 70, 72, 75, 
78, 81, 84, 87, 90, 93, 96, 99, 102, 105, 108, 111, 115, 118, 121, 124, 127};
int triTable[257] ={
127, 129, 131, 133, 135, 137, 139, 141, 143, 145, 147, 149, 151, 153, 155, 157, 
159, 161, 163, 165, 167, 169, 171, 173, 175, 177, 179, 181, 183, 185, 187, 189, 
191, 193, 195, 197, 199, 201, 203, 205, 207, 209, 211, 213, 215, 217, 219, 221, 
223, 225, 227, 229, 231, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 
254, 253, 251, 249, 247, 245, 243, 241, 239, 237, 235, 233, 231, 229, 227, 225, 
223, 221, 219, 217, 215, 213, 211, 209, 207, 205, 203, 201, 199, 197, 195, 193, 
191, 189, 187, 185, 183, 181, 179, 177, 175, 173, 171, 169, 167, 165, 163, 161, 
159, 157, 155, 153, 151, 149, 147, 145, 143, 141, 139, 137, 135, 133, 131, 129, 
127, 125, 123, 121, 119, 117, 115, 113, 111, 109, 107, 105, 103, 101, 99, 97, 
95, 93, 91, 89, 87, 85, 83, 81, 79, 77, 75, 73, 71, 69, 67, 65, 
63, 61, 59, 57, 55, 53, 51, 49, 47, 45, 43, 41, 39, 37, 35, 33, 
31, 29, 27, 25, 23, 21, 19, 17, 15, 13, 11, 9, 7, 5, 3, 1, 
0, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 
31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 
63, 65, 67, 69, 71, 73, 75, 77, 79, 81, 83, 85, 87, 89, 91, 93, 
95, 97, 99, 101, 103, 105, 107, 109, 111, 113, 115, 117, 119, 121, 123, 125, 127
};

//timer
IntervalTimer masterClock;
IntervalTimer sinTimer;
IntervalTimer triTimer;
IntervalTimer debuggerTimer;
IntervalTimer statusTimer;
unsigned long spdCtrlTimer = 0;
unsigned long spdCtrlTimeElapse = 0;

//osc data
volatile double sinVal = 0.0;
volatile double triVal = 0.0;
volatile double sinFreq = 0;
volatile double triFreq = 380;
volatile double sinAmp = 0.1; //modulation Index
volatile double triAmp = 0.5;
volatile int sinTableIndex = 0;
volatile int triTableIndex = 0;

//values and status
const double pi = 3.1415926535897935384626;
volatile int tractionMode = 0;
//EB, B5, B4, B3, B2, B1, Cruise, Neutral, P1, P2, P3, P4
//-7, -6, -5, -4, -3, -2, -1,     0,       +1, +2, +3, +4
volatile int accRate[12] = {25, 50, 75, 100, 200, 400, 800, 1000000, 400, 200, 100, 45};
volatile int P = 0;
volatile int N = 0;
volatile int outVal0 = 0;  //unsigned
volatile int outVal1 = 0;

//status
bool EB = false;  //emergency brake status
String tractionPosition = "";
String pwmMode = "";

//IO
int buttonSpdDn = 31;
int buttonSpdUp = 32;
int outPin0 = 33;
int outPin1 = 34;
int buttonPinEB = 35;

//class
TractionControl spdDn(buttonSpdDn, 0);
TractionControl spdUp(buttonSpdUp, 1);

void setup() {
  //serial setup
  Serial.begin(9600);

  //IO setup
  pinMode(buttonPinEB, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPinEB), ISR_EB, CHANGE);

  //object setup
  spdDn.pressHandler(onPress);
  spdUp.pressHandler(onPress);

  //timer setup
  masterClock.begin(master, 50);
  sinTimer.begin(oscSin, 151);
  triTimer.begin(oscTri, 151);
  debuggerTimer.begin(debugger, 50000);
  statusTimer.begin(trainStatus, 50000);
}

void loop() {
  spdDn.process();
  spdUp.process();
  volatile double sinInterval = 0;
  volatile double triInterval = 0;
  sinInterval = ((1 / sinFreq) / 255) * 1000000;
  triInterval = ((1 / triFreq) / 255) * 1000000;
  sinTimer.update(sinInterval);
  triTimer.update(triInterval);
}

void onPress(int val) {
  if (val == 1 && tractionMode < 4  && EB != true) {
    tractionMode ++;
    delay(5);
  } else if (val == 0 && tractionMode > -7 && EB != true) {
    tractionMode --;
    delay(5);
  }
}

void master() {
  spdCtrl();
  carrierCtrl();
  pwmCtrl();
  pwmOut();
}

void spdCtrl() {
  if (spdCtrlTimer - spdCtrlTimeElapse >= accRate[(tractionMode + 7)] && tractionMode > 0) {
    spdCtrlTimeElapse = spdCtrlTimer;
    sinFreq += 0.01;
  } else if (spdCtrlTimer - spdCtrlTimeElapse >= accRate[(tractionMode + 7)] && tractionMode < 0) {
    spdCtrlTimeElapse = spdCtrlTimer;
    sinFreq -= 0.01;
  } else {
    //do nothing
  }

  if (sinFreq < 0) {
    sinFreq = 0;
  }

  //reset the emergency brake
  if (sinFreq <= 0) {
    sinFreq = 0;
    EB = false;
  }

  spdCtrlTimer++;

}

void carrierCtrl() {
  if (sinFreq == 0) {
    triAmp = 0;
    pwmMode = "-";
  } else if (sinFreq > 0) {
    triAmp = 0.5;
  }

  //R188
  if (sinFreq > 0 && sinFreq < 1.5) {
    triFreq = 250;
    pwmMode = "Asynchronous";
  } else if (sinFreq >= 1.5 && sinFreq < 6.5) {
    triFreq = map(sinFreq, 1.5, 6.5, 250, 500);
  } else if (sinFreq >= 6.5 && sinFreq < 25) {
    triFreq = 500;
    pwmMode = "Asynchronous";
  } else if (sinFreq >= 25 && sinFreq < 25.5 && tractionMode > 0) {
    triFreq = map(sinFreq, 25, 25.5, 550, 350);
  } else if (sinFreq >= 25 && sinFreq < 25.5 && tractionMode < 0) {
    triFreq = 500;
    pwmMode = "Asynchronous";
  } else if (sinFreq >= 25.5 && sinFreq < 35) {
    triFreq = sinFreq * 16;
    pwmMode = "Synchronous - 15 Pulses";
  } else if (sinFreq >= 35 && sinFreq < 48) {
    triFreq = sinFreq * 10;
    pwmMode = "Synchronous - 9 Pulses";
  } else if (sinFreq >= 48 && sinFreq < 60) {
    triFreq = sinFreq * 4;
    pwmMode = "Synchronous - 3 Pulses";
  } else if (sinFreq >= 60 && sinFreq < 67) {
    triFreq = sinFreq * 6;
    pwmMode = "Synchronous - Wide 3 Pulse";
  } else if (sinFreq >= 67) {
    triFreq = sinFreq * 6;
    pwmMode = "Synchronous - 1 Pulse";
  }

  //R160
  //  if (sinFreq >= 0 and sinFreq<3.5 and tractionMode>0) {
  //    triFreq = 380;
  //  } else if (sinFreq >= 3.5 and sinFreq<7 and tractionMode>0) {
  //    triFreq = 665;
  //  } else if (sinFreq >= 0 and sinFreq < 7 and tractionMode < 0) {
  //    triFreq = 665;
  //  } else if (sinFreq >= 7 and sinFreq < 20) {
  //    triFreq = 1290;
  //  } else if (sinFreq >= 20 and sinFreq < 24) {
  //    triFreq = 1430;
  //  } else if (sinFreq >= 24 and sinFreq < 33) {
  //    triFreq = 1235;
  //  } else if (sinFreq >= 33 and sinFreq < 40) {
  //    triFreq = 1430;
  //  } else if (sinFreq >= 40 and sinFreq < 44) {
  //    triFreq = 1235;
  //  } else if (sinFreq >= 44 and sinFreq < 55) {
  //    triFreq = 1430;
  //  } else if (sinFreq >= 55 and sinFreq < 60) {
  //    triFreq = 1235;
  //  } else if (sinFreq >= 60 and sinFreq < 70) {
  //    triFreq = 1430;
  //  } else if (sinFreq >= 70 and sinFreq < 75) {
  //    triFreq = 1235;
  //  } else if (sinFreq >= 75) {
  //    triFreq = 1430;
  //  }

}

void pwmCtrl() {
  //R188
  if (sinFreq == 0) {
    sinAmp = 0;
  } else if (sinFreq > 0 && sinFreq < 1.5) {
    sinAmp = 0.05;
  } else if (sinFreq >= 1.5 && sinFreq < 25) {
    sinAmp = map(sinFreq, 1.5, 25, 0.05, 0.3);
  }
  else if (sinFreq >= 25 && sinFreq < 35) {
    sinAmp = map(sinFreq, 25, 35, 0.2, 0.35);
  }
  else if (sinFreq >= 35 && sinFreq < 48) {
    sinAmp = map(sinFreq, 25, 35, 0.2, 0.35);
  } else if (sinFreq >= 48 && sinFreq < 60) {
    sinAmp = map(sinFreq, 48, 60, 0.3, 0.4);
  } else if (sinFreq >= 60 && sinFreq < 67) {
    sinAmp = map(sinFreq, 60, 67, 0.8, 0.9);
  } else if (sinFreq >= 67) {
    sinAmp = 1;
  }

  //R160
  //  if (sinFreq >= 75) {
  //    sinAmp = 0.49;
  //  } else {
  //    //noInterrupts();
  //    sinAmp = map(sinFreq, 0, 75, 0.1, 0.49);
  //    //interrupts();
  //  }

  if (tractionMode == 0) {
    sinAmp = 0;
  }
}

void oscSin() {
  sinVal = sinAmp * sinTable[sinTableIndex];
  sinTableIndex++;
  if (sinTableIndex >= 255) {
    sinTableIndex = 0;
  }
}

void oscTri() {
  triVal = triAmp * triTable[triTableIndex];
  triTableIndex++;
  if (triTableIndex >= 255) {
    triTableIndex = 0;
  }
}

void pwmOut() {
  //Symmetric
  //  double sinValCopy = 0;
  //  double triValCopy = 0;
  //  if (triVal == 0.5){
  //    Serial.println("Hello!");
  //  }
  //noInterrupts();
  //interrupts();

  if (sinVal > triVal && sinFreq != 0 && sinVal > 0) { //&& sinVal > 0
    P = 1;
  } else {
    P = 0;
  }

  if (-(sinVal) > triVal && sinFreq != 0 && sinVal < 0) { //&& sinVal < 0
    N = 1;
  } else {
    N = 0;
  }

  outVal0 = P - N;
  outVal1 = N - P;

  if (outVal0 >= 0) {
    digitalWrite(outPin0, outVal0);
  }

  if (-(outVal1) >= 0) {
    digitalWrite(outPin1, -(outVal1));
  }
}

void debugger() {
  Serial.print("spdCtrlTimer: ");
  Serial.println(spdCtrlTimer);
  Serial.print("spdCtrlTimeElapse: ");
  Serial.println(spdCtrlTimeElapse);
  Serial.print("sin amp: ");
  Serial.println(sinAmp);
  Serial.print("tri amp: ");
  Serial.println(triAmp);
  Serial.print("sin val: ");
  Serial.println(sinVal);
  Serial.print("tri val: ");
  Serial.println(triVal);
  Serial.print("sin Freq: ");
  Serial.println(sinFreq);
  Serial.print("tri Freq: ");
  Serial.println(triFreq);
  Serial.print("tractionMode: ");
  Serial.println(tractionMode);
  Serial.print("EB: ");
  Serial.println(EB);
  Serial.print("pwmOut: ");
  Serial.println(P - N);
  Serial.print("outVal0: ");
  Serial.println(outVal0);
  Serial.print("outVal1: ");
  Serial.println(outVal1);
  Serial.print("sinTableIndex: ");
  Serial.println(sinTableIndex);
  Serial.print("triTableIndex: ");
  Serial.println(triTableIndex);



  Serial.println();
}

void trainStatus() {


  if (tractionMode == -7) {
    tractionPosition = "EB";
  } else if (tractionMode == -6) {
    tractionPosition = "B5";
  } else if (tractionMode == -5) {
    tractionPosition = "B4";
  } else if (tractionMode == -4) {
    tractionPosition = "B3";
  } else if (tractionMode == -3) {
    tractionPosition = "B2";
  } else if (tractionMode == -2) {
    tractionPosition = "B1";
  } else if (tractionMode == -1) {
    tractionPosition = "C";
  } else if (tractionMode == 0) {
    tractionPosition = "N";
  } else if (tractionMode == 1) {
    tractionPosition = "P1";
  } else if (tractionMode == 2) {
    tractionPosition = "P2";
  } else if (tractionMode == 3) {
    tractionPosition = "P3";
  } else if (tractionMode == 4) {
    tractionPosition = "P4";
  }


  Serial.print("tractionPosition: ");
  Serial.println(tractionPosition);
  Serial.print("pwmMode: ");
  Serial.println(pwmMode);
  Serial.print("speed: ");
  Serial.println(sinFreq);
  //  Serial.print("EB: ");
  //  Serial.println(EB);



  Serial.println();
}

void ISR_EB() {
  EB = true;
  tractionMode = -7;
}
