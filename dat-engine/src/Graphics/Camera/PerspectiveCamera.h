#pragma once
#include "pch.h"
#include "ICamera.h"

namespace dat
{
	class DAT_API PerspectiveCamera : public ICamera
	{
	public:
		PerspectiveCamera(float fov, float screenWidth, float screenHeight, float near, float far);

	public:
		void onUpdate(Timestep dt) override;

		void onEvent(IEvent&) override;

	public:
		float speed = 2.f;

	private:
		glm::vec3 m_Orientation = glm::vec3(0.f, 0.f, -1.f), m_Up = glm::vec3(0.f, 1.f, 0.f);
		glm::vec3 m_Movement = glm::vec3(0.f, 0.f, 0.f);

	public:
		bool clickedIn = false;
	};
}