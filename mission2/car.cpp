#include "car.h"

class Car
{
private:

public:
	int mType = CAR_TYPE_MIN;
	int mEngine = ENGINE_MIN;
	int mBreakSystem = BREAK_MIN;
	int mSteeringSystem = STREERING_MIN;

	Car() {}
	~Car() {}

	void setEngine(int engine)
	{
		mEngine = engine;
	}

	void setBreakSystem(int breakSystem)
	{
		mBreakSystem = breakSystem;
	}

	void setStreeringSystem(int streeringSystem)
	{
		mSteeringSystem = streeringSystem;
	}

	int getType(void)
	{
		return mType;
	}

	int getEngine(void)
	{
		return mEngine;
	}

	int getBreakSystem(void)
	{
		return mBreakSystem;
	}

	int getSteeringSystem(void)
	{
		return mSteeringSystem;
	}

	bool isEngineBroken(void) {
		if (mEngine == BROKEN)
			return true;
		return false;
	}

	virtual bool checkRestrict(void)
	{
		printf("Car::checkRestrict\n");
		return true;
	}
};

class Sedan : public Car //부모 클래스 상속받음
{
public:
	Sedan() {
		printf("Sedan\n");
		mType = SEDAN;
	}
	~Sedan() {}

	virtual bool checkRestrict(void) {
		printf("Sedan::checkRestrict\n");
		if (mBreakSystem == BOSCH_B && mSteeringSystem != BOSCH_S)
			return false;
		if (mBreakSystem == CONTINENTAL)
			return false;
		return true;
	}
};

class SUV : public Car //부모 클래스 상속받음
{
public:
	SUV() {
		printf("SUV\n");
		mType = SUV_TYPE;
	}
	~SUV() {}

	virtual bool checkRestrict(void) {
		printf("SUV::checkRestrict\n");
		if (mBreakSystem == BOSCH_B && mSteeringSystem != BOSCH_S)
			return false;
		if (mEngine == TOYOTA)
			return false;

		return true;
	}
};

class Truck : public Car
{
public:
	Truck() {
		printf("Truck\n");
		mType = TRUCK;
	}
	~Truck() {}

	virtual bool checkRestrict(void) {
		printf("Truck::checkRestrict\n");
		if (mBreakSystem == BOSCH_B && mSteeringSystem != BOSCH_S)
			return false;
		if (mEngine == WIA || mBreakSystem == MANDO)
			return false;

		return true;
	}
};