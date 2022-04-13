#version 150

in  vec4 color;
in  vec2 vst;
uniform sampler2D texMap;
out vec4 fColor;

void main() 
{ 
	fColor = mix(color, 
		color*texture2D(texMap, vst),
		step(255, color*texture2D(texMap, vst)));
}