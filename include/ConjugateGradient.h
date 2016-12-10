#ifndef CONJUGATEGRADIENT_H_
#define CONJUGATEGRADIENT_H_

#include "OptMethods.h"
#include "Point.h"

struct ConjugateGradientParams : MethodParams {
	// FIXME: const &
	Point x_0;
};

#endif	// CONJUGATEGRADIENT_H_
