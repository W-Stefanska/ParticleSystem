#pragma once

#include "particle.h"

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

	virtual void draw() { for (auto& p : particles) p.draw(); }
	Particle& access(int i) { return particles[i]; }
	void update() {
		float dt = static_cast<float>(ofGetLastFrameTime());
		timeSinceLastEmission += dt;

		for (auto& p : particles) p.update(dt);
	}

	Emitter(int particlesSize = 100) {
		particles.resize(particlesSize);
	}

	virtual ~Emitter() = default;
};

class SnowEmitter : public Emitter {};
class FireEmitter : public Emitter {};
class RainEmitter : public Emitter {};
class PathEmitter : public Emitter {};

   
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