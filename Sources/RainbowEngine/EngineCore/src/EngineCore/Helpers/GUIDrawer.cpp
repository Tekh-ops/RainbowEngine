/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <array>

#include <Tools/Utils/PathParser.h>

#include <UI/Widgets/Texts/TextColored.h>
#include <UI/Widgets/Drags/DragSingleScalar.h>
#include <UI/Widgets/Drags/DragMultipleScalars.h>
#include <UI/Widgets/InputFields/InputText.h>
#include <UI/Widgets/Selection/ColorEdit.h>
#include <UI/Widgets/Layout/Group.h>
#include <UI/Widgets/Layout/Columns.h>
#include <UI/Widgets/Selection/CheckBox.h>
#include <UI/Widgets/Buttons/Button.h>
#include <UI/Widgets/Buttons/ButtonSmall.h>
#include <UI/Plugins/DDTarget.h>

#include <EngineCore/Global/ServiceLocator.h>
#include <EngineCore/ResourceManagement/ModelManager.h>
#include <EngineCore/ResourceManagement/TextureManager.h>
#include <EngineCore/ResourceManagement/ShaderManager.h>
#include <EngineCore/ResourceManagement/MaterialManager.h>

//TODO
//#include <Core/ResourceManagement/SoundManager.h>

#include "EngineCore/Helpers/GUIDrawer.h"

const UI::Types::Color EngineCore::Helpers::GUIDrawer::TitleColor = { 0.85f, 0.65f, 0.0f };
const UI::Types::Color EngineCore::Helpers::GUIDrawer::ClearButtonColor = { 0.5f, 0.0f, 0.0f };
const float EngineCore::Helpers::GUIDrawer::_MIN_FLOAT = -999999999.f;
const float EngineCore::Helpers::GUIDrawer::_MAX_FLOAT = +999999999.f;
Rendering::Resources::Texture* EngineCore::Helpers::GUIDrawer::__EMPTY_TEXTURE = nullptr;

void EngineCore::Helpers::GUIDrawer::ProvideEmptyTexture(Rendering::Resources::Texture& p_emptyTexture)
{
	__EMPTY_TEXTURE = &p_emptyTexture;
}

void EngineCore::Helpers::GUIDrawer::CreateTitle(UI::Internal::WidgetContainer& p_root, const std::string & p_name)
{
	p_root.CreateWidget<UI::Widgets::Texts::TextColored>(p_name, TitleColor);
}

void EngineCore::Helpers::GUIDrawer::DrawBoolean(UI::Internal::WidgetContainer & p_root, const std::string & p_name, bool & p_data)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<UI::Widgets::Selection::CheckBox>();
	auto& dispatcher = widget.AddPlugin<UI::Plugins::DataDispatcher<bool>>();
	dispatcher.RegisterReference(reinterpret_cast<bool&>(p_data));
}

void EngineCore::Helpers::GUIDrawer::DrawVec2(UI::Internal::WidgetContainer & p_root, const std::string & p_name, OvMaths::FVector2 & p_data, float p_step, float p_min, float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<UI::Widgets::Drags::DragMultipleScalars<float, 2>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<UI::Plugins::DataDispatcher<std::array<float, 2>>>();
	dispatcher.RegisterReference(reinterpret_cast<std::array<float, 2>&>(p_data));
}

void EngineCore::Helpers::GUIDrawer::DrawVec3(UI::Internal::WidgetContainer & p_root, const std::string & p_name, OvMaths::FVector3 & p_data, float p_step, float p_min, float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<UI::Widgets::Drags::DragMultipleScalars<float, 3>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<UI::Plugins::DataDispatcher<std::array<float, 3>>>();
	dispatcher.RegisterReference(reinterpret_cast<std::array<float, 3>&>(p_data));
}

void EngineCore::Helpers::GUIDrawer::DrawVec4(UI::Internal::WidgetContainer & p_root, const std::string & p_name, OvMaths::FVector4& p_data, float p_step, float p_min, float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<UI::Widgets::Drags::DragMultipleScalars<float, 4>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<UI::Plugins::DataDispatcher<std::array<float, 4>>>();
	dispatcher.RegisterReference(reinterpret_cast<std::array<float, 4>&>(p_data));
}

void EngineCore::Helpers::GUIDrawer::DrawQuat(UI::Internal::WidgetContainer & p_root, const std::string & p_name, OvMaths::FQuaternion & p_data, float p_step, float p_min, float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<UI::Widgets::Drags::DragMultipleScalars<float, 4>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<UI::Plugins::DataDispatcher<std::array<float, 4>>>();
	dispatcher.RegisterReference(reinterpret_cast<std::array<float, 4>&>(p_data));
}

void EngineCore::Helpers::GUIDrawer::DrawString(UI::Internal::WidgetContainer & p_root, const std::string & p_name, std::string & p_data)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<UI::Widgets::InputFields::InputText>("");
	auto& dispatcher = widget.AddPlugin<UI::Plugins::DataDispatcher<std::string>>();
	dispatcher.RegisterReference(p_data);
}

void EngineCore::Helpers::GUIDrawer::DrawColor(UI::Internal::WidgetContainer & p_root, const std::string & p_name, UI::Types::Color & p_color, bool p_hasAlpha)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<UI::Widgets::Selection::ColorEdit>(p_hasAlpha);
	auto& dispatcher = widget.AddPlugin<UI::Plugins::DataDispatcher<UI::Types::Color>>();
	dispatcher.RegisterReference(p_color);
}

UI::Widgets::Texts::Text& EngineCore::Helpers::GUIDrawer::DrawMesh(UI::Internal::WidgetContainer & p_root, const std::string & p_name, Rendering::Resources::Model *& p_data, Tools::Eventing::Event<>* p_updateNotifier)
{
	CreateTitle(p_root, p_name);

	std::string displayedText = (p_data ? p_data->path : std::string("Empty"));
	auto& rightSide = p_root.CreateWidget<UI::Widgets::Layout::Group>();

	auto& widget = rightSide.CreateWidget<UI::Widgets::Texts::Text>(displayedText);

	widget.AddPlugin<UI::Plugins::DDTarget<std::pair<std::string, UI::Widgets::Layout::Group*>>>("File").DataReceivedEvent += [&widget, &p_data, p_updateNotifier](auto p_receivedData)
	{
		if (Tools::Utils::PathParser::GetFileType(p_receivedData.first) == Tools::Utils::PathParser::EFileType::MODEL)
		{
			if (auto resource = OVSERVICE(EngineCore::ResourceManagement::ModelManager).GetResource(p_receivedData.first); resource)
			{
				p_data = resource;
				widget.content = p_receivedData.first;
				if (p_updateNotifier)
					p_updateNotifier->Invoke();
			}
		}
	};

	widget.lineBreak = false;

	auto& resetButton = rightSide.CreateWidget<UI::Widgets::Buttons::ButtonSmall>("Clear");
	resetButton.idleBackgroundColor = ClearButtonColor;
	resetButton.ClickedEvent += [&widget, &p_data, p_updateNotifier]
	{
		p_data = nullptr;
		widget.content = "Empty";
		if (p_updateNotifier)
			p_updateNotifier->Invoke();
	};

	return widget;
}

UI::Widgets::Visual::Image& EngineCore::Helpers::GUIDrawer::DrawTexture(UI::Internal::WidgetContainer & p_root, const std::string & p_name, Rendering::Resources::Texture *& p_data, Tools::Eventing::Event<>* p_updateNotifier)
{
	CreateTitle(p_root, p_name);

	std::string displayedText = (p_data ? p_data->path : std::string("Empty"));
	auto& rightSide = p_root.CreateWidget<UI::Widgets::Layout::Group>();

	auto& widget = rightSide.CreateWidget<UI::Widgets::Visual::Image>(p_data ? p_data->id : (__EMPTY_TEXTURE ? __EMPTY_TEXTURE->id : 0), OvMaths::FVector2{ 75, 75 });

	widget.AddPlugin<UI::Plugins::DDTarget<std::pair<std::string, UI::Widgets::Layout::Group*>>>("File").DataReceivedEvent += [&widget, &p_data, p_updateNotifier](auto p_receivedData)
	{
		if (Tools::Utils::PathParser::GetFileType(p_receivedData.first) == Tools::Utils::PathParser::EFileType::TEXTURE)
		{
			if (auto resource = OVSERVICE(EngineCore::ResourceManagement::TextureManager).GetResource(p_receivedData.first); resource)
			{
				p_data = resource;
				widget.textureID.id = resource->id;
				if (p_updateNotifier)
					p_updateNotifier->Invoke();
			}
		}
	};

	widget.lineBreak = false;

	auto& resetButton = rightSide.CreateWidget<UI::Widgets::Buttons::Button>("Clear");
	resetButton.idleBackgroundColor = ClearButtonColor;
	resetButton.ClickedEvent += [&widget, &p_data, p_updateNotifier]
	{
		p_data = nullptr;
		widget.textureID.id = (__EMPTY_TEXTURE ? __EMPTY_TEXTURE->id : 0);
		if (p_updateNotifier)
			p_updateNotifier->Invoke();
	};

	return widget;
}

UI::Widgets::Texts::Text& EngineCore::Helpers::GUIDrawer::DrawShader(UI::Internal::WidgetContainer & p_root, const std::string & p_name, Rendering::Resources::Shader *& p_data, Tools::Eventing::Event<>* p_updateNotifier)
{
	CreateTitle(p_root, p_name);

	std::string displayedText = (p_data ? p_data->path : std::string("Empty"));
	auto& rightSide = p_root.CreateWidget<UI::Widgets::Layout::Group>();

	auto& widget = rightSide.CreateWidget<UI::Widgets::Texts::Text>(displayedText);

	widget.AddPlugin<UI::Plugins::DDTarget<std::pair<std::string, UI::Widgets::Layout::Group*>>>("File").DataReceivedEvent += [&widget, &p_data, p_updateNotifier](auto p_receivedData)
	{
		if (Tools::Utils::PathParser::GetFileType(p_receivedData.first) == Tools::Utils::PathParser::EFileType::SHADER)
		{
			if (auto resource = OVSERVICE(EngineCore::ResourceManagement::ShaderManager).GetResource(p_receivedData.first); resource)
			{
				p_data = resource;
				widget.content = p_receivedData.first;
				if (p_updateNotifier)
					p_updateNotifier->Invoke();
			}
		}
	};

	widget.lineBreak = false;

	auto& resetButton = rightSide.CreateWidget<UI::Widgets::Buttons::ButtonSmall>("Clear");
	resetButton.idleBackgroundColor = ClearButtonColor;
	resetButton.ClickedEvent += [&widget, &p_data, p_updateNotifier]
	{
		p_data = nullptr;
		widget.content = "Empty";
		if (p_updateNotifier)
			p_updateNotifier->Invoke();
	};

	return widget;
}

UI::Widgets::Texts::Text& EngineCore::Helpers::GUIDrawer::DrawMaterial(UI::Internal::WidgetContainer & p_root, const std::string & p_name, EngineCore::Resources::Material *& p_data, Tools::Eventing::Event<>* p_updateNotifier)
{
	CreateTitle(p_root, p_name);

	std::string displayedText = (p_data ? p_data->path : std::string("Empty"));
	auto& rightSide = p_root.CreateWidget<UI::Widgets::Layout::Group>();

	auto& widget = rightSide.CreateWidget<UI::Widgets::Texts::Text>(displayedText);

	widget.AddPlugin<UI::Plugins::DDTarget<std::pair<std::string, UI::Widgets::Layout::Group*>>>("File").DataReceivedEvent += [&widget, &p_data, p_updateNotifier](auto p_receivedData)
	{
		if (Tools::Utils::PathParser::GetFileType(p_receivedData.first) == Tools::Utils::PathParser::EFileType::MATERIAL)
		{
			if (auto resource = OVSERVICE(EngineCore::ResourceManagement::MaterialManager).GetResource(p_receivedData.first); resource)
			{
				p_data = resource;
				widget.content = p_receivedData.first;
				if (p_updateNotifier)
					p_updateNotifier->Invoke();
			}
		}
	};

	widget.lineBreak = false;

	auto& resetButton = rightSide.CreateWidget<UI::Widgets::Buttons::ButtonSmall>("Clear");
	resetButton.idleBackgroundColor = ClearButtonColor;
	resetButton.ClickedEvent += [&widget, &p_data, p_updateNotifier]
	{
		p_data = nullptr;
		widget.content = "Empty";
		if (p_updateNotifier)
			p_updateNotifier->Invoke();
	};

	return widget;
}

//TODO
//UI::Widgets::Texts::Text& Core::Helpers::GUIDrawer::DrawSound(UI::Internal::WidgetContainer& p_root, const std::string& p_name, Audio::Resources::Sound*& p_data, Tools::Eventing::Event<>* p_updateNotifier)
//{
//	CreateTitle(p_root, p_name);
//
//	std::string displayedText = (p_data ? p_data->path : std::string("Empty"));
//	auto & rightSide = p_root.CreateWidget<UI::Widgets::Layout::Group>();
//
//	auto & widget = rightSide.CreateWidget<UI::Widgets::Texts::Text>(displayedText);
//
//	widget.AddPlugin<UI::Plugins::DDTarget<std::pair<std::string, UI::Widgets::Layout::Group*>>>("File").DataReceivedEvent += [&widget, &p_data, p_updateNotifier](auto p_receivedData)
//	{
//		if (Tools::Utils::PathParser::GetFileType(p_receivedData.first) == Tools::Utils::PathParser::EFileType::SOUND)
//		{
//			if (auto resource = OVSERVICE(Core::ResourceManagement::SoundManager).GetResource(p_receivedData.first); resource)
//			{
//				p_data = resource;
//				widget.content = p_receivedData.first;
//				if (p_updateNotifier)
//					p_updateNotifier->Invoke();
//			}
//		}
//	};
//
//	widget.lineBreak = false;
//
//	auto & resetButton = rightSide.CreateWidget<UI::Widgets::Buttons::ButtonSmall>("Clear");
//	resetButton.idleBackgroundColor = ClearButtonColor;
//	resetButton.ClickedEvent += [&widget, &p_data, p_updateNotifier]
//	{
//		p_data = nullptr;
//		widget.content = "Empty";
//		if (p_updateNotifier)
//			p_updateNotifier->Invoke();
//	};
//
//	return widget;
//}

UI::Widgets::Texts::Text& EngineCore::Helpers::GUIDrawer::DrawAsset(UI::Internal::WidgetContainer& p_root, const std::string& p_name, std::string& p_data, Tools::Eventing::Event<>* p_updateNotifier)
{
    CreateTitle(p_root, p_name);

    const std::string displayedText = (p_data.empty() ? std::string("Empty") : p_data);
    auto& rightSide = p_root.CreateWidget<UI::Widgets::Layout::Group>();

    auto& widget = rightSide.CreateWidget<UI::Widgets::Texts::Text>(displayedText);

    widget.AddPlugin<UI::Plugins::DDTarget<std::pair<std::string, UI::Widgets::Layout::Group*>>>("File").DataReceivedEvent += [&widget, &p_data, p_updateNotifier](auto p_receivedData)
    {
        p_data = p_receivedData.first;
        widget.content = p_receivedData.first;
        if (p_updateNotifier)
            p_updateNotifier->Invoke();
    };

    widget.lineBreak = false;

    auto& resetButton = rightSide.CreateWidget<UI::Widgets::Buttons::ButtonSmall>("Clear");
    resetButton.idleBackgroundColor = ClearButtonColor;
    resetButton.ClickedEvent += [&widget, &p_data, p_updateNotifier]
    {
        p_data = "";
        widget.content = "Empty";
        if (p_updateNotifier)
            p_updateNotifier->Invoke();
    };

    return widget;
}

void EngineCore::Helpers::GUIDrawer::DrawBoolean(UI::Internal::WidgetContainer & p_root, const std::string & p_name, std::function<bool(void)> p_gatherer, std::function<void(bool)> p_provider)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<UI::Widgets::Selection::CheckBox>();
	auto& dispatcher = widget.AddPlugin<UI::Plugins::DataDispatcher<bool>>();

	dispatcher.RegisterGatherer([p_gatherer]()
	{
		bool value = p_gatherer();
		return reinterpret_cast<bool&>(value);
	});

	dispatcher.RegisterProvider([p_provider](bool p_value)
	{
		p_provider(reinterpret_cast<bool&>(p_value));
	});
}

void EngineCore::Helpers::GUIDrawer::DrawVec2(UI::Internal::WidgetContainer & p_root, const std::string & p_name, std::function<OvMaths::FVector2(void)> p_gatherer, std::function<void(OvMaths::FVector2)> p_provider, float p_step, float p_min, float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<UI::Widgets::Drags::DragMultipleScalars<float, 2>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<UI::Plugins::DataDispatcher<std::array<float, 2>>>();
	
	dispatcher.RegisterGatherer([p_gatherer]()
	{
		OvMaths::FVector2 value = p_gatherer();
		return reinterpret_cast<const std::array<float, 2>&>(value);
	});

	dispatcher.RegisterProvider([p_provider](std::array<float, 2> p_value)
	{
		p_provider(reinterpret_cast<OvMaths::FVector2&>(p_value));
	});
}

void EngineCore::Helpers::GUIDrawer::DrawVec3(UI::Internal::WidgetContainer & p_root, const std::string & p_name, std::function<OvMaths::FVector3(void)> p_gatherer, std::function<void(OvMaths::FVector3)> p_provider, float p_step, float p_min, float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<UI::Widgets::Drags::DragMultipleScalars<float, 3>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<UI::Plugins::DataDispatcher<std::array<float, 3>>>();

	dispatcher.RegisterGatherer([p_gatherer]()
	{
		OvMaths::FVector3 value = p_gatherer();
		return reinterpret_cast<const std::array<float, 3>&>(value);
	});

	dispatcher.RegisterProvider([p_provider](std::array<float, 3> p_value)
	{
		p_provider(reinterpret_cast<OvMaths::FVector3&>(p_value));
	});
}

void EngineCore::Helpers::GUIDrawer::DrawVec4(UI::Internal::WidgetContainer & p_root, const std::string & p_name, std::function<OvMaths::FVector4(void)> p_gatherer, std::function<void(OvMaths::FVector4)> p_provider, float p_step, float p_min, float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<UI::Widgets::Drags::DragMultipleScalars<float, 4>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<UI::Plugins::DataDispatcher<std::array<float, 4>>>();
	
	dispatcher.RegisterGatherer([p_gatherer]()
	{
		OvMaths::FVector4 value = p_gatherer();
		return reinterpret_cast<const std::array<float, 4>&>(value);
	});

	dispatcher.RegisterProvider([p_provider](std::array<float, 4> p_value)
	{
		p_provider(reinterpret_cast<OvMaths::FVector4&>(p_value));
	});
}

void EngineCore::Helpers::GUIDrawer::DrawQuat(UI::Internal::WidgetContainer & p_root, const std::string & p_name, std::function<OvMaths::FQuaternion(void)> p_gatherer, std::function<void(OvMaths::FQuaternion)> p_provider, float p_step, float p_min, float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<UI::Widgets::Drags::DragMultipleScalars<float, 4>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<UI::Plugins::DataDispatcher<std::array<float, 4>>>();
	
	dispatcher.RegisterGatherer([p_gatherer]()
	{
		OvMaths::FQuaternion value = p_gatherer();
		return reinterpret_cast<const std::array<float, 4>&>(value);
	});

	dispatcher.RegisterProvider([&dispatcher, p_provider](std::array<float, 4> p_value)
	{
		p_provider(OvMaths::FQuaternion::Normalize(reinterpret_cast<OvMaths::FQuaternion&>(p_value)));
	});
}

void EngineCore::Helpers::GUIDrawer::DrawDDString(UI::Internal::WidgetContainer& p_root, const std::string& p_name,
	std::function<std::string()> p_gatherer, std::function<void(std::string)> p_provider,
	const std::string& p_identifier)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<UI::Widgets::InputFields::InputText>("");
	auto& dispatcher = widget.AddPlugin<UI::Plugins::DataDispatcher<std::string>>();
	dispatcher.RegisterGatherer(p_gatherer);
	dispatcher.RegisterProvider(p_provider);

	auto& ddTarget = widget.AddPlugin<UI::Plugins::DDTarget<std::pair<std::string, UI::Widgets::Layout::Group*>>>(p_identifier);
	ddTarget.DataReceivedEvent += [&widget, &dispatcher](std::pair<std::string, UI::Widgets::Layout::Group*> p_data)
	{
		widget.content = p_data.first;
		dispatcher.NotifyChange();
	};
}

void EngineCore::Helpers::GUIDrawer::DrawString(UI::Internal::WidgetContainer & p_root, const std::string & p_name, std::function<std::string(void)> p_gatherer, std::function<void(std::string)> p_provider)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<UI::Widgets::InputFields::InputText>("");
	auto& dispatcher = widget.AddPlugin<UI::Plugins::DataDispatcher<std::string>>();
	dispatcher.RegisterGatherer(p_gatherer);
	dispatcher.RegisterProvider(p_provider);
}

void EngineCore::Helpers::GUIDrawer::DrawColor(UI::Internal::WidgetContainer & p_root, const std::string & p_name, std::function<UI::Types::Color(void)> p_gatherer, std::function<void(UI::Types::Color)> p_provider, bool p_hasAlpha)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<UI::Widgets::Selection::ColorEdit>(p_hasAlpha);
	auto& dispatcher = widget.AddPlugin<UI::Plugins::DataDispatcher<UI::Types::Color>>();
	dispatcher.RegisterGatherer(p_gatherer);
	dispatcher.RegisterProvider(p_provider);
}
