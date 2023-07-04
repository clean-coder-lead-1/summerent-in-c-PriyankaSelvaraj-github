#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(-1, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(0, 20, 30)  == TOO_LOW);
  REQUIRE(inferBreach(19, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(20, 20, 30) == NORMAL);
  REQUIRE(inferBreach(21, 20, 30) == NORMAL);
  REQUIRE(inferBreach(29, 20, 30) == NORMAL);
  REQUIRE(inferBreach(30, 20, 30) == NORMAL);
  REQUIRE(inferBreach(31, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(50, 20, 30) == TOO_HIGH);
}

TEST_CASE("infers the breach according to cooling type") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 35) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING , 35) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING , 35) == NORMAL);

  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 36) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING , 36) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING , 36) == NORMAL);

  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 41) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING , 41) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING , 41) == NORMAL);
  
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 46) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING , 46) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING , 46) == TOO_HIGH);
}
