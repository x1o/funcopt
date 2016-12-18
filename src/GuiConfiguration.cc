#include "include/GuiConfiguration.h"

GuiConfiguration::GuiConfiguration() : x_0_(nullptr) {}

ScalarField* GuiConfiguration::GetCurrentFunc() const {
  return f_cur_;
}

void GuiConfiguration::SetCurrentFunc(ScalarField* f) {
  f_cur_ = f;
}

void GuiConfiguration::SetInitialPoint(Point* x_0)
{
  if (x_0_ != nullptr) {
    delete x_0_;
  }
  x_0_ = x_0;
}

IterResult& GuiConfiguration::GetIterResult()
{
  return res_;
}

void GuiConfiguration::SetIterResult(const IterResult& res) {
  res_ = res;
}

Point* GuiConfiguration::GetInitialPoint() const
{
  return x_0_;
}

