#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <string.h>

using namespace std;

#define CLEAR_SCREEN "\033[H\033[2J"

enum questionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum carType
{
    CAR_TYPE_MIN,
    SEDAN = 1,
    SUV_TYPE,
    TRUCK,
    CAR_TYPE_MAX
};

enum engine
{
    ENGINE_MIN,
    GM = 1,
    TOYOTA,
    WIA,
    BROKEN,
    ENGINE_MAX
};

enum brakeSystem
{
    BREAK_MIN,
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B,
    BREAK_MAX
};

enum SteeringSystem
{
    STREERING_MIN,
    BOSCH_S = 1,
    MOBIS,
    STREERING_MAX
};

enum Command
{
    COMMAND_MIN,
    RUN_COMMAND = 1,
    TEST_COMMAND,
    COMMAND_MAX
};