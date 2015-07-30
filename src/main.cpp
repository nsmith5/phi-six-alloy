#include <iostream>
#include <random>
#include <vector>
#include <omp.h>

#include "methods.h"
#include "constants.h"

using namespace std;

int main(int argc, char ** argv)
{
  mt19937_64 twist;                                           // Mersenne twister random number generator
  normal_distribution<double> gaussian(0.0, 0.25);            // Gaussian distribution

  vector<vector<double> > phi_n(N, vector<double>(N, 0.0));   // Scalar order parameter
  vector<vector<double> > phi_x(N, vector<double>(N, 0.0));   // X part of vector order parameter
  vector<vector<double> > phi_y(N, vector<double>(N, 0.0));   // Y part of vector order parameter

  // Make initial conditions:
  for (int i = 125; i<175; i++)
  {
    for (int j = 0; j<N; j++)
    {
      phi_x[i][j] = 1.56 + gaussian(twist);
      phi_y[i][j] = gaussian(twist);
    }
  }

  // Simulate!
  int steps = 2000;
  omp_set_num_threads(4);
  for (int tim = 0; tim<steps; tim++)
  {
    if (tim%10 == 0)
    {
      cout<<100.0*static_cast<double>(tim)/static_cast<double>(steps)<<" Percent finished"<<endl;
      printer(phi_x, phi_y, phi_n, tim);
    }
    integrate(phi_x, phi_y, phi_n);
  }

  return 0;
}
