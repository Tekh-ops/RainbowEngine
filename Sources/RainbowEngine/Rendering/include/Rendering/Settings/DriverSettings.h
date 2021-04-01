#pragma once

#include "Rendering/API/Export.h"

namespace Rendering::Settings
{
	/**
	* Settings that are sent to the driver at construction
	*/
	struct API_RENDERING DriverSettings
	{
		bool debugMode = false;
	};
}