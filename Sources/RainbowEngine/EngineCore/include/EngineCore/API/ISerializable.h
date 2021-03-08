
#pragma once

#include <Tools/Filesystem/tinyxml2.h>

#include "EngineCore/API/Export.h"
#include "EngineCore/Helpers/Serializer.h"

namespace EngineCore::API
{
	/**
	* ISerializable is an interface for any class that can be serialized
	*/
	class API_ENGINECORE ISerializable
	{
	public:
		/**
		* Called when the serialization is asked
		* @param p_doc
		* @param p_node
		*/
		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) = 0;

		/**
		* Called when the deserialization is asked
		* @param p_doc
		* @param p_node
		*/
		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) = 0;
	};
}