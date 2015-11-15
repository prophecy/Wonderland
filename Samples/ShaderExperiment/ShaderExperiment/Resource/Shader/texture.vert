#version 330

in vec2 aTexCoord;
in vec2 LVertexPos2D; 

out vec2 vTexCoord;

void main() 
{ 
	vTexCoord = aTexCoord;
	gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); 
}