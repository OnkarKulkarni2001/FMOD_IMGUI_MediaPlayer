#pragma once
#include "AudioUtils.hpp"
#include "fmod.hpp"
#include "fmod_errors.h"
#include <iostream>
using namespace std;

class FMODInitialization
{
public:
	FMODInitialization(FMOD::System* fmodSystem, FMOD_RESULT result);
	~FMODInitialization();
};

