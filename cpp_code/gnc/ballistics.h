#ifndef BALLISTICS_H
#define BALLISTICS_H
#include <vector>

namespace gnc
{

struct Vector3
{
    double x;
    double y;
    double z;
};

struct ProjectileState
{
    Vector3 position;  // m
    Vector3 velocity;  // m/s
    
    double mass;       //kg 
    double Cd;         // drag coefficient
    double Area;       // cross-sectional area

    
};

struct Trajectory
{
    std::vector<ProjectileState> states;
};

class BallisticsEngine
{
public:
    BallisticsEngine();

    // Integrates the projectile forward with RK4 until simulationTime
    Trajectory predictTrajectory(
        const ProjectileState& initialState,
        double simulationTime,
        double dt);

private:
    const double GRAVITY = 9.81;

    // Air density in kg/m^3 at `altitude` meters. Constant for now.
    double airDensity(double altitude) const { return 1.225; } 

    // Acceleration from gravity and quadratic drag. Takes position and velocity separately
    Vector3 acceleration(const Vector3& pos, const Vector3& vel, const ProjectileState& p) const;
};

}

#endif