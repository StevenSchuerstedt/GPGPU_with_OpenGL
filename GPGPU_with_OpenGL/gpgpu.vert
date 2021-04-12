#version 100

attribute vec2 position;
attribute vec2 Texcoord;

varying vec2 texcoord;

uniform mat4 proj;
void main(){

texcoord = Texcoord;

gl_Position = proj * vec4(position, 0.0, 1.0);

}