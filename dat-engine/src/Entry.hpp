#pragma once
#include "Core/Engine/Engine.hpp"

extern dat::dat_unique<dat::DatEngine> CreateEngine();

int main(int argc, char** argv)
{
	using namespace dat;

	platform::InitializePlatform();

	logger::InitializeLogger();

	dat_unique<DatEngine> engine = CreateEngine();
	engine->Run();
}