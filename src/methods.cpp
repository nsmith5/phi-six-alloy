#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <omp.h>

#include "constants.h"
#include "methods.h"

using namespace std;

void printer(vector<vector<double> > field, int time)
{
  char timestr[21];
  sprintf(timestr, "./data/output%d.dat", time);
  ofstream file;

  file.open(timestr);

  for (int row = 0; row<N; row++)
  {
    for (int col = 0; col<N; col++)
    {
      file<<field[row][col]<<" ";
    }
    file<<endl;
  }

  file.close();

  return;
}

vector<vector<double> > laplacian(const vector<vector<double> > field)
{
  vector<vector<double> > output(N, vector<double>(N));

  #pragma omp parallel for
  for (int row = 0; row<N; row++)
  {
    for (int col = 0; col<N; col++)
    {
      output[row][col] = field[ring(row + 1, N)][col] + field[row][ring(col + 1, N)]
                       + field[ring(row - 1, N)][col] + field[row][ring(col - 1, N)]
                       - 4.0*field[row][col];
      output[row][col] *= 1.0/(dx*dx);
    }
  }

  return output;
}

void integrate(vector<vector<double> >& phi, vector<vector<double> >& theta)
{
  vector<vector<double> > laplace(N, vector<double>(N));
  vector<vector<double> > partial_t(N, vector<double>(N));

  // Integrate Phi first..

  partial_t = laplacian(phi);
  laplace = laplacian(theta);

  #pragma omp parallel for
  for (int row = 0; row<N; row++)
  {
    for (int col = 0; col<N; col++)
    {
      // Derivative term
      partial_t[row][col] *= -W;
      // Polynomial terms
      partial_t[row][col] += c0 + phi[row][col]
                           *(c1 + phi[row][col]
                           *(c2 + phi[row][col]
                           *(c3 + phi[row][col]
                           *(c4 + phi[row][col]*(c5)))));
      // Coupling term
      //partial_t[row][col] += c*(phi[row][col]-0.5)*laplace[row][col];
      // Multiply time scale
      partial_t[row][col] *= Gamma*dt;
    }
  }

  laplace = laplacian(partial_t);

  // Integrate Theta next

  #pragma omp parallel for
  for (int row = 0; row<N; row++)
  {
    for(int col = 0; col<N; col++)
    {
      //laplace[row][col] *= -D*c*(phi[row][col]-0.5)*(phi[row][col]-0.5)*dt;
      phi[row][col] += laplace[row][col];
      //theta[row][col] += laplace[row][col];
    }
  }

  return;
}
