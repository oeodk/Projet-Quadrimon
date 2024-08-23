#version 330 core
layout (location = 0) out vec4 FragColor;
  
in vec2 texCoords;

uniform sampler2D screenTexture;
uniform bool downscale;
uniform vec2 srcResolution;
uniform float filterRadius;

void main()
{       
	vec3 result;
    if(downscale)
    {
		vec2 srcTexelSize = 1.0 / srcResolution;
		float x = srcTexelSize.x;
		float y = srcTexelSize.y;

		// Take 13 samples around current texel:
		// a - b - c
		// - j - k -
		// d - e - f
		// - l - m -
		// g - h - i
		// === ('e' is the current texel) ===
		vec3 a = texture(screenTexture, vec2(texCoords.x - 2*x, texCoords.y + 2*y)).rgb;
		vec3 b = texture(screenTexture, vec2(texCoords.x,       texCoords.y + 2*y)).rgb;
		vec3 c = texture(screenTexture, vec2(texCoords.x + 2*x, texCoords.y + 2*y)).rgb;

		vec3 d = texture(screenTexture, vec2(texCoords.x - 2*x, texCoords.y)).rgb;
		vec3 e = texture(screenTexture, vec2(texCoords.x,       texCoords.y)).rgb;
		vec3 f = texture(screenTexture, vec2(texCoords.x + 2*x, texCoords.y)).rgb;

		vec3 g = texture(screenTexture, vec2(texCoords.x - 2*x, texCoords.y - 2*y)).rgb;
		vec3 h = texture(screenTexture, vec2(texCoords.x,       texCoords.y - 2*y)).rgb;
		vec3 i = texture(screenTexture, vec2(texCoords.x + 2*x, texCoords.y - 2*y)).rgb;

		vec3 j = texture(screenTexture, vec2(texCoords.x - x, texCoords.y + y)).rgb;
		vec3 k = texture(screenTexture, vec2(texCoords.x + x, texCoords.y + y)).rgb;
		vec3 l = texture(screenTexture, vec2(texCoords.x - x, texCoords.y - y)).rgb;
		vec3 m = texture(screenTexture, vec2(texCoords.x + x, texCoords.y - y)).rgb;

		// Apply weighted distribution:
		// 0.5 + 0.125 + 0.125 + 0.125 + 0.125 = 1
		// a,b,d,e * 0.125
		// b,c,e,f * 0.125
		// d,e,g,h * 0.125
		// e,f,h,i * 0.125
		// j,k,l,m * 0.5
		// This shows 5 square areas that are being sampled. But some of them overlap,
		// so to have an energy preserving downsample we need to make some adjustments.
		// The weights are the distributed, so that the sum of j,k,l,m (e.g.)
		// contribute 0.5 to the final color output. The code below is written
		// to effectively yield this sum. We get:
		// 0.125*5 + 0.03125*4 + 0.0625*4 = 1
		result = e*0.125;
		result += (a+c+g+i)*0.03125;
		result += (b+d+f+h)*0.0625;
		result += (j+k+l+m)*0.125;    
	}
	else
	{
		// The filter kernel is applied with a radius, specified in texture
		// coordinates, so that the radius will vary across mip resolutions.
		float x = filterRadius;
		float y = filterRadius;

		// Take 9 samples around current texel:
		// a - b - c
		// d - e - f
		// g - h - i
		// === ('e' is the current texel) ===
		vec3 a = texture(screenTexture, vec2(texCoords.x - x, texCoords.y + y)).rgb;
		vec3 b = texture(screenTexture, vec2(texCoords.x,     texCoords.y + y)).rgb;
		vec3 c = texture(screenTexture, vec2(texCoords.x + x, texCoords.y + y)).rgb;

		vec3 d = texture(screenTexture, vec2(texCoords.x - x, texCoords.y)).rgb;
		vec3 e = texture(screenTexture, vec2(texCoords.x,     texCoords.y)).rgb;
		vec3 f = texture(screenTexture, vec2(texCoords.x + x, texCoords.y)).rgb;

		vec3 g = texture(screenTexture, vec2(texCoords.x - x, texCoords.y - y)).rgb;
		vec3 h = texture(screenTexture, vec2(texCoords.x,     texCoords.y - y)).rgb;
		vec3 i = texture(screenTexture, vec2(texCoords.x + x, texCoords.y - y)).rgb;

		// Apply weighted distribution, by using a 3x3 tent filter:
		//  1   | 1 2 1 |
		// -- * | 2 4 2 |
		// 16   | 1 2 1 |
		result = e*4.0;
		result += (b+d+f+h)*2.0;
		result += (a+c+g+i);
		result *= 1.0 / 16.0;
	}	
    FragColor = vec4(result, 1.0f);
}