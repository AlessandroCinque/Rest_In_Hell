#version 450

//300 for the potato laptop

in vec3 colorOut;
in vec2 textureOut;
//=================
in mat4 modelOut;
in mat4 viewOut;
in mat4 projOut;
in vec3 vertexOut;
in vec3 normalOut;


//=================

out vec4 pixelColor;

uniform float time;
uniform sampler2D textureImage_1;
uniform sampler2D textureImage_2;
uniform vec3 lightColor;

struct light
{
	vec3 ambient;
	vec3 position;
	vec3 diffuse;
	vec3 specular;

};
struct material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform material Material;
uniform light Light;
uniform vec3 CamPos;

uniform bool is_textured;
uniform bool is_textured2;
uniform bool isLit;
uniform bool isDemon;
uniform bool isDamaged;
//=====================
vec3 lightDirection;
vec3 diffuseLight;
vec3 testColour = vec3(1.0f,0.0f,0.0f);
float specularTerm;
void main(void)
{
	
	if(isLit)
	{
		if(is_textured2)
		{
		vec3 normal= normalize(normalOut);
				//vec3 normal = vec3(0.0,1.0,0.0);
			// ====================== ambient ========================
				vec3 ambientColor = Light.ambient * Material.ambient;

				vec3 vertPos = (modelOut * vec4(vertexOut ,1.0f)).xyz;
				
				lightDirection = normalize(Light.position - vertPos);

				float lightIntensity = max(dot(lightDirection,normal),0.0f);

				diffuseLight = Light.diffuse * Material.diffuse * lightIntensity;

			

			// ====================== specular =======================
			vec3 viewDirection = normalize(CamPos - vertexOut);
			vec3 reflection = reflect(-lightDirection,normal);
			specularTerm = pow(max(dot(viewDirection,reflection),0.0f),Material.shininess);
			vec3 specularColor = Light.specular* Material.specular* specularTerm;
			
		
			
			
		

			//pixelColor =texture(textureImage_1,textureOut) * vec4((ambientColor + diffuseLight + specularColor ),1.0f);
			pixelColor = mix(texture(textureImage_1,textureOut),texture(textureImage_2,textureOut),0.5) * vec4((ambientColor + diffuseLight + specularColor )*vec3(testColour),1.0f);
		}
		else if(is_textured)
		{
				vec3 normal= normalize(normalOut);
			// ====================== ambient ========================
				vec3 ambientColor = Light.ambient * Material.ambient;

				vec3 vertPos = (modelOut * vec4(vertexOut ,1.0f)).xyz;
				
				lightDirection = normalize(Light.position - vertPos);

				float lightIntensity = max(dot(lightDirection,normal),0.0f);

				diffuseLight = Light.diffuse * Material.diffuse * lightIntensity;

			// ====================== specular =======================
			vec3 viewDirection = normalize(CamPos - vertexOut);
			vec3 reflection = reflect(-lightDirection,normal);
			specularTerm = pow(max(dot(viewDirection,reflection),0.0f),Material.shininess);
			vec3 specularColor = Light.specular* Material.specular* specularTerm;
			
			
		

			pixelColor =texture(textureImage_1,textureOut) * vec4((ambientColor + diffuseLight + specularColor )*vec3(testColour),1.0f);

		}
		else if(isDemon)
		{
		// start and end relugate the edges of the glowing effect
			float start= 0.0f;
			float end = 1.0f;
			float alpha = 1.0f;
			vec3 normal= normalize(normalOut);
			vec3 viewDirection = normalize(-CamPos);

			float rim = smoothstep(start,end,1.0 - dot(normal,viewDirection));
			pixelColor = vec4(clamp(rim,0.0,1.0)* alpha *colorOut,1.0f);
		}
		else if(isDamaged)
		{
		// this is the "Scanlines" effect.
				float speed = -10.0f;
				float resolution = 0.5f;
				float width = 4.0f;
			    vec3 outColor = vec3( 0.0f,0.0f,0.0f );

				float m = mod( ( gl_FragCoord.y + ( time * speed ) ) * resolution , width );

				if( m < 2.0 ) 
				{
				    outColor = colorOut;
				} 
				else if( m < 2.5 ) 
				{
				    outColor = colorOut * 0.5;
				}
				
				pixelColor = vec4( outColor, 1.0 );	
		}
		else
		{
				vec3 normal= normalize(normalOut);
			// ====================== ambient ========================
				vec3 ambientColor = Light.ambient * Material.ambient;

				vec3 vertPos = (modelOut * vec4(vertexOut ,1.0f)).xyz;
				
				lightDirection = normalize(Light.position - vertPos);

				float lightIntensity = max(dot(lightDirection,normal),0.0f);

				diffuseLight = Light.diffuse * Material.diffuse * lightIntensity;

			

			// ====================== specular =======================
			vec3 viewDirection = normalize(CamPos - vertexOut);
			vec3 reflection = reflect(-lightDirection,normal);
			specularTerm = pow(max(dot(viewDirection,reflection),0.0f),Material.shininess);
			vec3 specularColor = Light.specular* Material.specular* specularTerm;
			
		
			
			vec3 testColour = vec3(0.1f,0.1f,0.1f);
		
			pixelColor= vec4((ambientColor + diffuseLight + specularColor ),1.0f)* vec4(colorOut,1.0f);
		}
	}
	else
	{
		if(is_textured2)
		{
			pixelColor = mix(texture(textureImage_1,textureOut),texture(textureImage_2,textureOut),0.5);
		}
		else if(is_textured)
		{
			pixelColor =texture(textureImage_1,textureOut)/** vec4(testColour,1.0f)*/;
		}
		else
		{
			pixelColor = vec4(colorOut,1.0);
		}
	}

//cut off the "vec4(colorOut,1.0)" if you don't want to add the color on the texture "*texture(textureImage,textureOut)" is for only the textures
	//pixelColor = texture(textureImage,textureOut);
}