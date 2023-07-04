#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) 
{
  BreachType tempClassification = NORMAL;
  
  if(value < lowerLimit) 
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
  int upperLimit = 0, lowerLimit = 0;

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
  
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

  if((NORMAL != breachType))
  {
    if(TO_CONTROLLER == alertTarget) 
    {
      sendToController(breachType);
    }
    else /*If controller not present; send the alert to email*/
    {
      sendToEmail(breachType);
    }
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
  printf("To: %s\nHi, the temperature is ", recepient);
  
  switch(breachType) 
  {
    case TOO_LOW:
      printf("too low\n");
      break;
    case TOO_HIGH:
      printf("too high\n");
      break;
    default:
      printf("normal\n");
      break;
  }
}
