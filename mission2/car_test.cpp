#include "gmock/gmock.h"
#include "car.cpp"

TEST(Group, TC1) {
	std::unique_ptr<Car> car;

	car = std::make_unique<Car>();

	EXPECT_TRUE(car->checkRestrict());
}

TEST(Group, TC2) {
	std::unique_ptr<Car> car;

	car = std::make_unique<Sedan>();

	EXPECT_EQ(car->getType(), SEDAN);

	car->getEngine();

	car->setEngine(BROKEN);
	EXPECT_EQ(car->getEngine(), BROKEN);

	car->setBreakSystem(CONTINENTAL);
	EXPECT_EQ(car->getBreakSystem(), CONTINENTAL);

	car->setSteeringSystem(MOBIS);
	EXPECT_EQ(car->getSteeringSystem(), MOBIS);

	EXPECT_TRUE(car->isEngineBroken());

	car->setEngine(GM);
	EXPECT_FALSE(car->isEngineBroken());

	EXPECT_FALSE(car->checkRestrict());

	car->setBreakSystem(BOSCH_B);
	EXPECT_FALSE(car->checkRestrict());

	car->setBreakSystem(MANDO);
	EXPECT_TRUE(car->checkRestrict());
}

TEST(Group, TC3) {
	std::unique_ptr<Car> car;

	car = std::make_unique<SUV>();

	EXPECT_EQ(car->getType(), SUV_TYPE);

	car->getEngine();

	car->setEngine(BROKEN);
	EXPECT_EQ(car->getEngine(), BROKEN);

	car->setBreakSystem(MANDO);
	EXPECT_EQ(car->getBreakSystem(), MANDO);

	car->setSteeringSystem(MOBIS);
	EXPECT_EQ(car->getSteeringSystem(), MOBIS);

	EXPECT_TRUE(car->checkRestrict());

	car->setEngine(TOYOTA);
	EXPECT_FALSE(car->checkRestrict());

	car->setEngine(BROKEN);
	car->setBreakSystem(BOSCH_B);
	EXPECT_FALSE(car->checkRestrict());
}

TEST(Group, TC4) {
	std::unique_ptr<Car> car;

	car = std::make_unique<Truck>();

	EXPECT_EQ(car->getType(), TRUCK);

	car->getEngine();

	car->setEngine(BROKEN);
	EXPECT_EQ(car->getEngine(), BROKEN);

	car->setBreakSystem(MANDO);
	EXPECT_EQ(car->getBreakSystem(), MANDO);

	car->setSteeringSystem(MOBIS);
	EXPECT_EQ(car->getSteeringSystem(), MOBIS);

	EXPECT_FALSE(car->checkRestrict());

	car->setBreakSystem(CONTINENTAL);
	EXPECT_TRUE(car->checkRestrict());

	car->setBreakSystem(BOSCH_B);
	EXPECT_FALSE(car->checkRestrict());
}