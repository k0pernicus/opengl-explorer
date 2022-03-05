#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#endif

#include "logs.h"
#include "shader_utils.h"
#include <iostream>

ShaderUtils::Program::Program() {}

ShaderUtils::Program::~Program()
{
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if (registered)
        glDeleteProgram(program);
}

unsigned int ShaderUtils::Program::registerShader(const ShaderUtils::Type shader_type, const char *shader_source)
{
    int success = {};
    char errorMessage[1024] = {};

    if (shader_type == ShaderUtils::Type::VERTEX_SHADER_TYPE)
    {
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        // Now, pass the shaders
        glShaderSource(vertexShader, 1, &shader_source, NULL);
        // And now, compile them
        glCompileShader(vertexShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 1024, NULL, errorMessage);
            error("Vertex shader compilation error: " << errorMessage);
        }
    }
    else
    {
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        // Now, pass the shaders
        glShaderSource(fragmentShader, 1, &shader_source, NULL);
        // And now, compile them
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 1024, NULL, errorMessage);
            error("Fragment shader compilation error: " << errorMessage);
        }
    }
    return success;
}

bool ShaderUtils::Program::registerProgram()
{
    if (registered)
    {
        error("program is already registered");
        return 0;
    }
    int success = {};
    char errorMessage[1024] = {};

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 1024, NULL, errorMessage);
        error("Shader linking error: " << errorMessage);
        return false;
    }

    // We can now delete our vertex and fragment shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glUseProgram(program);
    registered = true;

    return true;
}

unsigned int ShaderUtils::Program::getProgram() const
{
    return program;
}

bool ShaderUtils::Program::programIsRegistered() const
{
    return registered;
}
