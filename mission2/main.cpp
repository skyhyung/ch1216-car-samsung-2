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

void runProducedCar(Car* car)
{
    if (car->checkRestrict() == false)
    {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
        return;
    }

    if (car->isEngineBroken() == true)
    {
        printf("������ ���峪�ֽ��ϴ�.\n");
        printf("�ڵ����� �������� �ʽ��ϴ�.\n");
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

    printf("�ڵ����� ���۵˴ϴ�.\n");
}

void handleStep(Car* car, int& step, int answer)
{
    if (step == Engine_Q)
    {
        car->setEngine(answer);
        printf("���� �������� %d�� �����ϼ̽��ϴ�.\n", answer);
        delay(800);
        step = brakeSystem_Q;
    }
    else if (step == brakeSystem_Q)
    {
        printf("���� �극��ũ �ý������� %d�� �����ϼ̽��ϴ�.\n", answer);
        car->setBreakSystem(answer);
        delay(800);
        step = SteeringSystem_Q;
    }
    else if (step == SteeringSystem_Q)
    {
        car->setStreeringSystem(answer);
        printf("���� ��Ƽ� �ý������� %d�� �����ϼ̽��ϴ�.\n", answer);
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
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
            printf("CarType_Q: %d, Engine_Q: %d, brakeSystem_Q: %d, SteeringSystem_Q: %d", car->getType(), car->getEngine(), car->getBreakSystem(), car->getSteeringSystem());
        }
        else {
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
        }

        delay(2000);
    }
}

int main()
{
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
        if (isValidNumber(checkNumber) == false)
            continue;

        if (isValidAnswer(step, answer) == false)
            continue;

        // ���� or �������� ���ư���
        if (isGoBack(step, answer) == false)
            continue;

        if (step == CarType_Q) {
            if (answer == SEDAN)
                car = std::make_unique<Sedan>();
            else if (answer == SUV_TYPE)
                car = std::make_unique<SUV>();
            else if (answer == TRUCK)
                car = std::make_unique<Truck>();

            printf("���� Ÿ������ %d�� �����ϼ̽��ϴ�.\n", answer);
            delay(1000);
            step = Engine_Q;
            continue;
        }

        handleStep(car.get(), step, answer);
    }
}

#endif