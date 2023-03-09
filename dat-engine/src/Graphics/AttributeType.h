#pragma once
#include <numeric>

namespace dat
{
	enum AttributeType : uint32_t
	{
		NONE				= 0x0000,
		BYTE				= 0x1400,
		UNSIGNED_BYTE		= 0x1401,
		SHORT				= 0x1402,
		UNSIGNED_SHORT		= 0x1403,
		INT					= 0x1404,
		UNSIGNED_INT		= 0x1405,
		FLOAT				= 0x1406 
	};

	inline unsigned int getAttributeSize(AttributeType attribute)
	{
		if (attribute == BYTE || attribute == UNSIGNED_BYTE)
			return sizeof(char);

		else if (attribute == SHORT || attribute == UNSIGNED_SHORT)
			return sizeof(short);

		else if (attribute == INT || attribute == UNSIGNED_INT || attribute == FLOAT)
			return sizeof(float);

		else
			return 0;
	}
}