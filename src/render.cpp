#include"mainfile.h"
int main(void)
{
    render render_;
    while (!glfwWindowShouldClose(render_.window->mainWindow))
    {

        render_.update();

    }
}