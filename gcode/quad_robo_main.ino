#include <Wire.h>
#include <ESP32Servo.h>


//DEFINE L1 15
//DEFINE L2 2
//DEFINE L3 4
//DEFINE L4 5 
//DEFINE R1 18
//DEFINE R2 19
//DEFINE R3 22
//DEFINE R4 23
enum ServoName : uint8_t {
  R1 = 0, 
  R2 = 1,
  L1 = 2,
  L2 = 3,
  R4 = 4,
  R3 = 5,
  L3 = 6,
  L4 = 7
};

Servo servos[8];
const int servoPins[8] = {18,19,15,2,23,22,4,5};
int8_t servoSubtrim[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() {

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  for (int i = 0; i < 8; i++) {
    servos[i].setPeriodHertz(50);
    servos[i].attach(servoPins[i], 732, 2929);
  }
  runStandPose(10);

}

void loop() {
  
  // runStandPose(10000);
  // sayHiAndDance();
  runStandPose(5000);

  
  // runPushupPose();
  // runCutePose();
  // runWalkPose(10,5);
  // runTurnRight(10,5);
  // runWalkBackward(10,5);
  // runTurnLeft(10,5);

  runFreakyPose();
  delay(20);

  

  
}

void setServoAngle(uint8_t channel, int angle) { 
  if (channel < 8) {
    int adjustedAngle = constrain(angle + servoSubtrim[channel], 0, 180);
    servos[channel].write(adjustedAngle);
    // servos[channel].write(angle);
    delay(20);
  }
}

void runStandPose(int d){
  setServoAngle(R1, 135); 
  setServoAngle(R2, 45); 
  setServoAngle(L1, 45); 
  setServoAngle(L2, 135); 
  setServoAngle(R4, 0); 
  setServoAngle(R3, 180); 
  setServoAngle(L3, 0); 
  setServoAngle(L4, 180);
  delay(d);
}


inline void runPushupPose() {
  Serial.println(F("PUSHUP"));
  runStandPose(0); 
  delayWithFace(200);
  setServoAngle(L1, 0);
  setServoAngle(R1, 180);
  setServoAngle(L3, 90);
  setServoAngle(R3, 90);
  delayWithFace(500);
  for (int i = 0; i < 4; i++) {
    setServoAngle(L3, 0);
    setServoAngle(R3, 180);
    delayWithFace(600);
    setServoAngle(L3, 90);
    setServoAngle(R3, 90);
    delayWithFace(500);
  }
  runStandPose(1);
}

inline void runCutePose() {
  Serial.println(F("CUTE"));
  runStandPose(0); 
  delayWithFace(200);
  setServoAngle(L2, 160);
  setServoAngle(R2, 20);
  setServoAngle(R4, 180);
  setServoAngle(L4, 0);

  setServoAngle(L1, 0);
  setServoAngle(R1, 180);
  setServoAngle(L3, 180);
  setServoAngle(R3, 0);
  delayWithFace(200);
  for (int i = 0; i < 5; i++) {
    setServoAngle(R4, 180);
    setServoAngle(L4, 45);
    delayWithFace(300);
    setServoAngle(R4, 135);
    setServoAngle(L4, 0);
    delayWithFace(300);
  }
  runStandPose(1);
}

void delayWithFace(int x){
  delay(x);
}

void runWavePose(){
  runStandPose(0); 
  delayWithFace(200);
  setServoAngle(R4, 80); setServoAngle(L3, 180); 
  setServoAngle(L2, 60); setServoAngle(R1, 100); 
  delayWithFace(200);
  setServoAngle(L3, 180); 
  delayWithFace(300); 
  for (int i = 0; i < 4; i++) { 
    setServoAngle(L3, 180); delayWithFace(300); 
    setServoAngle(L3, 100); delayWithFace(300); 
  } 
  runStandPose(1); 
}

void sayHiAndDance(){
  runStandPose(0);
  delayWithFace(200);
  setServoAngle(R1, 90); setServoAngle(R2, 90); setServoAngle(L1, 90); setServoAngle(L2, 90);
  setServoAngle(R4, 0); setServoAngle(R3, 180); setServoAngle(L3, 45); setServoAngle(L4, 135);
  for(int i=0; i<5; i++) {
    setServoAngle(R4, 45); setServoAngle(R3, 135); setServoAngle(L3, 0); setServoAngle(L4, 180);
    delayWithFace(300);
    setServoAngle(R4, 0); setServoAngle(R3, 180); setServoAngle(L3, 45); setServoAngle(L4, 135);
    delayWithFace(300);
  }
  runStandPose(1);

  delay(20);



  runWavePose();
  delay(20);
}

inline void runWalkPose(int d, int walkCycles) {
  Serial.println(F("WALK FWD"));
  // Initial Step
  setServoAngle(R3, 135); setServoAngle(L3, 45);
  setServoAngle(R2, 100); setServoAngle(L1, 25);
  delay(d*10);
  // if (!pressingCheck("forward", frameDelay)) return;
  
  for (int i = 0; i < walkCycles; i++) {
    setServoAngle(R3, 135); setServoAngle(L3, 0);
    delay(d);
    // if (!pressingCheck("forward", frameDelay)) return;
    setServoAngle(L4, 135); setServoAngle(L2, 90);
    setServoAngle(R4, 0); setServoAngle(R1, 180);
    delay(d);
    // if (!pressingCheck("forward", frameDelay)) return;    
    setServoAngle(R2, 45); setServoAngle(L1, 90);
    delay(d);
    // if (!pressingCheck("forward", frameDelay)) return;
    setServoAngle(R4, 45); setServoAngle(L4, 180);
    delay(d);
    // if (!pressingCheck("forward", frameDelay)) return;
    setServoAngle(R3, 180); setServoAngle(L3, 45);
    setServoAngle(R2, 90); setServoAngle(L1, 0);
    delay(d);
    // if (!pressingCheck("forward", frameDelay)) return;  
    setServoAngle(L2, 135); setServoAngle(R1, 90);
    delay(d);
    // if (!pressingCheck("forward", frameDelay)) return;
  }
  runStandPose(1);
}

inline void runWalkBackward(int d, int walkCycles) {
  delay(d);
  
  for (int i = 0; i < walkCycles; i++) {
    setServoAngle(R3, 135); setServoAngle(L3, 0);
    delay(d);                                   
    setServoAngle(L4, 135); setServoAngle(L2, 135);
    setServoAngle(R4, 0); setServoAngle(R1, 90);
    delay(d); 
    setServoAngle(R2, 90); setServoAngle(L1, 0);
    delay(d);
    setServoAngle(R4, 45); setServoAngle(L4, 180);
    delay(d);
    setServoAngle(R3, 180); setServoAngle(L3, 45);
    setServoAngle(R2, 45); setServoAngle(L1, 90);
    delay(d);
    setServoAngle(L2, 90); setServoAngle(R1, 180);
    delay(d);
  }
  runStandPose(1);
}


inline void runTurnLeft(int d, int walkCycles) {
  Serial.println(F("TURN LEFT"));
  for (int i = 0; i < walkCycles; i++) {
    //legset 1 (R1 L2)
    setServoAngle(R3, 135); setServoAngle(L4, 135); 
    delay(d);
    setServoAngle(R1, 180); setServoAngle(L2, 180); 
    delay(d);
    setServoAngle(R3, 180); setServoAngle(L4, 180); 
    delay(d);
    setServoAngle(R1, 135); setServoAngle(L2, 135);
    delay(d);
      //legset 2 (R2 L1)
    setServoAngle(R4, 45); setServoAngle(L3, 45); 
    delay(d);
    setServoAngle(R2, 90); setServoAngle(L1, 90); 
    delay(d);
    setServoAngle(R4, 0); setServoAngle(L3, 0); 
    delay(d);
    setServoAngle(R2, 45); setServoAngle(L1, 45);
    delay(d);  
  }
  runStandPose(1);
}

inline void runTurnRight(int d, int walkCycles) {

  Serial.println(F("TURN RIGHT"));

  for (int i = 0; i < walkCycles; i++) {
    //legset 2 (R2 L1)
    setServoAngle(R4, 45); setServoAngle(L3, 45); 
    delay(d);
    setServoAngle(R2, 0); setServoAngle(L1, 0); 
    delay(d);
    setServoAngle(R4, 0); setServoAngle(L3, 0); 
    delay(d);
    setServoAngle(R2, 45); setServoAngle(L1, 45);
    delay(d);  
    //legset 1 (R1 L2)
    setServoAngle(R3, 135); setServoAngle(L4, 135); 
    delay(d);
    setServoAngle(R1, 90); setServoAngle(L2, 90); 
    delay(d);
    setServoAngle(R3, 180); setServoAngle(L4, 180); 
    delay(d);
    setServoAngle(R1, 135); setServoAngle(L2, 135);
    delay(d);
  }
  runStandPose(1);
}

inline void runFreakyPose() {
  Serial.println(F("FREAKY"));
  runStandPose(0); 
  delayWithFace(200);
  setServoAngle(L1, 0);
  setServoAngle(R1, 180);
  setServoAngle(L2, 180);
  setServoAngle(R2, 0);
  setServoAngle(R4, 90);
  setServoAngle(R3, 0);
  delayWithFace(200);
  for (int i = 0; i < 3; i++) {
    setServoAngle(R3, 25);
    delayWithFace(400);
    setServoAngle(R3, 0);
    delayWithFace(400);
  }
  runStandPose(1);
}

