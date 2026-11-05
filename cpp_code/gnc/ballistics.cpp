#include "ballistics.h"
#include <vector>

using namespace gnc;

BallisticsEngine::BallisticsEngine()
{

}

Vector3 BallisticsEngine::acceleration(const Vector3& pos, const Vector3& vel,const ProjectileState& p) const
{
    
    double speed = std::sqrt(vel.x*vel.x + vel.y*vel.y + vel.z*vel.z);  // magnitude is squared root of x,y,z components
    double b = 0.5 * airDensity(pos.z) * p.Cd * p.area;                 // constants from quadratic drag equation
    double c = b / p.mass;
    return { -c*speed*vel.x,                                            // x-acceleration
             -c*speed*vel.y,                                            // y-acceleration
             -GRAVITY - c*speed*vel.z };                                // z-acceleration
}

Trajectory BallisticsEngine::predictTrajectory(
    const ProjectileState& initialState,
    double simulationTime,
    double dt)
{
    Trajectory trajectory;

    ProjectileState state = initialState;

    for(double t = 0.0; t <= simulationTime; t += dt)
    {
        //RK4 (Runge-Kutta) approximation for position
        trajectory.states.push_back(state);

        Vector3 p = state.position, v = state.velocity;

        Vector3 k1p = v;
        Vector3 k1v = acceleration(p, v, state);

        Vector3 k2p = v + k1v*(dt/2);
        Vector3 k2v = acceleration(p + k1p*(dt/2), k2p, state);

        Vector3 k3p = v + k2v*(dt/2);
        Vector3 k3v = acceleration(p + k2p*(dt/2), k3p, state);

        Vector3 k4p = v + k3v*dt;
        Vector3 k4v = acceleration(p + k3p*dt, k4p, state);

        state.position = p + (k1p + k2p*2 + k3p*2 + k4p) * (dt/6);
        state.velocity = v + (k1v + k2v*2 + k3v*2 + k4v) * (dt/6);
        // stop if projectile hits the ground
        if(state.position.z < 0)
            break;
    }

    return trajectory;
}