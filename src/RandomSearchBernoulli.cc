#include "RandomSearchBernoulli.h"

#include <cstdlib>	// rand()
#include <limits>	// infinity()
#include <iostream>	// verbose

#include "Domain.h"
#include "Point.h" 
#include "StopIterCriterion.h"
#include "ScalarField.h"

IterResult ScalarField::RandomSearchBernoulli(RandomSearchBernoulliParams* params,
                                              StopIterCriteria oracle, bool verbose) const {
  Domain dom_f = GetDomain();
  Domain dom_loc = dom_f;
//  Point x(dom_f.size());
  Point x = params->x_0;
  Point cur_argmin(x);
  Domain* dom_cur;
  double f_val;
  double lim_left, lim_right;
  double cur_min = std::numeric_limits<double>::max();
  auto rng = []() { return double(rand()) / RAND_MAX; };
  IterResult res;
  res.trace.push_back(x);
  for (size_t n_iter = 0;; n_iter++) {
    if (verbose) {
      std::cout << n_iter << ": ";
    }
    if (rng() < params->global_search_prob) {
      if (verbose) {
        std::cout << "Global search" << std::endl;
      }
      dom_cur = &dom_f;
    } else {
      if (verbose) {
        std::cout << "Local search" << std::endl;
      }
      dom_cur = &dom_loc;
    }
    if (verbose) {
      std::cout << "Search bounded on " << *dom_cur << " against min = " << cur_min << std::endl;
    }
    if (n_iter != 0) {
      for (size_t axis_idx = 0; axis_idx < dom_cur->size(); axis_idx++) {
        lim_left = (*dom_cur)[axis_idx][0];
        lim_right = (*dom_cur)[axis_idx][1];
        // std::cout << lim_left << std::endl;
        // std::cout << lim_right << std::endl;
        x[axis_idx] = rng() * (lim_right - lim_left) + lim_left;
      }
    }
    f_val = Eval(x);
    if (verbose) {
      std::cout << "f(" << x << ") = " << f_val << std::endl;
    }
    if (oracle.ShouldStop(n_iter, f_val)) {
      res.has_converged = oracle.HasConverged();
      res.arg = f_val < cur_min ? x : cur_argmin;
      res.val = f_val < cur_min ? f_val : cur_min;
      res.n_iter = n_iter;
      return res;
    }
    if (f_val < cur_min) {
      // TODO: add the full trace in the form of a graph: G = {(x_i, y_i)}
      // then draw only successful steps by comparing y_i's.
      res.trace.push_back(x);
      cur_min = f_val;
      cur_argmin = x;
      if (verbose) {
        std::cout << "Zooming " << *dom_cur << " to " << x << std::endl;
      }
      dom_cur->ZoomToPoint(dom_loc, x, params->contract_factor);
    }
    if (verbose) {
      std::cout << std::endl;
    }
  }
}
