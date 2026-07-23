#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

//vertex shader
const char* vertexShaderSource = R"(
    #version 330 core

    layout (location = 0) in vec3 aPos;

    void main() 
    {
        gl_Position = vec4(aPos, 1.0);
    }
)";

//fragment shader
const char* fragmentShaderSource = R"(
    #version 330 core

    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0, 1.0, 1.0, 1.0);
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
        "my first openGL triangle yipeeeee!",
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

    if (glewInit() != GLEW_OK) {

        std::cerr << "Failed to initialize GLEW\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    //three point of the triangle
    float vertices[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
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
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    //enable the vertex attribute
    glEnableVertexAttribArray(0);

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

    //delete indicidual shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //main render loop
    while (!glfwWindowShouldClose(window)) {

        //check for poll events
        glfwPollEvents();

        glClearColor(0.1f, 0.8f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        //use shader program
        glUseProgram(shaderProgram);

        //draw triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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