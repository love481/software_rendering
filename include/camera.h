#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include"defines.h"
enum direction { FORWARD , BACKWARD, LEFT, RIGHT };

class Camera
{
private:

	GLfloat movementSpeed;
	GLfloat turnSpeed;
	GLfloat sensitivity;
	GLfloat Zoom;

	glm::vec3 worldUp;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	GLfloat pitch;
	GLfloat yaw;

	void updateCameraVectors()
	{
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		front = glm::normalize(front);
		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}

public:
	Camera(glm::vec3 Position, glm::vec3 WorldUp)
	{
		movementSpeed = 6.f;
		sensitivity = -10.f;

		worldUp = WorldUp;
		position = Position;
		right = glm::vec3(0.f);
		front = glm::vec3(0.0f, 0.0f, -1.f);
		//up = WorldUp;

		pitch = 0.f;
		yaw = -90.f;
		Zoom = 45.0f;
		updateCameraVectors();
	}

	~Camera() {}

	const glm::mat4 getViewMatrix()
	{
		return glm::lookAt(position, position + front, up);
	}

	const glm::vec3 getPosition() const
	{
		return position;
	}

	void ProcessKeyboard(const float& dt, const int Direction)
	{
		//Update position vector
		switch (Direction)
		{
		case FORWARD:
			position += front * movementSpeed * dt;
			break;
		case BACKWARD:
			position -= front * movementSpeed * dt;
			break;
		case LEFT:
			position += right * movementSpeed * dt;
			break;
		case RIGHT:
			position -= right * movementSpeed * dt;
			break;
		default:
			break;
		}
	}

	void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY)
	{
		//Update pitch yaw and roll
		pitch += static_cast<GLfloat>(offsetY) * sensitivity * dt;
		yaw += static_cast<GLfloat>(offsetX) * sensitivity * dt;

		if (pitch > 90.f)
			pitch = 90.f;
		else if (pitch < -90.f)
			pitch = -90.f;

		if (yaw > 360.f || yaw < -360.f)
			yaw = 0.f;
		updateCameraVectors();
	}
	void ProcessMouseScroll(float yoffset)
	{
		Zoom -= (float)yoffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}

};
#endif