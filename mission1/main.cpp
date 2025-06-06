#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

void selectCarType(struct car& car, int answer);
void selectEngine(struct car& car, int answer);
void selectbrakeSystem(struct car& car, int answer);
void selectSteeringSystem(struct car& car, int answer);
void runProducedCar(struct car& car);
bool isValidCheck(struct car& car);
void delay(int ms);

struct car {
    int type;
    int engine;
    int breakSystem;
    int steeringSystem;
};


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
    SUV,
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
        printf("ERROR :: ���ڸ� �Է� ����\n");
        delay(800);
        return false;
    }

    return true;
}
bool isGoBack(int& step, int answer)
{
    // ó������ ���ư���
    if (answer == 0 && step == Run_Test)
    {
        step = CarType_Q;
        return false;
    }
    // �������� ���ư���
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
        printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
        delay(800);
        return false;
    }

    if (step == Engine_Q && !(answer >= ENGINE_MIN && answer < ENGINE_MAX))
    {
        printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
        delay(800);
        return false;
    }

    if (step == brakeSystem_Q && !(answer >= BREAK_MIN && answer < BREAK_MAX))
    {
        printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
        delay(800);
        return false;
    }

    if (step == SteeringSystem_Q && !(answer >= STREERING_MIN && answer < STREERING_MAX))
    {
        printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
        delay(800);
        return false;
    }

    if (step == Run_Test && !(answer >= COMMAND_MIN && answer < COMMAND_MAX))
    {
        printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
        delay(800);
        return false;
    }

    return true;
}

void handleStep(struct car& car, int& step, int answer)
{
    if (step == CarType_Q)
    {
        selectCarType(car, answer);
        delay(800);
        step = Engine_Q;
    }
    else if (step == Engine_Q)
    {
        selectEngine(car, answer);
        delay(800);
        step = brakeSystem_Q;
    }
    else if (step == brakeSystem_Q)
    {
        selectbrakeSystem(car, answer);
        delay(800);
        step = SteeringSystem_Q;
    }
    else if (step == SteeringSystem_Q)
    {
        selectSteeringSystem(car, answer);
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
        if (isValidCheck(car) == false) {
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
            printf("CarType_Q: %d, Engine_Q: %d, brakeSystem_Q: %d, SteeringSystem_Q: %d", car.type, car.engine, car.breakSystem, car.steeringSystem);
        }
        else {
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
        }

        delay(2000);
    }
}

int main()
{
    struct car car = { 0 };
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
            printf("� ���� Ÿ���� �����ұ��?\n");
            printf("1. Sedan\n");
            printf("2. SUV\n");
            printf("3. Truck\n");
        }
        else if (step == Engine_Q)
        {
            printf(CLEAR_SCREEN);
            printf("� ������ ž���ұ��?\n");
            printf("0. �ڷΰ���\n");
            printf("1. GM\n");
            printf("2. TOYOTA\n");
            printf("3. WIA\n");
            printf("4. ���峭 ����\n");
        }
        else if (step == brakeSystem_Q)
        {
            printf(CLEAR_SCREEN);
            printf("� ������ġ�� �����ұ��?\n");
            printf("0. �ڷΰ���\n");
            printf("1. MANDO\n");
            printf("2. CONTINENTAL\n");
            printf("3. BOSCH\n");
        }
        else if (step == SteeringSystem_Q)
        {
            printf(CLEAR_SCREEN);
            printf("� ������ġ�� �����ұ��?\n");
            printf("0. �ڷΰ���\n");
            printf("1. BOSCH\n");
            printf("2. MOBIS\n");
        }
        else if (step == Run_Test)
        {
            printf(CLEAR_SCREEN);
            printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
            printf("� ������ �ұ��?\n");
            printf("0. ó�� ȭ������ ���ư���\n");
            printf("1. RUN\n");
            printf("2. Test\n");
        }
        printf("===============================\n");

        printf("INPUT > ");
        fgets(buf, sizeof(buf), stdin);

        // ���� ���๮�� ����
        char* context = nullptr;
        strtok_s(buf, "\r", &context);
        strtok_s(buf, "\n", &context);

        if (!strcmp(buf, "exit"))
        {
            printf("���̹���\n");
            break;
        }

        // ���ڷ� �� ������� Ȯ��
        char* checkNumber;
        int answer = strtol(buf, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ

        // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
        if(isValidNumber(checkNumber) == false)
            continue;

        if (isValidAnswer(step, answer) == false)
            continue;

        // ���� or �������� ���ư���
        if (isGoBack(step, answer) == false)
            continue;

        handleStep(car, step, answer);
    }
}

void selectCarType(struct car &car, int answer)
{
    car.type = answer;
    if (answer == SEDAN)
        printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
    if (answer == TOYOTA)
        printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
    if (answer == WIA)
        printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
}

void selectEngine(struct car& car, int answer)
{
    car.engine = answer;
    if (answer == GM)
        printf("GM ������ �����ϼ̽��ϴ�.\n");
    if (answer == TOYOTA)
        printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
    if (answer == WIA)
        printf("WIA ������ �����ϼ̽��ϴ�.\n");
}

void selectbrakeSystem(struct car& car, int answer)
{
    car.breakSystem = answer;
    if (answer == MANDO)
        printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == CONTINENTAL)
        printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == BOSCH_B)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

void selectSteeringSystem(struct car& car, int answer)
{
    car.steeringSystem = answer;
    if (answer == BOSCH_S)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == MOBIS)
        printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
}

bool isValidCheck(struct car& car)
{
    if (car.type == SEDAN && car.breakSystem == CONTINENTAL)
        return false;
    if (car.type == SUV && car.engine == TOYOTA)
        return false;
    if (car.type == TRUCK && car.engine == WIA)
        return false;
    if (car.type == TRUCK && car.breakSystem == MANDO)
        return false;
    if (car.breakSystem == BOSCH_B && car.steeringSystem != BOSCH_S)
        return false;

    return true;
}

void runProducedCar(struct car& car)
{
    if (isValidCheck(car) == false)
    {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
        return;
    }
 
	if (car.engine == BROKEN)
	{
		printf("������ ���峪�ֽ��ϴ�.\n");
		printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        return;
	}
	
	if (car.type == SEDAN)
		printf("Car Type : Sedan\n");
	if (car.type == SUV)
		printf("Car Type : SUV\n");
	if (car.type == TRUCK)
		printf("Car Type : Truck\n");
	if (car.engine == GM)
		printf("Engine : GM\n");
	if (car.engine == TOYOTA)
		printf("Engine : TOYOTA\n");
	if (car.engine == WIA)
		printf("Engine : WIA\n");
	if (car.breakSystem == MANDO)
		printf("Brake System : Mando");
	if (car.breakSystem == CONTINENTAL)
		printf("Brake System : Continental\n");
	if (car.breakSystem == BOSCH_B)
		printf("Brake System : Bosch\n");
	if (car.steeringSystem == BOSCH_S)
		printf("SteeringSystem : Bosch\n");
	if (car.steeringSystem == MOBIS)
		printf("SteeringSystem : Mobis\n");

	printf("�ڵ����� ���۵˴ϴ�.\n");
}