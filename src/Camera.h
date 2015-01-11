#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"
#include <glm/gtc/quaternion.hpp>

class Camera
{
public:
	Camera(const glm::vec3& position, const glm::vec3& facedTo, const glm::vec3& up = glm::vec3(0.f, 1.f, 0.f));

	glm::mat4 View();
	glm::mat4 Projection();
	glm::vec3 Position();
	glm::mat4 NormalMatrix();
	glm::vec3 FaceToDirection();

	void rotate(float horizontalAngle, float verticalAngle);
	void pitch(float angle);
	void yaw(float angle);
	void move(float x, float y, float z);
	void move(float forward, float right);

private:
	void updateMatrix();
	glm::vec3 Right();	

	glm::mat4 m_view;
	glm::mat4 m_projection;

	glm::vec3 m_position;

	glm::vec3 m_direction;
	glm::vec3 m_cameraUp;
};