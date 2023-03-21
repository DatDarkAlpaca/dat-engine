#include "OrthoCamera.h"

namespace dat
{
	OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float near, float far)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, near, far);
	}

	void OrthoCamera::onUpdate(Timestep dt)
	{
		m_ViewMatrix = glm::inverse(glm::translate(glm::mat4(1.0), m_CameraPosition));
	}
}