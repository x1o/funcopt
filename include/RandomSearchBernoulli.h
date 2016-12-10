#ifndef RANDOMSEARCHBERNOULLI_H_
#define RANDOMSEARCHBERNOULLI_H_

#include "OptMethods.h"

struct RandomSearchBernoulliParams : MethodParams {
	double global_search_prob;
	double contract_factor;
};

#endif	// RANDOMSEARCHBERNOULLI_H_
