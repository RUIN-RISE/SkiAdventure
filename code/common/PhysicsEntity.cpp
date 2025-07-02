#include "PhysicsEntity.h"
#include "Vector.h"

PhysicsEntity::PhysicsEntity(
    Vector _position, 
    Vector _velocity, 
    Vector _acceleration, 
    bool _onCurve
): position(_position), velocity(_velocity), acceleration(_acceleration), onCurve(_onCurve){}

void PhysicsEntity::applyAcceleration(Vector acc) {
    acceleration += acc;
}

void PhysicsEntity::setAcceleration(Vector acc) {
    acceleration = acc;
}

void PhysicsEntity::setVelocity(Vector vel) {
    velocity = vel;
}

void PhysicsEntity::setPosition(Vector pos) {
    position = pos;
}

void PhysicsEntity::setOnCurve(bool onCurve) {
    this->onCurve = onCurve;
}

Vector PhysicsEntity::getPosition() const {
    return position;
}

Vector PhysicsEntity::getVelocity() const {
    return velocity;
}

Vector PhysicsEntity::getAcceleration() const {
    return acceleration;
}

bool PhysicsEntity::isOnCurve() const {
    return onCurve;
}

void PhysicsEntity::update(double deltaTime) {
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
}
