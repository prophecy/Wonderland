#version 140

in vec2 LVertexPos2D; 
in vec3 aColor;

out vec3 vColor;

void main() 
{ 
	gl_Position = vec4(LVertexPos2D.x, LVertexPos2D.y, 0, 1);
	vColor = vec3(.8, 0.0, 0.0);
}