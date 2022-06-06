#include "MlpNetwork.h"




MlpNetwork::MlpNetwork (const Matrix weights[MLP_SIZE],
                        const Matrix biases[MLP_SIZE]):
    dense1(weights[0],biases[0], RELU),
    dense2(weights[1],biases[1], RELU),
    dense3(weights[2],biases[2], RELU),
    dense4(weights[3],biases[3], SOFTMAX)
{

}



digit MlpNetwork::operator() (const Matrix& input_matrix) const
{
  Matrix material[4];
  material[0]= dense1(input_matrix);
  material[1]= dense2(material[0]);
  material[2]= dense3(material[1]);
  material[3]= dense4(material[2]);

  digit returned;
  float max_num=0.0;
  for(int i =0; i < 10; i++){
    std::cout << material[3][i] << std::endl;
  }
  unsigned int index = 0;
  for ( int i = 0; i < material[3].get_rows()*material[3].get_cols() ; ++i)
    {
      if(material[3][i]>max_num)
        {
          index = i;
          max_num = material[3][i];
        }
    }
    returned.value = index;
  returned.probability = max_num;
  return returned;
}
