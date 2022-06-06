
#include <iostream>
#include <cmath>
#define ERROR_MESSAGE "Error: THE SIZE OF MATRIXES DOES NOT MATCH \n"
#define ERROR_MESSAGE_1 \
"Error: SOMETHING WENT WRONG DURING THE READING OG THE FILE \n"
#define ERROR_MESSAGE_2 "Error: YOU CROSSED THE INDEX BOUND \n"
#define ERROR_MESSAGE_3 "Error: BAD ALLOCATION OF MEMORY \n"
#define Magic_number 0.1
using std::cout;
using std::endl;
using std::cerr;
using std::nothrow;
#include "Matrix.h"


//Constructor that builds new matrix as a list of size rows*cols
Matrix:: Matrix(int rows, int cols)  : rows(rows), cols(cols)
{
  if (rows<0||cols <0)
    {
      cerr << ERROR_MESSAGE << endl;
      exit (EXIT_FAILURE);
    }
  list = new(nothrow)float[rows*cols]();
  if(list== nullptr)
    {
      cerr << ERROR_MESSAGE_3 << endl;
      exit (EXIT_FAILURE);
    }
  for(unsigned long i = 0; i< (unsigned long)rows*cols; i++)
    {
      list[i] = 0;
    }

}



//Constructor that builds new matrix as a list of size 1
Matrix::Matrix() : rows(1), cols(1)
{
  list = new(nothrow) float[1];
  if(list== nullptr)
    {
      cerr << ERROR_MESSAGE_3 << endl;
      exit (EXIT_FAILURE);
    }
  list[0] = 0;

}



//Copy constructor that builds new matrix from existing one



Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols)
{
  list = new(nothrow) float[other.rows*other.cols];
  if(list== nullptr)
    {
      cerr << ERROR_MESSAGE_3 << endl;
      exit (EXIT_FAILURE);
    }
  for(unsigned long i = 0; i < (unsigned long)rows*cols; i++)
    {
      list[i] = other.list[i];
    }
}
//destructor

Matrix::~Matrix()
{
  delete[] list;
}

//We will write some getters

int Matrix::get_rows () const
{
  return rows;
}

int Matrix:: get_cols() const
{
  return cols;
}

//transpose function that transposes the given matrix//

Matrix& Matrix::transpose()
{
  float* new_list = new (nothrow)float [rows*cols];
  if(list== nullptr)
    {
      cerr << ERROR_MESSAGE_3 << endl;
      exit (EXIT_FAILURE);
    }
  for (int i = 0; i < (rows*cols); ++i)
    {
      new_list[i] = list[i];
    }
  for (unsigned long i = 0; i< (unsigned long)rows; i++)
    {
      for (unsigned long j = 0; j< (unsigned long)cols; j++)
        list[i* cols+j]= new_list[j*rows+i];
    }

  int temp = this->rows;
  this->rows = this->cols;
  this->cols = temp;
  delete[] new_list;
  return *this;
}

// Vectorize function. Should return the flatted matrix. In our case, returns the list.

Matrix& Matrix:: vectorize()
{

  rows = this->rows*this->cols;
  cols = 1;
  return *this;
}

void Matrix::plain_print() const
{
  for (unsigned long i = 0; i< (unsigned long)rows; i++)
    {
      for (unsigned long j = 0; j < (unsigned long)cols; j++)
        {
          cout << list[i * cols + j] << " ";
        }
      cout << endl;

    }
}
//This function returns the dot product of two matrixes.
// In case that matrixes does not match, returns nullptr

Matrix Matrix:: dot(Matrix const& m) const
{
  Matrix temp (rows, cols);
  if (this->get_cols()!= m.get_cols()|| this->get_rows()!= m.get_rows())
    {
      cerr << ERROR_MESSAGE << endl;
      exit (EXIT_FAILURE);
    }
  for (unsigned long i = 0; i < (unsigned long) rows*cols; i++)
    {
      temp.list[i] = this->list[i]* m.list[i];
    }

  return temp;
}



// This function returns the frobenius norm of the matrix

float Matrix::norm() const
{
  float sum = 0.0;
  for (int i = 0; i < rows* cols; ++i)
    {
      sum+=(list[i]*list[i]);
    }
  return sqrt(sum);
}


//************************************************//
//****************** operators *******************//
//************************************************//


//Matrix addition

Matrix Matrix::operator +(const Matrix& rhs) const
{

  if(rows!= rhs.rows || cols != rhs.cols)
    {
      cerr << ERROR_MESSAGE << endl;
      exit (EXIT_FAILURE);
    }
  Matrix temp (rows, cols);
  for (int i = 0; i < rows * cols; ++i)
    {
      temp.list[i] = this->list[i] + rhs.list[i];
    }
  return temp;
}



//assignment operator

Matrix& Matrix:: operator = (const Matrix& rhs)
{

  if(this!=&rhs)
    {
      delete [] this->list;
      this->list = new (nothrow)float[rhs.get_rows()*rhs.get_cols()];
      if(list== nullptr)
        {
          cerr << ERROR_MESSAGE_3 << endl;
          exit (EXIT_FAILURE);
        }
      this->rows = rhs.get_rows();
      this->cols = rhs.get_cols();
      for (int i = 0; i < rows * cols; ++i)
        {
          list[i] = rhs.list[i];
        }



    }
  return *this;
}



Matrix Matrix::operator *(const Matrix& rhs) const
{
  if(cols!= rhs.rows)
    {
      cerr << ERROR_MESSAGE << endl;
      exit (EXIT_FAILURE);

    }
  else
    {
      Matrix temp (rows, rhs.cols);

      for (int i = 0; i <rows ; ++i)
        {
          for (int j = 0; j <rhs.cols ; ++j)
            {
              double sum = 0;
              for (int k = 0; k < cols; ++k)
                {
                  sum += this->list[i*cols+k]*rhs.list[k*rhs.cols+j];
                }
              temp.list[i*rhs.cols+j] = sum;

            }
        }
      return temp;
    }

}

//operator multiplication on the right
Matrix Matrix::operator*( const float num) const
{
  Matrix temp (this->rows, this->cols);
  for (int i = 0; i < rows*cols ; ++i)
    {
      temp. list[i] = this->list[i] * num;
    }
  return temp;
}

//operator multiplication on the left


Matrix  operator *( const float num, const Matrix& lhs)
{
  Matrix temp (lhs.get_rows(), lhs.get_cols());
  for (int i = 0; i < lhs.get_rows()*lhs.get_cols() ; ++i)
    {
      temp.list[i] = lhs.list[i] * num;
    }
  return temp;
}



//operator Matrix addition accumulation
Matrix& Matrix:: operator +=(const Matrix& rhs)
{
  if(this->rows!= rhs.rows || this->cols!= rhs.cols)
    {
      cerr << ERROR_MESSAGE << endl;
      exit (EXIT_FAILURE);

    }
  for (int i = 0; i < rows*cols; ++i)
    {
      this->list[i]+= rhs.list[i];
    }
  return *this;
}



//const_operator
float &Matrix::operator() (int a, int b) const
{
  if (a>rows||b>cols|| a<0|| b< 0)
    {
      cerr << ERROR_MESSAGE_2 << endl;
      exit (EXIT_FAILURE);
    }
  return this->list[a*cols+b];
}



//non_const-operator
float &Matrix::operator() (int a, int b)
{
  if (a>rows||b>cols|| a<0|| b< 0)
    {
      cerr << ERROR_MESSAGE_2 << endl;
      exit (EXIT_FAILURE);
    }
  return this->list[a*cols+b];
}



//const operator
float Matrix::operator[] (unsigned int idx) const
{
  return this->list[idx];

}


//non const operator
float& Matrix::operator[] (unsigned int idx)
{
  return this->list[idx];
}



//operator<<//
std::ostream &operator<< (std::ostream &os, const Matrix &other)
{
  for (int i = 1; i < other.get_rows(); ++i)
    {
      for (int j = 1; j < other.get_cols(); ++j)
        {
          if (other.list[i * other.rows + j] > Magic_number)
            {
              os << "**";
            }
          else
            {
              os << "  ";
            }

        }
      os <<endl;
    }
  return os;
}



//operator>>//
std::istream &operator>> (std::istream &is, const Matrix &other)
{
  is.read((char *) other.list, (std::streamsize)(other.get_rows()*other.get_cols()*sizeof (float)));

  if ((int)is.gcount()!= (int)(other.get_rows()*other.get_cols()* sizeof (float )))
    {
      cerr << ERROR_MESSAGE_1 << endl;
      exit (EXIT_FAILURE);
    }
  return is;
}

