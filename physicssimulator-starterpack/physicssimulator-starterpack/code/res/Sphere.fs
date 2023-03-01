#version 330

in vec4 eyePos;
in vec4 centerEyePos;

out vec4 out_Color;

uniform mat4 projMat;
uniform mat4 mv_Mat;
uniform vec4 color;
uniform float radius;

void main() {
	vec4 diff = eyePos - centerEyePos;
	float distSq2C = dot(diff, diff);
	if (distSq2C > (radius*radius)) discard;
	float h = sqrt(radius*radius - distSq2C);
	vec4 nuEyePos = vec4(eyePos.xy, eyePos.z + h, 1.0);
	vec4 nuPos = projMat * nuEyePos;
	gl_FragDepth = ((nuPos.z / nuPos.w) + 1) * 0.5;
	vec3 normal = normalize(nuEyePos - centerEyePos).xyz;
	out_Color = vec4(color.xyz * dot(normal, (mv_Mat*vec4(0.0, 1.0, 0.0, 0.0)).xyz) + color.xyz * 0.3, 1.0 );
}