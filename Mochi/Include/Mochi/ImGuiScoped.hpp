#pragma once

#include "../../Source/Base.hpp"

struct ImVec2;
struct ImVec4;

namespace Mochi
{
	class ScopedImGuiID
	{
	public:
		ScopedImGuiID(int id);
		~ScopedImGuiID();
	};

	class ScopedImGuiStyle
	{
	public:
		~ScopedImGuiStyle();

		void PushStyleVar(int styleVar, float value);
		void PushStyleVar(int styleVar, const ImVec2& value);
		void PushStyleColor(int color, uint32_t value);
		void PushStyleColor(int color, const ImVec4& value);
	private:
		int m_StyleCount = 0;
		int m_ColorCount = 0;
	};
}
