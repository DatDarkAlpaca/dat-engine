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
		AttributesIt begin();

		AttributesIt end();

		AttributesCIt begin() const;
		
		AttributesCIt end() const;

	public:
		unsigned int stride() const;

	private:
		std::vector<Attribute> m_Attributes;
		unsigned int m_Stride = 0;
	};
}