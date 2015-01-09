#include <iostream>

#include "Camera.h"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/ext.hpp"


Camera::Camera(const glm::vec3& position, const glm::vec3& facedTo, const glm::vec3& up /*= glm::vec3(0.f, 1.f, 0.f)*/) :
	m_cameraPosition(position),
	m_cameraFacedTo(facedTo),
	m_cameraUp(up)
{
	updateMatrix();
}

void Camera::rotate(float horizontalAngle, float verticalAngle)
{
	glm::vec3 direction = m_cameraFacedTo - m_cameraPosition;
	glm::vec3 newDirection = glm::rotateY(direction, -horizontalAngle);
	//change the faced to point accordingly to new direction
	m_cameraFacedTo = newDirection - m_cameraPosition;

	updateMatrix();
}


void Camera::move(float forward, float right)
{

	Direction();


	//we don't want to go up
	glm::vec3 faceTo_XZ(direction.x, 0, direction.z);
	glm::vec3 stepForward = glm::normalize( faceTo_XZ) * forward;

	m_cameraPosition += stepForward;

	direction = m_cameraFacedTo - m_cameraPosition;

	glm::vec3 rightVector = glm::cross(direction, m_cameraUp);
	glm::vec3 right_XZ(rightVector.x, 0, rightVector.z);
	glm::vec3 stepRight = glm::normalize(right_XZ) * right;

	m_cameraPosition += stepRight;

	updateMatrix();
}


void Camera::updateMatrix()
{
	m_view = glm::lookAt(m_cameraPosition,	m_cameraFacedTo, m_cameraUp);
	m_projection = glm::perspective(45.f, 1.f, 0.01f, 1000.f); 

	std::cout << "Camera Position\n" << glm::to_string(m_cameraPosition) << "\n";
	std::cout << "Faced to \n" << glm::to_string(m_cameraFacedTo) << "\n";
}


glm::vec3 Camera::FaceToDirection()
{
	return m_cameraFacedTo - m_cameraPosition;
}


glm::vec3 Camera::FaceToPoint()
{
	return m_cameraFacedTo;
}


glm::vec3 Camera::Position()
{
	return m_cameraPosition;
}


glm::mat4 Camera::View()
{
	return m_view;
}


glm::mat4 Camera::Projection()
{
	return m_projection;
}