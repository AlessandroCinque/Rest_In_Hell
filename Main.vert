#version 450

//300 for the potato laptop

in vec3 vertexIn;
in vec3 colorIn;
in vec2 textureIn;
in vec3 normalIn;

out vec3 colorOut;
out vec2 textureOut;

out mat4 modelOut;
out mat4 viewOut;
out vec3 vertexOut;
out vec3 normalOut;
//uniform vec3 CamPos;
//======= EXPERIMENT ==========

//=============================
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(void)
{
	//===============
	modelOut = model;
	viewOut = view;
	vertexOut = vertexIn;
	normalOut = normalIn;
	//===============
	colorOut = colorIn;
	textureOut = textureIn;
	gl_Position =proj*view* model * vec4(vertexIn,1.0);
}