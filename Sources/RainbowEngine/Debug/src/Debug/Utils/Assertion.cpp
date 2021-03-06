

#include "Debug/Utils/Assertion.h"

#include <assert.h>

void Debug::Assertion::Assert(bool p_condition, const std::string& p_message)
{
	assert(p_condition && p_message.c_str());
}
