#pragma once

#include "../../Source/Base.hpp"

namespace Mochi
{
	struct ApplicationIcon
	{
		// The path to the icon. Ignored if Data is not nullptr.
		std::string_view Path;
		// The image data. Remember to also set DataBufferSize.
		const uint8_t* Data = nullptr;
		// The size of Data.
		int DataBufferSize = 0;
	};
}
