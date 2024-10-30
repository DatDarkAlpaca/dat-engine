#pragma once
#include <numeric>
#include "Utils/Random.hpp"

namespace dat
{
	class UUID
	{
	public:
		UUID()
			: m_UUID(GenerateRandom<std::uint64_t>())
		{

		}

	public:
		operator uint64_t() const { return m_UUID; }

	private:
		std::uint64_t m_UUID;
	};
}

namespace std
{
	template <typename T> struct hash;

	template<>
	struct hash<dat::UUID>
	{
		size_t operator()(const dat::UUID& uuid) const
		{
			return (uint64_t)uuid;
		}
	};
}