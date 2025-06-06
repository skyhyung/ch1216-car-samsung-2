#include "car.h"

class Car
{
public:
	int mType = CAR_TYPE_MIN;
	int mEngine = ENGINE_MIN;
	int mBreakSystem = BREAK_MIN;
	int mSteeringSystem = STREERING_MIN;

	void setEngine(int engine)
	{
		mEngine = engine;
	}

	void setBreakSystem(int breakSystem)
	{
		mBreakSystem = breakSystem;
	}

	void setSteeringSystem(int streeringSystem)
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

	virtual bool checkRestrict() = 0;
	virtual ~Car() = default;
};

class Sedan : public Car //부모 클래스 상속받음
{
public:
	Sedan() {
		printf("Sedan\n");
		mType = SEDAN;
	}

	bool checkRestrict(void) override {
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

	bool checkRestrict(void) override {
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

	bool checkRestrict(void) override {
		printf("Truck::checkRestrict\n");
		if (mBreakSystem == BOSCH_B && mSteeringSystem != BOSCH_S)
			return false;
		if (mEngine == WIA || mBreakSystem == MANDO)
			return false;

		return true;
	}
};

class Creator {
public:
	virtual std::unique_ptr<Car> factoryMethod() = 0;
	virtual ~Creator() = default;
};

class SedanCreator : public Creator {
public:
	std::unique_ptr<Car> factoryMethod() override {
		return std::make_unique<Sedan>();
	}
};

class SUVCreator : public Creator {
public:
	std::unique_ptr<Car> factoryMethod() override {
		return std::make_unique<SUV>();
	}
};

class TruckCreator : public Creator {
public:
	std::unique_ptr<Car> factoryMethod() override {
		return std::make_unique<Truck>();
	}
};