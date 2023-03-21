#pragma once
#include "PerspectiveCamera.h"
#include "Input/Input.h"
#include "glm/gtx/rotate_vector.hpp"

namespace dat
{
	PerspectiveCamera::PerspectiveCamera(float fov, float screenWidth, float screenHeight, float near, float far)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(fov), screenWidth / screenHeight, near, far);
	}

	void PerspectiveCamera::onUpdate(Timestep dt)
	{
		m_ViewMatrix = glm::lookAt(m_CameraPosition, m_CameraPosition + m_Orientation, m_Up);

		m_CameraPosition += speed * m_Orientation * m_Movement.x * (float)dt.timestep();
		m_CameraPosition += speed * glm::normalize(glm::cross(m_Orientation, m_Up)) * m_Movement.y * (float)dt.timestep();
	
		if (Input::isKeyDown(KEY_4))
			m_Orientation = glm::rotate(m_Orientation, glm::radians(25.f * (float)dt.timestep()), m_Up);
		else if (Input::isKeyDown(KEY_5))
			m_Orientation = glm::rotate(m_Orientation, glm::radians(-25.f * (float)dt.timestep()), m_Up);

		m_CameraPosition.y += speed * (float)dt.timestep() * m_Movement.z;
	}

	void PerspectiveCamera::onEvent(IEvent& event)
	{
		if (Input::isMouseButtonDown(MOUSE_BUTTON_LEFT))
			clickedIn = true;
				
		if (Input::isKeyDown(KEY_W))
			m_Movement.x = 1.f;
		else if (Input::isKeyDown(KEY_S))
			m_Movement.x = -1.f;
		else
			m_Movement.x = 0;

		if (Input::isKeyDown(KEY_D))
			m_Movement.y = 1.f;
		else if (Input::isKeyDown(KEY_A))
			m_Movement.y = -1.f;
		else
			m_Movement.y = 0.f;

		if (Input::isKeyDown(KEY_SPACE))
			m_Movement.z = 1.f;
		else if (Input::isKeyDown(KEY_LEFT_CONTROL))
			m_Movement.z = -1.f;
		else
			m_Movement.z = 0.f;

		if (!clickedIn)
			return;

		auto pos = Input::getMousePosition();
	
	}
}