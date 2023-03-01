#version 330
in vec3 eyePos;
in vec3 capPoints[2];
out vec4 out_Color;
uniform mat4 projMat;
uniform mat4 mv_Mat;
uniform vec4 color;
uniform float radius;
const int lin_steps = 30;
const int bin_steps = 5;
vec3 closestPointInSegment(vec3 p, vec3 a, vec3 b) {
	vec3 pa = p - a, ba = b - a;
	float h = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
	return a + ba*h;
}
void main() {
	vec3 viewDir = normalize(eyePos);
	float step = radius / 5.0;
	vec3 nuPB = eyePos;
	int i = 0;
	for(i = 0; i < lin_steps; ++i) {
		nuPB = eyePos + viewDir*step*i;
		vec3 C = closestPointInSegment(nuPB, capPoints[0], capPoints[1]);
		float dist = length(C - nuPB) - radius;
		if(dist < 0.0) break;
	}
	if(i==lin_steps) discard;
	vec3 nuPA = nuPB - viewDir*step;
	vec3 C;
	for(i = 0; i < bin_steps; ++i) {
		vec3 nuPC = nuPA + (nuPB - nuPA)*0.5; 
		C = closestPointInSegment(nuPC, capPoints[0], capPoints[1]); 
		float dist = length(C - nuPC) - radius; 
		if(dist > 0.0) nuPA = nuPC; 
		else nuPB = nuPC; 
	}
	vec4 nuPos = projMat * vec4(nuPA, 1.0);
	gl_FragDepth = ((nuPos.z / nuPos.w) + 1) * 0.5;
	vec3 normal = normalize(nuPA - C);
	out_Color = vec4(color.xyz * dot(normal, (mv_Mat*vec4(0.0, 1.0, 0.0, 0.0)).xyz) + color.xyz * 0.3, 1.0 );
}