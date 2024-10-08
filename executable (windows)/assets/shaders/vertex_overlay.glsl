#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 projection_view;

void main()
{
    gl_Position = projection_view * model * vec4(inPosition, 1.0);
    texCoord = inTexCoord;
}  