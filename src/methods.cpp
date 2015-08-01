#include <vector>
#include <openblas/cblas.h>        // gsl cblas
#include <fstream>
#include <iostream>
#include <string>

#include "constants.h"
#include "methods.h"

using namespace std;

void printer(double* field, int time)
{
  char timestr[21];
  sprintf(timestr, "./data/output%d.dat", time);
  ofstream file;

  file.open(timestr);

  for (int row = 0; row<N; row++)
  {
    for (int col = 0; col<N; col++)
    {
      file<<*(field +N*row+col)<<" ";
    }
    file<<endl;
  }

  file.close();

  return;
}

void laplacian(double* output, double* field, double* laplacian)
{
  cblas_dgemv(CblasRowMajor, CblasNoTrans, N*N, N*N, 1.0, laplacian,
              N*N, field, 1, 0.0, output, 1);
  return;
}

// void integrate(vector<vector<double> >& field)
// {
//   vector<vector<double> > laplace(N, vector<double>(N));
//   vector<vector<double> > partial_t(N, vector<double>(N));
//
//   laplace = laplacian(field);
//
//   for (int row = 0; row<N; row++)
//   {
//     for (int col = 0; col<N; col++)
//     {
//       // Derivative term
//       partial_t[row][col] = -W*laplace[row][col];
//       // Polynomial terms
//       partial_t[row][col] += c0 + field[row][col]*(c1 + field[row][col]*(c2 + field[row][col]*(c3 + field[row][col]*(c4 + field[row][col]*(c5)))));
//       // Multiply time scale
//       partial_t[row][col] *= Gamma*dt;
//     }
//   }
//
//   laplace = laplacian(partial_t);
//
//   for (int row = 0; row<N; row++)
//   {
//     for (int col = 0; col<N; col++)
//       field[row][col] += laplace[row][col];
//   }
//
//   return;
// }

void make_laplace(double* laplace)
{
  // Set to zero first and make diagonal -4
  for (int row = 0; row<N*N; row++)
  {
    for (int col = 0; col<N*N; col++)
    {
      *(laplace + N*N*row + col) = 0.0;
    }
    *(laplace + N*N*row + row) = -4.0;
  }

  // Find the neighbours and make them one
  for (int row = 0; row<N*N; row++)
  {
    int i = row/N;
    int j = row-i*N;
    *(laplace + (N*N)*row + (ring(i+1,N)*N+j)) = 1.0;
    *(laplace + (N*N)*row + (ring(i-1,N)*N+j)) = 1.0;
    *(laplace + (N*N)*row + (i*N+ring(j+1,N))) = 1.0;
    *(laplace + (N*N)*row + (i*N+ring(j-1,N))) = 1.0;
  }

  for (int row = 0; row<N*N; row++)
  {
    for (int col = 0; col<N*N; col++)
    {
      *(laplace + (N*N)*row + col) *= 1.0/(dx*dx);
    }
  }

  return;
}
