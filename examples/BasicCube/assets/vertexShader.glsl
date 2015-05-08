#version 120

attribute vec3 vertexPosition_modelspace;
attribute vec2 vertexUV;
attribute vec3 vertexNormal_modelspace;
attribute vec4 vertexColor;

varying vec2 UV;
varying vec4 color;
varying vec3 Position_worldspace;
varying vec3 Normal_cameraspace;
varying vec3 EyeDirection_cameraspace;
varying vec3 LightDirection_cameraspace;

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform vec3 LightPosition_worldspace;

void main(){
	gl_Position =  MVP * vec4(vertexPosition_modelspace, 1.0);

	Position_worldspace = (M * vec4(vertexPosition_modelspace, 1.0)).xyz;
	vec3 vertexPosition_cameraspace = (V * M * vec4(vertexPosition_modelspace, 1)).xyz;
	EyeDirection_cameraspace = vec3(0.0, 0.0, 0.0) - vertexPosition_cameraspace;

	vec3 LightPosition_cameraspace = (V * vec4(LightPosition_worldspace, 1.0)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
	
	Normal_cameraspace = (V * M * vec4(vertexNormal_modelspace,0)).xyz;
	
	UV = vertexUV;
	color = vertexColor;
}