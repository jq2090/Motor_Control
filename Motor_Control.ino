//library
#include "TractionControl.h"

//table
int sinTable[257] =
{0, 402, 804, 1205, 1606, 2006, 2404, 2801, 3196, 3590, 
3981, 4370, 4756, 5139, 5519, 5896, 6270, 6639, 7005, 7366, 
7723, 8075, 8423, 8765, 9102, 9434, 9760, 10080, 10394, 10701, 
11002, 11297, 11585, 11866, 12139, 12406, 12665, 12916, 13159, 13395, 
13622, 13842, 14053, 14255, 14449, 14634, 14811, 14978, 15136, 15286, 
15426, 15557, 15678, 15790, 15893, 15985, 16069, 16142, 16206, 16260, 
16305, 16339, 16364, 16379, 16384, 16379, 16364, 16339, 16305, 16260, 
16206, 16142, 16069, 15985, 15893, 15790, 15678, 15557, 15426, 15286, 
15136, 14978, 14811, 14634, 14449, 14255, 14053, 13842, 13622, 13395, 
13159, 12916, 12665, 12406, 12139, 11866, 11585, 11297, 11002, 10701, 
10394, 10080, 9760, 9434, 9102, 8765, 8423, 8075, 7723, 7366, 
7005, 6639, 6270, 5896, 5519, 5139, 4756, 4370, 3981, 
3590, 3196, 2801, 2404, 2006, 1606, 1205, 804, 402, 0, 
-402, -804, -1205, -1606, -2006, -2404, -2801, -3196, -3590, -3981, 
-4370, -4756, -5139, -5519, -5896, -6270, -6639, -7005, -7366, -7723, 
-8075, -8423, -8765, -9102, -9434, -9760, -10080, -10394, -10701, -11002, 
-11297, -11585, -11866, -12139, -12406, -12665, -12916, -13159, -13395, -13622, 
-13842, -14053, -14255, -14449, -14634, -14811, -14978, -15136, -15286, -15426, 
-15557, -15678, -15790, -15893, -15985, -16069, -16142, -16206, -16260, -16305, 
-16339, -16364, -16379, -16383, -16379, -16364, -16339, -16305, -16260, -16206, 
-16142, -16069, -15985, -15893, -15790, -15678, -15557, -15426, -15286, -15136, 
-14978, -14811, -14634, -14449, -14255, -14053, -13842, -13622, -13395, -13159, 
-12916, -12665, -12406, -12139, -11866, -11585, -11297, -11002, -10701, -10394, 
-10080, -9760, -9434, -9102, -8765, -8423, -8075, -7723, -7366, -7005, 
-6639, -6270, -5896, -5519, -5139, -4756, -4370, -3981, -3590, -3196, 
-2801, -2404, -2006, -1606, -1205, -804, -402, 0};

int triTable[257]
{0, 315, 632, 947, 1264, 1579, 1894, 2212, 2526, 2842, 
3159, 3473, 3791, 4105, 4421, 4738, 5052, 5370, 5685, 6000, 
6317, 6631, 6949, 7264, 7579, 7896, 8210, 8527, 8843, 9158, 
9476, 9790, 10106, 10423, 10737, 11055, 11369, 11685, 12002, 12315, 
12634, 12948, 13264, 13582, 13894, 14213, 14528, 14842, 15161, 15473, 
15791, 16108, 16420, 16741, 17052, 17370, 17688, 17997, 18322, 18630, 
18947, 19273, 19566, 19920, 20130, 19920, 19566, 19273, 18947, 18630, 
18322, 17997, 17688, 17370, 17052, 16741, 16420, 16108, 15791, 15473, 
15161, 14842, 14528, 14213, 13894, 13582, 13264, 12948, 12634, 12315, 
12002, 11685, 11369, 11055, 10737, 10423, 10106, 9790, 9476, 9158, 
8843, 8527, 8210, 7896, 7579, 7264, 6949, 6631, 6317, 6000, 
5685, 5370, 5052, 4738, 4421, 4105, 3791, 3473, 3159, 2842, 
2526, 2212, 1894, 1579, 1264, 947, 632, 315, 0, -315, 
-632, -947, -1264, -1579, -1894, -2212, -2526, -2842, -3159, -3473, 
-3791, -4105, -4421, -4738, -5052, -5370, -5685, -6000, -6317, -6631, 
-6949, -7264, -7579, -7896, -8210, -8527, -8843, -9158, -9476, -9790, 
-10106, -10423, -10737, -11055, -11369, -11685, -12002, -12315, -12634, -12948, 
-13264, -13582, -13894, -14213, -14528, -14842, -15161, -15473, -15791, -16108, 
-16419, -16740, -17051, -17369, -17687, -17996, -18321, -18629, -18946, -19272, 
-19565, -19919, -20129, -19919, -19565, -19272, -18946, -18629, -18321, -17996, 
-17687, -17369, -17051, -16740, -16419, -16108, -15791, -15473, -15161, -14842, 
-14528, -14213, -13894, -13582, -13264, -12948, -12634, -12315, -12002, -11685, 
-11369, -11055, -10737, -10423, -10106, -9790, -9476, -9158, -8843, -8527, 
-8210, -7896, -7579, -7264, -6949, -6631, -6317, -6000, -5685, -5370, 
-5052, -4738, -4421, -4105, -3791, -3473, -3159, -2842, -2526, -2212, 
-1894, -1579, -1264, -947, -632, -315, 0};

//timer
IntervalTimer masterClock;
//IntervalTimer spdCtrlTimer;
IntervalTimer debuggerTimer;
//unsigned long oscTimer = 0;
unsigned long spdCtrlTimer = 0;
unsigned long spdCtrlTimeElapse = 0;
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
volatile int accRate[12] = {25, 50, 75, 100, 150, 200, 800, 1000000, 800, 250, 150, 50};//{25, 50, 75, 100, 150, 200, 800, 1000000, 1600, 500, 300, 150};
volatile int P = 0;
volatile int N = 0;
bool EB = false;  //emergency brake status

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
  //spdCtrlTimer.begin(spdCtrl, 50000);
  //debuggerTimer.begin(debugger, 50000);
}

void loop() {
  spdDn.process();
  spdUp.process();
  //tractionCtrl();
  //spdCtrl();
  //carrierCtrl();
  //pwmCtrl();
  //osc();
  //pwmOut();
  //debugger();
}

void onPress(int val) {
  if (val == 1 && tractionMode < 4) {
    tractionMode ++;
    delay(5);
  } else if (val == 0 && tractionMode > -7) {
    tractionMode --;
    delay(5);
  }
}

void master() {
  //tractionCtrl();
  spdCtrl();
  carrierCtrl();
  pwmCtrl();
  osc();
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
  } else if (sinFreq > 0) {
    triAmp = 0.5;
  }

  if (sinFreq >= 0 && sinFreq < 1.5) {
    triFreq = 250;
  } else if (sinFreq >= 1.5 && sinFreq < 6.5) {
    triFreq = map(sinFreq, 1.5, 6.5, 250, 500);
  } else if (sinFreq >= 6.5 && sinFreq < 25) {
    triFreq = 500;
  } else if (sinFreq >= 25 && sinFreq < 25.5 && tractionMode > 0) {
    triFreq = map(sinFreq, 25, 25.5, 550, 350);
  } else if (sinFreq >= 25 && sinFreq < 25.5 && tractionMode < 0) {
    triFreq = 500;
  } else if (sinFreq >= 25.5 && sinFreq < 35) {
    triFreq = sinFreq * 16;
  } else if (sinFreq >= 35 && sinFreq < 48) {
    triFreq = sinFreq * 10;
  } else if (sinFreq >= 48 && sinFreq < 60) {
    triFreq = sinFreq * 4;
  } else if (sinFreq >= 60 && sinFreq < 67) {
    triFreq = sinFreq * 6;
  } else if (sinFreq >= 67) {
    triFreq = sinFreq * 6;
  }
}

void pwmCtrl() {
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
    sinAmp = map(sinFreq, 60, 67, 0.7, 0.75);
  } else if (sinFreq >= 67) {
    sinAmp = 1;
  }
}

void osc() {
  //if (micros() - oscTimer >= 25 ) {
  //reset timer
  //oscTimer = micros();

  //calculate sin value
  sinVal = sinAmp * sin(2 * pi * sinFreq * sampleIndexSin);
  sampleIndexSin += 0.00005;
  if (sampleIndexSin >= 1000) {
    sampleIndexSin = 0;
  }

  //calculate tri value
  double temp = 0;
  for (int i = 1; i < 15; i += 2) {
    temp += triAmp * (pow(-1, ((i - 1) / 2)) * (1 / (pow(i, 2))) * sin(2 * pi * triFreq * i * sampleIndexTri));
  }
  triVal = temp;
  sampleIndexTri +=  0.00005;
  
  Serial.print(sinVal);
  Serial.print("\t");
  Serial.println(triVal);
  
  if (sampleIndexTri >= 1000) {
    sampleIndexTri = 0;
  }
  //}
}

void pwmOut() {
  //Symmetric
  double sinValCopy = 0;
  double triValCopy = 0;
//  if (triVal == 0.5){
//    Serial.println("Hello!");
//  }
  //noInterrupts();
  
  //interrupts();
  
  if (sinVal > triVal && sinFreq != 0 ) { //&& sinVal > 0
    P = 1;
  } else {
    P = 0;
  }

  if (-(sinVal) > triVal && sinFreq != 0 ) { //&& -(sinVal) > 0
    N = 1;
  } else {
    N = 0;
  }
  int outVal1 = 0;
  int outVal2 = 0;
  outVal1 = P - N;
  outVal2 = N - P;
  //    if (outVal1 < 0) {
  //      outVal1 = 0;
  //    }
  //    if (outVal2 < 0) {
  //      outVal2 = 0;
  //    }

  digitalWrite(outPin0, abs(outVal1));
  digitalWrite(outPin1, abs(outVal2));
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

  Serial.println();
}

void ISR_EB() {
  EB = true;
  tractionMode = -8;
}
