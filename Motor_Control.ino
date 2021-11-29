//library
#include "TractionControl.h"

//table
//int sinTable[257] =
//{0, 402, 804, 1205, 1606, 2006, 2404, 2801, 3196, 3590,
//3981, 4370, 4756, 5139, 5519, 5896, 6270, 6639, 7005, 7366,
//7723, 8075, 8423, 8765, 9102, 9434, 9760, 10080, 10394, 10701,
//11002, 11297, 11585, 11866, 12139, 12406, 12665, 12916, 13159, 13395,
//13622, 13842, 14053, 14255, 14449, 14634, 14811, 14978, 15136, 15286,
//15426, 15557, 15678, 15790, 15893, 15985, 16069, 16142, 16206, 16260,
//16305, 16339, 16364, 16379, 16384, 16379, 16364, 16339, 16305, 16260,
//16206, 16142, 16069, 15985, 15893, 15790, 15678, 15557, 15426, 15286,
//15136, 14978, 14811, 14634, 14449, 14255, 14053, 13842, 13622, 13395,
//13159, 12916, 12665, 12406, 12139, 11866, 11585, 11297, 11002, 10701,
//10394, 10080, 9760, 9434, 9102, 8765, 8423, 8075, 7723, 7366,
//7005, 6639, 6270, 5896, 5519, 5139, 4756, 4370, 3981,
//3590, 3196, 2801, 2404, 2006, 1606, 1205, 804, 402, 0,
//-402, -804, -1205, -1606, -2006, -2404, -2801, -3196, -3590, -3981,
//-4370, -4756, -5139, -5519, -5896, -6270, -6639, -7005, -7366, -7723,
//-8075, -8423, -8765, -9102, -9434, -9760, -10080, -10394, -10701, -11002,
//-11297, -11585, -11866, -12139, -12406, -12665, -12916, -13159, -13395, -13622,
//-13842, -14053, -14255, -14449, -14634, -14811, -14978, -15136, -15286, -15426,
//-15557, -15678, -15790, -15893, -15985, -16069, -16142, -16206, -16260, -16305,
//-16339, -16364, -16379, -16383, -16379, -16364, -16339, -16305, -16260, -16206,
//-16142, -16069, -15985, -15893, -15790, -15678, -15557, -15426, -15286, -15136,
//-14978, -14811, -14634, -14449, -14255, -14053, -13842, -13622, -13395, -13159,
//-12916, -12665, -12406, -12139, -11866, -11585, -11297, -11002, -10701, -10394,
//-10080, -9760, -9434, -9102, -8765, -8423, -8075, -7723, -7366, -7005,
//-6639, -6270, -5896, -5519, -5139, -4756, -4370, -3981, -3590, -3196,
//-2801, -2404, -2006, -1606, -1205, -804, -402, 0};
int sinTable[257] =
{127, 130, 133, 136, 139, 143, 146, 149, 152, 155, 158, 161, 164, 167, 170, 173, 176, 179, 182, 184, 187, 190, 193, 195, 198, 200, 203, 205, 208, 210, 213, 215, 217, 219, 221, 224, 226, 228, 229, 231, 233, 235, 236, 238, 239, 241, 242, 244, 245, 246, 247, 248, 249, 250, 251, 251, 252, 253, 253, 254, 254, 254, 254, 254, 255, 254, 254, 254, 254, 254, 253, 253, 252, 251, 251, 250, 249, 248, 247, 246, 245, 244, 242, 241, 239, 238, 236, 235, 233, 231, 229, 228, 226, 224, 221, 219, 217, 215, 213, 210, 208, 205, 203, 200, 198, 195, 193, 190, 187, 184, 182, 179, 176, 173, 170, 167, 164, 161, 158, 155, 152, 149, 146, 143, 139, 136, 133, 130, 127, 124, 121, 118, 115, 111, 108, 105, 102, 99, 96, 93, 90, 87, 84, 81, 78, 75, 72, 70, 67, 64, 61, 59, 56, 54, 51, 49, 46, 44, 41, 39, 37, 35, 33, 30, 28, 26, 25, 23, 21, 19, 18, 16, 15, 13, 12, 10, 9, 8, 7, 6, 5, 4, 3, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 15, 16, 18, 19, 21, 23, 25, 26, 28, 30, 33, 35, 37, 39, 41, 44, 46, 49, 51, 54, 56, 59, 61, 64, 67, 70, 72, 75, 78, 81, 84, 87, 90, 93, 96, 99, 102, 105, 108, 111, 115, 118, 121, 124, 127};
int triTable[257] =
{127, 129, 132, 134, 137, 139, 142, 144, 147, 149, 152, 154, 156, 159, 161, 164, 166, 169, 171, 174, 176, 179, 181, 184, 186, 188, 191, 193, 196, 198, 201, 203, 206, 208, 211, 213, 215, 218, 220, 223, 225, 228, 230, 233, 235, 238, 240, 243, 245, 247, 250, 252, 255, 257, 260, 262, 265, 267, 270, 272, 274, 277, 279, 282, 284, 282, 279, 277, 274, 272, 270, 267, 265, 262, 260, 257, 255, 252, 250, 247, 245, 243, 240, 238, 235, 233, 230, 228, 225, 223, 220, 218, 215, 213, 211, 208, 206, 203, 201, 198, 196, 193, 191, 188, 186, 184, 181, 179, 176, 174, 171, 169, 166, 164, 161, 159, 156, 154, 152, 149, 147, 144, 142, 139, 137, 134, 132, 129, 127, 125, 122, 120, 117, 115, 112, 110, 107, 105, 102, 100, 98, 95, 93, 90, 88, 85, 83, 80, 78, 75, 73, 70, 68, 66, 63, 61, 58, 56, 53, 51, 48, 46, 43, 41, 39, 36, 34, 31, 29, 26, 24, 21, 19, 16, 14, 11, 9, 7, 4, 2, 0, -2, -5, -7, -10, -12, -15, -17, -19, -22, -24, -27, -29, -27, -24, -22, -19, -17, -15, -12, -10, -7, -5, -2, 0, 2, 4, 7, 9, 11, 14, 16, 19, 21, 24, 26, 29, 31, 34, 36, 39, 41, 43, 46, 48, 51, 53, 56, 58, 61, 63, 66, 68, 70, 73, 75, 78, 80, 83, 85, 88, 90, 93, 95, 98, 100, 102, 105, 107, 110, 112, 115, 117, 120, 122, 125, 127};

//int triTable[257]
//{ 0, 315, 632, 947, 1264, 1579, 1894, 2212, 2526, 2842,
//  3159, 3473, 3791, 4105, 4421, 4738, 5052, 5370, 5685, 6000,
//  6317, 6631, 6949, 7264, 7579, 7896, 8210, 8527, 8843, 9158,
//  9476, 9790, 10106, 10423, 10737, 11055, 11369, 11685, 12002, 12315,
//  12634, 12948, 13264, 13582, 13894, 14213, 14528, 14842, 15161, 15473,
//  15791, 16108, 16420, 16741, 17052, 17370, 17688, 17997, 18322, 18630,
//  18947, 19273, 19566, 19920, 20130, 19920, 19566, 19273, 18947, 18630,
//  18322, 17997, 17688, 17370, 17052, 16741, 16420, 16108, 15791, 15473,
//  15161, 14842, 14528, 14213, 13894, 13582, 13264, 12948, 12634, 12315,
//  12002, 11685, 11369, 11055, 10737, 10423, 10106, 9790, 9476, 9158,
//  8843, 8527, 8210, 7896, 7579, 7264, 6949, 6631, 6317, 6000,
//  5685, 5370, 5052, 4738, 4421, 4105, 3791, 3473, 3159, 2842,
//  2526, 2212, 1894, 1579, 1264, 947, 632, 315, 0, -315,
//  -632, -947, -1264, -1579, -1894, -2212, -2526, -2842, -3159, -3473,
//  -3791, -4105, -4421, -4738, -5052, -5370, -5685, -6000, -6317, -6631,
//  -6949, -7264, -7579, -7896, -8210, -8527, -8843, -9158, -9476, -9790,
//  -10106, -10423, -10737, -11055, -11369, -11685, -12002, -12315, -12634, -12948,
//  -13264, -13582, -13894, -14213, -14528, -14842, -15161, -15473, -15791, -16108,
//  -16419, -16740, -17051, -17369, -17687, -17996, -18321, -18629, -18946, -19272,
//  -19565, -19919, -20129, -19919, -19565, -19272, -18946, -18629, -18321, -17996,
//  -17687, -17369, -17051, -16740, -16419, -16108, -15791, -15473, -15161, -14842,
//  -14528, -14213, -13894, -13582, -13264, -12948, -12634, -12315, -12002, -11685,
//  -11369, -11055, -10737, -10423, -10106, -9790, -9476, -9158, -8843, -8527,
//  -8210, -7896, -7579, -7264, -6949, -6631, -6317, -6000, -5685, -5370,
//  -5052, -4738, -4421, -4105, -3791, -3473, -3159, -2842, -2526, -2212,
//  -1894, -1579, -1264, -947, -632, -315, 0
//};

//timer
IntervalTimer masterClock;
//IntervalTimer spdCtrlTimer;
IntervalTimer sinTimer;
IntervalTimer triTimer;
IntervalTimer debuggerTimer;
IntervalTimer statusTimer;
//unsigned long oscTimer = 0;
unsigned long spdCtrlTimer = 0;
unsigned long spdCtrlTimeElapse = 0;
//unsigned long sinTimer = 0;
//unsigned long debuggerTimer = 0;


//osc data
volatile double sinVal = 0.0;
volatile double triVal = 0.0;
volatile double sinFreq = 0;
volatile double triFreq = 380;
volatile double sinAmp = 0.1; //modulation Index
volatile double triAmp = 0.5;
volatile double sampleIndexSin = 0.0;
volatile double sampleIndexTri = 0.0;

//values and status
const double pi = 3.1415926535897935384626;
volatile int tractionMode = 0;
//EB, B5, B4, B3, B2, B1, Cruise, Neutral, P1, P2, P3, P4
//-7, -6, -5, -4, -3, -2, -1,     0,       +1, +2, +3, +4
volatile int accRate[12] = {25, 50, 75, 100, 200, 400, 800, 1000000, 400, 200, 100, 45};//{25, 50, 75, 100, 150, 200, 800, 1000000, 1600, 500, 300, 150};
volatile int P = 0;
volatile int N = 0;
volatile int outVal1 = 0;  //volatile
volatile int outVal2 = 0;
bool EB = false;  //emergency brake status
volatile int sinTableIndex = 0;
volatile int triTableIndex = 0;
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
  //spdCtrlTimer.begin(spdCtrl, 50000);
  //debuggerTimer.begin(debugger, 50000);
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
  //tractionCtrl();
  //spdCtrl();
  //carrierCtrl();
  //pwmCtrl();
  //osc();
  //pwmOut();
  //debugger();
  //Serial.print("triTableIndex: ");
  //Serial.println(triTableIndex);
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
  //tractionCtrl();
  spdCtrl();
  carrierCtrl();
  pwmCtrl();


  //osc();
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
  //analogWrite(outPin0, sinTable[sinTableIndex]);
  //Serial.println(sinTable[sinTableIndex]);
  sinVal = sinAmp * sinTable[sinTableIndex];
  sinTableIndex++;
  if (sinTableIndex >= 255) {
    sinTableIndex = 0;
  }
}

void oscTri() {
  //analogWrite(outPin0, sinTable[sinTableIndex]);
  //Serial.println(sinTable[sinTableIndex]);
  triVal = triAmp * triTable[triTableIndex];
  triTableIndex++;
  if (triTableIndex >= 255) {
    triTableIndex = 0;
  }
}

//void osc() {
//if (micros() - oscTimer >= 25 ) {
//reset timer
//oscTimer = micros();

//calculate sin value
//  sinVal = sinAmp * sin(2 * pi * sinFreq * sampleIndexSin);
//  sampleIndexSin += 0.00005;
//  if (sampleIndexSin >= 1000) {
//    sampleIndexSin = 0;
//  }

//calculate tri value
//  double temp = 0;
//  for (int i = 1; i < 15; i += 2) {
//    temp += triAmp * (pow(-1, ((i - 1) / 2)) * (1 / (pow(i, 2))) * sin(2 * pi * triFreq * i * sampleIndexTri));
//  }
//  triVal = temp;
//  sampleIndexTri +=  0.00005;
//  if (sampleIndexTri >= 1000) {
//    sampleIndexTri = 0;
//  }

//  Serial.print(sinVal);
//  Serial.print("\t");
//  Serial.println(triVal);


//}
//}

void pwmOut() {
  //Symmetric
  double sinValCopy = 0;
  double triValCopy = 0;
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
  outVal1 = P - N;
  outVal2 = N - P;
  //    if (outVal1 < 0) {
  //      outVal1 = 0;
  //    }
  //    if (outVal2 < 0) {
  //      outVal2 = 0;
  //    }
  //  digitalWrite(outPin0, abs(outVal1));
  //  digitalWrite(outPin1, abs(-(outVal2)));
  if (outVal1 >= 0) {
    digitalWrite(outPin0, outVal1);
  }

  if (-(outVal2) >= 0) {
    digitalWrite(outPin1, -(outVal2));
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
  Serial.print("sample index sin: ");
  Serial.println(sampleIndexSin);
  Serial.print("sample index tri: ");
  Serial.println(sampleIndexTri);
  Serial.print("EB: ");
  Serial.println(EB);
  Serial.print("pwmOut: ");
  Serial.println(P - N);
  Serial.print("outVal1: ");
  Serial.println(outVal1);
  Serial.print("outVal2: ");
  Serial.println(outVal2);
  Serial.print("sinTableIndex: ");
  Serial.println(sinTableIndex);
  Serial.print("triTableIndex: ");
  Serial.println(triTableIndex);



  Serial.println();
}

void trainStatus(){

  
  if(tractionMode==-7){
    tractionPosition = "EB";
  }else if(tractionMode==-6){
    tractionPosition = "B5";
  }else if(tractionMode==-5){
    tractionPosition = "B4";
  }else if(tractionMode==-4){
    tractionPosition = "B3";
  }else if(tractionMode==-3){
    tractionPosition = "B2";
  }else if(tractionMode==-2){
    tractionPosition = "B1";
  }else if(tractionMode==-1){
    tractionPosition = "C";
  }else if(tractionMode==0){
    tractionPosition = "N";
  }else if(tractionMode==1){
    tractionPosition = "P1";
  }else if(tractionMode==2){
    tractionPosition = "P2";
  }else if(tractionMode==3){
    tractionPosition = "P3";
  }else if(tractionMode==4){
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
