#pragma once
#include <vector>
#include "View.hpp"
#include "Common.hpp"

namespace dat
{
	using ViewHandle = size_t;

	class ViewSystem
	{
		using ViewContainer = std::vector<dat_unique<View>>;

	public:
		ViewHandle Add(dat_unique<View> view);

		void Remove(ViewHandle index);

		View& GetView(ViewHandle index);

	public:
		ViewContainer::reverse_iterator rbegin() { return m_Views.rbegin(); }
		ViewContainer::reverse_iterator rend() { return m_Views.rend(); }
		ViewContainer::iterator begin() { return m_Views.begin(); }
		ViewContainer::iterator end() { return m_Views.end(); }

		ViewContainer::const_reverse_iterator rbegin() const { return m_Views.rbegin(); }
		ViewContainer::const_reverse_iterator rend() const { return m_Views.rend(); }
		ViewContainer::const_iterator begin() const { return m_Views.begin(); }
		ViewContainer::const_iterator end()	const { return m_Views.end(); }

	private:
		std::vector<dat_unique<View>> m_Views;
	};
}