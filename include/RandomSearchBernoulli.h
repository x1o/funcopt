#ifndef RANDOMSEARCHBERNOULLI_H_
#define RANDOMSEARCHBERNOULLI_H_

#include "OptMethods.h"
#include "Point.h"

struct RandomSearchBernoulliParams : MethodParams {
    Point x_0;
    double global_search_prob;
    double contract_factor;
};

#endif	// RANDOMSEARCHBERNOULLI_H_
