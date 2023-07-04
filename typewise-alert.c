#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double upperLimit) 
{
  BreachType tempClassification = NORMAL;
  
  if(value < BATTERYTEMP_LOWER_LIMIT) 
  {
    tempClassification = TOO_LOW;
  }
  else if(value > upperLimit) 
  {
    tempClassification = TOO_HIGH;
  }
  else
  {
    /* Do Nothing; tempClassification is already initialized to NORMAL */
  }
  
  return tempClassification;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{
  int upperLimit = 0;

  /* Classify the upperlimit of temperature based on the Cooling type used in the system */
  if(PASSIVE_COOLING == coolingType) 
  {
    upperLimit = 35;
  }
  else if(HI_ACTIVE_COOLING == coolingType)
  {
    upperLimit = 45;
  }
  else /* MED_ACTIVE_COOLING */
  {
    upperLimit = 40;
  }

  return inferBreach(temperatureInC, upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    
  switch(alertTarget) 
  {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";
  switch(breachType) 
  {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
  }
}
