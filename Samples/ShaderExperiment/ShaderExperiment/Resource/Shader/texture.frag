#version 330

uniform sampler2D uTexUnit0;

in vec2 vTexCoord;
out vec4 LFragment; 

void main() 
{
	vec4 texColor0 = texture2D(uTexUnit0, vTexCoord);
	LFragment = texColor0;
}