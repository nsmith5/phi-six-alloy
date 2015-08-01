#include <iostream>
#include <random>
#include <vector>

#include "methods.h"
#include "constants.h"

using namespace std;

int main(int argc, char ** argv)
{
  mt19937_64 twist;                                           // Mersenne twister random number generator
  normal_distribution<double> gaussian(0.9, 0.01);             // Gaussian distribution

  vector<vector<double> > phi(N, vector<double>(N, 0.9));

  // Make initial conditions:
  for (int i = 125; i<175; i++)
    for (int j = 125; j<175; j++)
      phi[i][j] =  0.5;

  // Simulate!

  int steps = 200000;
  for (int tim = 0; tim<steps; tim++)
  {
    r = 1.0 - 15.0*tim/static_cast<double>(steps);
    if (tim%1000 == 0)
    {
      cout<<100.0*static_cast<double>(tim)/static_cast<double>(steps)
          <<" Percent finished"
          <<". r ="<<r<<endl;
      printer(phi, tim);
    }
    integrate(phi);
  }

  return 0;
}
