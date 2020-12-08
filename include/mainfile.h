#pragma once
#ifndef _MAINFILE_H_
#define _MAINFILE_H_
#include"window.h"
#include"camera.h"
#include"model.h"
#include"DirectionalLight.h"

class render {
	shader* shader_;
	Model* ourModel;

	glm::mat4 ModelMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;


	//Mouse Input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	Camera* camera;


	DirectionalLight mainLight;


	//Delta time
	float dt;
	float curTime;
	float lastTime;

	void init_input(void);
	void init_transformation(void);

	void processKeyboardInput(void);
	void processMouseInput(void);
public:
	Window* window;
	render();
	~render() {}
	void updateInput(void);
	void update(void);
	void update_transformation(void);
};
#endif//!_MAINFILE_H_
