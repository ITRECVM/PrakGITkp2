#include <stdio.h>
#include <iostream>
#include <cmath>
#include <exception>
#include <cstdlib>
#include <vector>
#include "matrix.h"

void number_multi(Matrix& a, float val)
{
   for (int i = 0; i < a.get_m(); i++)
        for (int j = 0; j < a.get_n(); j++)
            a.value[i][j] *= val;
}

Matrix adamara(const Matrix&a, const Matrix &b)
{
   if (a.get_m() != b.get_m())
     throw MyException1();
   if (a.get_n() != b.get_n())
     throw MyException1();
   int m1 = a.get_m();
   int n1 = b.get_n();
          
   Matrix tmp(m1, n1);
          
   for (int i = 0; i < m1; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            tmp.value[i][j] = a.value[i][j] * b.value[i][j];;
        }
    }
    return tmp; 
}

float sled(const Matrix& a)
{
    if (a.get_m() != a.get_n())
      throw MyException3();
    float s = 0;
    for (int i = 0; i < a.get_n(); i++)
      s += a.value[i][i];
    return s;
}

float dtrm(const Matrix& a)
{
  if (a.get_m() != a.get_n())
      throw MyException3();
  //int mul_col = 0;
  //int mul_row = 0;
  
  float determinant = 1;
  
  for (int i = 0; i < a.get_n(); i++)
  {
    for (int j = i + 1; j < a.get_n(); j++)
    {
        float multiplier = a.value[j][i] / a.value[i][i];
        for (int z = i; z < a.get_n(); z++)
        {
            a.value[j][z] = a.value[j][z] - a.value[i][z] * multiplier;
        }
    }
  }
  for (int i = 0; i < a.get_n(); i++)
    determinant *= a.value[i][i];
  return determinant;
}

float skal_mul(const Vector& a, const Vector &b)
{
    if (a.get_m() != b.get_m())
      throw MyException3();
    float res = 0;
    for (int i = 0; i < a.get_m(); i++)
      res += a.value[i][0] * b.value[i][0];
    return res;
}

float norma(const Vector& a)
{
    float res = 0;

    for (int i = 0; i < a.get_m(); i++)
      res += a.value[i][0] * a.value[i][0];

    res = sqrt(res);

    return res;
}

float norma_f(const Matrix& a)
{
    float *arr = new float[a.get_m()];
    for (int i = 0; i < a.get_m(); i++)
      arr[i] = 0;
    for (int i = 0; i < a.get_m(); i++)
    {
        for (int j = 0; j < a.get_n(); j++)
          arr[i] += a.value[i][j] * a.value[i][j];
    }
    for (int i = 0; i < a.get_m(); i++)
      arr[i] = sqrt(arr[i]);
    float max = 0;
    for (int i = 0; i < a.get_m(); i++)
    {
        if (arr[i] > max)
          max = arr[i];
    }
    delete[] arr;
    return max;
}