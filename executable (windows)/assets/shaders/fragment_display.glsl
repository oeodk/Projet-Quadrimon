#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;
uniform sampler2D bloomTexture;
uniform float gamma;

void main()
{
	vec3 fragment = texture(screenTexture,texCoords).rgb;
	vec3 bloom = texture(bloomTexture,texCoords).rgb;

	vec3 color = fragment + bloom;

	float exposure = 1.f;
    //float exposure = 1.5f;
	vec3 toneMapped = vec3(1.f) - exp(-color * exposure);
    //vec3 quantified_color = (floor(toneMapped * 5.f)) / 5.f;

    FragColor = vec4(pow(toneMapped, vec3(1.f / gamma)), 1.f);
}
/*
#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;

const float offset_x = 1.0f / 800.0f;  
const float offset_y = 1.0f / 800.0f;  

vec2 offsets[9] = vec2[]
(
    vec2(-offset_x,  offset_y), vec2( 0.0f,    offset_y), vec2( offset_x,  offset_y),
    vec2(-offset_x,  0.0f),     vec2( 0.0f,    0.0f),     vec2( offset_x,  0.0f),
    vec2(-offset_x, -offset_y), vec2( 0.0f,   -offset_y), vec2( offset_x, -offset_y) 
);

float kernel[9] = float[]
(
    1,  1, 1,
    1, -8, 1,
    1,  1, 1
);

void main()
{
    vec3 color = vec3(0.0f);
    for(int i = 0; i < 9; i++)
        color += vec3(texture(screenTexture, texCoords.st + offsets[i])) * kernel[i];
    FragColor = vec4(color, 1.0f);
}*/