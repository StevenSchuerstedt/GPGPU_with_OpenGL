#version 100

varying mediump vec2 texcoord;


uniform sampler2D textureX;
uniform sampler2D textureY;

void main(){

	mediump vec4 x = texture2D(textureX, texcoord);
	mediump vec4 y = texture2D(textureY, texcoord);

	gl_FragColor = x + y;
}
