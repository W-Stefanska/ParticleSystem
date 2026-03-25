#pragma once

#include "particle.h"

enum class EmitterType {
	Snow,
	Fire,
	Rain,
	Fountain,
	Firework,
	Spiral,
	Basic
};

class Emitter {
protected:
	std::vector<Particle> particles;
	ofVec3f position;
	float	emissionRate = 10.f;
	float	timeSinceLastEmission = 0.f;

	// impl
	virtual ofVec3f	genVelocity	() = 0;
	virtual ofVec3f genPosition	() = 0;
	virtual ofColor	genColor	() = 0;
	virtual float	genSize		() = 0;
	virtual float	genlifetime	() = 0;

	void spawn(Particle& p) {
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

	// set
	void	setPosition(ofVec3f pos)	{ position = pos; }
	void	setEmissionRate(float rate) { emissionRate = rate; }

	// impl
	virtual void drawSettings() = 0;
	
	// main
	void draw()		{ for (auto& p : particles) p.draw(); }
	void update()	{
		float dt = static_cast<float>(ofGetLastFrameTime());
		timeSinceLastEmission += dt;

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
class RainEmitter		: public Emitter {
public:
	ofVec3f genVelocity() override { return {}; }
	ofVec3f genPosition() override { return position; }
	ofColor genColor()    override { return {}; }
	float   genSize()     override { return 10.f; }
	float   genlifetime() override { return 1.f; }
	void    drawSettings() override {}
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
	ofVec3f genVelocity() override { return {}; }
	ofVec3f genPosition() override { return position; }
	ofColor genColor()    override { return {}; }
	float   genSize()     override { return 10.f; }
	float   genlifetime() override { return 1.f; }
	void    drawSettings() override {}
};
   
//std::unique_ptr<Emitter> createEmitter(EmitterType type) {
//	switch (type) {
//	case EmitterType::Snow:     return std::make_unique<SnowEmitter>();
//	case EmitterType::Fire:     return std::make_unique<FireEmitter>();
//	case EmitterType::Rain:     return std::make_unique<RainEmitter>();
//	case EmitterType::Fountain: return std::make_unique<FountainEmitter>();
//	case EmitterType::Firework: return std::make_unique<FireworkEmitter>();
//	case EmitterType::Spiral:   return std::make_unique<SpiralEmitter>();
//	case EmitterType::Basic:    return std::make_unique<BasicEmitter>();
//	default:                    return std::make_unique<BasicEmitter>();
//	}
//}
//    void update(float dt) {

//        while (timeSinceLastEmission >= 1.0f / emissionRate) {
//            bool emitted = false;
//            for (auto& p : particles) {
//                if (!p.isAlive) {
//                    p.reset(gen.generatePosition(position), gen.generateColor());
//                    p.velocity = gen.generateVelocity();
//                    p.size = gen.generateSize();
//                    p.lifetime = gen.generatelifetime();
//                    p.col = gen.generateColor();
//                    emitted = true;
//                    break;
//                }
//            }
//            if (!emitted) break;
//            timeSinceLastEmission -= 1.0f / emissionRate;
//        }

//    }