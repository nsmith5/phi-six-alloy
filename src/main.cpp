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

  vector<vector<double> > phi(N, vector<double>(N, 1.71));

  // Make initial conditions:
  for (int i = 0; i<N; i++)
    for (int j = 0; j<N; j++)
      phi[i][j] -= 0.81*exp(-(i-150)*(i-150)/100.0)*exp(-(j-150)*(j-150)/100.0);

  // Simulate!
  omp_set_num_threads(4);
  for (int tim = 0; tim<800000; tim++)
  {
    if (tim%1000 == 0)
    {
      cout<<100.0*static_cast<double>(tim)/800000.0<<" Percent finished"<<endl;
      printer(phi, tim);
    }
    integrate(phi);
  }

  return 0;
}
