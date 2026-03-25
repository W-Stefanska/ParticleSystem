#pragma once

#include "imgui.h"
#include <Gui.h>

class Manager {
private:
	ofxImGui::Gui gui;
	int emitterCounter = 0;
	int colliderCounter = 0;

	std::vector<std::unique_ptr<Collider>>* colliders = nullptr;
	std::vector<std::unique_ptr<Emitter>>* emitters = nullptr;

	Emitter* selectedEmitter = nullptr;
	Collider* selectedCollider = nullptr;
	Emitter* selectedBasicEmitter = nullptr;
	Collider* selectedBasicCollider = nullptr;
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

		if (ImGui::Button("Add Emitter")) {
			emitters->push_back(std::make_unique<BasicEmitter>());
			emitters->back()->setName("Emitter " + std::to_string(emitterCounter++));
		}
		if (ImGui::Button("Add Collider")) {
			colliders->push_back(std::make_unique<BasicCollider>());
			colliders->back()->setName("Collider " + std::to_string(colliderCounter++));
		}

		ImGui::Separator();
		if (ImGui::CollapsingHeader("Emitters")) {
			for (int i = 0; i < emitters->size(); i++) {
				std::string label = (*emitters)[i].get()->getName();
				if (ImGui::Selectable(label.c_str(), selectedEmitter == (*emitters)[i].get())) {
					Emitter* current = (*emitters)[i].get();

					if (current->isBasicEmitter()) {
						selectedBasicEmitter = current;
						selectedEmitter = nullptr;
					}
					else {
						selectedEmitter = current;
						selectedBasicEmitter = nullptr;
					}

					selectedCollider = nullptr;
				}
			}
		}	

		ImGui::Separator();
		if (ImGui::CollapsingHeader("Colliders")) {
			for (int i = 0; i < colliders->size(); i++) {
				std::string label = (*colliders)[i].get()->getName();
				if (ImGui::Selectable(label.c_str(), selectedCollider == (*colliders)[i].get())) {
					Collider* current = (*colliders)[i].get();

					if (current->isBasicCollider()) {
						selectedBasicCollider = current;
						selectedCollider = nullptr;
					}
					else {
						selectedCollider = current;
						selectedBasicCollider = nullptr;
					}

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
		if (selectedBasicEmitter) {
			EmitterType type = selectedBasicEmitter->drawBasicSettings();
			if (type != EmitterType::Basic) {
				for (auto& e : *emitters) {
					if (e.get() == selectedBasicEmitter) {
						std::string oldName = e->getName();
						e = createEmitter(type);
						e->setName(oldName);
						selectedEmitter = e.get();
						selectedBasicEmitter = nullptr;
						break;
					}
				}
			}
		}
		if (selectedBasicCollider) {
			ColliderType type = selectedBasicCollider->drawBasicSettings();
			if (type != ColliderType::Basic) {
				for (auto& c : *colliders) {
					if (c.get() == selectedBasicCollider) {
						std::string oldName = c->getName();
						c = createCollider(type);
						c->setName(oldName);
						selectedCollider = c.get();
						selectedBasicCollider = nullptr;
						break;
					}
				}
			}
		}
		ImGui::End();

		gui.end();
	}
};