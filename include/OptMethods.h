#ifndef OPTMETHODS_H_
#define OPTMETHODS_H_

#include <vector>
#include <string>

enum class OptMethod { ConjugateGradient, RandomSearchBernoulli };
const std::vector<std::string> all_opt_methods = {"Conjugate Gradient", "Random Search" };	// same order

struct MethodParams {
	// virtual ~MethodParams();	// make it a virtual struct
};

#endif	// OPTMETHODS_H_
