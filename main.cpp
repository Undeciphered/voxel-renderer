#include "shader.h"
#include "cube.h"

#include <GLFW/glfw3.h>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {

    //initialise glfw
    if (!glfwInit()) {

        std::cerr << "failled to initialise GLFW\n";
        return 1;
    }

    //openGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create the window
    GLFWwindow* window = glfwCreateWindow(
        800, //width
        600, //height
        "rotating cube yipeeeee!",
        nullptr,
        nullptr
    );

    if (!window) {

        std::cerr << "failed to GLFW window\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    //enable depth buffer
    glEnable(GL_DEPTH_TEST);

    std::vector<float> vertices = createCube();

    //creat vertex array object (VAO)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    //create vertex buffer object (VBO)
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    //activate VAO
    glBindVertexArray(VAO);

    //activate VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //copy our vertices into the GPU
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW
    );

    //tell OpenGL how our vertex data is organized
    // 1. Position Attribute (Location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 2. Color Attribute (Location 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int shaderProgram = createShaderProgram();
    
    //get uniform locations
    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    //create transformation matrices
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::translate(
        view,
        glm::vec3(0.0f, 0.0f, -3.0f)
    );

    projection = glm::perspective(
        glm::radians(45.0f),
        800.0f / 600.0f,
        0.1f,
        100.0f
    );

    float rotation = 0.0f;

    auto previousTime = std::chrono::high_resolution_clock::now();

    //main render loop
    while (!glfwWindowShouldClose(window)) {

        //calculate the time since last rotation and
        //rotate it the amount it would have rotated in that time
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - previousTime).count();
        previousTime = currentTime;
        rotation += 50.0f * deltaTime;

        model = glm::mat4(1.0f);

        model = glm::rotate(
            model,
            glm::radians(rotation),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        //check for poll events
        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //use shader program
        glUseProgram(shaderProgram);

        glUniformMatrix4fv(
            modelLoc,
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        glUniformMatrix4fv(
            viewLoc,
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );

        glUniformMatrix4fv(
            projectionLoc,
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );

        //draw cube
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 6);

        //swap front and back buffers
        glfwSwapBuffers(window);
    }

    //clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}