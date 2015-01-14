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


void Camera::rotate(glm::vec3 rotateOn)
{
	pitch(rotateOn.x);
	yaw(rotateOn.y);
	roll(rotateOn.z);
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


void Camera::roll(float angle)
{

}


void Camera::move(float forward, float right)
{
	move(right, 0.f, forward);
}


void Camera::move(float x, float y, float z)
{
	move(vec3(x, y, z));
}


void Camera::move(vec3 moveOn)
{
	if (moveOn == vec3(0.f))
		return;

	vec3 movingDirection = glm::normalize(moveOn * m_direction); 

	m_position += glm::abs(moveOn) * movingDirection;

	updateMatrix();
}


std::shared_ptr<Interpolation> Camera::getMoveInterpolation(float x, float y, float z, float startTime, float endTime)
{
	return std::shared_ptr<Interpolation>(new MoveInterpolation(this, startTime, endTime, glm::vec3(x, y, z)));
}


std::shared_ptr<Interpolation> Camera::getRotateInterpolation(float pitchAngle, float yawAngle, float rollAngle, float startTime, float endTime)
{
	return std::shared_ptr<Interpolation>(new RotateInterpolation(this, startTime, endTime, glm::vec3(pitchAngle, yawAngle, rollAngle)));
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





Camera::MoveInterpolation::MoveInterpolation(Camera* camera, int startTime, int endTime, glm::vec3 moneOn):
	m_camera(camera),
	m_moveOn(moneOn),
	m_startTime(startTime),
	m_endTime(endTime),
	m_previousStep(startTime)
{
	m_step = m_moveOn / float(m_endTime - m_startTime);
}


void Camera::MoveInterpolation::interpolate(int currentTime)
{
	if (m_camera)
	{
		vec3 currentValue = m_step * float(currentTime - m_previousStep);
		m_camera->move(currentValue);
		m_previousStep = currentTime;
	}
}


bool Camera::MoveInterpolation::isValid(int currentTime)
{
	return currentTime < m_endTime; 
}


Camera::RotateInterpolation::RotateInterpolation(Camera* camera, float startTime, float endTime, glm::vec3 rotateAngle) :
	m_camera(camera),
	m_rotateAngle(rotateAngle),
	m_startTime(startTime),
	m_endTime(endTime),
	m_previousStep(startTime)
{
	m_step = m_rotateAngle / float(m_endTime - m_startTime);
}


void Camera::RotateInterpolation::interpolate(int currentTime)
{
	if (m_camera)
	{
		vec3 currentValue = m_step * float(currentTime - m_previousStep);
		m_camera->rotate(currentValue);
		m_previousStep = currentTime;
	}
}


bool Camera::RotateInterpolation::isValid(int currentTime)
{
	return currentTime < m_endTime; 
}
