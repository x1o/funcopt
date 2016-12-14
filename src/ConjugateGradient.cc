#include "ConjugateGradient.h"

#include <iostream>

#include "StopIterCriterion.h"
#include "ScalarField.h"

IterResult ScalarField::ConjugateGradient(ConjugateGradientParams* params,
                                          StopIterCriteria oracle, bool verbose) const {
  Point x_0 = params->x_0;
  Point x_k(x_0);
  Point grad_k = Gradient(x_0);
  Point p_k(-grad_k);
  Point x_prev;
  Point grad_next;
  IterResult res;
  double alpha, beta, f_k;
  // std::cout << x_k << " ~ " << p_k << std::endl;
  // while (!IsZeroVector(grad_k, eps)) {
  for (size_t k = 0;; k++) {
    if (verbose)/*{{{*/
      std::cout << x_k << std::endl;/*}}}*/
    f_k = Eval(x_k);
    if (oracle.ShouldStop(k, f_k)) {
      res.has_converged = oracle.HasConverged();
      res.arg = x_k;
      res.val = f_k;
      res.n_iter = k;
      return res;
    }
    // FIXME: magic constant
    alpha = LineSearch(x_k, p_k, 10e-10);
    if (verbose)
      std::cout << "alpha = " << alpha << std::endl;/*}}}*/
    x_prev = x_k;
    x_k = x_k + alpha * p_k;
    grad_next = Gradient(x_k);
    beta = (grad_next * grad_next) / (grad_k * grad_k);
    p_k = -grad_next + beta * p_k;
    grad_k = grad_next;
  }
}
