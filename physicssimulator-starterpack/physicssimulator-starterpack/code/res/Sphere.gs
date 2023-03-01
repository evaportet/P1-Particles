#version 330

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

out vec4 eyePos;
out vec4 centerEyePos;

uniform mat4 projMat;
uniform float radius;

vec4 nu_verts[4];
void main() {
	vec3 n = normalize(-gl_in[0].gl_Position.xyz);
	vec3 up = vec3(0.0, 1.0, 0.0);
	vec3 u = normalize(cross(up, n));
	vec3 v = normalize(cross(n, u));
	nu_verts[0] = vec4(-radius*u - radius*v, 0.0); 
	nu_verts[1] = vec4( radius*u - radius*v, 0.0); 
	nu_verts[2] = vec4(-radius*u + radius*v, 0.0); 
	nu_verts[3] = vec4( radius*u + radius*v, 0.0); 
	centerEyePos = gl_in[0].gl_Position;
	for (int i = 0; i < 4; ++i) {
		eyePos = (gl_in[0].gl_Position + nu_verts[i]);
		gl_Position = projMat * eyePos;
		EmitVertex();
	}
	EndPrimitive();
}