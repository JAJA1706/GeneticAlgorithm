#include <cmath>

#include "ackley.hpp"

double ackley_func(std::vector<double>& x, int dim)
{
	const double PI = 3.1415926535897932384626433832795029, E = 2.7182818284590452353602874713526625;
	int i;
	double sum1, sum2, result;
	sum1 = 0.0;
	sum2 = 0.0;

	for (i = 0; i < dim; i++)
	{
		sum1 += x[i] * x[i];
		sum2 += cos(2.0 * PI * x[i]);
	}
	sum1 = -0.2 * sqrt(sum1 / dim);
	sum2 /= dim;
	result = E - 20.0 * exp(sum1) - exp(sum2) + 20.0;
	return result;
}
