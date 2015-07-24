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
  normal_distribution<double> gaussian(0.0, 0.1);             // Gaussian distribution

  vector<vector<double> > phi(N, vector<double>(N, 0.25));

  // Make initial conditions:
  for (int i = N/4; i<3*N/4; i++)
    for (int j = N/4; j<3*N/4; j++)
      phi[i][j] = 0.25;

  // Simulate!
  omp_set_num_threads(6);
  for (int tim = 0; tim<60000; tim++)
  {
    integrate(phi);
    if (tim%100 == 0)
    {
      cout<<100.0*static_cast<double>(tim)/60000.0<<" Percent finished"<<endl;
      printer(phi, tim);
    }
  }

  return 0;
}
