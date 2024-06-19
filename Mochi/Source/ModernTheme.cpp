#include "ModernTheme.hpp"

#include <imgui.h>
#include <cstdint>

namespace Mochi::Internal
{
	namespace Colors
	{
		constexpr uint32_t Highlight = IM_COL32(39, 185, 242, 255);
		constexpr uint32_t Background = IM_COL32(36, 36, 36, 255);
		constexpr uint32_t BackgroundDark = IM_COL32(26, 26, 26, 255);
		constexpr uint32_t TitleBar = IM_COL32(21, 21, 21, 255);
		constexpr uint32_t PropertyField = IM_COL32(15, 15, 15, 255);
		constexpr uint32_t Text = IM_COL32(192, 192, 192, 255);
		// constexpr uint32_t TextBrighter = IM_COL32(210, 210, 210, 255);
		// constexpr uint32_t TextDarker = IM_COL32(128, 128, 128, 255);
		// constexpr uint32_t TextError = IM_COL32(230, 51, 51, 255);
		constexpr uint32_t GroupHeader = IM_COL32(47, 47, 47, 255);
		constexpr uint32_t BackgroundPopup = IM_COL32(50, 50, 50, 255);
		constexpr uint32_t Button = IM_COL32(56, 56, 56, 200);
		constexpr uint32_t ButtonHovered = IM_COL32(70, 70, 70, 255);
		constexpr uint32_t ButtonActive = IM_COL32(56, 56, 56, 150);
	}

	void SetModernColors()
	{
		// A slightly modified version of the "Hazel theme" from Walnut: https://github.com/StudioCherno/Walnut/blob/dev/Walnut/Platform/GUI/Walnut/ImGui/ImGuiTheme.cpp#L5
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4* colors = ImGui::GetStyle().Colors;

		// Headers
		colors[ImGuiCol_Header] = ImGui::ColorConvertU32ToFloat4(Colors::Button);
		colors[ImGuiCol_HeaderHovered] = ImGui::ColorConvertU32ToFloat4(Colors::ButtonHovered);
		colors[ImGuiCol_HeaderActive] = ImGui::ColorConvertU32ToFloat4(Colors::ButtonActive);

		// Buttons
		colors[ImGuiCol_Button] = ImGui::ColorConvertU32ToFloat4(Colors::Button);
		colors[ImGuiCol_ButtonHovered] = ImGui::ColorConvertU32ToFloat4(Colors::ButtonHovered);
		colors[ImGuiCol_ButtonActive] = ImGui::ColorConvertU32ToFloat4(Colors::ButtonActive);

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImGui::ColorConvertU32ToFloat4(Colors::PropertyField);
		colors[ImGuiCol_FrameBgHovered] = ImGui::ColorConvertU32ToFloat4(Colors::PropertyField);
		colors[ImGuiCol_FrameBgActive] = ImGui::ColorConvertU32ToFloat4(Colors::PropertyField);

		// Tabs
		colors[ImGuiCol_Tab] = ImGui::ColorConvertU32ToFloat4(Colors::Button);
		colors[ImGuiCol_TabHovered] = ImGui::ColorConvertU32ToFloat4(Colors::ButtonActive);
		colors[ImGuiCol_TabActive] = ImGui::ColorConvertU32ToFloat4(Colors::ButtonHovered);
		colors[ImGuiCol_TabUnfocused] = ImGui::ColorConvertU32ToFloat4(Colors::Button);
		colors[ImGuiCol_TabUnfocusedActive] = colors[ImGuiCol_TabHovered];

		// Title
		colors[ImGuiCol_TitleBg] = ImGui::ColorConvertU32ToFloat4(Colors::TitleBar);
		colors[ImGuiCol_TitleBgActive] = ImGui::ColorConvertU32ToFloat4(Colors::TitleBar);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.15f, 0.1505f, 0.151f, 1.0f);

		// Resize Grip
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.91f, 0.91f, 0.91f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.81f, 0.81f, 0.81f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.46f, 0.46f, 0.46f, 0.95f);

		// Scrollbar
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.0f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.0f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.0f);

		// Check Mark
		colors[ImGuiCol_CheckMark] = ImColor(200, 200, 200, 255);

		// Slider
		colors[ImGuiCol_SliderGrab] = ImVec4(0.51f, 0.51f, 0.51f, 0.7f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.66f, 0.66f, 0.66f, 1.0f);

		// Text
		colors[ImGuiCol_Text] = ImGui::ColorConvertU32ToFloat4(Colors::Text);

		// Checkbox
		colors[ImGuiCol_CheckMark] = ImGui::ColorConvertU32ToFloat4(Colors::Text);

		// Separator
		colors[ImGuiCol_Separator] = ImGui::ColorConvertU32ToFloat4(Colors::BackgroundDark);
		colors[ImGuiCol_SeparatorActive] = ImGui::ColorConvertU32ToFloat4(Colors::Highlight);
		colors[ImGuiCol_SeparatorHovered] = ImColor(39, 185, 242, 150);

		// Window Background
		colors[ImGuiCol_WindowBg] = ImGui::ColorConvertU32ToFloat4(Colors::TitleBar);
		colors[ImGuiCol_ChildBg] = ImGui::ColorConvertU32ToFloat4(Colors::Background);
		colors[ImGuiCol_PopupBg] = ImGui::ColorConvertU32ToFloat4(Colors::BackgroundPopup);
		colors[ImGuiCol_Border] = ImGui::ColorConvertU32ToFloat4(Colors::BackgroundDark);

		// Tables
		colors[ImGuiCol_TableHeaderBg] = ImGui::ColorConvertU32ToFloat4(Colors::GroupHeader);
		colors[ImGuiCol_TableBorderLight] = ImGui::ColorConvertU32ToFloat4(Colors::BackgroundDark);

		// Menu bar
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

		// Style
		style.FrameBorderSize = 1.0f;
		style.IndentSpacing	= 11.0f;
	}
}
