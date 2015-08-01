#version 120

varying vec2 UV;
varying vec4 color;
varying vec3 Position_worldspace;
varying vec3 Normal_cameraspace;
varying vec3 EyeDirection_cameraspace;
varying vec3 LightDirection_cameraspace;

uniform vec3 LightPosition_worldspace;
uniform sampler2D DiffuseTexture;

void main() {
	vec3	LightColor = vec3(1.0, 1.0, 1.0);
	float	LightPower = 100.0f;
	
	vec3	MaterialDiffuseColor = color.xyz + texture2D(DiffuseTexture, UV).rgb;
	vec3	MaterialAmbientColor = vec3(0.1, 0.1, 0.1) * MaterialDiffuseColor;
	vec3	MaterialSpecularColor = vec3(0.3, 0.3, 0.3);

	float	distance = length(LightPosition_worldspace - Position_worldspace);

	vec3	n = normalize(Normal_cameraspace);
	vec3	l = normalize(LightDirection_cameraspace);
	float	cosTheta = clamp(dot(n, l), 0.0, 1.0);
	
	vec3	E = normalize(EyeDirection_cameraspace);
	vec3	R = reflect(-l, n);
	float	cosAlpha = clamp(dot(E, R), 0.0, 1.0);
	
	gl_FragColor.rgb =
		MaterialAmbientColor +
		MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance * distance) +
		MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance * distance);
}