//  Header file for the methods source file
//
//  Includes the function definitions for file i/o, taking derivatives
// and time integration

inline int ring(int i, int length)
{
	if (i<length && i>=0)
		return i;
	else if (i>-length && i<0)
		return i+length;
	else if (i > length && i < 2*length)
		return i-length;
	else if(i<-length)
		return (i+(300*length))%length;
	else return i%length;
}

void printer(double* field, int time);

void laplacian(double* output, double* field, double* laplacian);

// void integrate(std::vector<std::vector<double> >& field);

void make_laplace(double* laplace);
