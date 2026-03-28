#pragma once

#include "particle.h"
#include "imgui.h"
#include "ofApp.h"
#include "imgui_stdlib.h"

enum class ColliderType {
    Sphere,
    Plane,
    Basic
};

const std::vector<std::string> colliderTypeNames = {
    "Sphere",
    "Plane",
	"Basic"
};

class Collider {
protected:
    float bounceFactor  = 1.f;
    ofVec3f    position = ofVec3f();
    ofColor    color    = ofColor();
	string     name     = "";
	bool 	   isBasic  = false;
public:
    virtual void resolve(Particle& p)   = 0;
    virtual void draw() const           = 0;

	virtual void drawSettings()         = 0; 
	virtual ColliderType drawBasicSettings() { return ColliderType::Basic; }

    void setBounceFactor(float f)    { bounceFactor = f; }
    void setPosition(ofVec3f pos)    { position = pos; }
    void setColor(ofColor c)         { color = c; }
	void setName(string n)           { name = n; }

    float getBounceFactor() const       { return bounceFactor; }
    ofVec3f getPosition() const         { return position; }
    ofColor getColor() const            { return color; }
	string getName() const              { return name; }
	bool isBasicCollider() const        { return isBasic; }

    virtual ~Collider() = default;
};

class BasicCollider : public Collider {
public:
    BasicCollider() {
        isBasic = true;
	}
    void resolve(Particle& p) override {
    }
    void draw() const override {
        ofMaterial mat;
        mat.setDiffuseColor(color);
        mat.setSpecularColor(ofColor(255, 255, 255));
        mat.setShininess(120);
        mat.begin();
        ofDrawSphere(position, 10.f);
        mat.end();
	}
    void drawSettings() override {}
    ColliderType drawBasicSettings() {
        ColliderType type = ColliderType::Basic;

        if (ImGui::CollapsingHeader("Collider Type")) {
            if (ImGui::Selectable("Sphere")) {
                type = ColliderType::Sphere;
            }
            if (ImGui::Selectable("Plane")) {
                type = ColliderType::Plane;
            }
        }

        return type;
    }
};

class SphereCollider : public Collider {
private:
    float size = 100.f;
public:
    void resolve(Particle& p) override {
        ofVec3f r = p.position - position;

        float distance = r.length();

        if (distance < (size + p.size)) {
            ofVec3f normal = r.normalize();

            p.velocity = (p.velocity - 2.0f * normal.dot(p.velocity) * normal) * bounceFactor;

            float overlap = (size + p.size) - distance;
            p.position += normal * overlap;
        }
    }

    void draw() const override {
        ofMaterial mat;
        mat.setDiffuseColor(color);
        mat.setSpecularColor(ofColor(255, 255, 255));
        mat.setShininess(120);
        mat.setEmissiveColor(ofColor(color.r * 0.3, color.g * 0.3, color.b * 0.3));
        mat.begin();
        ofDrawSphere(position, size);
        mat.end();
    }

    void drawSettings() override {
        float speed = ImGui::GetIO().KeyShift ? 0.1f : 1.f;
        float col[3] = {
            color.r / 255.f,
            color.g / 255.f,
            color.b / 255.f
        };

        ImGui::InputText("Name", &name);
        
        ImGui::DragFloat("X", &position.x, speed, -FLT_MAX, FLT_MAX);
        ImGui::DragFloat("Y", &position.y, speed, -FLT_MAX, FLT_MAX);
        ImGui::DragFloat("Z", &position.z, speed, -FLT_MAX, FLT_MAX);

		ImGui::SliderFloat("Size", &size, 10.f, 500.f);
        if (ImGui::ColorEdit3("Color", col)) {
            color.r = col[0] * 255;
            color.g = col[1] * 255;
            color.b = col[2] * 255;
        }

		ImGui::SliderFloat("Bounce Factor", &bounceFactor, 0.f, 2.f);

        if (ImGui::Button("Reset Position")) {
            position.set(0, 0, 0);
        }
    }
};

class PlaneCollider : public Collider {
private:
    float width  = 100.f;
    float length = 100.f;
    ofVec3f rotation = ofVec3f(0, 0, 0);
    ofVec3f normal = ofVec3f(0, 1, 0);

    void updateNormal() {
        ofQuaternion q;
        q.makeRotate(
            rotation.x, ofVec3f(1, 0, 0),
            rotation.y, ofVec3f(0, 1, 0),
            rotation.z, ofVec3f(0, 0, 1)
        );
        normal = q * ofVec3f(0, 1, 0);
        normal.normalize();
    }
public: 
    void resolve(Particle& p) override {
        float sideNow = normal.dot(p.position - position);
        float sidePrev = normal.dot(p.previousPosition - position);
        
        if (sidePrev > 0 && sideNow < 0 || sidePrev < 0 && sideNow > 0) {
            p.position -= normal * sideNow;
            p.velocity = (p.velocity - 2.0f * normal.dot(p.velocity) * normal) * bounceFactor;
        }
    }

    void draw() const override {
        ofMaterial mat;
        mat.setDiffuseColor(color);
        mat.setShininess(120);
        mat.setEmissiveColor(ofColor(color.r * 0.5, color.g * 0.5, color.b * 0.5));
        mat.begin();
        ofPushMatrix();
        ofTranslate(position);
        ofRotateXDeg(90);
        ofRotateXDeg(rotation.x);
        ofRotateYDeg(rotation.y);
        ofRotateZDeg(rotation.z);
        ofDrawPlane(0, 0, 0, width, length);
        ofPopMatrix();
        mat.end();
    }

    void drawSettings() override {
        float speed = ImGui::GetIO().KeyShift ? 0.1f : 1.f;
        float col[3] = {
            color.r / 255.f,
            color.g / 255.f,
            color.b / 255.f
        };

		ImGui::InputText("Name", &name);

        ImGui::DragFloat("X", &position.x, speed, -FLT_MAX, FLT_MAX);
        ImGui::DragFloat("Y", &position.y, speed, -FLT_MAX, FLT_MAX);
        ImGui::DragFloat("Z", &position.z, speed, -FLT_MAX, FLT_MAX);

        if (ImGui::DragFloat3("Rotation", &rotation.x, speed, -180.f, 180.f)) {
            updateNormal();
        }

		ImGui::SliderFloat("Width", &width, 10.f, 500.f);
		ImGui::SliderFloat("Length", &length, 10.f, 500.f);

        if (ImGui::ColorEdit3("Color", col)) {
            color.r = col[0] * 255;
            color.g = col[1] * 255;
            color.b = col[2] * 255;
        }

        ImGui::SliderFloat("Bounce Factor", &bounceFactor, 0.f, 2.f);

	    if (ImGui::Button("Reset Rotation")) {
            rotation.set(0, 0, 0);
            updateNormal();
		}

        if (ImGui::Button("Reset Position")) {
            position.set(0, 0, 0);
		}
    }
};

std::unique_ptr<Collider> createCollider(ColliderType type) {
    switch (type) {
    case ColliderType::Sphere:  return std::make_unique<SphereCollider>();
    case ColliderType::Plane:   return std::make_unique<PlaneCollider>();
	case ColliderType::Basic:   return std::make_unique<BasicCollider>();
	default:                    return std::make_unique<BasicCollider>();
    }
}