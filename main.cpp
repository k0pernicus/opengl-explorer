#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
// #else
//  #include <GL/gl.h>
// #include <GL/glut.h>
#endif

#include "logs.h"
#include "shader_utils.h"
#include "maths_utils.h"
#include <iostream>

const size_t WIDTH = 640;
const size_t HEIGHT = 480;
const char *WINDOW_NAME = "Test OpenGL";

/*
 * Callback to handle the "close window" event, once the user pressed the Escape key.
 */
static void quitCallback(GLFWwindow *window, int key, int scancode, int action, int _mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

/*
 * Initializes the window and viewport via GLFW.
 * The viewport takes the all window.
 * If an error happens, the function returns `NULL` but **does not** free / terminate the GLFW library.
 * Then, do not forget to call `glfwTerminate` if this function returns `NULL`.
 */
GLFWwindow *initializeWindow()
{
    // Minimum target is OpenGL 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(HEIGHT, WIDTH, WINDOW_NAME, NULL, NULL);
    if (!window)
    {
        error("window creation failed");
        return NULL;
    }
    // Close the window as soon as the Escape key has been pressed
    glfwSetKeyCallback(window, quitCallback);
    // Makes the window context current
    glfwMakeContextCurrent(window);
    // Enable the viewport
    glViewport(0, 0, HEIGHT, WIDTH);

    return window;
}

int main(void)
{
    // Initialize the lib
    if (!glfwInit())
    {
        error("could not start GLFW3");
        return -1;
    }

    GLFWwindow *window = initializeWindow();
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Note: Once you have a current OpenGL context, you can use OpenGL normally
    // get version info
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    info("Renderer: " << renderer);
    info("OpenGL version supported: " << version);

    /* SHADER PART */
    const char *basicVertexShaderSource = "#version 410 core\n"
                                          "layout (location = 0) in vec3 vertexPosition;\n"
                                          "layout (location = 1) in vec3 vertexColor;\n"
                                          "layout (location = 0) out vec3 fragmentColor;\n"
                                          "void main()\n"
                                          "{\n"
                                          "    gl_Position = vec4(vertexPosition, 1.0);\n" // `w` is used for perspective
                                          "    fragmentColor = vertexColor;\n"
                                          "}\0";

    const char *basicFragmentShaderSource = "#version 410 core\n"
                                            "layout (location = 0) in vec3 fragmentColor;\n"
                                            "out vec4 finalColor;\n"
                                            "void main()\n"
                                            "{\n"
                                            "    finalColor = vec4(fragmentColor, 1.0);\n"
                                            "}\0";

    auto shader_utils = ShaderUtils::Program{};

    if (!shader_utils.registerShader(ShaderUtils::Type::VERTEX_SHADER_TYPE, basicVertexShaderSource))
    {
        glfwTerminate();
        return -1;
    }

    if (!shader_utils.registerShader(ShaderUtils::Type::FRAGMENT_SHADER_TYPE, basicFragmentShaderSource))
    {
        glfwTerminate();
        return -1;
    }

    if (!shader_utils.registerProgram())
    {
        glfwTerminate();
        return -1;
    }
    /* END OF SHADER PART */

    const MathsUtils::vertex vertices[3] = {
        {0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f},
        {0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f},
        {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f}};

    // Vertex Buffer Object = VBO
    GLuint VBO = {};
    glGenBuffers(1, &VBO);

    // Something failed when generating buffers
    if (glGetError() != GL_NO_ERROR)
    {
        error("error when generating buffers");
        glDeleteBuffers(1, &VBO); // TODO: Needed?
        glfwTerminate();
        return -1;
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, MathsUtils::getNbElements(vertices) * sizeof(float), vertices, GL_STATIC_DRAW | GL_MAP_READ_BIT);

    // Vertex Arrays Object = VAO
    GLuint VAO = {};
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Specify position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, MathsUtils::VERTEX_ELEMENTS_NB * sizeof(float), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    // Specify color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, MathsUtils::VERTEX_ELEMENTS_NB * sizeof(float), (GLvoid *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window))
    {
        // Render
        glClearColor(0.5, 0.2, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader_utils.getProgram().value());
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // Poll for and process events
        glfwPollEvents();
        // Swap front and back buffers
        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    // ... here, the user closed the window
    glfwTerminate();
    return 0;
}
