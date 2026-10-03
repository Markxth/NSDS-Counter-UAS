from enum import Enum
import math
import numpy as np
# NOTE: these need to be moved to central utils files/folder

C_SPEED_OF_LIGHT = 299_792_458

class ProjectileProperties:
    """
    A class describing the properties of a projectile
    """

    def __init__(self, launch_velocity: float, mass: float, drag_factor: float):
        """Initialize class members.

        Keyword Args:
            launch_velocity -- the launch (muzzle) velocity of the projectile in m/s (C_SPEED_OF_LIGHT when EliminationMode is EM)
            mass -- the mass of the projectile in kg (ignored when EliminationMode is EM)
            drag_factor -- the drag factor of the projectile (ignored when EliminationMode is EM)
        """

        self.launch_velocity = launch_velocity
        self.mass = mass
        self.drag_factor = drag_factor

class EMProjectileProperties(ProjectileProperties):
    """
    A child class of ProjectileProperties for electromagnetic elimination methods.
    """

    def __init__(self):
        """Initializes a projectile properties object with the speed of light and no mass or drag.
        """

        super().__init__(C_SPEED_OF_LIGHT, 0, 0)

class EliminationMode(Enum):
    """
    An enumeration describing different types of elimination method.
    """
    BALLISTIC = 0
    EM = 1

class EliminationMethod:
    """
    A class describing a method for eliminating.
    """

    def __init__(self, elimination_mode: EliminationMode, projectile_properties: ProjectileProperties):
        """Initialize class members.

        Keyword Args:
            elimination_mode -- the elimination mode currently in use
            projectile_properties -- the properties of the elimination system's projectile
        """

        self.elimination_mode: EliminationMode = elimination_mode
        self.projectile_propeprties: ProjectileProperties = projectile_properties

###################################################

class Guidance:
    """
    A guidance engine used for calculating the necessary lead angles for a target package from an elimination method and current sentry state. Also
    generates guidance commands for the control engine from the lead angle and current state.
    """

    def __init__(self, n=3.0):
        """Initialize class members.
        """
        self.N = N

        pass
    #Proportional Navigation
    def compute_acceleration(self,elim_pos,elim_vel,target_pos, target_vel):
        """
        target_pos = np.array(fusion_output.position)
        target_vel = np.array(fusion_output.velocity
        elim_pos = np.array(nav_output.position)
        elim_vel = np.array(nav_output.velocity)
        """  
        R = target_pos - elim_pos
        r = np.linalg.norm(R)
        los = R / r

        Vrel = target_vel - elim_vel
        Vc = -np.dot(los, Vrel)

        omega = np.cross(R, Vrel) / (r**2)

        a_cmd = self.N * Vc * np.cross(omega, los)
        return a_cmd)
    

    ###################################################

    # accessors

    ###################################################

    def calc_lead_angle(elimination_method: EliminationMethod) -> float: #, target_package: TargetPackage) -> float:
        """Calculate the lead angle from a target's position and elimination method parameters.
        Returns the lead angle (λ).
        projectile_speed
        """


        """
        Keyword Args:
            elimination_method -- the elimination method that calculations should use
            NOTE: target_package will desscribe the target volume that should be aimed at, and may contain information like the bounding volume
            of the target, the RAE coordinates of the target, and the target speed
        """

    
        pass

