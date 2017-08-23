#include<iostream>
#include <vector>
#include <ctime>

#include "./include/natgrid.h"

int main()
{
	const unsigned NUMIN = 6, NUMXOUT = 21, NUMYOUT = 21;

	std::vector<double> ix = { 0.00, 1.00, 0.00, 1.00, 0.40, 0.75 },
		iy = { 0.00, 0.00, 1.00, 1.00, 0.20, 0.65 },
		iv = { 0.00, 0.00, 0.00, 0.00, 1.25, 0.80 };

	natgrid::natgrid ng(ix, iy, iv);

	std::cout << std::endl;
	std::cout << ng.xq(0, 1, NUMXOUT).yq(0, 1, NUMYOUT).griddata();
	std::cout << std::endl;

	std::cout << ng.xq(0, 0.1, 1.0).yq(0, 0.15, 1.0).griddata();

	auto begin = clock();
	for (auto i = 0; i < 200000; i++)
	{
		ng.griddata();
	}
	std::cout << "time: " << (clock() - begin) / CLOCKS_PER_SEC << std::endl;

	while (true);
	return 0;
}