#pragma once
#include "pch.h"
#include "Event/IEvent.h"
#include "Timestep.h"

namespace dat
{
	class DAT_API ICamera
	{
	public:
		ICamera() = default;
		virtual ~ICamera() = default;

	public:
		virtual void onUpdate(Timestep dt) = 0;

		virtual void onEvent(IEvent& event) { }

	public:
		void setPosition(const glm::vec3& position) { m_CameraPosition = position; }

		const glm::mat4& projection() const { return m_ProjectionMatrix; }

		const glm::mat4& view() const { return m_ViewMatrix; }

		const glm::vec3& position() const { return m_CameraPosition; }

	protected:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0), m_ViewMatrix = glm::mat4(1.0);
		glm::vec3 m_CameraPosition = { 0, 0, 0 };
	};
}