

#pragma once

#include "Rendering/API/Export.h"

#define FORCE_DEDICATED_GPU \
extern "C"\
{\
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;\
}