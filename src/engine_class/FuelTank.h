#pragma once
#include"IFuelTank.h"
#include"Engine.h"
class FuelTank : public IFuelTank
{
public:
    void Consume(double liters) override
    {
        fillLevel -= liters;
        if (fillLevel <= 5)
            isOnReserve = true;
    }
    void Refuel(double liters) override
    {
        fillLevel += liters;
        if (fillLevel >= maxFuelLevel)
            fillLevel = maxFuelLevel;
            isComplete = true;
    }
    double getFillLevel()
    {
        return fillLevel;
    }
    double getIsOnReserve()
    {
        return isOnReserve;
    }
    double getIsComplete()
    {
        return isComplete;
    }
    FuelTank(double litres)
    {
        fillLevel = litres;
        engine = new Engine();
    }

    Engine* engine;

private:
    const int maxFuelLevel = 60.f;
};