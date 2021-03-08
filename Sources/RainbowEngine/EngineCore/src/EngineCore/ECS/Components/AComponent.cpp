

#include "EngineCore/ECS/Components/AComponent.h"
#include "EngineCore/ECS/Actor.h"

EngineCore::ECS::Components::AComponent::AComponent(ECS::Actor& p_owner) : owner(p_owner)
{
}

EngineCore::ECS::Components::AComponent::~AComponent()
{
	if (owner.IsActive())
	{
		OnDisable();
		OnDestroy();
	}
}
