#version 330
layout(lines) in; 
layout(triangle_strip, max_vertices = 14) out;
out vec3 eyePos;
out vec3 capPoints[2];
uniform mat4 projMat;
uniform float radius;
vec3 boxVerts[8];
int boxIdx[14];
void main(){
	vec3 A = gl_in[0].gl_Position.xyz;
	vec3 B = gl_in[1].gl_Position.xyz;
	if(gl_in[1].gl_Position.x < gl_in[0].gl_Position.x) {
		A = gl_in[1].gl_Position.xyz;
		B = gl_in[0].gl_Position.xyz;
	}
	vec3 u = vec3(0.0, 1.0, 0.0);
	if (abs(dot(u, normalize(gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz))) - 1.0 < 1e-6) {
		if(gl_in[1].gl_Position.y > gl_in[0].gl_Position.y) {
			A = gl_in[1].gl_Position.xyz;
			B = gl_in[0].gl_Position.xyz;
		}
		u = vec3(1.0, 0.0, 0.0);
	}
	vec3 Am = normalize(A - B); 
	vec3 Bp = -Am;
	vec3 v = normalize(cross(Am, u)) * radius;
	u = normalize(cross(v, Am)) * radius;
	Am *= radius;
	Bp *= radius;
	boxVerts[0] = A + Am - u - v;
	boxVerts[1] = A + Am + u - v;
	boxVerts[2] = A + Am + u + v;
	boxVerts[3] = A + Am - u + v;
	boxVerts[4] = B + Bp - u - v;
	boxVerts[5] = B + Bp + u - v;
	boxVerts[6] = B + Bp + u + v;
	boxVerts[7] = B + Bp - u + v;
	boxIdx = int[](0, 3, 4, 7, 6, 3, 2, 1, 6, 5, 4, 1, 0, 3);
	capPoints[0] = A;
	capPoints[1] = B;
	for (int i = 0; i<14; ++i) {
		eyePos = boxVerts[boxIdx[i]];
		gl_Position = projMat * vec4(boxVerts[boxIdx[i]], 1.0);
		EmitVertex();
	}
	EndPrimitive();
}