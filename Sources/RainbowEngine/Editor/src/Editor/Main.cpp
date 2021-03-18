#include <filesystem>

#include <Tools/Utils/String.h>

#include <Rendering/Utils/Defines.h>

#include "Editor/Core/ProjectHub.h"
#include "Editor/Core/Application.h"

#undef APIENTRY
#include "Windows.h"

FORCE_DEDICATED_GPU

/**
* When Overload is launched from a project file, we should consider the executable path as
* the current working directory
* @param p_executablePath
*/
void UpdateWorkingDirectory(const std::string& p_executablePath)
{
	if (!IsDebuggerPresent())
	{
		std::filesystem::current_path(Tools::Utils::PathParser::GetContainingFolder(p_executablePath));
	}
}

int main(int argc, char** argv);

#ifndef _DEBUG
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	main(__argc, __argv);
}
#endif

int main(int argc, char** argv)
{
	UpdateWorkingDirectory(argv[0]);

	bool ready = false;
	std::string projectPath;
	std::string projectName;

	{
		Editor::Core::ProjectHub hub;

		if (argc < 2)
		{
			// No project file given as argument ==> Open the ProjectHub
			std::tie(ready, projectPath, projectName) = hub.Run();
		}
		else
		{
			// Project file given as argument ==> Open the project
			std::string projectFile = argv[1];
			if (Tools::Utils::PathParser::GetExtension(projectFile) == "ovproject")
			{
				ready = true;
				projectPath = Tools::Utils::PathParser::GetContainingFolder(projectFile);
				projectName = Tools::Utils::PathParser::GetElementName(projectFile);
				Tools::Utils::String::Replace(projectName, ".ovproject", "");
			}

			hub.RegisterProject(projectPath);
		}
	}

	if (ready)
	{
		Editor::Core::Application app(projectPath, projectName);
		app.Run();
	}

	return EXIT_SUCCESS;
}