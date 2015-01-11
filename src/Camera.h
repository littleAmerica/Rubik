#pragma once

#include <memory>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"
#include <glm/gtc/quaternion.hpp>

#include "Interpolation.h"


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
	void rotate(glm::vec3 rotateOn);
	void pitch(float angle);
	void yaw(float angle);
	void roll(float angle);
	void move(float x, float y, float z);
	void move(float forward, float right);
	void move(glm::vec3 moveOn);
	
	std::shared_ptr<Interpolation> getMoveInterpolation(float x, float y, float z, float startTime, float endTime);
	std::shared_ptr<Interpolation> getRotateInterpolation(float x, float y, float z, float startTime, float endTime);

private:
	void updateMatrix();
	glm::vec3 Right();	

	glm::mat4 m_view;
	glm::mat4 m_projection;

	glm::vec3 m_position;

	glm::vec3 m_direction;
	glm::vec3 m_cameraUp;


	class MoveInterpolation: public Interpolation
	{
	public:
		MoveInterpolation(Camera* camera, int startTime, int endTime, glm::vec3 moneOn);
		virtual void interpolate(int currentTime);
		virtual bool isValid(int currentTime);
		
	private:
		Camera* m_camera;
		glm::vec3 m_moveOn;
		
		glm::vec3 m_step;
		int m_startTime;
		int m_endTime;
		int m_previousStep;
	};

	class RotateInterpolation: public Interpolation
	{
	public:
		RotateInterpolation(Camera* camera, float startTime, float endTime, glm::vec3 rotateAngle);
		virtual void interpolate(int currentTime);
		virtual bool isValid(int currentTime);

	private:
		Camera* m_camera;
		glm::vec3 m_rotateAngle;

		glm::vec3 m_step;
		int m_startTime;
		int m_endTime;
		int m_previousStep;
	};
};