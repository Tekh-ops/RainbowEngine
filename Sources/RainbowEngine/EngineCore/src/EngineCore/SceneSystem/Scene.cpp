#include <algorithm>
#include <string>

#include "EngineCore/SceneSystem/Scene.h"

EngineCore::SceneSystem::Scene::Scene()
{

}

EngineCore::SceneSystem::Scene::~Scene()
{
	std::for_each(m_actors.begin(), m_actors.end(), [](EngineCore::ECS::Actor* element)
	{ 
		delete element;
	});

	m_actors.clear();
}

void EngineCore::SceneSystem::Scene::Play()
{
	m_isPlaying = true;

	/* Wake up actors to allow them to react to OnEnable, OnDisable and OnDestroy, */
	std::for_each(m_actors.begin(), m_actors.end(), [](ECS::Actor * p_element) { p_element->SetSleeping(false); });

	std::for_each(m_actors.begin(), m_actors.end(), [](ECS::Actor * p_element) { if (p_element->IsActive()) p_element->OnAwake(); });
	std::for_each(m_actors.begin(), m_actors.end(), [](ECS::Actor * p_element) { if (p_element->IsActive()) p_element->OnEnable(); });
	std::for_each(m_actors.begin(), m_actors.end(), [](ECS::Actor * p_element) { if (p_element->IsActive()) p_element->OnStart(); });
}

bool EngineCore::SceneSystem::Scene::IsPlaying() const
{
	return m_isPlaying;
}

void EngineCore::SceneSystem::Scene::Update(float p_deltaTime)
{
	auto actors = m_actors;
	std::for_each(actors.begin(), actors.end(), std::bind(std::mem_fn(&ECS::Actor::OnUpdate), std::placeholders::_1, p_deltaTime));
}

void EngineCore::SceneSystem::Scene::FixedUpdate(float p_deltaTime)
{
	auto actors = m_actors;
	std::for_each(actors.begin(), actors.end(), std::bind(std::mem_fn(&ECS::Actor::OnFixedUpdate), std::placeholders::_1, p_deltaTime));
}

void EngineCore::SceneSystem::Scene::LateUpdate(float p_deltaTime)
{
	auto actors = m_actors;
	std::for_each(actors.begin(), actors.end(), std::bind(std::mem_fn(&ECS::Actor::OnLateUpdate), std::placeholders::_1, p_deltaTime));
}

EngineCore::ECS::Actor& EngineCore::SceneSystem::Scene::CreateActor()
{
	return CreateActor("New Actor");
}

EngineCore::ECS::Actor& EngineCore::SceneSystem::Scene::CreateActor(const std::string& p_name, const std::string& p_tag)
{
	m_actors.push_back(new EngineCore::ECS::Actor(m_availableID++, p_name, p_tag, m_isPlaying));
	ECS::Actor& instance = *m_actors.back();
	instance.ComponentAddedEvent	+= std::bind(&Scene::OnComponentAdded, this, std::placeholders::_1);
	instance.ComponentRemovedEvent	+= std::bind(&Scene::OnComponentRemoved, this, std::placeholders::_1);
	if (m_isPlaying)
	{
		instance.SetSleeping(false);
		if (instance.IsActive())
		{
			instance.OnAwake();
			instance.OnEnable();
			instance.OnStart();
		}
	}
	return instance;
}

bool EngineCore::SceneSystem::Scene::DestroyActor(ECS::Actor& p_target)
{
	auto found = std::find_if(m_actors.begin(), m_actors.end(), [&p_target](EngineCore::ECS::Actor* element)
	{
		return element == &p_target;
	});

	if (found != m_actors.end())
	{
		delete *found;
		m_actors.erase(found);
		return true;
	}
	else
	{
		return false;
	}
}

void EngineCore::SceneSystem::Scene::CollectGarbages()
{
	m_actors.erase(std::remove_if(m_actors.begin(), m_actors.end(), [this](ECS::Actor* element)
	{ 
		bool isGarbage = !element->IsAlive();
		if (isGarbage)
		{
			delete element;
		}
		return isGarbage;
	}), m_actors.end());
}

EngineCore::ECS::Actor* EngineCore::SceneSystem::Scene::FindActorByName(const std::string& p_name)
{
	auto result = std::find_if(m_actors.begin(), m_actors.end(), [p_name](EngineCore::ECS::Actor* element)
	{ 
		return element->GetName() == p_name;
	});

	if (result != m_actors.end())
		return *result;
	else
		return nullptr;
}

EngineCore::ECS::Actor* EngineCore::SceneSystem::Scene::FindActorByTag(const std::string & p_tag)
{
	auto result = std::find_if(m_actors.begin(), m_actors.end(), [p_tag](EngineCore::ECS::Actor* element)
	{
		return element->GetTag() == p_tag;
	});

	if (result != m_actors.end())
		return *result;
	else
		return nullptr;
}

EngineCore::ECS::Actor* EngineCore::SceneSystem::Scene::FindActorByID(int64_t p_id)
{
	auto result = std::find_if(m_actors.begin(), m_actors.end(), [p_id](EngineCore::ECS::Actor* element)
	{
		return element->GetID() == p_id;
	});

	if (result != m_actors.end())
		return *result;
	else
		return nullptr;
}

std::vector<std::reference_wrapper<EngineCore::ECS::Actor>> EngineCore::SceneSystem::Scene::FindActorsByName(const std::string & p_name)
{
	std::vector<std::reference_wrapper<EngineCore::ECS::Actor>> actors;

	for (auto actor : m_actors)
	{
		if (actor->GetName() == p_name)
			actors.push_back(std::ref(*actor));
	}

	return actors;
}

std::vector<std::reference_wrapper<EngineCore::ECS::Actor>> EngineCore::SceneSystem::Scene::FindActorsByTag(const std::string & p_tag)
{
	std::vector<std::reference_wrapper<EngineCore::ECS::Actor>> actors;

	for (auto actor : m_actors)
	{
		if (actor->GetTag() == p_tag)
			actors.push_back(std::ref(*actor));
	}

	return actors;
}

void EngineCore::SceneSystem::Scene::OnComponentAdded(ECS::Components::AComponent& p_compononent)
{
	if (auto result = dynamic_cast<ECS::Components::CModelRenderer*>(&p_compononent))
		m_fastAccessComponents.modelRenderers.push_back(result);

	if (auto result = dynamic_cast<ECS::Components::CCamera*>(&p_compononent))
		m_fastAccessComponents.cameras.push_back(result);

	if (auto result = dynamic_cast<ECS::Components::CLight*>(&p_compononent))
		m_fastAccessComponents.lights.push_back(result);
}

void EngineCore::SceneSystem::Scene::OnComponentRemoved(ECS::Components::AComponent& p_compononent)
{
	if (auto result = dynamic_cast<ECS::Components::CModelRenderer*>(&p_compononent))
		m_fastAccessComponents.modelRenderers.erase(std::remove(m_fastAccessComponents.modelRenderers.begin(), m_fastAccessComponents.modelRenderers.end(), result), m_fastAccessComponents.modelRenderers.end());

	if (auto result = dynamic_cast<ECS::Components::CCamera*>(&p_compononent))
		m_fastAccessComponents.cameras.erase(std::remove(m_fastAccessComponents.cameras.begin(), m_fastAccessComponents.cameras.end(), result), m_fastAccessComponents.cameras.end());

	if (auto result = dynamic_cast<ECS::Components::CLight*>(&p_compononent))
		m_fastAccessComponents.lights.erase(std::remove(m_fastAccessComponents.lights.begin(), m_fastAccessComponents.lights.end(), result), m_fastAccessComponents.lights.end());
}

std::vector<EngineCore::ECS::Actor*>& EngineCore::SceneSystem::Scene::GetActors()
{
	return m_actors;
}

const EngineCore::SceneSystem::Scene::FastAccessComponents& EngineCore::SceneSystem::Scene::GetFastAccessComponents() const
{
	return m_fastAccessComponents;
}

void EngineCore::SceneSystem::Scene::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_root)
{
	tinyxml2::XMLNode* sceneNode = p_doc.NewElement("scene");
	p_root->InsertEndChild(sceneNode);

	tinyxml2::XMLNode* actorsNode = p_doc.NewElement("actors");
	sceneNode->InsertEndChild(actorsNode);

	for (auto& actor : m_actors)
	{
		actor->OnSerialize(p_doc, actorsNode);
	}
}

void EngineCore::SceneSystem::Scene::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_root)
{
	tinyxml2::XMLNode* actorsRoot = p_root->FirstChildElement("actors");

	if (actorsRoot)
	{
		tinyxml2::XMLElement* currentActor = actorsRoot->FirstChildElement("actor");

		int64_t maxID = 1;

		while (currentActor)
		{
			auto& actor = CreateActor();
			actor.OnDeserialize(p_doc, currentActor);
			maxID = std::max(actor.GetID() + 1, maxID);
			currentActor = currentActor->NextSiblingElement("actor");
		}

		m_availableID = maxID;

		/* We recreate the hierarchy of the scene by attaching children to their parents */
		for (auto actor : m_actors)
		{
			if (actor->GetParentID() > 0)
			{
				if (auto found = FindActorByID(actor->GetParentID()); found)
					actor->SetParent(*found);
			}
		}
	}
}
