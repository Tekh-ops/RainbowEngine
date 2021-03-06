#pragma once

#pragma warning(disable : 4251)
#pragma warning(disable : 4275)

#ifdef WINDOWING_EXPORT
#define API_WINDOWING __declspec(dllexport)
#else
#define API_WINDOWING __declspec(dllimport)
#endif // WINDOWING_EXPORT