//  Constants for Simulation

const double Gamma = 1.0;     //# Mobility
const double W = 1.0;         //# Curvature penalty
const double r = 4.0;         //# Quadratic Landau constant
const double u = -2.0;        //# Quartic Landau constant
const double v = 0.30;        //# Sixth order Landau constant

const double dx = 0.8;        //# Lattice spacing
const double dt = 0.001;       //# Time step size
const int N = 300;         //# Number of lattice points (N x N)


// A note on some parameters to try:
//
//   Eutectic point:
//     r = 1.0
//     u = -2.0
//     v = 1.0
//
//   Below Eutectic (liquid still very stable):
//     r = 1.0
//     u = -2.3
//     v = 1.0
//
//   Melting point of both solids (Solids become unstable):
//     r = 4.0
//     u = -2.0
//     v = 0.33
//
//   Below melting point of solids (solids are meta-stable to liquid):
//     r = 4.0
//     u = -2.0
//     v = 0.30
