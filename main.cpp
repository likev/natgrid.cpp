#include<iostream>

double *c_natgridd(int, double[], double[], double[],
	int, int, double[], double[], int *);
void c_nnseti(char *, int);


int main()
{
	const unsigned NUMIN = 6, NUMXOUT = 21, NUMYOUT = 21;
	

	double x[] = { 0.00, 1.00, 0.00, 1.00, 0.40, 0.75 },
		y[] = { 0.00, 0.00, 1.00, 1.00, 0.20, 0.65 },
		z[] = { 0.00, 0.00, 0.00, 0.00, 1.25, 0.80 };


	double xc = 1. / (NUMXOUT - 1.), xo[NUMXOUT];
	for (auto i = 0; i < NUMXOUT; i++) {
		xo[i] = i * xc;
	}

	double yc = 1. / (NUMYOUT - 1.), yo[NUMYOUT];
	for (auto j = 0; j < NUMYOUT; j++) {
		yo[j] = j * yc;
	}

	/*
	*  Set the flag to indicate use of gradient estimates.
	*/
	c_nnseti("igr", 1);

	/*
	*  Do the regridding.
	*/

	int ier;
	double *out = c_natgridd(NUMIN, x, y, z, NUMXOUT, NUMYOUT, xo, yo, &ier);
	if (ier != 0) {
		printf(" Error return from c_natgrids = %d\n", ier);
	}


	for (auto i = 0; i < NUMXOUT; i++)
	{
		std::cout << i << ': ';
		for (auto j = 0; j < NUMYOUT; j++)
		{
			std::cout<<out[i*NUMYOUT + j] << ' ' ;
		}
		std::cout << std::endl;
	}

	return 0;
}