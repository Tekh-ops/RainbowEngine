/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#pragma warning(disable : 4251)
#pragma warning(disable : 4275)

#ifdef ENGINECORE_EXPORT
#define API_ENGINECORE __declspec(dllexport)
#else
#define API_ENGINECORE __declspec(dllimport)
#endif // CORE_EXPORT