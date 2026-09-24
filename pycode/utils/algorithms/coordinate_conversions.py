import math

from typing import Tuple

def rae_xyz(rae: Tuple[float, float, float]) -> Tuple[float, float, float]:
    r, a, e = rae

    x = r * math.cos(e) * math.cos(a)
    y = r * math.cos(e) * math.sin(a)
    z = r * math.sin(e)

    return (x, y, z)

def xyzv_raer(xyzv: Tuple[float, float, float, float, float, float]) -> Tuple[float, float, float]:
    x, y, z, vx, vy, vz = xyzv

    r = math.sqrt(x*x + y*y + z*z)
    a = math.atan2(y, x)
    e = math.atan2(z, math.sqrt(x*x + y*y))
    rdot = (x*vx + y*vy + z*vz) / r

    return (r, a, e, rdot)