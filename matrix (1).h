#include <initializer_list>
#include <tuple>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <exception>
#include <cstdlib>
#include <vector>
#include <ostream>
#include <fstream>

class MyException1
{
    public:
    private:
};

class MyException2
{
    public:
    private:
};

class MyException3
{
    public:
    private:
};

#include <ostream>
#include <istream>
#include <fstream>

using namespace std;

class Matrix
{
    protected:
        int m;
        int n;
        float** value;

    public:
        void destroy()
        {
          if (m == 0 || n == 0 || value == nullptr)
            return;

          for (int i = 0; i < m; i++)
              delete[] value[i];

          delete[] value;
        }

        void initialize()
        {
          alloc();

            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++)
                    cin >> value[i][j];
        }

        void alloc()
        {
          value = new float* [m];

          for (int i = 0; i < m; i++)
            value[i] = new float[n];
        }

        /*void input_values()
        {
            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++)
                    cin >> value[i][j];
        } */

        friend ostream& operator<<(ostream& os, Matrix&a)
        {
            for (int i = 0; i < a.get_m(); i++)
            {
                for (int j = 0; j < a.get_n(); j++)
                {
                    os << a.value[i][j] << " ";
                }

                os << endl;
            }

            return os;
        }

        friend istream& operator>>(istream& is, Matrix& a)
        {
          for (int i = 0; i < a.get_m(); i++)
          {
            for (int j = 0; j < a.get_n(); j++)
            {
              is >> a.value[i][j];
            }
          }

          return is;
        }

        friend void write(string finename, Matrix& a)
        {
          ofstream f(finename, ios::binary);

          if (!f.good())
          {
            f.close();
            throw MyException3();
          }

          for (int i = 0; i < a.get_m(); i++)
          {
            f.write((char *)a.value[i], (size_t)a.get_n() * sizeof(a.value[0][0]));
          }

          f.close();
        }

        friend void read(string finename, Matrix& a)
        {
          ifstream f(finename, ios::binary);

          if (!f.good())
          {
            f.close();
            throw MyException3();
          }

          for (int i = 0; i < a.get_m(); i++)
          {
            f.read((char*)a.value[i], (size_t)a.get_n() * sizeof(a.value[0][0]));
          }

          f.close();
        }

        int get_m() const
        {
            return m;
        };
        
        int get_n() const
        {
            return n;
        };

        Matrix()
        {
            m = 0;
            n = 0;
            value = nullptr;
        }

        Matrix(int m, int n)
        {
            this->m = m;
            this->n = n;
            alloc();
        }

        Matrix(const Matrix& a)
        {
          m = a.m;
          n = a.n;
          alloc();

          for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
              value[i][j] = a.value[i][j];
        }

        /*Matrix(initializer_list<float> list)
        {
          ///

        }*/

        friend Matrix center(const Matrix& a)
        {
          Matrix b = a;

          for (int j = 0; j < b.n; j++)
          {
            float med = 0;

            for (int i = 0; i < b.m; i++)
              med += b.value[i][j];

            med /= b.m;

            for (int i = 0; i < b.m; i++)
              b.value[i][j] -= med;
          }

          return b;
        }

        friend Matrix scaling(const Matrix& a)
        {
          Matrix b = a;

          for (int j = 0; j < b.n; j++)
          {
            float med = 0;

            for (int i = 0; i < b.m; i++)
              med += b.value[i][j];

            med /= b.m;

            float s = 0;

            for (int i = 0; i < b.m; i++)
              s += (b.value[i][j] - med) * (b.value[i][j] - med);

            s /= b.m - 1;

            for (int i = 0; i < b.m; i++)
              b.value[i][j] = b.value[i][j] / s;
          }

          return b;
        }

        void copy(const Matrix& b)
        {
            //destroy();
            n = b.n;
            m = b.m;
            alloc();

            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++)
                    value[i][j] = b.value[i][j];
        }

        friend Matrix operator+(const Matrix& a, const Matrix& b)
        {
            if (a.get_m() != b.get_m())
              throw MyException2();
            if (a.get_n() != b.get_n())
              throw MyException2();
            int m1 = a.get_m();
            int n1 = b.get_n();
            Matrix tmp(m1, n1);

            for (int i = 0; i < m1; i++)
            {
                for (int j = 0; j < n1; j++)
                {
                    tmp.value[i][j] = a.value[i][j] + b.value[i][j];
                }
            }

            return tmp;
        }

        friend Matrix operator-(const Matrix& a, const Matrix& b)
        {
            if (a.get_m() != b.get_m())
              throw MyException2();
            if (a.get_n() != b.get_n())
              throw MyException2();
            int m1 = a.get_m(); 
            int n1 = b.get_n();
            Matrix tmp(m1, n1);

            for (int i = 0; i < m1; i++)
            {
                for (int j = 0; j < n1; j++)
                {
                    tmp.value[i][j] = a.value[i][j] - b.value[i][j];
                }
            }

            return tmp;
        }

        Matrix operator=(const Matrix& b)
        {
            copy(b);
            return *this;
        }
        
        friend Matrix operator*(const Matrix& a, const Matrix& b)
        {
          if (a.get_n() != b.get_m())
            throw MyException1();
          int m1 = a.get_m();
          int n1 = b.get_n();
          
          Matrix tmp(m1, n1);
          
          for (int i = 0; i < m1; i++)
          {
              for (int j = 0; j < n1; j++)
              {
                tmp.value[i][j] = 0;
                for (int z = 0; z < a.get_n(); z++)
                  tmp.value[i][j] += a.value[i][z] * b.value[z][j];
              }
          }
          return tmp;
        }
        
        friend Matrix operator/(const Matrix& a, const Matrix& b)
        {
          return a * obratka(b);
        }

        friend Matrix operator/(const Matrix& a, const float b)
        {
          Matrix c = a;

          for (int i = 0; i < c.m; i++)
            for (int j = 0; j < c.n; j++)
              c.value[i][j] /= b;

          return c;
        }
 
        friend void number_multi(Matrix& a, float val);
        friend Matrix adamara(const Matrix&a, const Matrix &b);
        friend float sled(const Matrix& a);
        friend float dtrm(const Matrix& a);
        friend float norma_f(const Matrix& a);

        friend Matrix trans(const Matrix& a)
        {
          Matrix m(a.n, a.m);

          for (int i = 0; i < a.m; i++)
            for (int j = 0; j < a.n; j++)
              m.value[j][i] = a.value[i][j];

          return m;
        }

        friend Matrix obratka(const Matrix& a)
        {
          Matrix b = trans(a);
          float det = dtrm(a);

          if (det == 0)
            throw MyException3();

          number_multi(b, 1 / det);

          return b;
        }

        friend int prank(const Matrix& a)
        {
          const double EPS = 1E-8;
          int rank = max(a.n, a.m);
          vector<int> used(a.n);

          for (int i = 0; i < a.m; i++)
          {
            int j;

            for (j = 0; j < a.n; j++)
              if (!used[j] && abs(a.value[j][i]) > EPS)
                break;

            if (j == a.n)
              rank--;
            else
            {
              used[j] = true;

              for (int p = i + 1; p < a.m; p++)
                a.value[j][p] /= a.value[j][i];

              for (int k = 0; k < a.n; k++)
                if (k != j && abs(a.value[k][i]) > EPS)
                  for (int p = i + 1; p < a.m; p++)
                    a.value[k][p] -= a.value[j][p] * a.value[k][i];
            }
          }

          return rank;
        }

        friend tuple<Matrix, Matrix, Matrix> nipals(const Matrix& x)
        {
          const float eps = 1e-8f;

          Matrix P, T;

          Matrix D(x);
          D = center(D);
          D = scaling(D);

          Matrix E(D);
          int PC = prank(D);

          P.n = T.n = PC;
          P.m = E.n;
          T.m = E.m;

          P.alloc();
          T.alloc();

          for (int h = 0; h < PC; h++)
          {
            Matrix t(E.m, 1);

            for (int i = 0; i < E.m; i++)
              t.value[i][0] = E.value[i][h];

            Matrix d, p;

            do
            {
              p = trans((trans(t) * E) / (trans(t) * t).value[0][0]);
              p = p / norma_f(p);

              Matrix t_old = t;
              t = (E * p) / (trans(p)*p).value[0][0];
              d = t_old - t;
            } while (norma_f(d) > eps);

            E = E - t * trans(p);

            for (int i = 0; i < P.m; i++)
              P.value[i][h] = p.value[i][0];

            for (int i = 0; i < T.m; i++)
              T.value[i][h] = t.value[i][0];
          }

          return tuple<Matrix, Matrix, Matrix>(T, P, E);
        }

        ~Matrix()
        {
          destroy();
        }
};

void number_multi(Matrix& a, float val);
Matrix adamara(const Matrix& a, const Matrix& b);
float sled(const Matrix& a);
float dtrm(const Matrix& a);
float norma_f(const Matrix& a);

class Unit_Matrix: public Matrix
{
    public:
      Unit_Matrix()
      {
        int m = 0;
        int n = 0;
        float value = 0;
      }
      
      Unit_Matrix(int m, int n)
      {
          this->m = m;
          this->n = n;
          initialize();
      }
      
      void initialize()
      {
        value = new float* [m];

        for (int i = 0; i < m; i++)
            value[i] = new float[n];

        for (int i = 0; i < m; i++)
          for (int j = 0; j < n; j++)
            if (i == j)
              value[i][j] = 1;
            else
              value[i][j] = 0;
      }
};


class diagonal_matrix: public Matrix
{
   public:
     diagonal_matrix()
     {
       int m = 0;
       int n = 0;
       float value = 0;
     }
     
     diagonal_matrix(int m, int n)
     {
          this->m = m;
          this->n = n;
          initialize();
     }
     
     void initialize()
     {
        value = new float* [m];

        for (int i = 0; i < m; i++)
            value[i] = new float[n];

        for (int i = 0; i < m; i++)
          for (int j = 0; j < n; j++)
            if (i == j)
              cin >> value[i][j];
            else
              value[i][j] = 0;
     }
};

class Upper_Triang: public Matrix
{
  public:
    Upper_Triang()
    {
      int m = 0;
      int n = 0;
      float value = 0;  
    }
    Upper_Triang(int m, int n)
     {
          this->m = m;
          this->n = n;
          initialize();
     }
     
     void initialize()
     {
        value = new float* [m];

        for (int i = 0; i < m; i++)
            value[i] = new float[n];

        for (int i = 0; i < m; i++)
          for (int j = 0; j < n; j++)
            if (i <= j)
              cin >> value[i][j];
            else
              value[i][j] = 0;
     }
};

class Lower_Triang: public Matrix
{
  public:
    Lower_Triang()
    {
      int m = 0;
      int n = 0;
      float value = 0;  
    }
    Lower_Triang(int m, int n)
     {
          this->m = m;
          this->n = n;
          initialize();
     }
     
     void initialize()
     {
        value = new float* [m];

        for (int i = 0; i < m; i++)
            value[i] = new float[n];

        for (int i = 0; i < m; i++)
          for (int j = 0; j < n; j++)
            if (i >= j)
              cin >> value[i][j];
            else
              value[i][j] = 0;
     }  
};

class Symmetric: public Matrix
{
  public:
    Symmetric()
    {
      int m = 0;
      int n = 0;
      float value = 0;   
    }
    Symmetric(int m, int n)
    {
        this->m = m;
        this->n = n;
        initialize();
    }
    void initialize()
     {
        value = new float* [m];

        for (int i = 0; i < m; i++)
            value[i] = new float[n];
            
        for (int i = 0; i < m; i++)
          for (int j = 0; j < n; j++)
            if (i >= j)
              cin >> value[i][j];
        
        for (int i = 0; i < m; i++)
          for (int j = 0; j < n; j++)
            if (i < j)
              {
                value[i][j] = value[j][i];
              }
     }  
};

class Vector: public Matrix
{
  public:
    Vector()
    {
        int m = 0;
        int n = 0;
        float value = 0;
    }

    Vector(int m)
    {
      this->m = m;
      this->n = 1;
      initialize();
    }

    void initialize()
    {
      value = new float* [m];

      for (int i = 0; i < m; i++)
        value[i] = new float[n];
            
      for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
          cin >> value[i][j];
        
    }  
    friend float skal_mul(const Vector& a, const Vector &b);
    friend float norma(const Vector& a);

    friend float angle(const Vector& a, const Vector& b)
    {
      return acos(skal_mul(a, b) / (norma(a) * norma(b)));
    }
};

float norma(Vector& a);
float skal_mul(Vector& a, Vector &b);