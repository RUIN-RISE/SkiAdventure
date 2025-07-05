#include "PhysicsEntity.h"
#include "Vector.h"

PhysicsEntity::PhysicsEntity(
    Vector _position, 
    Vector _velocity, 
    Vector _acceleration, 
    Angle _angle,
    bool _onCurve
): position(_position), velocity(_velocity), acceleration(_acceleration), angle(_angle), onCurve(_onCurve){}

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

void PhysicsEntity::setAngle(Angle ang) {
    angle = ang;
}

void PhysicsEntity::setOnCurve(bool onCurve) {
    this->onCurve = onCurve;
}

const Vector& PhysicsEntity::getPosition() const {
    return position;
}

const Vector& PhysicsEntity::getVelocity() const {
    return velocity;
}

const Vector& PhysicsEntity::getAcceleration() const {
    return acceleration;
}

const Angle& PhysicsEntity::getAngle() const {
    return angle;
}

bool PhysicsEntity::isOnCurve() const {
    return onCurve;
}

void PhysicsEntity::update(double deltaTime) {
    position += velocity * deltaTime;
    velocity += acceleration * deltaTime;
}
