#include "FMODInitialization.h"


FMODInitialization::FMODInitialization() {
	result = FMOD::System_Create(&fmodSystem);
	if (result != FMOD_OK) {
		cout << "System creation error! " << FMOD_ErrorString(result) << endl;
	}
	else {
		cout << "System created successfully!" << endl;
	}

	result = fmodSystem->init(512, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) {
		cout << "FMOD initialization error! " << FMOD_ErrorString(result) << endl;
	}
	else {
		cout << "System initialization successfull!" << endl;
	}
}



FMODInitialization::~FMODInitialization() {

}

FMOD::System* FMODInitialization::Initialized(FMOD_RESULT& result) {
	result = this->result;
	return fmodSystem;
}
