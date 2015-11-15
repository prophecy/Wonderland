#version 140

in vec3 vColor;

out vec4 LFragment;

void main() 
{
	LFragment = vec4(vColor.x, vColor.y, vColor.z, 1.0); 
}