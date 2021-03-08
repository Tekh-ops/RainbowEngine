
#pragma once

#include "Editor/Core/Context.h"
#include "Editor/Core/Editor.h"

namespace Editor::Core
{
	/**
	* Entry point of Editor
	*/
	class Application
	{
	public:
		/**
		* Constructor
		* @param p_projectPath
		* @param p_projectName
		*/
		Application(const std::string& p_projectPath, const std::string& p_projectName);

		/**
		* Destructor
		*/
		~Application();

		/**
		* Run the app
		*/
		void Run();

		/**
		* Returns true if the app is running
		*/
		bool IsRunning() const;

	private:
		Context m_context;
		RainbowEditor m_editor;
	};
}