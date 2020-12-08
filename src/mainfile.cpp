#include"mainfile.h"
void render::init_input()
{
    dt = 0.f;
    curTime = 0.f;
    lastTime = 0.f;

    lastMouseX = 0.0;
    lastMouseY = 0.0;
    mouseX = 0.0;
    mouseY = 0.0;
    mouseOffsetX = 0.0;
    mouseOffsetY = 0.0;
    firstMouse = true;

}
void render::init_transformation()
{
    ModelMatrix = glm::mat4(1.0f);
    ViewMatrix = glm::mat4(1.0f);
    ProjectionMatrix = glm::mat4(1.0f);
    ProjectionMatrix = glm::perspective(glm::radians(45.f), (GLfloat)window->bufferWidth / (GLfloat)window->bufferHeight, 0.1f, 100.0f);
}
 void  render::processMouseInput()

{
    glfwGetCursorPos(window->mainWindow, &mouseX, &mouseY);
    if (firstMouse)
    {
        lastMouseX = mouseX;
        lastMouseY = mouseY;
        firstMouse = false;
    }

    //Calc offset
    mouseOffsetX = mouseX - lastMouseX;
    mouseOffsetY = lastMouseY - mouseY;

    //Set last X and Y
    lastMouseX = mouseX;
    lastMouseY = mouseY;
    camera->updateMouseInput(dt, mouseOffsetX, mouseOffsetY);

}
void render::processKeyboardInput()
{
    //Program
    if (glfwGetKey(window->mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window->mainWindow, GLFW_TRUE);
    }

    //Camera
    if (glfwGetKey(window->mainWindow, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera->ProcessKeyboard(dt, FORWARD);
    }
    if (glfwGetKey(window->mainWindow, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera->ProcessKeyboard(dt, BACKWARD);
    }
    if (glfwGetKey(window->mainWindow, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera->ProcessKeyboard(dt, LEFT);
    }
    if (glfwGetKey(window->mainWindow, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera->ProcessKeyboard(dt, RIGHT);
    }
}

void render::updateInput()
{
    curTime = static_cast<float>(glfwGetTime());
    dt = curTime - lastTime;
    lastTime = curTime;
    processKeyboardInput();
    processMouseInput();
}
void render::update_transformation()
{
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f,0.f,0.f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.0f));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f));
    shader_->setMat4("modelMatrix", ModelMatrix);
    ViewMatrix = camera->getViewMatrix();
    shader_->setMat4("viewMatrix", ViewMatrix);
    shader_->setMat4("projectionMatrix", ProjectionMatrix);

    GLuint uniformAmbientIntensity = 0, uniformAmbientColour = 0,
        uniformDirection = 0, uniformDiffuseIntensity =0;

    uniformAmbientColour = shader_->GetAmbientColourLocation();
    uniformAmbientIntensity = shader_->GetAmbientIntensityLocation();
    uniformDirection = shader_->GetDirectionLocation();
    uniformDiffuseIntensity = shader_->GetDiffuseIntensityLocation();
    mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDirection);

}
render::render()
{  
    window = new Window("SOFTWARE RENDERING", 800, 600);
    ourModel = new Model("resources/objects/rock.obj");
    shader_ = new shader("resources / shaders / Basic.shader");
    camera = new Camera(glm::vec3(0.f, 0.f, 3.f), glm::vec3(0.f, 1.f, 0.f));

    mainLight = Light(1.0f, 0.5f, 0.0f, 0.5f,
                        2.0f,-1.0f, 2.0f, 1.0f);
    init_input();
    init_transformation();

}
void render::update()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glfwGetFramebufferSize(window->mainWindow, &window->bufferWidth, &window->bufferHeight);
    shader_->use();
    ourModel->Draw(shader_);
    update_transformation();
    updateInput();
    glBindVertexArray(0);
    glUseProgram(0);
    glfwSwapBuffers(window->mainWindow);
    glfwPollEvents();

}
