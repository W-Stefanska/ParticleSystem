#pragma once

class Particle {
public:
    ofVec3f     position;
	ofVec3f     previousPosition;
    ofVec3f     velocity;
    ofColor     color;
    float       size        = 1.f;
    float       lifetime    = 1.f;
    bool        isAlive     = false;
    std::function<void(Particle&, float)> behaviour;

    void update(double dt) {
        if (!isAlive) return;
		previousPosition = position;

        lifetime -= dt;
        position += velocity * dt;
        if (behaviour) behaviour(*this, dt);
        if (lifetime <= 0.f) isAlive = false;
    }

    void draw() {
        if (!isAlive) return;
        ofMaterial mat;
        mat.setDiffuseColor(color);
        mat.setSpecularColor(ofColor(255, 255, 255));
        mat.setShininess(120);
        mat.begin();
        ofDrawSphere(position, size);
        mat.end();
    }
};

