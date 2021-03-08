

#pragma once

#include <Rendering/Entities/Light.h>

#include "EngineCore/ECS/Components/AComponent.h"

namespace EngineCore::ECS { class Actor; }

namespace EngineCore::ECS::Components
{
	/**
	* Base class for any light
	*/
	class API_ENGINECORE CLight : public AComponent
	{
	public:
		/**
		* Constructor
		* @param p_owner
		*/
		CLight(ECS::Actor& p_owner);

		/**
		* Returns light data
		*/
		const Rendering::Entities::Light& GetData() const;

		/**
		* Returns light color
		*/
		const OvMaths::FVector3& GetColor() const;

		/**
		* Returns light intensity
		*/
		float GetIntensity() const;

		/**
		* Defines a new color for the light
		* @param p_color
		*/
		void SetColor(const OvMaths::FVector3& p_color);

		/**
		* Defines the intensity for the light
		* @param p_intensity
		*/
		void SetIntensity(float p_intensity);

		/**
		* Serialize the component
		* @param p_doc
		* @param p_node
		*/
		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		/**
		* Deserialize the component
		* @param p_doc
		* @param p_node
		*/
		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		/**
		* Defines how the component should be drawn in the inspector
		* @param p_root
		*/
		virtual void OnInspector(UI::Internal::WidgetContainer& p_root) override;

	protected:
		Rendering::Entities::Light m_data;
	};
}