
#include "UI/Widgets/Buttons/ButtonImage.h"
#include "UI/Internal/Converter.h"
#include "UI/ImGui/imgui_internal.h"

UI::Widgets::Buttons::ButtonImage::ButtonImage(uint32_t p_textureID, const OvMaths::FVector2 & p_size) :
	textureID{ p_textureID }, size(p_size)
{
}

void UI::Widgets::Buttons::ButtonImage::_Draw_Impl()
{
	ImVec4 bg = Internal::Converter::ToImVec4(background);
	ImVec4 tn = Internal::Converter::ToImVec4(tint);

	if (ImGui::ImageButton(textureID.raw, Internal::Converter::ToImVec2(size), ImVec2(0.f, 1.f), ImVec2(1.f, 0.f), -1, bg, tn, disabled ? ImGuiButtonFlags_Disabled : 0))
		ClickedEvent.Invoke();
}
