#include "CurieIMU.h"

boolean stepEventsEnabeled = true;   
int lastStepCount = 0;             

void setup() {
  Serial.begin(9600);
  while(!Serial) ;  
  CurieIMU.begin();
  CurieIMU.setStepDetectionMode(CURIE_IMU_STEP_MODE_SENSITIVE);
  CurieIMU.setStepCountEnabled(true);
  if (stepEventsEnabeled) {
    CurieIMU.attachInterrupt(eventCallback);
    CurieIMU.interrupts(CURIE_IMU_STEP);
    Serial.println("IMU initialisation complete, waiting for events...");
  }
}

void loop() {}

static void updateStepCount() {
  int stepCount = CurieIMU.getStepCount();
  if (stepCount != lastStepCount) {
    Serial.print("Step count: ");
    Serial.println(stepCount);
    lastStepCount = stepCount;
  }
}

static void eventCallback(void) {
  if (CurieIMU.stepsDetected())
    updateStepCount();
}
