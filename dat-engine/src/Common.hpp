#pragma once
#include <numeric>
#include <limits>
#include <filesystem>

#include "Core/Defines.hpp"
#include "Core/NonCopyable.hpp"

#include "Core/Memory/Memory.hpp"
#include "Core/Logger/Logger.hpp"
#include "Core/Assert/Assert.hpp"

#include "Utils/JSON/JsonCommon.hpp"

#define BIND(function, argument) std::bind(function, argument, std::placeholders::_1)

#define EXPOSE_PROPERTY(ClassName, SetterName, PropertyName)						\
	const ClassName& SetterName() const { return PropertyName; }					\
	ClassName& SetterName() { return PropertyName; }