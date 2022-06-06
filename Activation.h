#ifndef ACTIVATION_H
#define ACTIVATION_H
#include "Matrix.h"
//#ifndef ACTIVATION_H
/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    RELU,
    SOFTMAX
};

class Activation{
  ActivationType act_type;

 public:
  Activation(ActivationType act_type);
  ActivationType get_activation_type() const;
  Matrix operator() ( const Matrix &m) const;
};



#endif //ACTIVATION_H
