#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 Texcoord;

out vec2 texcoord;

uniform mat4 proj;
void main(){

texcoord = Texcoord;

gl_Position = proj * vec4(position, 0.0, 1.0);

}