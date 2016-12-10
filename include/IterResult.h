#ifndef _ITERRESULT_H_
#define _ITERRESULT_H_


#include "Point.h"

// TODO: aligning?
struct IterResult {
	bool has_converged;
	Point arg;
	double val;
	unsigned int n_iter;
};

#endif	// _ITERRESULT_H_
