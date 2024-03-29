#include <iostream>

#include "../src/Core.h"

#include "UnitTests.h"
#include "PresetTests.h"

int main()
{
	Onyx::ErrorHandler errorHandler(true, false);
	Onyx::Init(errorHandler);
	Onyx::Demo();
	Onyx::Terminate();
	
	return 0;
}
