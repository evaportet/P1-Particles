#version 330

in vec3 in_Position;

uniform mat4 mv_Mat;

void main() {
	gl_Position = mv_Mat * vec4(in_Position, 1.0);
}