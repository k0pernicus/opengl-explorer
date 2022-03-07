#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#endif

#include "logs.h"
#include "shader_utils.h"
#include <optional>
#include <iostream>

ShaderUtils::Program::Program() {}

ShaderUtils::Program::~Program()
{
    if (vertexShader.has_value())
        glDeleteShader(vertexShader.value());
    if (vertexShader.has_value())
        glDeleteShader(fragmentShader.value());
    if (registered && program.has_value())
        glDeleteProgram(program.value());
}

bool ShaderUtils::Program::registerShader(const ShaderUtils::Type shader_type, const char *shader_source)
{
    int success = {};
    char errorMessage[1024] = {};

    bool isFragmentShader = shader_type == ShaderUtils::Type::FRAGMENT_SHADER_TYPE;

    auto real_shader_type = !isFragmentShader ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;

    auto shader = glCreateShader(real_shader_type);
    // Now, pass the shaders
    glShaderSource(shader, 1, &shader_source, NULL);
    // And now, compile them
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, errorMessage);
        if (isFragmentShader)
        {
            error("Fragment shader compilation error : " << errorMessage);
        }
        else
        {

            error("Vertex shader compilation error : " << errorMessage);
        }

        return false;
    }

    if (isFragmentShader)
    {
        fragmentShader = shader;
    }
    else
    {
        vertexShader = shader;
    }
    return true;
}

bool ShaderUtils::Program::registerProgram()
{
    if (registered)
    {
        error("program is already registered");
        return false;
    }
    if (!vertexShader.has_value() || !fragmentShader.has_value())
    {
        error("cannot compile program without vertex and fragment shaders");
        return false;
    }
    int success = {};
    char errorMessage[1024] = {};
    const unsigned int vertexShaderValue = vertexShader.value();
    const unsigned int fragmentShaderValue = fragmentShader.value();

    program = glCreateProgram();
    const unsigned int programValue = program.value();

    glAttachShader(programValue, vertexShaderValue);
    glAttachShader(programValue, fragmentShaderValue);
    glLinkProgram(programValue);

    glGetProgramiv(programValue, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programValue, 1024, NULL, errorMessage);
        error("Shader linking error: " << errorMessage);
        return false;
    }

    // We can now delete our vertex and fragment shaders
    glDeleteShader(vertexShaderValue);
    glDeleteShader(fragmentShaderValue);
    glUseProgram(programValue);
    registered = true;

    return true;
}

std::optional<unsigned int> ShaderUtils::Program::getProgram() const
{
    return program;
}

bool ShaderUtils::Program::programIsRegistered() const
{
    return registered;
}
