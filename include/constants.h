//  Constants for Simulation

#include <cmath>

// Thermodynamic parameters

const double Gamma = 1.0;    //# Mobility
const double W = 1.00;       //# Curvature penalty
const double r = -1.50;      //# Quadratic Landau constant
const double u = 0.0;        //# Quartic Landau constant
const double v = 0.5;        //# Sixth order Landau constant

// Theta constants

const double c = 2.0;       // Coupling constant
const double D = 1.0;       // Diffusion constant

// Physical parameters

const double dx = 0.1;        //# Lattice spacing
const double dt = 0.00000125;       //# Time step size
const int N = 300;         //# Number of lattice points (N x N)

// Legendre constants (the coefficients of the derivative of r*P2(x)+u*P4(x)+v*P6(x), (normalized))

const double c5 = 426.0*pow(13.0, 1.5)*v;
const double c4 = -1065.0*pow(13.0, 1.5)*v;
const double c3 = (10650.0*pow(13.0, 1.5)*v)/11.0 + (840.0*u);
const double c2 = -(4260.0*pow(13.0, 1.5)*v)/11.0 -(1260.0*u);
const double c1 = (710.0*pow(13.0, 1.5)*v)/11.0 + (540.0*u) + (12.0*sqrt(5.0)*r);
const double c0 = -(71.0*pow(13.0, 1.5)*v)/22.0 - (60.0*u) - (6.0*sqrt(5.0)*r);
