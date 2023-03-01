#pragma once
#include <glm/glm.hpp>
#include <gl/glew.h>
#include "Buffers.h"
#include <Program.h>
#include <set>

namespace graphics {
	const int MAX_PARTICLES = SHRT_MAX;

	class Primitive {
	public:
		Primitive() : visible(false) {};
		virtual ~Primitive() {};
		void Render();

		bool IsVisible();
		void ToggleVisibility();
		void SetVisible(bool value);
	protected:
		virtual void RenderPrimitive() = 0;
	private:
		bool visible;
	};

	class SpherePrimitive : public Primitive {
	public:
		SpherePrimitive(Program& program, glm::vec3 center, float radius, glm::vec4 color = glm::vec4(0.6f, 0.1f, 0.1f, 1.f));
		~SpherePrimitive();

		void Update(const glm::vec3 pos, const float radius);
	protected:
		virtual void RenderPrimitive();
	private:
		glm::vec3 center;
		float radius;
		glm::vec4 color;

		Program& program;
		GLuint sphereVao;
		VertexBuffer* vb;
	};

	class CubePrimitive : public Primitive {
	public:
		CubePrimitive(Program& program, glm::mat4 objMat, glm::vec4 color = glm::vec4(0.1f, 1.0f, 1.0f, 0.f));
		~CubePrimitive();

		void Update(const glm::mat4 objMat);
	protected:
		void RenderPrimitive();
	private:
		glm::mat4 objMat;
		glm::vec4 color;
		Program& program;
		// Share with all the instances, we never change the data (updates are done by the transform matrix)
		GLuint cubeVao;
		VertexBuffer* cubeVb[2];
		IndexBuffer<GLubyte>* cubeIb;
	};

	class MeshPrimitive : public Primitive {
	public:
		MeshPrimitive(Program& program, int rows, int cols, glm::vec4 color = glm::vec4(0.1f, 1.f, 1.f, 0.f));
		~MeshPrimitive();
		void Update(const float* arrayData);
		int GetRows();
		int GetCols();
	protected:
		void RenderPrimitive();
	private:
		int rows;
		int cols;
		int meshNumVirtualVerts;

		glm::vec4 color;

		Program& program;
		GLuint meshVao;
		VertexBuffer* meshVb;
		IndexBuffer<GLubyte>* meshIb;
	};

	class CapsulePrimitive : public Primitive {
	public:
		CapsulePrimitive(Program& program, glm::vec3 posA, glm::vec3 posB, float radius, glm::vec4 color = glm::vec4(0.1f, 0.6f, 0.1f, 1.f));
		~CapsulePrimitive();

		void Update(const glm::vec3 posA, const glm::vec3 posB, const float radius);
	protected:
		void RenderPrimitive();
	private:
		glm::vec4 color;
		float radius;
		
		Program& program;
		GLuint vao;
		VertexBuffer* vb;
		IndexBuffer<GLubyte>* ib;
	};

	class ParticlesPrimitive : public Primitive {
	public:
		ParticlesPrimitive(Program& program, int maxParticles = SHRT_MAX, glm::vec4 color = glm::vec4(0.1f, 0.1f, 0.6f, 1.f));
		~ParticlesPrimitive();

		void Update(const int startIdx, const int count, const float* arrayData);
		const int maxParticles;
		int numParticles;
		int firstParticle;
	protected:
		void RenderPrimitive();
	private:
		glm::vec4 color;
		float radius;

		Program& program;
		GLuint vao;
		VertexBuffer* vb;
	};

	class SimulationBox : public Primitive {
	public:
		SimulationBox();
		~SimulationBox();

		void SetMvp(glm::mat4 mvp);
	protected:
		void RenderPrimitive();
	private:
		const float cubeVerts[3 * 8] = {
			// -5,0,-5 -- 5, 10, 5
			-5.f,  0.f, -5.f,
			 5.f,  0.f, -5.f,
			 5.f,  0.f,  5.f,
			-5.f,  0.f,  5.f,
			-5.f, 10.f, -5.f,
			 5.f, 10.f, -5.f,
			 5.f, 10.f,  5.f,
			-5.f, 10.f,  5.f,
		};
		const GLubyte cubeIdx[4 * 5] = {
			1, 0, 2, 3, // Floor - TriangleStrip
			0, 1, 5, 4, // Wall - Lines
			1, 2, 6, 5, // Wall - Lines
			2, 3, 7, 6, // Wall - Lines
			3, 0, 4, 7  // Wall - Lines
		};
		const glm::vec4 floorColor{ 0.6f, 0.6f, 0.6f, 1.f };
		const glm::vec4 wallColor{ 0.f, 0.f, 0.f, 1.f };

		Program* program;
		GLuint vao;
		VertexBuffer* vb;
		IndexBuffer<GLubyte>* ib;
		glm::mat4 mvp;
	};

	class Axis : public Primitive {
	public:
		Axis();
		~Axis();

		void SetMvp(glm::mat4 mvp);
	protected:
		void RenderPrimitive();
	private:
		const float axisVerts[3*6] = {
			0.0, 0.0, 0.0,
			1.0, 0.0, 0.0,
			0.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 0.0,
			0.0, 0.0, 1.0
		};
		const float axisColors[4*6] = {
			1.0, 0.0, 0.0, 1.0,
			1.0, 0.0, 0.0, 1.0,
			0.0, 1.0, 0.0, 1.0,
			0.0, 1.0, 0.0, 1.0,
			0.0, 0.0, 1.0, 1.0,
			0.0, 0.0, 1.0, 1.0
		};
		const GLubyte axisIdx[6] = {
			0, 1,
			2, 3,
			4, 5
		};
		
		Program* program;
		GLuint vao;
		VertexBuffer* vb[2];
		IndexBuffer<GLubyte>* ib;
		glm::mat4 mvp;
	};
}