#pragma once

#include "particle.h"
#include "imgui.h"
#include "imgui_stdlib.h"

enum class EmitterType {
	Snow,
	Fire,
	Rain,
	Fountain,
	Firework,
	Spiral,
	Basic
};

const std::vector<std::string> emitterTypeNames = {
	"Snow",
	"Fire",
	"Rain",
	"Fountain",
	"Firework",
	"Spiral",
	"Basic"
};

class Emitter {
protected:
	std::vector<Particle> particles;
	ofVec3f position;
	float	emissionRate = 10.f;
	float	timeSinceLastEmission = 0.f;
	string	name = "";
	bool	isBasic = false;

	// impl
	virtual ofVec3f	genVelocity	() = 0;
	virtual ofVec3f genPosition	() = 0;
	virtual ofColor	genColor	() = 0;
	virtual float	genSize		() = 0;
	virtual float	genlifetime	() = 0;

	virtual void spawn(Particle& p) {
		p.position	= genPosition();
		p.velocity	= genVelocity();
		p.color		= genColor();
		p.size		= genSize();
		p.lifetime	= genlifetime();
		p.isAlive	= true;
	}

public:
	// get
	ofVec3f getPosition() const		{ return position; }
	float	getEmissionRate() const { return emissionRate; }
	string	getName() const			{ return name; }
	bool	isBasicEmitter() const	{ return isBasic; }

	// set
	void	setPosition(ofVec3f pos)	{ position = pos; }
	void	setEmissionRate(float rate) { emissionRate = rate; }
	void	setName(string n)			{ name = n; }

	// impl
	virtual void drawSettings() = 0;
	virtual EmitterType drawBasicSettings() { return EmitterType::Basic; }
	
	// main
	void draw()		{ for (auto& p : particles) p.draw(); }
	void update()	{
		float dt = static_cast<float>(ofGetLastFrameTime());
		timeSinceLastEmission += dt;

		while (timeSinceLastEmission >= 1.0f / emissionRate) {
			for (auto& p : particles) {
				if (!p.isAlive) {
					spawn(p);
					break;
				}
			}
			timeSinceLastEmission -= 1.0f / emissionRate;
		}

		for (auto& p : particles) p.update(dt);
	}

	Emitter(int particlesSize = 100) {
		particles.resize(particlesSize);
	}

	virtual ~Emitter() = default;
};

class SnowEmitter		: public Emitter {
public:
	ofVec3f genVelocity() override { return {}; }
	ofVec3f genPosition() override { return position; }
	ofColor genColor()    override { return {}; }
	float   genSize()     override { return 10.f; }
	float   genlifetime() override { return 1.f; }
	void    drawSettings() override {}
};
class FireEmitter		: public Emitter {
public:
	ofVec3f genVelocity() override { return {}; }
	ofVec3f genPosition() override { return position; }
	ofColor genColor()    override { return {}; }
	float   genSize()     override { return 10.f; }
	float   genlifetime() override { return 1.f; }
	void    drawSettings() override {}
};
class RainEmitter : public Emitter {
	float wind = 200.f;
	float lifetime = 2.f;
	float size = 5.f;
	float velocity = -1000.f;
	float emissionRate = 100.f;
public:
	RainEmitter() : Emitter() {
		position.y = 500.f;
		particles.resize(500);
	}
	ofVec3f genVelocity() override { return ofVec3f(wind, velocity, 0); }
	ofVec3f genPosition() override { 
		return ofVec3f(
			ofRandom(position.x - 1000, position.x + 1000),
			position.y,
			ofRandom(position.z - 1000, position.z + 1000)
		);
	}
	ofColor genColor()  override { return ofColor(140, 140, 200); }
	float genSize()     override { return size; }
	float genlifetime() override { return lifetime; }

	void spawn(Particle& p) override {
		Emitter::spawn(p);
		p.dieOnHit = true;
		p.bounceMult = 0.f;
	}

	void drawSettings() override {
		ImGui::InputText("Name", &name);

		ImGui::DragFloat("X", &position.x, 1.f, -FLT_MAX, FLT_MAX);
		ImGui::DragFloat("Y", &position.y, 1.f, -FLT_MAX, FLT_MAX);
		ImGui::DragFloat("Z", &position.z, 1.f, -FLT_MAX, FLT_MAX);

		ImGui::DragFloat("Wind", &wind, 1.f, -FLT_MAX, FLT_MAX);

		ImGui::DragFloat("Emission Rate", &emissionRate, 1.f, 0.f, FLT_MAX);
		ImGui::DragFloat("Lifetime", &lifetime, 1.f, 0.f, FLT_MAX);
		ImGui::DragFloat("Size", &size, 0.1f, 0.1f, FLT_MAX);

		ImGui::DragFloat("Velocity", &velocity, 1.f, -FLT_MAX, FLT_MAX);
	}
};
class FountainEmitter	: public Emitter {
public:
	ofVec3f genVelocity() override { return {}; }
	ofVec3f genPosition() override { return position; }
	ofColor genColor()    override { return {}; }
	float   genSize()     override { return 10.f; }
	float   genlifetime() override { return 1.f; }
	void    drawSettings() override {}
};
class FireworkEmitter	: public Emitter {
public:
	ofVec3f genVelocity() override { return {}; }
	ofVec3f genPosition() override { return position; }
	ofColor genColor()    override { return {}; }
	float   genSize()     override { return 10.f; }
	float   genlifetime() override { return 1.f; }
	void    drawSettings() override {}
};
class SpiralEmitter		: public Emitter {
public:
	ofVec3f genVelocity() override { return {}; }
	ofVec3f genPosition() override { return position; }
	ofColor genColor()    override { return {}; }
	float   genSize()     override { return 10.f; }
	float   genlifetime() override { return 1.f; }
	void    drawSettings() override {}
};

class BasicEmitter : public Emitter {
public:
	BasicEmitter() : Emitter() {
		isBasic = true;
	}
	ofVec3f genVelocity() override { return {}; }
	ofVec3f genPosition() override { return position; }
	ofColor genColor()    override { return {}; }
	float   genSize()     override { return 10.f; }
	float   genlifetime() override { return 1.f; }
	void    drawSettings() override {}
	EmitterType	drawBasicSettings() override {
		EmitterType type = EmitterType::Basic;
		if (ImGui::CollapsingHeader("Emitter Type")) {
			if (ImGui::Selectable("Snow")) {
				type = EmitterType::Snow;
			}
			if (ImGui::Selectable("Fire")) {
				type = EmitterType::Fire;
			}
			if (ImGui::Selectable("Rain")) {
				type = EmitterType::Rain;
			}
			if (ImGui::Selectable("Fountain")) {
				type = EmitterType::Fountain;
			}
			if (ImGui::Selectable("Firework")) {
				type = EmitterType::Firework;
			}
			if (ImGui::Selectable("Spiral")) {
				type = EmitterType::Spiral;
			}
		}
		return type;
	}
};
   
std::unique_ptr<Emitter> createEmitter(EmitterType type) {
	switch (type) {
	case EmitterType::Snow:     return std::make_unique<SnowEmitter>();
	case EmitterType::Fire:     return std::make_unique<FireEmitter>();
	case EmitterType::Rain:     return std::make_unique<RainEmitter>();
	case EmitterType::Fountain: return std::make_unique<FountainEmitter>();
	case EmitterType::Firework: return std::make_unique<FireworkEmitter>();
	case EmitterType::Spiral:   return std::make_unique<SpiralEmitter>();
	case EmitterType::Basic:    return std::make_unique<BasicEmitter>();
	default:                    return std::make_unique<BasicEmitter>();
	}
}