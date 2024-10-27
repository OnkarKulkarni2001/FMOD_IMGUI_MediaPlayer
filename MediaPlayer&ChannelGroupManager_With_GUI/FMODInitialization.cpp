#include "FMODInitialization.h"
#include "AudioUtils.hpp"

FMODInitialization::FMODInitialization() {
	result = FMOD::System_Create(&fmodSystem);
	if (result != FMOD_OK) {
		cout << "System creation error! " << FMOD_ErrorString(result) << endl;		// Error checking
		FMODCheckError(result);
		return;
	}
	result = fmodSystem->init(512, FMOD_INIT_3D_RIGHTHANDED, 0);
	if (result != FMOD_OK) {
		cout << "FMOD initialization error! " << FMOD_ErrorString(result) << endl;		// Error checking
		FMODCheckError(result);
		return;
	}
}



FMODInitialization::~FMODInitialization() {

}

FMOD::System* FMODInitialization::Initialized(FMOD_RESULT& resultOut, bool& m_InitializedOut) {
	m_InitializedOut = this->m_Initialized;			
	resultOut = this->result;
	return fmodSystem;
}
