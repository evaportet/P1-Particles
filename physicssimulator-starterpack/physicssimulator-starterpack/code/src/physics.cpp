#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include <cstdio>

#include "Parabola.h"


#pragma region simulationSelection
enum class EnabledSimulation {
	PARABOLA,
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
	}
}
#pragma endregion

#pragma region GUI
bool show_test_window = false;
void GUI() {
	bool show = true;
	
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Simulation")) {
			if (ImGui::MenuItem("Parabola")) { setSimulation(EnabledSimulation::PARABOLA); };
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
	currentSimulation = EnabledSimulation::PARABOLA;
	currentSimulator = new ParabolaSim();
}

void PhysicsUpdate(float dt) {
	currentSimulator->Update(dt);
	currentSimulator->RenderUpdate();
}

void PhysicsCleanup() {
	delete currentSimulator;
}