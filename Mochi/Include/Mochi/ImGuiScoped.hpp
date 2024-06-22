#pragma once

namespace Mochi
{
	class ScopedImGuiID
	{
	public:
		ScopedImGuiID(int id);
		~ScopedImGuiID();
	};
}
