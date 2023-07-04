#pragma once

#define BATTERYTEMP_LOWER_LIMIT  0

typedef enum 
{
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum 
{
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef enum 
{
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct 
{
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

BreachType inferBreach(double value, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
