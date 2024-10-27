#pragma once
#include "AudioUtils.hpp"
#include "fmod.hpp"
#include "fmod_errors.h"
#include <iostream>
using namespace std;

class FMODInitialization
{
public:
	FMODInitialization();
	~FMODInitialization();

	FMOD::System* Initialized(FMOD_RESULT &result);
};

