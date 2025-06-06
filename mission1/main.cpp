#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

int stack[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
bool isValidCheck();
void delay(int ms);

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum CarType
{
    CAR_TYPE_MIN,
    SEDAN = 1,
    SUV,
    TRUCK,
    CAR_TYPE_MAX
};

enum Engine
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

int main()
{
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

        if (step == CarType_Q)
        {
            selectCarType(answer);
            delay(800);
            step = Engine_Q;
        }
        else if (step == Engine_Q)
        {
            selectEngine(answer);
            delay(800);
            step = brakeSystem_Q;
        }
        else if (step == brakeSystem_Q)
        {
            selectbrakeSystem(answer);
            delay(800);
            step = SteeringSystem_Q;
        }
        else if (step == SteeringSystem_Q)
        {
            selectSteeringSystem(answer);
            delay(800);
            step = Run_Test;
        }
        else if (step == Run_Test && answer == RUN_COMMAND)
        {
            runProducedCar();
            delay(2000);
        }
        else if (step == Run_Test && answer == TEST_COMMAND)
        {
            printf("Test...\n");
            delay(1500);
            if (isValidCheck() == false) {
                printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
                printf("CarType_Q: %d, Engine_Q: %d, brakeSystem_Q: %d, SteeringSystem_Q: %d", stack[CarType_Q], stack[Engine_Q], stack[brakeSystem_Q], stack[SteeringSystem_Q]);
            }
            else {
                printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
            }

            delay(2000);
        }
    }
}

void selectCarType(int answer)
{
    stack[CarType_Q] = answer;
    if (answer == SEDAN)
        printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
    if (answer == TOYOTA)
        printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
    if (answer == WIA)
        printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
}

void selectEngine(int answer)
{
    stack[Engine_Q] = answer;
    if (answer == GM)
        printf("GM ������ �����ϼ̽��ϴ�.\n");
    if (answer == TOYOTA)
        printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
    if (answer == WIA)
        printf("WIA ������ �����ϼ̽��ϴ�.\n");
}

void selectbrakeSystem(int answer)
{
    stack[brakeSystem_Q] = answer;
    if (answer == MANDO)
        printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == CONTINENTAL)
        printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == BOSCH_B)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

void selectSteeringSystem(int answer)
{
    stack[SteeringSystem_Q] = answer;
    if (answer == BOSCH_S)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == MOBIS)
        printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
}

bool isValidCheck()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        return false;
    }
    if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        return false;
    }
    if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        return false;
    }
    if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        return false;
    }
    if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        return false;
    }

    return true;
}

void runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
        return;
    }
 
	if (stack[Engine_Q] == BROKEN)
	{
		printf("������ ���峪�ֽ��ϴ�.\n");
		printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        return;
	}
	
	if (stack[CarType_Q] == SEDAN)
		printf("Car Type : Sedan\n");
	if (stack[CarType_Q] == SUV)
		printf("Car Type : SUV\n");
	if (stack[CarType_Q] == TRUCK)
		printf("Car Type : Truck\n");
	if (stack[Engine_Q] == GM)
		printf("Engine : GM\n");
	if (stack[Engine_Q] == TOYOTA)
		printf("Engine : TOYOTA\n");
	if (stack[Engine_Q] == WIA)
		printf("Engine : WIA\n");
	if (stack[brakeSystem_Q] == MANDO)
		printf("Brake System : Mando");
	if (stack[brakeSystem_Q] == CONTINENTAL)
		printf("Brake System : Continental\n");
	if (stack[brakeSystem_Q] == BOSCH_B)
		printf("Brake System : Bosch\n");
	if (stack[SteeringSystem_Q] == BOSCH_S)
		printf("SteeringSystem : Bosch\n");
	if (stack[SteeringSystem_Q] == MOBIS)
		printf("SteeringSystem : Mobis\n");

	printf("�ڵ����� ���۵˴ϴ�.\n");
}