#include "pch.hpp"
#include "ViewSystem.hpp"

namespace dat
{
	ViewHandle ViewSystem::Add(dat_unique<View> view)
	{
		view->OnViewInstantiated();
		view->SetHandler(this);

		m_Views.push_back(std::move(view));

		return m_Views.size() - 1;
	}

	void ViewSystem::Remove(ViewHandle handle)
	{
		auto it = m_Views.begin() + handle;
		it->get()->OnViewRemoved();

		m_Views.erase(it);
	}

	View& ViewSystem::GetView(ViewHandle handle)
	{
		DAT_ASSERT(m_Views.size() - 1 <= handle, "Invalid view index selected");
		return *m_Views[handle].get();
	}
}