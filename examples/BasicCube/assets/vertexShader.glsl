#version 120

attribute vec3 position;
attribute vec3 normal;
attribute vec2 texCoord;
attribute vec4 color;

varying vec4 vertexColor;

void main() {
	gl_Position.xyz = position;
    gl_Position.w = 1.0;
    vertexColor = color;
}