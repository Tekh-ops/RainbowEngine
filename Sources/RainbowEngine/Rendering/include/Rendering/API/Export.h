
#pragma once

#pragma warning(disable : 4251)
#pragma warning(disable : 4275)

#ifdef RENDERING_EXPORT
#define API_RENDERING __declspec(dllexport)
#else
#define API_RENDERING __declspec(dllimport)
#endif // OVRENDERING_EXPORT