//library
#include "TractionControl.h"

//table
int sinTable[257] = {
  0, 804, 1607, 2410, 3211, 4011, 4807, 5601, 6392, 7179, 7961, 8739, 9511, 10278, 11038, 11792,
  12539, 13278, 14009, 14732, 15446, 16150, 16845, 17530, 18204, 18867, 19519, 20159, 20787, 21402, 22004, 22594,
  23169, 23731, 24278, 24811, 25329, 25831, 26318, 26789, 27244, 27683, 28105, 28510, 28897, 29268, 29621, 29955,
  30272, 30571, 30851, 31113, 31356, 31580, 31785, 31970, 32137, 32284, 32412, 32520, 32609, 32678, 32727, 32757,
  32767, 32757, 32727, 32678, 32609, 32520, 32412, 32284, 32137, 31970, 31785, 31580, 31356, 31113, 30851, 30571,
  30272, 29955, 29621, 29268, 28897, 28510, 28105, 27683, 27244, 26789, 26318, 25831, 25329, 24811, 24278, 23731,
  23169, 22594, 22004, 21402, 20787, 20159, 19519, 18867, 18204, 17530, 16845, 16150, 15446, 14732, 14009, 13278,
  12539, 11792, 11038, 10278, 9511, 8739, 7961, 7179, 6392, 5601, 4807, 4011, 3211, 2410, 1607, 804,
  0, -804, -1607, -2410, -3211, -4011, -4807, -5601, -6392, -7179, -7961, -8739, -9511, -10278, -11038, -11792,
  -12539, -13278, -14009, -14732, -15446, -16150, -16845, -17530, -18204, -18867, -19519, -20159, -20787, -21402, -22004, -22594,
  -23169, -23731, -24278, -24811, -25329, -25831, -26318, -26789, -27244, -27683, -28105, -28510, -28897, -29268, -29621, -29955,
  -30272, -30571, -30851, -31113, -31356, -31580, -31785, -31970, -32137, -32284, -32412, -32520, -32609, -32678, -32727, -32757,
  -32767, -32757, -32727, -32678, -32609, -32520, -32412, -32284, -32137, -31970, -31785, -31580, -31356, -31113, -30851, -30571,
  -30272, -29955, -29621, -29268, -28897, -28510, -28105, -27683, -27244, -26789, -26318, -25831, -25329, -24811, -24278, -23731,
  -23169, -22594, -22004, -21402, -20787, -20159, -19519, -18867, -18204, -17530, -16845, -16150, -15446, -14732, -14009, -13278,
  -12539, -11792, -11038, -10278, -9511, -8739, -7961, -7179, -6392, -5601, -4807, -4011, -3211, -2410, -1607, -804,
  0
};
int triTable[257] = {
  0, 512, 1028, 1539, 2054, 2568, 3080, 3596, 4107, 4622, 5136, 5647, 6163, 6675, 7189, 7704,
  8215, 8731, 9243, 9756, 10272, 10782, 11298, 11811, 12323, 12840, 13350, 13866, 14379, 14891, 15407, 15918,
  16433, 16948, 17458, 17975, 18486, 19000, 19516, 20025, 20543, 21054, 21567, 22084, 22593, 23110, 23623, 24133,
  24653, 25160, 25678, 26192, 26700, 27222, 27727, 28244, 28762, 29264, 29793, 30294, 30809, 31338, 31815, 32391,
  32733, 32391, 31815, 31338, 30809, 30294, 29793, 29264, 28762, 28244, 27727, 27222, 26700, 26192, 25678, 25160,
  24653, 24133, 23623, 23110, 22593, 22084, 21567, 21054, 20543, 20025, 19516, 19000, 18486, 17975, 17458, 16948,
  16433, 15918, 15407, 14891, 14379, 13866, 13350, 12840, 12323, 11811, 11298, 10782, 10272, 9756, 9243, 8731,
  8215, 7704, 7189, 6675, 6163, 5647, 5136, 4622, 4107, 3596, 3080, 2568, 2054, 1539, 1028, 512,
  0, -512, -1028, -1539, -2054, -2568, -3080, -3596, -4107, -4622, -5136, -5647, -6163, -6675, -7189, -7704,
  -8215, -8731, -9243, -9756, -10272, -10782, -11298, -11811, -12323, -12840, -13350, -13866, -14379, -14891, -15407, -15918,
  -16433, -16948, -17458, -17975, -18486, -19000, -19516, -20025, -20543, -21054, -21567, -22084, -22593, -23110, -23623, -24133,
  -24653, -25160, -25678, -26192, -26700, -27222, -27727, -28244, -28762, -29264, -29793, -30294, -30809, -31338, -31815, -32391,
  -32733, -32391, -31815, -31338, -30809, -30294, -29793, -29264, -28762, -28244, -27727, -27222, -26700, -26192, -25678, -25160,
  -24653, -24133, -23623, -23110, -22593, -22084, -21567, -21054, -20543, -20025, -19516, -19000, -18486, -17975, -17458, -16948,
  -16433, -15918, -15407, -14891, -14379, -13866, -13350, -12840, -12323, -11811, -11298, -10782, -10272, -9756, -9243, -8731,
  -8215, -7704, -7189, -6675, -6163, -5647, -5136, -4622, -4107, -3596, -3080, -2568, -2054, -1539, -1028, -512,
  0
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
volatile double triAmp = 1;
volatile int sinTableIndex = 0;
volatile int triTableIndex = 0;
volatile double sinInterval = 0;
volatile double triInterval = 0;

//values and status
const double pi = 3.1415926535897935384626;
volatile int tractionMode = 0;
//EB, B5, B4, B3, B2, B1, Cruise, Neutral, P1, P2, P3, P4
//-7, -6, -5, -4, -3, -2, -1,     0,       +1, +2, +3, +4
volatile unsigned int accRate[12] = {32, 35, 50, 75, 150, 200, 800, 1000000, 400, 200, 75, 40};
volatile int P = 0;
volatile int N = 0;
volatile int outVal0 = 0;  //unsigned
volatile int outVal1 = 0;

//status
bool EB = false;  //emergency brake status
char *tractionPosition[] = {"EB", "B5", "B4", "B3", "B2", "B1", "C", "N", "P1", "P2", "P3", "P4"};
char *pwmMode[] = {"-", "Asynchronous", "Synchronous - 15 Pulses", "Synchronous - 9 Pulses", "Synchronous - 3 Pulses", "Synchronous - Wide 3 Pulse", "Synchronous - 1 Pulse"};
String pwmModeDisply = "";

//IO
int buttonSpdDn = 31;
int buttonSpdUp = 32;
int R160Pin = 33;
int R188Pin = 34;
int outPin0 = 35;
int outPin1 = 36;
int buttonPinEB = 37;

//class
TractionControl spdDn(buttonSpdDn, 0);
TractionControl spdUp(buttonSpdUp, 1);

void setup() {
  //serial setup
  Serial.begin(9600);

  //IO setup
  pinMode(buttonPinEB, INPUT);
  pinMode(R160Pin, INPUT);
  pinMode(R188Pin, INPUT);
  pinMode(outPin0, OUTPUT);
  pinMode(outPin1, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPinEB), ISR_EB, CHANGE);

  //object setup
  spdDn.pressHandler(onPress);
  spdUp.pressHandler(onPress);

  //timer setup
  masterClock.begin(master, 50);
  sinTimer.begin(oscSin, 151);
  triTimer.begin(oscTri, 151);
  //debuggerTimer.begin(debugger, 50000);
  statusTimer.begin(trainStatus, 50000);
}

void loop() {
  spdDn.process();
  spdUp.process();
  intervalUpdator();
}

void intervalUpdator() {
  sinInterval = ((1 / sinFreq) / 255) * 1000000;
  triInterval = ((1 / triFreq) / 255) * 1000000;
  sinTimer.update(sinInterval);
  triTimer.update(triInterval);
}

void master() {
  spdCtrl();
  carrierCtrl();
  pwmCtrl();
  pwmOut();
}

void onPress(int val) {
  if (val == 1 && tractionMode < 4  && EB != true) {
    tractionMode ++;
    delay(10);
  } else if (val == 0 && tractionMode > -7 && EB != true) {
    tractionMode --;
    delay(10);
  }
}

void spdCtrl() {
  if (spdCtrlTimer - spdCtrlTimeElapse >= accRate[(tractionMode + 7)] && tractionMode > 0) {
    spdCtrlTimeElapse = spdCtrlTimer;
    sinFreq += 0.01;
  } else if (spdCtrlTimer - spdCtrlTimeElapse >= accRate[(tractionMode + 7)] && tractionMode < 0) {
    spdCtrlTimeElapse = spdCtrlTimer;
    sinFreq -= 0.01;
  }

  if (sinFreq <= 0) {
    sinFreq = 0;
    EB = false; //reset the emergency brake
  }

  spdCtrlTimer++;
}

void carrierCtrl() {
  if (sinFreq == 0) {
    triAmp = 0;
    pwmModeDisply = pwmMode[0];
  } else if (digitalRead(R188Pin) == HIGH && sinFreq >= 67) {
    triAmp = 0;
  } else if (sinFreq > 0) {
    triAmp = 1;
  }

  if (digitalRead(R188Pin) == HIGH) {
    //R188
    if (sinFreq > 0 && sinFreq < 1.5) {
      triFreq = 250;
      pwmModeDisply = pwmMode[1];
    } else if (sinFreq >= 1.5 && sinFreq < 6.5) {
      triFreq = map(sinFreq, 1.5, 6.5, 250, 500);
    } else if (sinFreq >= 6.5 && sinFreq < 25) {
      triFreq = 500;
      pwmModeDisply = pwmMode[1];
    } else if (sinFreq >= 25 && sinFreq < 25.5 && tractionMode > 0) {
      triFreq = map(sinFreq, 25, 25.5, 550, 350);
    } else if (sinFreq >= 25 && sinFreq < 25.5 && tractionMode < 0) {
      triFreq = 500;
      pwmModeDisply = pwmMode[1];
    } else if (sinFreq >= 25.5 && sinFreq < 35) {
      triFreq = sinFreq * 15;
      pwmModeDisply = pwmMode[2];
    } else if (sinFreq >= 35 && sinFreq < 48) {
      triFreq = sinFreq * 9;
      pwmModeDisply = pwmMode[3];
    } else if (sinFreq >= 48 && sinFreq < 60) {
      triFreq = sinFreq * 3;
      pwmModeDisply = pwmMode[4];
    } else if (sinFreq >= 60 && sinFreq < 67) {
      triFreq = sinFreq * 7;
      pwmModeDisply = pwmMode[5];
    } else if (sinFreq >= 67) {
      triFreq = sinFreq * 7;
      pwmModeDisply = pwmMode[6];
    }
  } else if (digitalRead(R160Pin) == HIGH) {
    //R160
    if (sinFreq >= 0 and sinFreq<3.5 and tractionMode>0) {
      triFreq = 380;
    } else if (sinFreq >= 3.5 and sinFreq<7 and tractionMode>0) {
      triFreq = 665;
    } else if (sinFreq >= 0 and sinFreq < 7 and tractionMode < 0) {
      triFreq = 665;
    } else if (sinFreq >= 7 and sinFreq < 20) {
      triFreq = 1290;
    } else if (sinFreq >= 20 and sinFreq < 24) {
      triFreq = 1430;
    } else if (sinFreq >= 24 and sinFreq < 33) {
      triFreq = 1235;
    } else if (sinFreq >= 33 and sinFreq < 40) {
      triFreq = 1430;
    } else if (sinFreq >= 40 and sinFreq < 44) {
      triFreq = 1235;
    } else if (sinFreq >= 44 and sinFreq < 55) {
      triFreq = 1430;
    } else if (sinFreq >= 55 and sinFreq < 60) {
      triFreq = 1235;
    } else if (sinFreq >= 60 and sinFreq < 70) {
      triFreq = 1430;
    } else if (sinFreq >= 70 and sinFreq < 75) {
      triFreq = 1235;
    } else if (sinFreq >= 75) {
      triFreq = 1430;
    }
  }
}

void pwmCtrl() {
  if (digitalRead(R188Pin) == HIGH) {
    //R188
    if (sinFreq == 0 or tractionMode == 0) {  //or tractionMode == 0
      sinAmp = 0;
    } else if (sinFreq > 0 && sinFreq < 1.5) {  //asyn
      sinAmp = 0.1;
    } else if (sinFreq >= 1.5 && sinFreq < 25) {
      sinAmp = map(sinFreq, 1.5, 25, 0.1, 0.6);
    }
    else if (sinFreq >= 25 && sinFreq < 35) {  //15
      sinAmp = map(sinFreq, 25, 35, 0.3, 0.7);
    }
    else if (sinFreq >= 35 && sinFreq < 48) { //9
      sinAmp = map(sinFreq, 25, 35, 0.1, 0.3);
    } else if (sinFreq >= 48 && sinFreq < 60) { //3
      sinAmp = map(sinFreq, 48, 60, 0.5, 0.7);
    } else if (sinFreq >= 60 && sinFreq < 67) { //W3
      sinAmp = map(sinFreq, 60, 67, 1.2, 1.3);
    } else if (sinFreq >= 67) {  //1
      sinAmp = 1;
    }
  } else if (digitalRead(R160Pin) == HIGH) {
    //R160
    if (sinFreq == 0 or tractionMode == 0) {  //or tractionMode == 0
      sinAmp = 0;
    } else if (sinFreq >= 75) {
      sinAmp = 0.99;
    } else {
      sinAmp = map(sinFreq, 0, 75, 0.1, 0.98);
    }
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

  if (sinVal > triVal && sinFreq != 0) { //&& sinTable[sinTableIndex] > 0
    P = 1;
  } else {
    P = 0;
  }

  if (-sinVal > triVal && sinFreq != 0) { //&& sinTable[sinTableIndex] < 0
    N = 1;
  } else {
    N = 0;
  }

  outVal0 = P - N;
  outVal1 = N - P;

  if (outVal0 >= 0) {
    digitalWrite(outPin0, outVal0);
  } else {
    digitalWrite(outPin0, LOW);
  }

  if (outVal1 >= 0) {
    digitalWrite(outPin1, outVal1);
  } else {
    digitalWrite(outPin1, LOW);
  }
}

void ISR_EB() {
  EB = true;
  tractionMode = -7;
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
  Serial.println(sinTable[sinTableIndex]);
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
  Serial.print("tractionPosition: ");
  Serial.println(tractionPosition[(tractionMode + 7)]);
  Serial.print("pwmMode: ");
  Serial.println(pwmModeDisply);
  Serial.print("speed: ");
  Serial.println(sinFreq);



  Serial.println();
}
