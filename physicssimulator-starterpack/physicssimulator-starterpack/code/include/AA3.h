#pragma once
#include <Simulator.h>
#include <RenderPrims.h>
#include <vector>
#include <PrimitiveManager.h>

extern graphics::PrimitiveManager manager;

class AA3 : public Simulator
{
public:
	AA3();
	~AA3();
	//Inherited via Simualtor
	void Update(float dt) override;
	void RenderUpdate() override;
	void RenderGui() override;
private:
	graphics::MeshPrimitive* mesh;
};

