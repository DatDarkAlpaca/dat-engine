#pragma once
#include "AttributeType.h"

namespace dat
{
	struct Attribute
	{
		unsigned int location = -1;
		size_t size = 0;
		AttributeType type = AttributeType::NONE;
		bool normalized = 0;
	};
}