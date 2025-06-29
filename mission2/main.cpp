#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}
#else
#include "car.cpp"

void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}
bool isValidNumber(char* checkNumber)
{
    if (*checkNumber != '\0')
    {
        printf("ERROR :: 숫자만 입력 가능\n");
        delay(800);
        return false;
    }

    return true;
}
bool isGoBack(int& step, int answer)
{
    // 처음으로 돌아가기
    if (answer == 0 && step == Run_Test)
    {
        step = CarType_Q;
        return false;
    }
    // 이전으로 돌아가기
    if (answer == 0 && step >= CarType_Q)
    {
        step -= 1;
        return false;
    }

    return true;
}

bool isValidAnswer(int step, int answer)
{
    if (step == CarType_Q && !(answer > CAR_TYPE_MIN && answer < CAR_TYPE_MAX))
    {
        printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
        delay(800);
        return false;
    }

    if (step == Engine_Q && !(answer >= ENGINE_MIN && answer < ENGINE_MAX))
    {
        printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
        delay(800);
        return false;
    }

    if (step == brakeSystem_Q && !(answer >= BREAK_MIN && answer < BREAK_MAX))
    {
        printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
        delay(800);
        return false;
    }

    if (step == SteeringSystem_Q && !(answer >= STREERING_MIN && answer < STREERING_MAX))
    {
        printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
        delay(800);
        return false;
    }

    if (step == Run_Test && !(answer >= COMMAND_MIN && answer < COMMAND_MAX))
    {
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
        delay(800);
        return false;
    }

    return true;
}

void runProducedCar(Car* car)
{
    if (car->checkRestrict() == false)
    {
        printf("자동차가 동작되지 않습니다\n");
        return;
    }

    if (car->isEngineBroken() == true)
    {
        printf("엔진이 고장나있습니다.\n");
        printf("자동차가 움직이지 않습니다.\n");
        return;
    }

    if (car->getType() == SEDAN)
        printf("Car Type : Sedan\n");
    if (car->getType() == SUV_TYPE)
        printf("Car Type : SUV\n");
    if (car->getType() == TRUCK)
        printf("Car Type : Truck\n");
    if (car->getEngine() == GM)
        printf("Engine : GM\n");
    if (car->getEngine() == TOYOTA)
        printf("Engine : TOYOTA\n");
    if (car->getEngine() == WIA)
        printf("Engine : WIA\n");
    if (car->getBreakSystem() == MANDO)
        printf("Brake System : Mando\n");
    if (car->getBreakSystem() == CONTINENTAL)
        printf("Brake System : Continental\n");
    if (car->getBreakSystem() == BOSCH_B)
        printf("Brake System : Bosch\n");
    if (car->getSteeringSystem() == BOSCH_S)
        printf("SteeringSystem : Bosch\n");
    if (car->getSteeringSystem() == MOBIS)
        printf("SteeringSystem : Mobis\n");

    printf("자동차가 동작됩니다.\n");
}

void handleStep(Car* car, int& step, int answer)
{
    if (step == Engine_Q)
    {
        car->setEngine(answer);
        printf("차량 엔진으로 %d을 선택하셨습니다.\n", answer);
        delay(800);
        step = brakeSystem_Q;
    }
    else if (step == brakeSystem_Q)
    {
        printf("차량 브레이크 시스템으로 %d을 선택하셨습니다.\n", answer);
        car->setBreakSystem(answer);
        delay(800);
        step = SteeringSystem_Q;
    }
    else if (step == SteeringSystem_Q)
    {
        car->setSteeringSystem(answer);
        printf("차량 스티어링 시스템으로 %d을 선택하셨습니다.\n", answer);
        delay(800);
        step = Run_Test;
    }
    else if (step == Run_Test && answer == RUN_COMMAND)
    {
        runProducedCar(car);
        delay(2000);
    }
    else if (step == Run_Test && answer == TEST_COMMAND)
    {
        printf("Test...\n");
        delay(1500);
        if (car->checkRestrict() == false) {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("CarType_Q: %d, Engine_Q: %d, brakeSystem_Q: %d, SteeringSystem_Q: %d", car->getType(), car->getEngine(), car->getBreakSystem(), car->getSteeringSystem());
        }
        else {
            printf("자동차 부품 조합 테스트 결과 : PASS\n");
        }

        delay(2000);
    }
}

int main()
{
    std::unique_ptr<Creator> creator;
    std::unique_ptr<Car> car;
    char buf[100];
    int step = CarType_Q;

    while (1)
    {
        if (step == CarType_Q)
        {
            printf(CLEAR_SCREEN);

            printf("        ______________\n");
            printf("       /|            | \n");
            printf("  ____/_|_____________|____\n");
            printf(" |                      O  |\n");
            printf(" '-(@)----------------(@)--'\n");
            printf("===============================\n");
            printf("어떤 차량 타입을 선택할까요?\n");
            printf("1. Sedan\n");
            printf("2. SUV\n");
            printf("3. Truck\n");
        }
        else if (step == Engine_Q)
        {
            printf(CLEAR_SCREEN);
            printf("어떤 엔진을 탑재할까요?\n");
            printf("0. 뒤로가기\n");
            printf("1. GM\n");
            printf("2. TOYOTA\n");
            printf("3. WIA\n");
            printf("4. 고장난 엔진\n");
        }
        else if (step == brakeSystem_Q)
        {
            printf(CLEAR_SCREEN);
            printf("어떤 제동장치를 선택할까요?\n");
            printf("0. 뒤로가기\n");
            printf("1. MANDO\n");
            printf("2. CONTINENTAL\n");
            printf("3. BOSCH\n");
        }
        else if (step == SteeringSystem_Q)
        {
            printf(CLEAR_SCREEN);
            printf("어떤 조향장치를 선택할까요?\n");
            printf("0. 뒤로가기\n");
            printf("1. BOSCH\n");
            printf("2. MOBIS\n");
        }
        else if (step == Run_Test)
        {
            printf(CLEAR_SCREEN);
            printf("멋진 차량이 완성되었습니다.\n");
            printf("어떤 동작을 할까요?\n");
            printf("0. 처음 화면으로 돌아가기\n");
            printf("1. RUN\n");
            printf("2. Test\n");
        }
        printf("===============================\n");

        printf("INPUT > ");
        fgets(buf, sizeof(buf), stdin);

        // 엔터 개행문자 제거
        char* context = nullptr;
        strtok_s(buf, "\r", &context);
        strtok_s(buf, "\n", &context);

        if (!strcmp(buf, "exit"))
        {
            printf("바이바이\n");
            break;
        }

		// 숫자로 된 대답인지 확인
		char* checkNumber;
		int answer = strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환

		// 입력받은 문자가 숫자가 아니라면
		if (isValidNumber(checkNumber) == false)
			continue;

		if (isValidAnswer(step, answer) == false)
			continue;

		// 이전 or 이전으로 돌아가기
		if (isGoBack(step, answer) == false)
			continue;

		if (step == CarType_Q) {
			if (answer == SEDAN)
                creator = std::make_unique<SedanCreator>();	
			else if (answer == SUV_TYPE)
				creator = std::make_unique<SUVCreator>();
			else if (answer == TRUCK)
				creator = std::make_unique<TruckCreator>();

            car = creator->factoryMethod();
			printf("차량 타입으로 %d을 선택하셨습니다.\n", answer);
			delay(1000);
			step = Engine_Q;
			continue;
		}

        handleStep(car.get(), step, answer);
    }
}

#endif