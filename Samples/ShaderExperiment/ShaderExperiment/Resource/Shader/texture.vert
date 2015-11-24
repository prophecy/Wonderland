#version 330

uniform float uColorScale = 1.0;

in vec2 aVertex;
in vec2 aTexCoord; 
in vec3 aColor;

out vec4 vColor;
out vec2 vTexCoord;

void main()
{
	gl_Position = vec4(aVertex.x * 0.6,
					   aVertex.y, 0, 1);
	vColor = vec4(aColor.x + 0.5, aColor.y + 0.5, aColor.z + 1.0, 1.0);
	vTexCoord = aTexCoord;
}