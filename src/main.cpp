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
  normal_distribution<double> gaussian(0.0, 0.0000005);       // Gaussian distribution
  normal_distribution<double> theta_dist(0.0, 0.002);

  vector<vector<double> > phi(N, vector<double>(N, 0.9));
  vector<vector<double> > theta(N, vector<double>(N, 0.0));

  // Make initial conditions:
  for (int i = 0; i<N; i++)
  {
    for (int j = 0; j<N; j++)
    {
      theta[i][j] = theta_dist(twist);
      phi[i][j] *= exp(-(j-150.0)*(j-150.0)/200.0);
      phi[i][j] += 0.5 + gaussian(twist);
    }
  }

  // Simulate!
  omp_set_num_threads(4);

  int steps = 200;
  for (int tim = 0; tim<steps; tim++)
  {
    if (tim%10 == 0)
    {
      cout<<100.0*static_cast<double>(tim)/static_cast<double>(steps)
          <<" Percent finished"<<endl;
      printer(phi, tim);
    }
    integrate(phi, theta);
  }

  return 0;
}
