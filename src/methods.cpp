#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <omp.h>

#include "constants.h"
#include "methods.h"

using namespace std;


void printer(vector<vector<double> > phi_x, vector<vector<double> > phi_y, int time)
{
  char timestr[21];
  sprintf(timestr, "./data/output%d.dat", time);
  ofstream file;

  file.open(timestr);

  for (int row = 0; row<N; row++)
  {
    for (int col = 0; col<N; col++)
    {
      file<<phi_x[row][col]*phi_x[row][col] + phi_y[row][col]*phi_y[row][col]<<" ";
    }
    file<<endl;
  }

  file.close();

  return;
}

vector<vector<double> > div(const vector<vector<double> > phi_x, const vector<vector<double> > phi_y)
{
  vector<vector<double> > output(N, vector<double>(N));

  #pragma omp parallel for
  for (int row = 0; row<N; row++)
  {
    for (int col = 0; col<N; col++)
    {
      output[row][col] = phi_x[row][ring(col+1, N)] - phi_x[row][ring(col - 1, N)];
      output[row][col] += phi_y[ring(row+1, N)][col] - phi_y[ring(row - 1, N)][col];
      output[row][col] /= 2*dx;
    }
  }

  return output;
}

vector<vector<double> > curl(const vector<vector<double> > phi_x, const vector<vector<double> > phi_y)
{
  vector<vector<double> > output(N, vector<double>(N));

  #pragma omp parallel for
  for (int row = 0; row<N; row++)
  {
    for (int col = 0; col<N; col++)
    {
      output[row][col] = phi_y[row][ring(col+1, N)] - phi_y[row][ring(col - 1, N)];
      output[row][xol] -= phi_x[ring(row+1, N)][col] - phi_x[ring(row - 1, N)][col];
      output[row][col] /= 2*dx;
    }
  }

  return output;
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
  vector<vector<double> > partial_x_t(N, vector<double>(N));
  vector<vector<double> > partial_y_t(N, vector<double>(N));
  vector<vector<double> > partial_t(N, vector<double>(N));

  // Integrate the x part of the field first:
  partial_x_t = laplacian(phi_x);

  #pragma omp parallel for
  for (int row = 0; row<N; row++)
  {
    for (int col = 0; col<N; col++)
    {
      // Derivative term
      partial_t[row][col] = -W*partial_x_t[row][col];
      // Polynomial terms
      partial_t[row][col] += r*phi_x[row][col];
      partial_t[row][col] += u*phi_x[row][col]*phi_x[row][col]*phi_x[row][col]
                           + u*phi_y[row][col]*phi_y[row][col]*phi_x[row][col];
      partial_t[row][col] += v*phi_x[row][col]*phi_x[row][col]*phi_x[row][col]*phi_x[row][col]*phi_x[row][col]
                           + 2.0*v*phi_y[row][col]*phi_y[row][col]*phi_x[row][col]*phi_x[row][col]*phi_x[row][col]
                           + v*phi_x[row][col]*phi_y[row][col]*phi_y[row][col]*phi_y[row][col]*phi_y[row][col];
      // Multiply time scale
      partial_t[row][col] *= Gamma*dt;
    }
  }

  partial_x_t = laplacian(partial_t);

  // Integrate in y next:
  partial_y_t = laplacian(phi_y);

  #pragma omp parallel for
  for (int row = 0; row<N; row++)
  {
    for (int col = 0; col<N; col++)
    {
      // Derivative term
      partial_t[row][col] = -W*partial_y_t[row][col];
      // Polynomial terms
      partial_t[row][col] += r*phi_y[row][col];
      partial_t[row][col] += u*phi_y[row][col]*phi_y[row][col]*phi_y[row][col]
                           + u*phi_x[row][col]*phi_x[row][col]*phi_y[row][col];
      partial_t[row][col] += v*phi_y[row][col]*phi_y[row][col]*phi_y[row][col]*phi_y[row][col]*phi_y[row][col]
                           + 2.0*v*phi_x[row][col]*phi_x[row][col]*phi_y[row][col]*phi_y[row][col]*phi_y[row][col]
                           + v*phi_y[row][col]*phi_x[row][col]*phi_x[row][col]*phi_x[row][col]*phi_x[row][col];
      // Multiply time scale
      partial_t[row][col] *= Gamma*dt;
    }
  }

  partial_y_t = laplacian(partial_t);

  #pragma omp parallel for
  for (int row = 0; row<N; row++)
  {
    for (int col = 0; col<N; col++)
    {
      phi_y[row][col] += partial_y_t[row][col];
      phi_x[row][col] += partial_x_t[row][col];
    }
  }

  return;
}
