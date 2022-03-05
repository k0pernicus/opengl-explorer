#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
// #include <OpenGL/gl.h>
// #include <GLUT/glut.h>
#include <GLFW/glfw3.h>
// #else
// #include <GL/gl.h>
// #include <GL/glut.h>
#endif

#include <iostream>

const size_t WIDTH = 640;
const size_t HEIGHT = 480;
const char *WINDOW_NAME = "Test OpenGL";

#define info(x) std::cout << "INFO: " << x << std::endl;
#define debug(x) std::cout << "DEBUG: " << x << std::endl;
#define warning(x) std::cout << "WARN: " << x << std::endl;
#define error(x) std::cerr << "ERRO: " << x << std::endl;

/*
 * Callback to handle the "close window" event, once the user pressed the Escape key.
 */
static void quit_callback(GLFWwindow *window, int key, int scancode, int action, int _mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
    // Initialize the lib
    if (!glfwInit())
    {
        error("could not start GLFW3");
        return -1;
    }

    // Minimum target is OpenGL 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(HEIGHT, WIDTH, WINDOW_NAME, NULL, NULL);
    if (!window)
    {
        error("window creation failed");
        glfwTerminate();
        return -1;
    }
    // Close the window as soon as the Escape key has been pressed
    glfwSetKeyCallback(window, quit_callback);
    // Makes the window context current
    glfwMakeContextCurrent(window);

    // Note: Once you have a current OpenGL context, you can use OpenGL normally
    // get version info
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    debug("Renderer: " << renderer);
    debug("OpenGL version supported: " << version);

    while (!glfwWindowShouldClose(window))
    {
        // Render
        glClear(GL_COLOR_BUFFER_BIT);
        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }

    // ... here, the user closed the window
    glfwTerminate();
    return 0;
}
