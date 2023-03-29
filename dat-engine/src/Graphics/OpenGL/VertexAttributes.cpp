#include "pch.h"
#include "VertexAttributes.h"

namespace dat
{
	void VertexAttributes::addAttribute(unsigned int location, size_t size, AttributeType type, bool normalized)
	{
		m_Attributes.push_back({ location, size, type, normalized });
		m_Stride += size * getAttributeSize(type);
	}

	VertexAttributes::AttributesIt VertexAttributes::begin()
	{
		return m_Attributes.begin();
	}

	VertexAttributes::AttributesIt VertexAttributes::end()
	{
		return m_Attributes.end();
	}

	VertexAttributes::AttributesCIt VertexAttributes::begin() const
	{
		return m_Attributes.cbegin();
	}

	VertexAttributes::AttributesCIt VertexAttributes::end() const
	{
		return m_Attributes.cend();
	}

	unsigned int VertexAttributes::stride() const
	{
		return m_Stride;
	}
}