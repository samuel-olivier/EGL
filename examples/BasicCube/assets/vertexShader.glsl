#version 120

attribute vec3 position;
attribute vec3 normal;
attribute vec2 texCoord;
attribute vec4 color;

uniform mat4 mvp;
uniform mat4 v;
uniform mat4 m;
uniform mat4 p;

varying vec4 vertexColor;

void main() {
	gl_Position = mvp * vec4(position, 1.0);
    vertexColor = color;
}