#include "pch.h"
#include "VertexAttributes.h"

namespace dat
{
	void VertexAttributes::addAttribute(unsigned int location, size_t size, AttributeType type, bool normalized)
	{
		m_Attributes.push_back({ location, size, type, normalized });
		m_Stride += size * getAttributeSize(type);
	}
}