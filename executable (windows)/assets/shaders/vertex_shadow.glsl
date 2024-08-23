#version 330 core

layout(location = 0) in vec3 inPosition;

uniform mat4 light_projection;
uniform mat4 model;

void main()
{
    gl_Position = light_projection * model * vec4(inPosition, 1.0);
}
