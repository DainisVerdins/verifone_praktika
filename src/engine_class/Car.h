#pragma once
#include"ICar.h"
#include"IFuelTank.h"
#include"FuelTankDisplay.h"
#include"Engine.h"
class Car :public ICar
{
public:
	Car() {
		fuelTankDisplay= new FuelTankDisplay();
		fueltank = new FuelTank (20);
		engine = new Engine();
	};
	Car(double litres) {  
		fuelTankDisplay = new FuelTankDisplay();
		fueltank = new FuelTank(litres);
		engine = new Engine();
	};

	void EngineStart() override {
		if (fueltank->getFillLevel()!=0)
		{
			engine->Start();
		}
		 };
	void EngineStop() override { engine->Stop(); };
	void Refuel(double liters)override { fueltank->Refuel(liters); };
	void RunningIdle()override { fueltank->Consume(0.0003); }
	bool getEngineIsRunning()
	{
		engineIsRunning = engine->getIsRunning();
		return engineIsRunning;
	}

	FuelTank* fueltank;
	FuelTankDisplay* fuelTankDisplay;
	Engine* engine;
};

