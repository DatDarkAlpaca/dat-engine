#pragma once
#include "Utils/UUID.hpp"
#include <string>

namespace dat
{
	struct IdentifierComponent
	{
	public:
		IdentifierComponent() = default;
		IdentifierComponent(const IdentifierComponent&) = default;

	public:
		UUID uuid;
	};

	struct NameComponent
	{
	public:
		NameComponent() = default;
		NameComponent(const NameComponent&) = default;
		NameComponent(const std::string& name) : name(name) { }

	public:
		std::string name;
	};
}