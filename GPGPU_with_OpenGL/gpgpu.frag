#version 330 core

in vec2 texcoord;


uniform sampler2DRect textureX;
uniform sampler2DRect textureY;

void main(){

	vec4 x = texture2DRect(textureX, texcoord);
	vec4 y = texture2DRect(textureY, texcoord);

	gl_FragColor = x + y;
}
