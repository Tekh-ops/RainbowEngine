#pragma once

#pragma warning(disable : 4251)
#pragma warning(disable : 4275)

#ifdef UI_EXPORT
#define API_UI __declspec(dllexport)
#else
#define API_UI __declspec(dllimport)
#endif // UI_EXPORT