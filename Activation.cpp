
#include "Activation.h"
#include <cmath>

//constructor of an actovation class
Activation::Activation (ActivationType act_type): act_type( act_type){}


// getter function
ActivationType Activation::get_activation_type () const
{
  return act_type;
}

void softmax_implementation(const Matrix &in_matrix, Matrix &out_matrix)
{
  float exponent;
  float exponent_sum = 0;
  for (int i = 0; i < in_matrix.get_rows()*in_matrix.get_cols(); ++i)
    { exponent = std::exp (in_matrix[i]);
      out_matrix[i] = exponent;
      exponent_sum+= exponent;
    }
  out_matrix= (1/exponent_sum)*out_matrix;
}


void relu_implementation(const Matrix &in_matrix, Matrix &out_matrix)
{
  for (int i = 0; i < in_matrix.get_rows()*in_matrix.get_cols(); ++i)
    {
      if (in_matrix[i]>0||in_matrix[i]==0)
        {
          out_matrix[i]= in_matrix[i];
        }
      else
        {
          out_matrix[i]=0;
        }
    }
}
Matrix Activation::operator() (const Matrix &m) const
{
  Matrix new_matrix(m.get_rows(), m.get_cols());
  if(act_type== SOFTMAX)
    {
      softmax_implementation(m, new_matrix);
    }
  else
    {
       relu_implementation (m, new_matrix);
    }
  return new_matrix;
}
