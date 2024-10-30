#pragma once
#include <memory>

// Raw pointer purpose identifiers
#define NON_OWNING

namespace dat
{
	template<typename T, typename Deleter = std::default_delete<T>>
	using dat_unique = std::unique_ptr<T, Deleter>;

	template<typename T, typename ... Args>
	constexpr dat_unique<T> MakeUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using dat_shared = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr dat_shared<T> MakeShared(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using dat_weak = std::weak_ptr<T>;
}