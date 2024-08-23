#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 texCoord;
out vec4 frag_light_pos;

uniform mat4 model;
uniform mat4 projection_view;
uniform mat4 light_projection;

void main()
{
	texCoord = inTexCoord;
    FragPos = vec3(model * vec4(inPosition, 1.0));
    frag_light_pos =  light_projection * vec4(FragPos, 1.0);
    gl_Position = projection_view * vec4(FragPos, 1.0);
    Normal = mat3(transpose(inverse(model))) * inNormal;
}
