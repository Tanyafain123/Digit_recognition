
#include "Dense.h"

Dense::Dense (const Matrix& weights, const Matrix& bias, ActivationType act_type) :
    act_type(act_type), weights(weights), bias(bias){}


Activation Dense::get_activation() const
{
  return act_type;
}
Matrix Dense::get_weights () const
{
  return weights;
}

Matrix Dense::get_bias () const
{
  return bias;
}
Matrix Dense::operator() (const Matrix &m) const
{
  Matrix matrix_output = get_activation()((weights*m+bias));
  return matrix_output;
}
