#include "pch.hpp"
#include "View.hpp"

#include "Core/Engine/Engine.hpp"

namespace dat
{
	AssetLibrary& View::AssetLibrary() const
	{
		return engine->GetAssetLibrary();
	}

	WorkerPool& View::WorkerPool() const
	{
		return engine->GetWorkerPool();
	}
}

