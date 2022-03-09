#version 410 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 0) out vec3 fragmentColor;

void main()
{
    gl_Position = vec4(vertexPosition, 1.0);
    fragmentColor = vertexColor;
}
