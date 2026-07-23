#include <GLFW/glfw3.h>
#include <iostream>

int main() {

    //initialise glfw
    if (!glfwInit()) {

        std::cerr << "failled to initialise GLFW\n";
        return 1;
    }

    //create a window
    GLFWwindow* window = glfwCreateWindow(
        800, //width
        600, //height
        "my first openGL window yipeeeee!",
        nullptr,
        nullptr
    );

    if (!window) {

        std::cerr << "failed to GLFW window\n";
        glfwTerminate();
        return 1;
    }

    //make this window the current context
    glfwMakeContextCurrent(window);

    //keep the windo open
    while (!glfwWindowShouldClose(window)) {

        //check for poll events
        glfwPollEvents();

        glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //swap the front and back buffers
        glfwSwapBuffers(window);
    }

    //clean up
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}