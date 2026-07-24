#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//vertex shader
const char* vertexShaderSource = R"(
    #version 330 core

    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    flat out vec3 ourColor;

    void main() {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
        ourColor = aColor;
    }
)";

//fragment shader
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    
    flat in vec3 ourColor;

    void main() {
        FragColor = vec4(ourColor, 1.0); 
    }
)";

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
        "openGL cube yipeeeee!",
        nullptr,
        nullptr
    );

    if (!window) {

        std::cerr << "failed to GLFW window\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    //enable depth buffer
    glEnable(GL_DEPTH_TEST);

    if (glewInit() != GLEW_OK) {

        std::cerr << "Failed to initialize GLEW\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    float vertices[] = {

        // FRONT FACE
        // Triangle 1
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,

        // Triangle 2
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,


        // BACK FACE
        // Triangle 1
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,

        // Triangle 2
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,


        // LEFT FACE
        // Triangle 1
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,

        // Triangle 2
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,


        // RIGHT FACE
        // Triangle 1
        0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,

        // Triangle 2
        0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,


        // TOP FACE
        // Triangle 1
        -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,

        // Triangle 2
        -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f,


        // BOTTOM FACE
        // Triangle 1
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,

        // Triangle 2
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f
    };

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
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    //tell OpenGL how our vertex data is organized
    // 1. Position Attribute (Location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 2. Color Attribute (Location 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //create vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    //create fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    //create shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //delete individual shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //create transformation matrices
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    model = glm::rotate(
        model,
        glm::radians(25.0f),
        glm::vec3(1.0f, 0.0f, 0.0f)
    );

    model = glm::rotate(
        model,
        glm::radians(-35.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

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

    //main render loop
    while (!glfwWindowShouldClose(window)) {

        //check for poll events
        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //use shader program
        glUseProgram(shaderProgram);

        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");

        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");

        unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

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
        glDrawArrays(GL_TRIANGLES, 0, 36);

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