#include "FMODInitialization.h"


FMODInitialization::FMODInitialization() {
	result = FMOD::System_Create(&fmodSystem);
	if (result != FMOD_OK) {
		cout << "System creation error! " << FMOD_ErrorString(result) << endl;
		CheckError(result);
		return;
	}
	result = fmodSystem->init(512, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) {
		cout << "FMOD initialization error! " << FMOD_ErrorString(result) << endl;
		return;
	}
}



FMODInitialization::~FMODInitialization() {

}

FMOD::System* FMODInitialization::Initialized(FMOD_RESULT& resultOut) {
	resultOut = this->result;
	return fmodSystem;
}
