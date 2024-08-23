#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BloomColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 texCoord;  // Coordonnées de texture du fragment
in vec4 frag_light_pos;


struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform sampler2D textureSampler;
uniform sampler2D secondTextureSampler;
uniform sampler2D shadowMap;

uniform vec3 light_position;
uniform vec3 cam_pos;

uniform vec4 object_color;

uniform Material material;

uniform bool has_texture;
uniform bool has_second_texture;
uniform float blend_factor;

void main()
{
    // Ambient
    float ambientStrength = 1.f;
    vec3 ambient = ambientStrength * material.ambient;

    // Diffuse
    vec3 lightDir = normalize(light_position - FragPos);
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * material.diffuse;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cam_pos- FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = specularStrength * spec * material.specular;

    float shadow = 0.f;
    vec3 lightCoords = frag_light_pos.xyz / frag_light_pos.w;
    if(lightCoords.z <= 1.0f)
	{
		// Get from [-1, 1] range to [0, 1] range just like the shadow map
		lightCoords = (lightCoords + 1.0f) / 2.0f;
		float currentDepth = lightCoords.z;
		// Prevents shadow acne
		float bias = max(0.025f * (1.0f - dot(Normal, normalize(light_position))), 0.0005f);

		// Smoothens out the shadows
		int sampleRadius = 2;
		vec2 pixelSize = 1.0 / textureSize(shadowMap, 0);
		for(int y = -sampleRadius; y <= sampleRadius; y++)
		{
		    for(int x = -sampleRadius; x <= sampleRadius; x++)
		    {
		        float closestDepth = texture(shadowMap, lightCoords.xy + vec2(x, y) * pixelSize).r;
				if (currentDepth > closestDepth + bias)
					shadow += 1.0f;     
		    }    
		}
		// Get average shadow
		shadow /= pow((sampleRadius * 2 + 1), 2);

	}

    vec3 result = ambient + (1 - shadow) * (diffuse + specular);
	vec4 texture_color; 
    if(has_texture)
    {
        if(has_second_texture)
        {
            texture_color = object_color * ((1 - blend_factor) * texture(textureSampler, texCoord)  + blend_factor * texture(secondTextureSampler, texCoord));
        }
        else
        {
	        texture_color = object_color * texture(textureSampler, texCoord);
        }
    }
    else
    {
	    texture_color = object_color;
    }
   
    FragColor = texture_color * vec4(result, 1.0);
    const float threshold = 10.f;
    if(FragColor.r > threshold || FragColor.g > threshold || FragColor.b > threshold)
    {
        vec3 sub_color = FragColor.rgb - vec3(threshold);
        BloomColor = vec4(max(sub_color, vec3(0.f)), 1.f);
    }
    else
    {
        BloomColor = vec4(0.f, 0.f, 0.f, 1.f);
    }
}
