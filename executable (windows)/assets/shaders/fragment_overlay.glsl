#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D textureSampler;
uniform vec4 object_color;
void main()
{
    vec3 color = object_color.rgb * texture(textureSampler, texCoord).rgb;
	float exposure = 1.f;
	vec3 toneMapped = vec3(1.f) - exp(-color * exposure);
	const float gamma = 2.2f;
    FragColor = vec4(pow(toneMapped, vec3(1.f / gamma)), object_color.a);
}