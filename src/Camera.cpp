#include <iostream>

#include "Camera.h"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/ext.hpp"

using glm::vec4;
using glm::mat4;
using glm::vec3;



Camera::Camera(const glm::vec3& position, const glm::vec3& facedTo, const glm::vec3& up /*= glm::vec3(0.f, 1.f, 0.f)*/) :
	m_position(position),
	m_direction(glm::normalize(facedTo - position)),
	m_cameraUp(up)
{
	updateMatrix();
}

void Camera::rotate(float horizontalAngle, float verticalAngle)
{
	yaw(horizontalAngle);
	pitch(verticalAngle);
}


void Camera::pitch(float angle)
{
	if (angle == 0.f)
		return;
	vec3 right = Right();
	glm::quat q = glm::angleAxis(angle, right);

	m_cameraUp = glm::rotate(q, m_cameraUp);
	m_direction = glm::rotate(q, m_direction);

	updateMatrix();
}


void Camera::yaw(float angle) 
{
	if (angle == 0.f)
		return;
	
	glm::quat q = glm::angleAxis(angle, m_cameraUp);
	m_direction = glm::rotate(q, m_direction);

	updateMatrix();
}


void Camera::move(float forward, float right)
{
	move(right, 0.f, forward);
}


void Camera::move(float x, float y, float z)
{
	vec3 moveTo = vec3(x, y, z);
	if (moveTo == vec3(0.f))
		return;
	
	m_position += moveTo;
	
	updateMatrix();
}


void Camera::updateMatrix()
{
	m_view = glm::lookAt(m_position, m_direction + m_position, m_cameraUp);
	m_projection = glm::perspective(45.f, 1.f, 0.01f, 1000.f); 
}


glm::vec3 Camera::FaceToDirection()
{
	return m_direction;
}


glm::vec3 Camera::Position()
{
	return m_position;
}


glm::mat4 Camera::View()
{

	return m_view;
}


glm::mat4 Camera::Projection()
{
	return m_projection;
}


glm::vec3 Camera::Right()
{
	return glm::normalize(glm::cross(m_direction, m_cameraUp));
}


glm::mat4 Camera::NormalMatrix()
{
	return glm::transpose(glm::inverse(m_view));
}


