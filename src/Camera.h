#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"


class Camera
{
public:
	Camera(const glm::vec3& position, const glm::vec3& facedTo, const glm::vec3& up = glm::vec3(0.f, 1.f, 0.f));

	glm::mat4 View();
	glm::mat4 Projection();
	
	glm::vec3 FaceToDirection();
	glm::vec3 FaceToPoint();
	glm::vec3 Position();


	void rotate(float horizontalAngle, float verticalAngle);
	void move(float forward, float right);

	



private:
	void updateMatrix();
	
	glm::mat4 m_view;
	glm::mat4 m_projection;

	glm::vec3 m_cameraPosition;
	glm::vec3 m_cameraFacedTo;
	glm::vec3 m_cameraUp;
};