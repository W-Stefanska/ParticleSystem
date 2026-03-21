#pragma once

class Collider {
protected:
    float bounceFactor  = 1.f;
    ofVec3f position    = ofVec3f();
    ofColor color       = ofColor();
public:
    virtual void resolve(Particle& p)   = 0;
    virtual void draw() const           = 0;

    void changeBounceFactor(float f)    { bounceFactor = f; }
    void changePosition(ofVec3f pos)    { position = pos; }
    void changeColor(ofColor c)         { color = c; }

    float getBounceFactor() const       { return bounceFactor; }
    ofVec3f getPosition() const         { return position; }
    ofColor getColor() const            { return color; }

    virtual ~Collider() = default;
};

class SphereCollider : public Collider {
public:
    float size = 100.f;

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
};