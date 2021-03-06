#pragma once

#pragma warning(disable : 4251)
#pragma warning(disable : 4275)

#ifdef DEBUG_EXPORT
#define API_DEBUG __declspec(dllexport)
#else
#define API_DEBUG __declspec(dllimport)
#endif // DEBUG_EXPORT
