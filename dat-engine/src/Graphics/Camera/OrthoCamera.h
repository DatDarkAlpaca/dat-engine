#pragma once
#include "pch.h"
#include "ICamera.h"

namespace dat
{
	class DAT_API OrthoCamera : public ICamera
	{
	public:
		OrthoCamera(float left, float right, float bottom, float top, float near = -1, float far = 1);

	public:
		void onUpdate(Timestep dt) override;
	};
}