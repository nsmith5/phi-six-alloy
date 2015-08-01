#include <iostream>
#include <openblas/cblas.h>
#include <cstdlib>
#include <cassert>
#include "methods.h"
#include "constants.h"

using namespace std;

int main(int argc, char ** argv)
{
   double* phi = (double*)malloc(N*N*sizeof(double));
   double* laplace = (double*)malloc(N*N*N*N*sizeof(double));
   double* output = (double*)malloc(N*N*sizeof(double));

   make_laplace(laplace);

  // Make initial conditions:
  for (int i = 0; i<N; i++)
    for (int j = 0; j<N; j++)
      *(phi+i*N+j) = sin(2.0*3.1415*i/N)*sin(2.0*3.1416*j/N);

  // Simulate!
  for (int i = 0; i<100; i++)
    laplacian(output, phi, laplace);

  //printer(output, 0);
  // int steps = 200;
  // for (int tim = 0; tim<steps; tim++)
  // {
  //   // if (tim%100 == 0)
  //   // {
  //   //   cout<<100.0*static_cast<double>(tim)/static_cast<double>(steps)
  //   //       <<" Percent finished"
  //   //       <<". r ="<<r<<endl;
  //   //   printer(phi, tim);
  //   // }
  //   integrate(phi);
  // }

  return 0;
}
