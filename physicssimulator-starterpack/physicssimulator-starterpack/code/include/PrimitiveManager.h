#pragma once

#include <Program.h>
#include <RenderPrims.h>

namespace graphics {
	class PrimitiveManager {
	public:
		SpherePrimitive* NewSphere(glm::vec3 center, float radius);
		CubePrimitive* NewCube(glm::mat4 objMat);
		MeshPrimitive* NewMesh(int rows, int cols);
		CapsulePrimitive* NewCapsule(glm::vec3 posA, glm::vec3 posB, float radius);
		ParticlesPrimitive* NewParticles(int maxParticles = MAX_PARTICLES);

		void DestroyPrimitive(Primitive* primitive);

		void Render();
		void Setup();
		void Cleanup();
	private:
		void TrackPrimitive(Primitive* primitive);

		std::set<Primitive*> primitives;

		Program* sphereProgram, * capsuleProgram, * cubeProgram, * meshProgram;
	};
}