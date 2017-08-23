#include<iostream>
#include <vector>

#include "./include/natgrid.h"

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
	natgrid::c_nnseti("igr", 1);

	/*
	*  Do the regridding.
	*/

	int ier;
	double *out = natgrid::c_natgridd(NUMIN, x, y, z, NUMXOUT, NUMYOUT, xo, yo, &ier);
	if (ier != 0) {
		printf(" Error return from c_natgrids = %d\n", ier);
	}


	for (auto i = 0; i < NUMXOUT; i++)
	{
		std::cout << i << ": ";
		for (auto j = 0; j < NUMYOUT; j++)
		{
			std::cout<<out[i*NUMYOUT + j] << ' ' ;
		}
		std::cout << std::endl;
	}

	std::vector<double> ix = { 0.00, 1.00, 0.00, 1.00, 0.40, 0.75 },
		iy = { 0.00, 0.00, 1.00, 1.00, 0.20, 0.65 },
		iv = { 0.00, 0.00, 0.00, 0.00, 1.25, 0.80 };
	
	natgrid::natgrid ng(ix, iy, iv);

	std::cout << std::endl;
	std::cout << ng.xq(0, 1, NUMXOUT).yq(0,1, NUMYOUT).griddata();
	std::cout << std::endl;

	std::cout << ng.xq(0, 0.1, 1.0).yq(0, 0.15, 1.0).griddata();



	return 0;
}