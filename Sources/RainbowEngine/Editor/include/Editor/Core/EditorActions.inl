
#pragma once

#include "Editor/Core/EditorActions.h"

namespace Editor::Core
{
	template<typename T>
	inline EngineCore::ECS::Actor & EditorActions::CreateMonoComponentActor(bool p_focusOnCreation, EngineCore::ECS::Actor* p_parent)
	{
		auto& instance = CreateEmptyActor(false, p_parent);

		instance.AddComponent<T>();

		if (p_focusOnCreation)
			SelectActor(instance);

		return instance;
	}
}