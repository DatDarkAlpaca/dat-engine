#pragma once
#include "AttributeType.h"
#include "Attribute.h"

namespace dat
{
	class VertexAttributes
	{
	private:
		using AttributesCIt = std::vector<Attribute>::const_iterator;
		using AttributesIt = std::vector<Attribute>::iterator;

	public:
		VertexAttributes() = default;

	public:
		void addAttribute(unsigned int location, size_t size, AttributeType type, bool normalized);

	public:
		AttributesIt begin() { return m_Attributes.begin(); }

		AttributesIt end() { return m_Attributes.end(); }

		AttributesCIt begin() const { return m_Attributes.cbegin(); }
		
		AttributesCIt end() const { return m_Attributes.cend(); }

	public:
		unsigned int stride() const { return m_Stride; }

	private:
		std::vector<Attribute> m_Attributes;
		unsigned int m_Stride = 0;
	};
}