#pragma once

#include <string>

#include "Tools/API/Export.h"

namespace Tools::Time
{
	/*
	* Date system to get the current date in a string format
	*/
	class API_TOOLS Date
	{
	public:
		/**
		* Default constructor
		*/
		Date() = delete;

		/*
		* Return the current date in a string format
		*/
		static std::string GetDateAsString();
	};
}