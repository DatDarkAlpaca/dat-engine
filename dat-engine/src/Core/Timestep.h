#pragma once

namespace dat
{
	class Timestep
	{
	public:
		Timestep(double time) : m_Timestep (time) { }

	public:
		double timestep() const { return m_Timestep; }

	public:
		double m_Timestep;
	};
}