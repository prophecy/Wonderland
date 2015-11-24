#version 330

uniform float uColorScale;
uniform sampler2D texUnit0;

in vec2 vTexCoord;
in vec4 vColor;

out vec4 fragColor;

void main(void)
{
	vec4 color0 = vec4(vColor.x, vColor.y, vColor.z, 1);
	vec4 color1 = texture2D(texUnit0, vTexCoord);

	float lerper = clamp(.3 * uColorScale, 0., 1.);
	fragColor = (lerper)*color1 + (1.-lerper)*color0;
}