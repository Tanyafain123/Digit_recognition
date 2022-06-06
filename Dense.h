
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

class Dense {
  Activation act_type;
  Matrix weights ;
  Matrix bias ;

 public:
Dense (const Matrix& weights, const Matrix& bias, ActivationType act_type);
Activation get_activation() const;
Matrix get_weights() const;
Matrix get_bias() const;
Matrix operator() ( const Matrix &m) const;

};
#endif //DENSE_H
