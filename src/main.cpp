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
  normal_distribution<double> gaussian(0.0, 0.05);       // Gaussian distribution
  uniform_real_distribution<double> theta_dist(0.0, 2.0*3.14159);

  vector<vector<double> > phi(N, vector<double>(N, 0.7));
  vector<vector<double> > theta(N, vector<double>(N, 0.0));

  // Make initial conditions:
  for (int i = 0; i<N; i++)
  {
    for (int j = 0; j<N; j++)
    {
      theta[i][j] = theta_dist(twist);
      //phi[i][j] += 0.4*exp(-(j-150.0)*(j-150.0)/200.0) + gaussian(twist);
      phi[i][j] += gaussian(twist);
    }
  }

  // Simulate!
  omp_set_num_threads(6);

  int steps = 200000;
  for (int tim = 0; tim<steps; tim++)
  {
    if (tim%1000 == 0)
    {
      cout<<100.0*static_cast<double>(tim)/static_cast<double>(steps)
          <<" Percent finished"<<endl;
      printer(phi, tim);
      printer(theta, tim+steps);
    }
    integrate(phi, theta);
  }

  return 0;
}
