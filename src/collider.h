#pragma once

#include "particle.h"
#include "imgui.h"

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
    ofParameter<float> size = ofParameter<float>("Size", 100.f);
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
        mat.begin();
        ofDrawSphere(position, size);
        mat.end();
    }

    void drawSettings() override {

        std::cout << "drawSettings invoked" << std::endl;
        
    }
};

class PlaneCollider : public Collider {
private:
    float width  = 100.f;
    float length = 100.f;
	ofVec3f normal  = ofVec3f(0, 1, 0);
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
		mat.setSpecularColor(ofColor(255, 255, 255));
		mat.setShininess(120);
        mat.begin();
		ofDrawPlane(position, width, length);
		mat.end();
    }

    void drawSettings() override {
		ImGui::SliderFloat("Width", &width, 10.f, 500.f);
		ImGui::SliderFloat("Length", &length, 10.f, 500.f);
		std::cout << "drawSettings invoked" << std::endl;
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