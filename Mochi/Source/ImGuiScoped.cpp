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
}
