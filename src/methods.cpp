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

void integrate(vector<vector<double> >& phi_x, vector<vector<double> >& phi_y)
{
  vector<vector<double> > laplace(N, vector<double>(N));
  vector<vector<double> > partial_t(N, vector<double>(N));

  // Integrate the x part of the field first:
  laplace = laplacian(phi_x);

  #pragma omp parallel for
  for (int row = 0; row<N; row++)
  {
    for (int col = 0; col<N; col++)
    {
      // Derivative term
      partial_t[row][col] = -W*laplace[row][col];
      // Polynomial terms
      partial_t[row][col] += r*phi_x[row][col];
      partial_t[row][col] += u*pow(phi_x[row][col], 3.0)
                           + u*pow(phi_y[row][col], 2.0)*phi_x[row][col];
      partial_t[row][col] += v*pow(phi_x[row][col], 5.0)
                           + 2.0*v*pow(phi_y[row][col], 2.0)*pow(phi_x[row][col], 3.0)
                           + v*phi_x[row][col]*pow(phi_y[row][col], 4.0);
      // Multiply time scale
      partial_t[row][col] *= Gamma*dt;
    }
  }

  laplace = laplacian(partial_t);

  #pragma omp parallel for
  for (int row = 0; row<N; row++)
  {
    for (int col = 0; col<N; col++)
      field[row][col] += laplace[row][col];
  }

  return;
}
