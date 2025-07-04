#ifndef __PHYSICS_ENTITY_H__
#define __PHYSICS_ENTITY_H__

#include "Vector.h"
#include "Angle.h"

class PhysicsEntity {
public:
    // Accelaration is set with a default value of (0, -10) to simulate gravity
    PhysicsEntity(
        Vector _position = Vector(0,0),
        Vector _velocity = Vector(0,0),
        Vector _acceleration = Vector(0,-10),
        Angle _angle = Angle(0),
        bool _onCurve = false
    );
    
    //Add acceleration to the current acceleration
    void applyAcceleration(Vector acc);

    void setAcceleration(Vector acc);

    void setVelocity(Vector vel);
    
    void setPosition(Vector pos);

    void setAngle(Angle ang);
    
    void setOnCurve(bool onCurve);

    const Vector & PhysicsEntity::getPosition() const;
    
    const Vector & getVelocity() const;

    const Vector & getAcceleration() const;

    const Angle & getAngle() const;

    bool isOnCurve() const;
    
    // Update position/velocity based on velocity/acceleration
    void update(double deltaTime);

private:
    Vector position;
    Vector velocity;
    Vector acceleration;
    Angle angle;
    
    // Point is on(at) the curve if onCurve is true
    bool onCurve;
};

#endif
