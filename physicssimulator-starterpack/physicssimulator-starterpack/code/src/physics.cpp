#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include <cstdio>

#include "Parabola.h" //AA2
#include "AA3.h"
#include "AA4.h"
#include "AA5.h"

#pragma region simulationSelection
enum class EnabledSimulation {
	PARABOLA,
	AA3,
	AA4,
	AA5
};

Simulator* currentSimulator;
EnabledSimulation currentSimulation;
void setSimulation(EnabledSimulation simulation) {
	if (currentSimulation == simulation) {
		return;
	}

	delete currentSimulator;
	currentSimulation = simulation;
	switch (simulation) {
		case EnabledSimulation::PARABOLA:
			printf("Start the random particles simulation\n");
			currentSimulator = new ParabolaSim();
			break;
		case EnabledSimulation::AA3:
			printf("Start the cloth simulation\n");
			currentSimulator = new AA3();
			break;
		case EnabledSimulation::AA4:
			printf("Start the AA4 simulation\n");
			currentSimulator = new AA4();
			break;
		case EnabledSimulation::AA5:
			printf("Start the AA5 simulation\n");
			currentSimulator = new AA5();
			break;
	}
}
#pragma endregion

#pragma region GUI
bool show_test_window = false;
void GUI() {
	bool show = true;
	
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Simulation")) {
			if (ImGui::MenuItem("AA2: Particles")) { setSimulation(EnabledSimulation::PARABOLA); };
			if (ImGui::MenuItem("AA3: Cloth")) { setSimulation(EnabledSimulation::AA3); };
			if (ImGui::MenuItem("AA4: Rigidbody")) { setSimulation(EnabledSimulation::AA4); };
			if (ImGui::MenuItem("AA5: Fluids")) { setSimulation(EnabledSimulation::AA5); };
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	ImGui::Begin("Physics Parameters", &show, 0);
	{	
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate
		
		currentSimulator->RenderGui();
	}
	
	ImGui::End();
}

#pragma endregion


void PhysicsInit() {
	// The default simulation
	currentSimulation = EnabledSimulation::AA4;
	currentSimulator = new AA5();
}

void PhysicsUpdate(float dt) {
	currentSimulator->Update(dt);
	currentSimulator->RenderUpdate();
}

void PhysicsCleanup() {
	delete currentSimulator;
}