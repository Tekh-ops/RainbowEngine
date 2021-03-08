/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <Tools/Utils/SystemCalls.h>

#include <EngineCore/ECS/Components/CCamera.h>
#include <EngineCore/ECS/Components/CPointLight.h>
#include <EngineCore/ECS/Components/CDirectionalLight.h>
#include <EngineCore/ECS/Components/CSpotLight.h>
#include <EngineCore/ECS/Components/CAmbientBoxLight.h>
#include <EngineCore/ECS/Components/CAmbientSphereLight.h>

#include <UI/Widgets/Visual/Separator.h>
#include <UI/Widgets/Sliders/SliderInt.h>
#include <UI/Widgets/Sliders/SliderFloat.h>
#include <UI/Widgets/Drags/DragFloat.h>
#include <UI/Widgets/Selection/ColorEdit.h>

#include "Editor/Panels/MenuBar.h"
#include "Editor/Panels/SceneView.h"
#include "Editor/Panels/AssetView.h"
#include "Editor/Core/EditorActions.h"
#include "Editor/Settings/EditorSettings.h"

using namespace UI::Panels;
using namespace UI::Widgets;
using namespace UI::Widgets::Menu;
using namespace EngineCore::ECS::Components;

Editor::Panels::MenuBar::MenuBar()
{
	CreateFileMenu();
	CreateBuildMenu();
	CreateWindowMenu();
	CreateActorsMenu();
	CreateResourcesMenu();
	CreateSettingsMenu();
	CreateLayoutMenu();
	CreateHelpMenu();
}

void Editor::Panels::MenuBar::HandleShortcuts(float p_deltaTime)
{
	auto& inputManager = *EDITOR_CONTEXT(inputManager);

	if (inputManager.GetKeyState(Windowing::Inputs::EKey::KEY_LEFT_CONTROL) == Windowing::Inputs::EKeyState::KEY_DOWN)
	{
		if (inputManager.IsKeyPressed(Windowing::Inputs::EKey::KEY_N))
			EDITOR_EXEC(LoadEmptyScene());

		if (inputManager.IsKeyPressed(Windowing::Inputs::EKey::KEY_S))
		{
			if (inputManager.GetKeyState(Windowing::Inputs::EKey::KEY_LEFT_SHIFT) == Windowing::Inputs::EKeyState::KEY_UP)
				EDITOR_EXEC(SaveSceneChanges());
			else
				EDITOR_EXEC(SaveAs());
		}
	}
}

void Editor::Panels::MenuBar::CreateFileMenu()
{
	auto& fileMenu = CreateWidget<MenuList>("File");
	fileMenu.CreateWidget<MenuItem>("New Scene", "CTRL + N").ClickedEvent					+= EDITOR_BIND(LoadEmptyScene);
	fileMenu.CreateWidget<MenuItem>("Save Scene", "CTRL + S").ClickedEvent					+= EDITOR_BIND(SaveSceneChanges);
	fileMenu.CreateWidget<MenuItem>("Save Scene As...", "CTRL + SHIFT + S").ClickedEvent	+= EDITOR_BIND(SaveAs);
	fileMenu.CreateWidget<MenuItem>("Exit", "ALT + F4").ClickedEvent						+= [] { EDITOR_CONTEXT(window)->SetShouldClose(true); };
}

void Editor::Panels::MenuBar::CreateBuildMenu()
{
	auto& buildMenu = CreateWidget<MenuList>("Build");
	buildMenu.CreateWidget<MenuItem>("Build game").ClickedEvent					+=	EDITOR_BIND(Build, false, false);
	buildMenu.CreateWidget<MenuItem>("Build game and run").ClickedEvent			+=	EDITOR_BIND(Build, true, false);
	buildMenu.CreateWidget<Visual::Separator>();
	buildMenu.CreateWidget<MenuItem>("Temporary build").ClickedEvent			+=	EDITOR_BIND(Build, true, true);
}

void Editor::Panels::MenuBar::CreateWindowMenu()
{
	m_windowMenu = &CreateWidget<MenuList>("Window");
	m_windowMenu->CreateWidget<MenuItem>("Close all").ClickedEvent	+= std::bind(&MenuBar::OpenEveryWindows, this, false);
	m_windowMenu->CreateWidget<MenuItem>("Open all").ClickedEvent		+= std::bind(&MenuBar::OpenEveryWindows, this, true);
	m_windowMenu->CreateWidget<Visual::Separator>();

	/* When the menu is opened, we update which window is marked as "Opened" or "Closed" */
	m_windowMenu->ClickedEvent += std::bind(&MenuBar::UpdateToggleableItems, this);
}

void Editor::Panels::MenuBar::CreateActorsMenu()
{
	auto& actorsMenu = CreateWidget<MenuList>("Actors");

	actorsMenu.CreateWidget<MenuItem>("Create Empty").ClickedEvent += EDITOR_BIND(CreateEmptyActor, true, nullptr);

	auto& primitives = actorsMenu.CreateWidget<MenuList>("Primitives");
	std::string modelsPath = ":Models\\";
	primitives.CreateWidget<MenuItem>("Cube").ClickedEvent		+= EDITOR_BIND(CreateActorWithModel, modelsPath + "Cube.fbx", true, nullptr);
	primitives.CreateWidget<MenuItem>("Sphere").ClickedEvent	+= EDITOR_BIND(CreateActorWithModel, modelsPath + "Sphere.fbx", true, nullptr);
	primitives.CreateWidget<MenuItem>("Cone").ClickedEvent		+= EDITOR_BIND(CreateActorWithModel, modelsPath + "Cone.fbx", true, nullptr);
	primitives.CreateWidget<MenuItem>("Cylinder").ClickedEvent	+= EDITOR_BIND(CreateActorWithModel, modelsPath + "Cylinder.fbx", true, nullptr);
	primitives.CreateWidget<MenuItem>("Plane").ClickedEvent		+= EDITOR_BIND(CreateActorWithModel, modelsPath + "Plane.fbx", true, nullptr);
	primitives.CreateWidget<MenuItem>("Gear").ClickedEvent		+= EDITOR_BIND(CreateActorWithModel, modelsPath + "Gear.fbx", true, nullptr);
	primitives.CreateWidget<MenuItem>("Helix").ClickedEvent		+= EDITOR_BIND(CreateActorWithModel, modelsPath + "Helix.fbx", true, nullptr);
	primitives.CreateWidget<MenuItem>("Pipe").ClickedEvent		+= EDITOR_BIND(CreateActorWithModel, modelsPath + "Pipe.fbx", true, nullptr);
	primitives.CreateWidget<MenuItem>("Pyramid").ClickedEvent	+= EDITOR_BIND(CreateActorWithModel, modelsPath + "Pyramid.fbx", true, nullptr);
	primitives.CreateWidget<MenuItem>("Torus").ClickedEvent		+= EDITOR_BIND(CreateActorWithModel, modelsPath + "Torus.fbx", true, nullptr);

	auto& physicals = actorsMenu.CreateWidget<MenuList>("Physicals");
	physicals.CreateWidget<MenuItem>("Physical Box").ClickedEvent		+= EDITOR_BIND(CreatePhysicalBox, true, nullptr);
	physicals.CreateWidget<MenuItem>("Physical Sphere").ClickedEvent	+= EDITOR_BIND(CreatePhysicalSphere, true, nullptr);
	physicals.CreateWidget<MenuItem>("Physical Capsule").ClickedEvent	+= EDITOR_BIND(CreatePhysicalCapsule, true, nullptr);

	auto& lights = actorsMenu.CreateWidget<MenuList>("Lights");
	lights.CreateWidget<MenuItem>("Point").ClickedEvent				+= EDITOR_BIND(CreateMonoComponentActor<CPointLight>, true, nullptr);
	lights.CreateWidget<MenuItem>("Directional").ClickedEvent		+= EDITOR_BIND(CreateMonoComponentActor<CDirectionalLight>, true, nullptr);
	lights.CreateWidget<MenuItem>("Spot").ClickedEvent				+= EDITOR_BIND(CreateMonoComponentActor<CSpotLight>, true, nullptr);
	lights.CreateWidget<MenuItem>("Ambient Box").ClickedEvent		+= EDITOR_BIND(CreateMonoComponentActor<CAmbientBoxLight>, true, nullptr);
	lights.CreateWidget<MenuItem>("Ambient Sphere").ClickedEvent	+= EDITOR_BIND(CreateMonoComponentActor<CAmbientSphereLight>, true, nullptr);

	//TODO
	//auto& audio = actorsMenu.CreateWidget<MenuList>("Audio");
	//audio.CreateWidget<MenuItem>("Audio Source").ClickedEvent	+= EDITOR_BIND(CreateMonoComponentActor<CAudioSource>, true, nullptr);
	//audio.CreateWidget<MenuItem>("Audio Listener").ClickedEvent += EDITOR_BIND(CreateMonoComponentActor<CAudioListener>, true, nullptr);

	auto& others = actorsMenu.CreateWidget<MenuList>("Others");
	others.CreateWidget<MenuItem>("Camera").ClickedEvent += EDITOR_BIND(CreateMonoComponentActor<CCamera>, true, nullptr);
}

void Editor::Panels::MenuBar::CreateResourcesMenu()
{
	auto& resourcesMenu = CreateWidget<MenuList>("Resources");
	resourcesMenu.CreateWidget<MenuItem>("Compile shaders").ClickedEvent += EDITOR_BIND(CompileShaders);
	resourcesMenu.CreateWidget<MenuItem>("Save materials").ClickedEvent += EDITOR_BIND(SaveMaterials);
}

void Editor::Panels::MenuBar::CreateSettingsMenu()
{
	auto& settingsMenu = CreateWidget<MenuList>("Settings");
	settingsMenu.CreateWidget<MenuItem>("Spawn actors at origin", "", true, true).ValueChangedEvent		+= EDITOR_BIND(SetActorSpawnAtOrigin, std::placeholders::_1);
	settingsMenu.CreateWidget<MenuItem>("Vertical Synchronization", "", true, true).ValueChangedEvent	+= [this](bool p_value) { EDITOR_CONTEXT(device)->SetVsync(p_value); };
	auto& cameraSpeedMenu = settingsMenu.CreateWidget<MenuList>("Camera Speed");
	cameraSpeedMenu.CreateWidget<UI::Widgets::Sliders::SliderInt>(1, 20, 5, UI::Widgets::Sliders::ESliderOrientation::HORIZONTAL, "Scene View").ValueChangedEvent += EDITOR_BIND(SetSceneViewCameraSpeed, std::placeholders::_1);
	cameraSpeedMenu.CreateWidget<UI::Widgets::Sliders::SliderInt>(1, 20, 5, UI::Widgets::Sliders::ESliderOrientation::HORIZONTAL, "Asset View").ValueChangedEvent += EDITOR_BIND(SetAssetViewCameraSpeed, std::placeholders::_1);
	auto& cameraPositionMenu = settingsMenu.CreateWidget<MenuList>("Reset Camera");
	cameraPositionMenu.CreateWidget<MenuItem>("Scene View").ClickedEvent += EDITOR_BIND(ResetSceneViewCameraPosition);
	cameraPositionMenu.CreateWidget<MenuItem>("Asset View").ClickedEvent += EDITOR_BIND(ResetAssetViewCameraPosition);

	auto& viewColors = settingsMenu.CreateWidget<MenuList>("View Colors");
	auto& sceneViewBackground = viewColors.CreateWidget<MenuList>("Scene View Background");
	auto& sceneViewBackgroundPicker = sceneViewBackground.CreateWidget<Selection::ColorEdit>(false, UI::Types::Color{ 0.278f, 0.278f, 0.278f });
	sceneViewBackgroundPicker.ColorChangedEvent += [this](const auto & color)
	{
		EDITOR_PANEL(Panels::SceneView, "Scene View").GetCamera().SetClearColor({ color.r, color.g, color.b });
	};
	sceneViewBackground.CreateWidget<MenuItem>("Reset").ClickedEvent += [this, &sceneViewBackgroundPicker]
	{
		EDITOR_PANEL(Panels::SceneView, "Scene View").GetCamera().SetClearColor({ 0.278f, 0.278f, 0.278f });
		sceneViewBackgroundPicker.color = { 0.278f, 0.278f, 0.278f };
	};

	auto& sceneViewGrid = viewColors.CreateWidget<MenuList>("Scene View Grid");
	auto& sceneViewGridPicker = sceneViewGrid.CreateWidget<Selection::ColorEdit>(false, UI::Types::Color::White);
	sceneViewGridPicker.ColorChangedEvent += [this](const auto & color)
	{
		EDITOR_PANEL(Panels::SceneView, "Scene View").SetGridColor({ color.r, color.g, color.b });
	};
	sceneViewGrid.CreateWidget<MenuItem>("Reset").ClickedEvent += [this, &sceneViewGridPicker]
	{
		EDITOR_PANEL(Panels::SceneView, "Scene View").SetGridColor(OvMaths::FVector3::One);
		sceneViewGridPicker.color = UI::Types::Color::White;
	};

	auto& assetViewBackground = viewColors.CreateWidget<MenuList>("Asset View Background");
	auto& assetViewBackgroundPicker = assetViewBackground.CreateWidget<Selection::ColorEdit>(false, UI::Types::Color{ 0.278f, 0.278f, 0.278f });
	assetViewBackgroundPicker.ColorChangedEvent += [this](const auto & color)
	{
		EDITOR_PANEL(Panels::AssetView, "Asset View").GetCamera().SetClearColor({ color.r, color.g, color.b });
	};
	assetViewBackground.CreateWidget<MenuItem>("Reset").ClickedEvent += [this, &assetViewBackgroundPicker]
	{
		EDITOR_PANEL(Panels::AssetView, "Asset View").GetCamera().SetClearColor({ 0.278f, 0.278f, 0.278f });
		assetViewBackgroundPicker.color = { 0.278f, 0.278f, 0.278f };
	};

	auto& assetViewGrid = viewColors.CreateWidget<MenuList>("Asset View Grid");
	auto& assetViewGridPicker = assetViewGrid.CreateWidget<Selection::ColorEdit>(false, UI::Types::Color::White);
	assetViewGridPicker.ColorChangedEvent += [this](const auto & color)
	{
		EDITOR_PANEL(Panels::AssetView, "Asset View").SetGridColor({ color.r, color.g, color.b });
	};
	assetViewGrid.CreateWidget<MenuItem>("Reset").ClickedEvent += [this, &assetViewGridPicker]
	{
		EDITOR_PANEL(Panels::AssetView, "Asset View").SetGridColor(OvMaths::FVector3::One);
		assetViewGridPicker.color = UI::Types::Color::White;
	};

	auto& sceneViewBillboardScaleMenu = settingsMenu.CreateWidget<MenuList>("3D Icons Scales");
	auto& lightBillboardScaleSlider = sceneViewBillboardScaleMenu.CreateWidget<Sliders::SliderInt>(0, 100, static_cast<int>(Settings::EditorSettings::LightBillboardScale * 100.0f), UI::Widgets::Sliders::ESliderOrientation::HORIZONTAL, "Lights");
	lightBillboardScaleSlider.ValueChangedEvent += [this](int p_value) { Settings::EditorSettings::LightBillboardScale = p_value / 100.0f; };
	lightBillboardScaleSlider.format = "%d %%";

	auto& snappingMenu = settingsMenu.CreateWidget<MenuList>("Snapping");
	snappingMenu.CreateWidget<Drags::DragFloat>(0.001f, 999999.0f, Settings::EditorSettings::TranslationSnapUnit, 0.05f, "Translation Unit").ValueChangedEvent += [this](float p_value) { Settings::EditorSettings::TranslationSnapUnit = p_value; };
	snappingMenu.CreateWidget<Drags::DragFloat>(0.001f, 999999.0f, Settings::EditorSettings::RotationSnapUnit, 1.0f, "Rotation Unit").ValueChangedEvent += [this](float p_value) { Settings::EditorSettings::RotationSnapUnit = p_value; };
	snappingMenu.CreateWidget<Drags::DragFloat>(0.001f, 999999.0f, Settings::EditorSettings::ScalingSnapUnit, 0.05f, "Scaling Unit").ValueChangedEvent += [this](float p_value) { Settings::EditorSettings::ScalingSnapUnit = p_value; };

	auto& debuggingMenu = settingsMenu.CreateWidget<MenuList>("Debugging");
	debuggingMenu.CreateWidget<MenuItem>("Show geometry bounds", "", true, Settings::EditorSettings::ShowGeometryBounds).ValueChangedEvent += [this](bool p_value) { Settings::EditorSettings::ShowGeometryBounds = p_value; };
	debuggingMenu.CreateWidget<MenuItem>("Show lights bounds", "", true, Settings::EditorSettings::ShowLightBounds).ValueChangedEvent += [this](bool p_value) { Settings::EditorSettings::ShowLightBounds = p_value; };
	auto& subMenu = debuggingMenu.CreateWidget<MenuList>("Frustum culling visualizer...");
	subMenu.CreateWidget<MenuItem>("For geometry", "", true, Settings::EditorSettings::ShowGeometryFrustumCullingInSceneView).ValueChangedEvent += [this](bool p_value) { Settings::EditorSettings::ShowGeometryFrustumCullingInSceneView = p_value; };
	subMenu.CreateWidget<MenuItem>("For lights", "", true, Settings::EditorSettings::ShowLightFrustumCullingInSceneView).ValueChangedEvent += [this](bool p_value) { Settings::EditorSettings::ShowLightFrustumCullingInSceneView = p_value; };
}

void Editor::Panels::MenuBar::CreateLayoutMenu() 
{
	auto& layoutMenu = CreateWidget<MenuList>("Layout");
	layoutMenu.CreateWidget<MenuItem>("Reset").ClickedEvent += EDITOR_BIND(ResetLayout);
}

void Editor::Panels::MenuBar::CreateHelpMenu()
{
    auto& helpMenu = CreateWidget<MenuList>("Help");
    helpMenu.CreateWidget<MenuItem>("GitHub").ClickedEvent += [] {Tools::Utils::SystemCalls::OpenURL("https://github.com/adriengivry/Overload"); };
    helpMenu.CreateWidget<MenuItem>("Tutorials").ClickedEvent += [] {Tools::Utils::SystemCalls::OpenURL("https://github.com/adriengivry/Overload/wiki/Tutorials"); };
    helpMenu.CreateWidget<MenuItem>("Scripting API").ClickedEvent += [] {Tools::Utils::SystemCalls::OpenURL("https://github.com/adriengivry/Overload/wiki/Scripting-API"); };
    helpMenu.CreateWidget<Visual::Separator>();
    helpMenu.CreateWidget<MenuItem>("Bug Report").ClickedEvent += [] {Tools::Utils::SystemCalls::OpenURL("https://github.com/adriengivry/Overload/issues/new?assignees=&labels=Bug&template=bug_report.md&title="); };
    helpMenu.CreateWidget<MenuItem>("Feature Request").ClickedEvent += [] {Tools::Utils::SystemCalls::OpenURL("https://github.com/adriengivry/Overload/issues/new?assignees=&labels=Feature&template=feature_request.md&title="); };
    helpMenu.CreateWidget<Visual::Separator>();
    helpMenu.CreateWidget<Texts::Text>("Version: 1.3.0");
}

void Editor::Panels::MenuBar::RegisterPanel(const std::string& p_name, UI::Panels::PanelWindow& p_panel)
{
	auto& menuItem = m_windowMenu->CreateWidget<MenuItem>(p_name, "", true, true);
	menuItem.ValueChangedEvent += std::bind(&UI::Panels::PanelWindow::SetOpened, &p_panel, std::placeholders::_1);

	m_panels.emplace(p_name, std::make_pair(std::ref(p_panel), std::ref(menuItem)));
}

void Editor::Panels::MenuBar::UpdateToggleableItems()
{
	for (auto&[name, panel] : m_panels)
		panel.second.get().checked = panel.first.get().IsOpened();
}

void Editor::Panels::MenuBar::OpenEveryWindows(bool p_state)
{
	for (auto&[name, panel] : m_panels)
		panel.first.get().SetOpened(p_state);
}
