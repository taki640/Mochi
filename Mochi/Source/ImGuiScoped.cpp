#include "ImGuiScoped.hpp"

#include <imgui.h>

namespace Mochi
{
	ScopedImGuiID::ScopedImGuiID(int id)
	{
		ImGui::PushID(id);
	}

	ScopedImGuiID::~ScopedImGuiID()
	{
		ImGui::PopID();
	}

	ScopedImGuiStyle::~ScopedImGuiStyle()
	{
		ImGui::PopStyleColor(m_ColorCount);
		ImGui::PopStyleVar(m_StyleCount);
	}

	void ScopedImGuiStyle::PushStyleVar(ImGuiStyleVar styleVar, float value)
	{
		ImGui::PushStyleVar(styleVar, value);
		m_StyleCount++;
	}

	void ScopedImGuiStyle::PushStyleVar(ImGuiStyleVar styleVar, const ImVec2& value)
	{
		ImGui::PushStyleVar(styleVar, value);
		m_StyleCount++;
	}

	void ScopedImGuiStyle::PushStyleColor(ImGuiCol color, ImU32 value)
	{
		ImGui::PushStyleColor(color, value);
		m_ColorCount++;
	}

	void ScopedImGuiStyle::PushStyleColor(ImGuiCol color, const ImVec4& value)
	{
		ImGui::PushStyleColor(color, value);
		m_ColorCount++;
	}
}
