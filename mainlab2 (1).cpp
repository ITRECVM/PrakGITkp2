#include "matrix.h"

using namespace std;

int main()
{
    Matrix mat1(32, 12), T, P, E;

    ifstream f("data.txt");

    f >> mat1;
    f.close();

    tie(T, P, E) = nipals(mat1);

    cout << T << endl << P << endl << E;

    //Matrix mat2(3,3);
    /*Matrix mat3(2,2);
    try
    {
        Matrix matRES = mat2 + mat3;
    }
    catch (const MyException2& ex1)
    {
        cout << "Can't sum!" << endl;
    }
    catch (...)
    {
        cout << "Smth is wrong!" << endl;
    }
    cout << sled(mat2); */
    //cout << norma_f(mat2);
    //
    //float det = dtrm(mat2);
    //cout << det;
    //
    //Vector a(3), b(3);
    //ofstream kal("yes.txt");
    //kal << b;
    //float res = skal_mul(a,b);
    //write("yes.txt", b);
    //read("yes.txt", a);
    //
    //cout << a;
    /*mat1.matrix_out();
    Matrix mat2(4,5);
    mat2.matrix_out();
    Matrix mat3 = adamara(mat1, mat2);
    mat3.matrix_out(); */
    //cout << mat1;

    //Vector a(2), b(2);
    //
    //cout << angle(a, b);

    return 0; 
}