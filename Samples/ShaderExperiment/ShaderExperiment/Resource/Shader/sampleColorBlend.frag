#version 140

//uniform vec4 color = vec4(1.0, 0.0, 0.0, 0.0);
in vec4 color;
out vec4 LFragment;

void main() 
{
	LFragment = vec4(color.x, color.y, 0.0/*color.z*/, 1.0/*color.a*/); 
}