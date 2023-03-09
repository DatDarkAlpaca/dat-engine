#pragma once

namespace dat
{
	enum AttributeType : uint32_t
	{
		NONE			= 0x0000,
		BYTE			= 0x1400, // 5120
		UNSIGNED_BYTE	= 0x1401, // 5121
		SHORT			= 0x1402, // 5122
		UNSIGNED_SHORT	= 0x1403, // 5123
		INT				= 0x1404, // 5124
		UNSIGNED_INT	= 0x1405, // 5125
		FLOAT			= 0x1406  // 5126
	};

	struct Attribute
	{
		unsigned int location = -1;
		size_t size = 0;
		AttributeType type = AttributeType::NONE;
		bool normalized = 0;
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

	class VertexAttributes
	{
	private:
		using AttributesCIt = std::vector<Attribute>::const_iterator;
		using AttributesIt = std::vector<Attribute>::iterator;

	public:
		VertexAttributes() = default;

	public:
		void addAttribute(unsigned int location, size_t size, AttributeType type, bool normalized)
		{
			m_Attributes.push_back({ location, size, type, normalized });
			m_Stride += size * getAttributeSize(type);
		}

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