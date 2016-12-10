#include <iostream>
#include <sstream>

#include <cstdlib>	// srand()
#include <string>

#include "ConjugateGradient.h"
#include "DirectionFunction.h"
#include "Domain.h"
#include "Function.h"
#include "MaxIterCriterion.h"
#include "OptMethods.h"
#include "Point.h"
#include "scalar_fields.h"
#include "StopIterCriteria.h"
#include "ValDiffCriterion.h"

int main() {
	std::string input;

	srand(4);

	std::cout << "Select a scalar field to minimize: " << std::endl;
	for (size_t i = 0; i < all_scalar_fields.size(); i++ ) {
		std::cout << " " << i << ": " << *all_scalar_fields[i] << std::endl;
	}

	unsigned int f_idx;
	while((std::cout << "> ") && getline(std::cin, input)) {
		std::istringstream is {input};
		if((is >> f_idx) && !(is >> input) && (f_idx < all_scalar_fields.size())) {
			break;
		}
		std::cerr << "Invalid input, try again." << std::endl;
	}

	std::cout << "Select an optimization method: " << std::endl;
	for (size_t i = 0; i < all_opt_methods.size(); i++ ) {
		std::cout << " " << i << ": " << all_opt_methods[i] << std::endl;
	}
	unsigned int method_idx;
	while((std::cout << "> ") && getline(std::cin, input)) {
		std::istringstream is {input};
		if((is >> method_idx) && !(is >> input) && (method_idx < all_opt_methods.size())) {
			break;
		}
		std::cerr << "Invalid input, try again." << std::endl;
	}

	// FIXME: ask for StopIterCritera

	auto f = all_scalar_fields[f_idx];
	IterResult res;
	if (method_idx == 0) {
		std::cout << "The function is defined on " << f->GetDomain() << std::endl;
		unsigned int n_dim = f->GetDomain().size();
		Point x_0(n_dim);
		do {
			for (size_t i = 0; i < n_dim; i++) {
				while((std::cout << "x_0[" << i << "] > ") && getline(std::cin, input)) {
					std::istringstream is {input};
					if((is >> x_0[i]) && !(is >> input)) {
						break;
					}
					std::cerr << "Invalid input, try again." << std::endl;
				}
			}
		} while (!f->GetDomain().Contains(x_0) and std::cout << "x_0 does not belong to the function's domain" << std::endl);

		// f->grad_h_ = 0.0005;
		// FIXME: more params
		ConjugateGradientParams params;
		params.x_0 = x_0;
		StopIterCriteria oracle = {new MaxIterCriterion(100), new ValDiffCriterion(10e-2)};
		res = f->FindMin(OptMethod::ConjugateGradient, &params, oracle, true);
	// FIXME use enum
	} else if (method_idx == 1) {
		// FIXME: more params
		RandomSearchBernoulliParams params;
		params.global_search_prob = 0.4;
		params.contract_factor = 0.5;
		StopIterCriteria oracle = {new MaxIterCriterion(10000), new ValDiffCriterion(10e-6)};
		res = f->FindMin(OptMethod::RandomSearchBernoulli, &params, oracle, true);
	} else {
		throw std::invalid_argument("Unsupported method");	// Shouldn't happen
	}
	std::cout << "argmin = " << res.arg << std::endl;
	std::cout << "min = " << res.val << std::endl;
	if (res.has_converged) {
		std::cout << "Converged in ";
	} else {
		std::cout << "Couldn't converge after ";
	}
	std::cout << res.n_iter << " iterations." << std::endl;

	return 0;
}
