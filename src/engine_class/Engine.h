#pragma once
#include"IEngine.h"
class Engine : public IEngine
{
public:
	void Consume(double litres) override {};
	void Start() override { isRunning = true; };

	void Stop() override { isRunning = false; };
	bool getIsRunning() { return isRunning; }
	Engine() { isRunning = false; }

};