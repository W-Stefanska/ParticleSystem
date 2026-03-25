#pragma once

#include "imgui.h"
#include <Gui.h>

class Manager {
private:
	ofxImGui::Gui gui;

	std::vector<std::unique_ptr<Collider>>* colliders = nullptr;
	std::vector<std::unique_ptr<Emitter>>* emitters = nullptr;

	Emitter* selectedEmitter = nullptr;
	Collider* selectedCollider = nullptr;
public:
	void setup(
		std::vector<std::unique_ptr<Collider>>& c,
		std::vector<std::unique_ptr<Emitter>>& e)
	{
		colliders = &c;
		emitters = &e;
		gui.setup();
	}

	void draw() {
		ofDisableLighting();
		ofSetColor(255);
		gui.begin();

		ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(200, 400), ImGuiCond_Always);
		ImGui::Begin("Objects");

		if (ImGui::Button("Add Emitter"))  emitters->push_back(std::make_unique<BasicEmitter>());
		if (ImGui::Button("Add Collider")) colliders->push_back(std::make_unique<SphereCollider>());

		ImGui::Separator();
		if (ImGui::CollapsingHeader("Emitters")) {
			for (int i = 0; i < emitters->size(); i++) {
				std::string label = "Emitter " + std::to_string(i);
				if (ImGui::Selectable(label.c_str(), selectedEmitter == (*emitters)[i].get())) {
					selectedEmitter = (*emitters)[i].get();
					selectedCollider = nullptr;
				}
			}
		}	

		ImGui::Separator();
		if (ImGui::CollapsingHeader("Colliders")) {
			for (int i = 0; i < colliders->size(); i++) {
				std::string label = "Collider " + std::to_string(i);
				if (ImGui::Selectable(label.c_str(), selectedCollider == (*colliders)[i].get())) {
					selectedCollider = (*colliders)[i].get();
					selectedEmitter = nullptr;
				}
			}
		}
		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(ofGetWidth() - 220, 20), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(200, 400), ImGuiCond_Always);
		ImGui::Begin("Settings");
		if (selectedEmitter)  selectedEmitter->drawSettings();
		if (selectedCollider) selectedCollider->drawSettings();
		ImGui::End();

		gui.end();
	}
};