#include <PrimitiveManager.h>

using namespace graphics;

void PrimitiveManager::TrackPrimitive(Primitive* primitive) {
	primitives.insert(primitive);
}
void PrimitiveManager::DestroyPrimitive(Primitive* primitive) {
	primitives.erase(primitive);
	delete primitive;
}

SpherePrimitive* PrimitiveManager::NewSphere(glm::vec3 center, float radius) {
	auto sphere = new SpherePrimitive(*sphereProgram, center, radius);
	sphere->SetVisible(true);
	TrackPrimitive(sphere);
	return sphere;
}

CubePrimitive* PrimitiveManager::NewCube(glm::mat4 objMat) {
	auto cube = new CubePrimitive(*cubeProgram, objMat);
	cube->SetVisible(true);
	TrackPrimitive(cube);
	return cube;
}

MeshPrimitive* PrimitiveManager::NewMesh(int rows, int cols) {
	auto mesh = new MeshPrimitive(*meshProgram, rows, cols);
	mesh->SetVisible(true);
	TrackPrimitive(mesh);
	return mesh;
}

CapsulePrimitive* PrimitiveManager::NewCapsule(glm::vec3 posA, glm::vec3 posB, float radius) {
	auto capsule = new CapsulePrimitive(*capsuleProgram, posA, posB, radius);
	capsule->SetVisible(true);
	TrackPrimitive(capsule);
	return capsule;
}

ParticlesPrimitive* PrimitiveManager::NewParticles(int maxParticles) {
	auto particles = new ParticlesPrimitive(*sphereProgram, maxParticles);
	particles->SetVisible(true);
	TrackPrimitive(particles);
	return particles;
}

void PrimitiveManager::Setup() {
	std::vector<LayoutAttrib> layout = { {0, "in_Position"} };

	// all the programs share the layout
	sphereProgram = new Program({ "res/Sphere.vs", "res/Sphere.gs", "res/Sphere.fs" }, "sphere", layout);
	capsuleProgram = new Program({ "res/Capsule.vs", "res/Capsule.gs", "res/Capsule.fs" }, "capsule", layout);
	cubeProgram = new Program({ "res/Cube.vs", "", "res/Cube.fs" }, "cube", layout);
	meshProgram = new Program({ "res/Mesh.vs", "", "res/Mesh.fs" }, "mesh", layout);
}

void PrimitiveManager::Cleanup() {
	delete sphereProgram, cubeProgram, meshProgram, capsuleProgram;
}

void PrimitiveManager::Render() {
	for (auto& prim : primitives) {
		prim->Render();
	}
}