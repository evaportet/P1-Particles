#include "RenderPrims.h"
#include "Program.h"
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

// TODO move to statics or sth
namespace CubeConstants {
	extern const float halfW = 0.5f;
	int numVerts = 24 + 6; // 4 vertex/face * 6 faces + 6 PRIMITIVE RESTART

	//   4---------7
	//  /|        /|
	// / |       / |
	//5---------6  |
	//|  0------|--3
	//| /       | /
	//|/        |/
	//1---------2
	glm::vec3 verts[] = {
		glm::vec3(-halfW, -halfW, -halfW),
		glm::vec3(-halfW, -halfW,  halfW),
		glm::vec3(halfW, -halfW,  halfW),
		glm::vec3(halfW, -halfW, -halfW),
		glm::vec3(-halfW,  halfW, -halfW),
		glm::vec3(-halfW,  halfW,  halfW),
		glm::vec3(halfW,  halfW,  halfW),
		glm::vec3(halfW,  halfW, -halfW)
	};
	glm::vec3 norms[] = {
		glm::vec3(0.f, -1.f,  0.f),
		glm::vec3(0.f,  1.f,  0.f),
		glm::vec3(-1.f,  0.f,  0.f),
		glm::vec3(1.f,  0.f,  0.f),
		glm::vec3(0.f,  0.f, -1.f),
		glm::vec3(0.f,  0.f,  1.f)
	};

	glm::vec3 cubeVerts[] = {
		verts[1], verts[0], verts[2], verts[3],
		verts[5], verts[6], verts[4], verts[7],
		verts[1], verts[5], verts[0], verts[4],
		verts[2], verts[3], verts[6], verts[7],
		verts[0], verts[4], verts[3], verts[7],
		verts[1], verts[2], verts[5], verts[6]
	};
	glm::vec3 cubeNorms[] = {
		norms[0], norms[0], norms[0], norms[0],
		norms[1], norms[1], norms[1], norms[1],
		norms[2], norms[2], norms[2], norms[2],
		norms[3], norms[3], norms[3], norms[3],
		norms[4], norms[4], norms[4], norms[4],
		norms[5], norms[5], norms[5], norms[5]
	};
	GLubyte cubeIdx[] = {
		0, 1, 2, 3, UCHAR_MAX,
		4, 5, 6, 7, UCHAR_MAX,
		8, 9, 10, 11, UCHAR_MAX,
		12, 13, 14, 15, UCHAR_MAX,
		16, 17, 18, 19, UCHAR_MAX,
		20, 21, 22, 23, UCHAR_MAX
	};
}

namespace RenderVars {
	extern glm::mat4 _MVP, _modelView, _projection;
	extern glm::vec4 _cameraPoint;
}

using namespace graphics;

#pragma region primitive
void Primitive::Render() {
	if (visible) RenderPrimitive();
}

bool Primitive::IsVisible() { return visible; };
void Primitive::ToggleVisibility() { visible = !visible; };
void Primitive::SetVisible(bool value) { visible = value; }
#pragma endregion

#pragma region sphere
SpherePrimitive::SpherePrimitive(
	Program& program,
	glm::vec3 center, float radius,
	glm::vec4 color
) : program(program), center(center), radius(radius), color(color)
{
	glGenVertexArrays(1, &sphereVao);
	glBindVertexArray(sphereVao);

	vb = new VertexBuffer(&(center.x), sizeof(float) * 3, true);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	vb->Unbind();
};

SpherePrimitive::~SpherePrimitive() {
	delete vb;
}

void SpherePrimitive::Update(const glm::vec3 pos, const float radius) {
	float* buff = vb->MapWriteOnly();
	buff[0] = pos.x;
	buff[1] = pos.y;
	buff[2] = pos.z;
	vb->Unmap();
	vb->Unbind();
	this->radius = radius;
}
	
void SpherePrimitive::RenderPrimitive() {
	glBindVertexArray(sphereVao);
	program.Bind();
	program.SetUniform("mvpMat", RenderVars::_MVP);
	program.SetUniform("mv_Mat", RenderVars::_modelView);
	program.SetUniform("projMat", RenderVars::_projection);
	program.SetUniform("color", color);
	program.SetUniform("radius", radius);
	glDrawArrays(GL_POINTS, 0, 1);

	program.Unbind();
	glBindVertexArray(0);
}
#pragma endregion

#pragma region cube
CubePrimitive::CubePrimitive(
	Program& program, glm::mat4 objMat, glm::vec4 color
) : program(program), objMat(objMat), color(color)
{
	glGenVertexArrays(1, &cubeVao);
	glBindVertexArray(cubeVao);

	cubeVb[0] = new VertexBuffer(CubeConstants::cubeVerts, sizeof(CubeConstants::cubeVerts), false);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	cubeVb[1] = new VertexBuffer(CubeConstants::cubeNorms, sizeof(CubeConstants::cubeNorms), false);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glPrimitiveRestartIndex(UCHAR_MAX);
	auto indexCount = sizeof(CubeConstants::cubeIdx) / sizeof(GLubyte);
	cubeIb = new IndexBuffer<GLubyte>(CubeConstants::cubeIdx, indexCount, false);

	glBindVertexArray(0);
	cubeVb[1]->Unbind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

CubePrimitive::~CubePrimitive() {
	glDeleteVertexArrays(1, &cubeVao);
	delete cubeVb[0];
	delete cubeVb[1];
	delete cubeIb;
}

void CubePrimitive::Update(const glm::mat4 objMat) {
	this->objMat = objMat;
}

void CubePrimitive::RenderPrimitive() {
		glEnable(GL_PRIMITIVE_RESTART);
		glBindVertexArray(cubeVao);
		program.Bind();

		program.SetUniform("objMat", objMat);
		program.SetUniform("mv_Mat", RenderVars::_modelView);
		program.SetUniform("mvpMat", RenderVars::_MVP);
		program.SetUniform("color", color);

		glDrawElements(GL_TRIANGLE_STRIP, CubeConstants::numVerts, GL_UNSIGNED_BYTE, 0);

		program.Unbind();
		glBindVertexArray(0);
		glDisable(GL_PRIMITIVE_RESTART);
	}
#pragma endregion

#pragma region mesh
MeshPrimitive::MeshPrimitive(
	Program& program, int rows, int cols, glm::vec4 color
) : program(program), rows(rows), cols(cols), color(color)
{
	glGenVertexArrays(1, &meshVao);
	glBindVertexArray(meshVao);

	meshVb = new VertexBuffer(0, sizeof(float) * 3 * cols * rows, true);

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glPrimitiveRestartIndex(UCHAR_MAX);
	int facesVertsIdx = 5 * (cols - 1) * (rows- 1);
	GLubyte* facesIdx = new GLubyte[facesVertsIdx];
	for (int i = 0; i < (rows - 1); ++i) {
		for (int j = 0; j < (cols - 1); ++j) {
			facesIdx[5 * (i * (cols - 1) + j) + 0] = i * cols + j;
			facesIdx[5 * (i * (cols - 1) + j) + 1] = (i + 1) * cols + j;
			facesIdx[5 * (i * (cols - 1) + j) + 2] = (i + 1) * cols + (j + 1);
			facesIdx[5 * (i * (cols - 1) + j) + 3] = i * cols + (j + 1);
			facesIdx[5 * (i * (cols - 1) + j) + 4] = UCHAR_MAX;
		}
	}
	meshNumVirtualVerts = facesVertsIdx;

	meshIb = new IndexBuffer<GLubyte>(facesIdx, meshNumVirtualVerts, false);
	delete[] facesIdx;

	glBindVertexArray(0);
	meshVb->Unbind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

MeshPrimitive::~MeshPrimitive() {
	glDeleteVertexArrays(1, &meshVao);
	delete meshIb;
	delete meshVb;
}

int MeshPrimitive::GetRows() { return rows; }
int MeshPrimitive::GetCols() { return cols; }

void MeshPrimitive::Update(const float* arrayData) {
	float* buff = meshVb->MapWriteOnly();
	memcpy(buff, arrayData, sizeof(float) * 3 * cols * rows);
	meshVb->Unmap();
	meshVb->Unbind();
}

void MeshPrimitive::RenderPrimitive() {
	glEnable(GL_PRIMITIVE_RESTART);
	glBindVertexArray(meshVao);
	program.Bind();

	program.SetUniform("mvpMat", RenderVars::_MVP);
	program.SetUniform("color", color);
	glDrawElements(GL_LINE_LOOP, meshNumVirtualVerts, GL_UNSIGNED_BYTE, 0);

	program.Unbind();
	glBindVertexArray(0);
	glDisable(GL_PRIMITIVE_RESTART);
}
#pragma endregion

#pragma region capsule
CapsulePrimitive::CapsulePrimitive(
	Program& program, glm::vec3 posA, glm::vec3 posB, float radius, glm::vec4 color
) : program(program), radius(radius), color(color)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	float capsuleVerts[] = {
		posA.x, posA.y, posA.z,
		posB.x, posB.y, posB.z
	};
	GLubyte capsuleIdx[] = {
		0, 1
	};

	vb = new VertexBuffer(capsuleVerts, sizeof(float) * 6, true);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	ib = new IndexBuffer<GLubyte>(capsuleIdx, 2, false);
		
	glBindVertexArray(0);
	vb->Unbind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

CapsulePrimitive::~CapsulePrimitive() {
	delete vb, ib;
	glDeleteVertexArrays(1, &vao);
}

void CapsulePrimitive::Update(const glm::vec3 posA, const glm::vec3 posB, const float radius) {
	float vertPos[] = { posA.x, posA.y, posA.z, posB.z, posB.y, posB.z };
	float* buff = vb->MapWriteOnly();
	buff[0] = posA.x; buff[1] = posA.y; buff[2] = posA.z;
	buff[3] = posB.x; buff[4] = posB.y; buff[5] = posB.z;
	vb->Unmap();
	vb->Unbind();
	this->radius = radius;
}

void CapsulePrimitive::RenderPrimitive() {
	glBindVertexArray(vao);
	program.Bind();
	program.SetUniform("mvpMat", RenderVars::_MVP);
	program.SetUniform("mv_Mat", RenderVars::_modelView);
	program.SetUniform("projMat", RenderVars::_projection);
	program.SetUniform("camPoint", RenderVars::_cameraPoint);
	program.SetUniform("color", color);
	program.SetUniform("radius", radius);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, 0);

	program.Unbind();
	glBindVertexArray(0);
}
#pragma endregion

#pragma region particles
ParticlesPrimitive::ParticlesPrimitive(
	Program& program, int maxParticles, glm::vec4 color
) : program(program), maxParticles(maxParticles), numParticles(0), firstParticle(0), radius(0.05f), color(color)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	vb = new VertexBuffer(0, sizeof(float) * 3 * maxParticles, true);

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	vb->Unbind();
}
ParticlesPrimitive::~ParticlesPrimitive() {
	glDeleteVertexArrays(1, &vao);
	delete vb;
}

void ParticlesPrimitive::RenderPrimitive() {
	glBindVertexArray(vao);
	program.Bind();

	program.SetUniform("mvpMat", RenderVars::_MVP);
	program.SetUniform("mv_Mat", RenderVars::_modelView);
	program.SetUniform("projMat", RenderVars::_projection);
	program.SetUniform("color", color);
	program.SetUniform("radius", radius);

	if (firstParticle + numParticles < maxParticles) {
		glDrawArrays(GL_POINTS, firstParticle, numParticles);
	}
	else {
		int rem = maxParticles - firstParticle;
		glDrawArrays(GL_POINTS, firstParticle, rem);
		glDrawArrays(GL_POINTS, 0, numParticles - rem);
	}

	program.Unbind();
	glBindVertexArray(0);
}

void ParticlesPrimitive::Update(const int startIdx, const int count, const float* arrayData) {
	float* buff = vb->MapWriteOnly();
	buff = &buff[3 * startIdx];
	memcpy(buff, arrayData, sizeof(float) * 3 * count);
	vb->Unmap();
	vb->Unbind();
}
#pragma endregion

#pragma region simbox
SimulationBox::SimulationBox() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	vb = new graphics::VertexBuffer(cubeVerts, sizeof(cubeVerts), false);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	ib = new graphics::IndexBuffer<GLubyte>(cubeIdx, sizeof(cubeIdx) / sizeof(GLubyte), false);

	glBindVertexArray(0);
	vb->Unbind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	std::vector<graphics::LayoutAttrib> layout = {
		{0, "in_Position"}
	};

	program = new graphics::Program({ "res/Box.vs", "", "res/Box.fs" }, "box", layout);
}

SimulationBox::~SimulationBox() {
	delete vb;
	delete ib;
	glDeleteVertexArrays(1, &vao);
	delete program;
}

void SimulationBox::SetMvp(glm::mat4 mvp) { this->mvp = mvp; }

void SimulationBox::RenderPrimitive() {
	glBindVertexArray(vao);
	program->Bind();
	program->SetUniform("mvpMat", mvp);
	// FLOOR
	program->SetUniform("color", floorColor);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, 0);
	// WALLS
	program->SetUniform("color", wallColor);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, (void*)(sizeof(GLubyte) * 4));
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, (void*)(sizeof(GLubyte) * 8));
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, (void*)(sizeof(GLubyte) * 12));
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, (void*)(sizeof(GLubyte) * 16));

	program->Unbind();
	glBindVertexArray(0);
}
#pragma endregion

#pragma region axis
Axis::Axis() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vb[0] = new VertexBuffer(axisVerts, sizeof(axisVerts), false);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	vb[1] = new VertexBuffer(axisColors, sizeof(axisColors), false);
	glVertexAttribPointer((GLuint)1, 4, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(1);

	ib = new IndexBuffer<GLubyte>(axisIdx, sizeof(axisIdx) / sizeof(GLubyte), false);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	std::vector<graphics::LayoutAttrib> layout = {
		{0, "in_Position"},
		{1, "in_Color"}
	};

	program = new graphics::Program({ "res/Axis.vs", "", "res/Axis.fs" }, "axis", layout);
}

Axis::~Axis() {
	delete vb[0];
	delete vb[1];
	delete ib;

	glDeleteVertexArrays(1, &vao);

	delete program;
}

void Axis::SetMvp(glm::mat4 mvp) { this->mvp = mvp; };

void Axis::RenderPrimitive() {
	glBindVertexArray(vao);
	program->Bind();
	program->SetUniform("mvpMat", mvp);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_BYTE, 0);

	program->Unbind();
	glBindVertexArray(0);
}
#pragma endregion
