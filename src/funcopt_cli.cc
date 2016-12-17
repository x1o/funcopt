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

  auto f = all_scalar_fields[f_idx];

  std::cout << "The function is defined on " << f->GetDomain() << std::endl;
  unsigned int n_dim = f->GetDomain().size();
  std::cout << "Specify initial point:" << std::endl;
  Point x_0(n_dim);
  do {
    for (size_t i = 0; i < n_dim; i++) {
      while((std::cout << " x_0[" << i << "] > ") && getline(std::cin, input)) {
        std::istringstream is {input};
        if((is >> x_0[i]) && !(is >> input)) {
          break;
        }
        std::cerr << "Invalid input, try again." << std::endl;
      }
    }
  } while (!f->GetDomain().Contains(x_0) and std::cout << "x_0 does not belong to the function's domain" << std::endl);

  int max_iter;
  double val_diff;
  std::cout << "Select optimization method: " << std::endl;
  for (size_t i = 0; i < all_opt_methods.size(); i++ ) {
    std::cout << " " << i << ": " << all_opt_methods[i] << std::endl;
  }
  unsigned int method_idx;
  while((std::cout << "> ") && getline(std::cin, input)) {
    std::istringstream is {input};
    if((is >> method_idx) && !(is >> input) && (method_idx < all_opt_methods.size())) {
      switch (method_idx) {
        case 0:
          max_iter = 100;
          val_diff = 10e-2;
          break;
        case 1:
          max_iter = 10e4;
          val_diff = 10e-6;
          break;
        default:
          break;
      }
      break;
    }
    std::cerr << "Invalid input, try again." << std::endl;
  }

  double global_search_prob = 0.4;
  double contract_factor = 0.5;
  if (method_idx == 1) {
    std::cout << "Specify global search probability ["
              << global_search_prob << "]: " << std::endl;
    while(std::cout << "> ") {
      getline(std::cin, input);
      if (input == "") {
        break;
      }
      std::istringstream is {input};
      if((is >> global_search_prob) && !(is >> input)
         && (global_search_prob > 0) && (global_search_prob < 1)) {
        break;
      }
      std::cerr << "Invalid input, try again." << std::endl;
    }
    std::cout << "Specify domain contraction factor ["
              << contract_factor << "]: " << std::endl;
    while(std::cout << "> ") {
      getline(std::cin, input);
      if (input == "") {
        break;
      }
      std::istringstream is {input};
      if((is >> contract_factor) && !(is >> input)
         && (contract_factor > 0) && (contract_factor < 1)) {
        break;
      }
      std::cerr << "Invalid input, try again." << std::endl;
    }
  }

  CriteriaList stop_iter_crit_list = {nullptr, nullptr};
  int crit_idx;
  std::cout << "Select stop iteration criteria: (Enter to continue)" << std::endl;
  while(std::cout
        << " " << (stop_iter_crit_list[0] != nullptr ? "*" : " ")
        << "0: Max. # of iterations [" << max_iter << "]: " << std::endl
        << " " << (stop_iter_crit_list[1] != nullptr ? "*" : " ")
        << "1: Difference between succesive values [" << val_diff << "]: " << std::endl) {
    std::cout << "> ";
    getline(std::cin, input);
    if (input == "") {
      if (stop_iter_crit_list[0] != nullptr or stop_iter_crit_list[1] != nullptr) {
        break;
      } else {
        std::cout << "At least one criterion should be selected." << std::endl;
        continue;
      }
    } else {
      std::istringstream is {input};
      if((is >> crit_idx) && !(is >> input)
         && (crit_idx >= 0) && (crit_idx <= 1)) {
        switch (crit_idx) {
          case 0:
            while((std::cout << "[" << max_iter << "] > ")) {
              getline(std::cin, input);
              std::istringstream is2 {input};
              if((input == "") or ((is2 >> max_iter) && !(is2 >> input)
                                   && (max_iter >= 1))) {
                // FIXME: delete previous
                stop_iter_crit_list[0] = new MaxIterCriterion(max_iter);
                break;
              } else {
                std::cerr << "Invalid input, try again." << std::endl;
              }
            }
            break;
          case 1:
            while((std::cout << "[" << val_diff << "] > ")) {
              getline(std::cin, input);
              std::istringstream is2 {input};
              if ((input == "") or ((is2 >> val_diff) && !(is2 >> input))) {
                // FIXME: delete previous
                stop_iter_crit_list[1] = new ValDiffCriterion(val_diff);
                break;
              } else {
                std::cerr << "Invalid input, try again." << std::endl;
              }
            }
            break;
          default:
            break;
        }
      } else {
        std::cerr << "Invalid input, try again." << std::endl;
      }
    }
  }

  for (auto it = stop_iter_crit_list.begin(); it != stop_iter_crit_list.end(); it++) {
    if (*it == nullptr) {
      stop_iter_crit_list.erase(it);
    }
  }
  StopIterCriteria oracle(stop_iter_crit_list);

  IterResult res;
  ConjugateGradientParams cg_params;
  RandomSearchBernoulliParams rs_params;
  switch (method_idx) {
    case 0:
      cg_params.x_0 = x_0;
      res = f->FindMin(OptMethod::ConjugateGradient, &cg_params, oracle, true);
      break;
    case 1:
      rs_params.x_0 = x_0;
      rs_params.global_search_prob = global_search_prob;
      rs_params.contract_factor = contract_factor;
      res = f->FindMin(OptMethod::RandomSearchBernoulli, &rs_params, oracle, true);
      break;
    default:
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
