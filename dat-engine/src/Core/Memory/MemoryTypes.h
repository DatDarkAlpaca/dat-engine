#pragma once
#include <memory>

namespace dat
{
	template<typename T> using dat_shared = std::shared_ptr<T>;

	template<typename T> using dat_unique = std::unique_ptr<T>;

	template<typename T> using dat_weak = std::weak_ptr<T>;
}