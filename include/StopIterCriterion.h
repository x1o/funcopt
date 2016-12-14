#ifndef STOPITERCRITERION_H_
#define STOPITERCRITERION_H_

class StopIterCriterion {
  public:
    bool HasConverged();
    virtual bool ShouldStop(int n_iter, double f_val) = 0;

  protected:
    bool has_converged_ = false;
};

#endif	// STOPITERCRITERION_H_
