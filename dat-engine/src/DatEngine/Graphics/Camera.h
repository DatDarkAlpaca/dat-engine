#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace dat
{
	class OrthoCamera
	{
	public:
		OrthoCamera(float height, float _near, float _far, float aspectRatio)
			: m_Height(height), m_Near(_near), m_Far(_far), m_AspectRatio(aspectRatio)
		{
			computeProjectionMatrix();
		}

		OrthoCamera(const OrthoCamera& other)
			: m_Height(other.m_Height),
			  m_Near(other.m_Near),
			  m_Far(other.m_Far),
			  m_AspectRatio(other.m_AspectRatio)
		{
			computeProjectionMatrix();
		}

	public:
		void setHeight(float height)
		{
			m_Height = height;
			computeProjectionMatrix();
		}

		void setNear(float _near)
		{
			m_Near = _near;
			computeProjectionMatrix();
		}
		
		void setFar(float _far)
		{
			m_Far = _far;
			computeProjectionMatrix();
		}

		void setAspectRatio(float aspectRatio)
		{
			m_AspectRatio = aspectRatio;
			computeProjectionMatrix();
		}

	public:
		inline float getHeight() const { return m_Height; }

		inline float getNear() const { return m_Near; }

		inline float getFar() const { return m_Far; }

		inline float getAspectRatio() const { return m_AspectRatio; }

	public:
		const glm::mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }

	private:
		void computeProjectionMatrix() 
		{
			float halfWidth = m_Height * m_AspectRatio * 0.5f;
			float halfHeight = m_Height * 0.5f;
			m_ProjectionMatrix = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, m_Near, m_Far);
		}

	private:
		float m_Height = 0.f, m_Near = 0.f, m_Far = 0.f;
		float m_AspectRatio = 1.0f;

	private:
		glm::vec2 m_Position = glm::vec2(0.0, 0.0);
		glm::mat4 m_ProjectionMatrix;
	};
}