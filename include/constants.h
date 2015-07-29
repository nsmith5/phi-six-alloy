//  Constants for Simulation

#include <cmath>

// Thermodynamic parameters

const double Gamma = 1.0;     //# Mobility
const double W = 1.00;         //# Curvature penalty
const double r = 2.0;         //# Quadratic Landau constant
const double u = 0.0;        //# Quartic Landau constant
const double v = 0.67;        //# Sixth order Landau constant

// Physical parameters

const double dx = 0.1;        //# Lattice spacing
const double dt = 0.00000125;       //# Time step size
const int N = 300;         //# Number of lattice points (N x N)
