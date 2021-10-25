#pragma once

#include"IFuelTankDisplay.h"
#include"FuelTank.h"
class FuelTankDisplay : public IFuelTankDisplay
{
public:
    double getFillLevel()
    {
        fillLevel = fuelTank->getFillLevel();
        return fillLevel;
    }

    bool getIsComplete()
    {
        isComplete = fuelTank->getIsComplete();
        return isComplete;
    }

    bool getIsOnReserve()
    {
        isOnReserve = fuelTank->getIsOnReserve();
        return isOnReserve;
    }
    FuelTankDisplay()
    {

    }

    FuelTank* fuelTank;
};

