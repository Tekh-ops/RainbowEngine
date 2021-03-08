#pragma once


#pragma warning(disable : 4251)
#pragma warning(disable : 4275)

#ifdef TOOLS_EXPORT
#define API_TOOLS __declspec(dllexport)
#else
#define API_TOOLS __declspec(dllimport)
#endif // Tools_EXPORT
