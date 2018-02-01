
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <ios>
#include <utility>
#include <vector>
#include <cstdlib>
#include <cfloat>
#include <algorithm>

using std::cerr;
using std::cout;
using std::endl;
using std::ios;
using std::vector;

template<typename _Scalar, int _Rows, int _Cols>
class Matrix{
public:
    Matrix();
    Matrix(_Scalar** dat);
    Matrix(_Scalar* vector_dat);
    Matrix(vector<_Scalar> vec);

    _Scalar data[_Rows][_Cols];

    _Scalar* operator[](unsigned int i);
    Matrix<_Scalar,_Cols,_Rows> transpose();
    Matrix<_Scalar,_Rows,1> gauss_solve(char verbose='n');
    Matrix<_Scalar,_Rows,1> leftPerron();
    _Scalar* to_Array();
    vector<_Scalar> to_Vector();
    int getSize();
    int getRows();
    int getCols();
    void dump(int precision=2);

    static bool nearlyEqual(double a, double b, double epsilon=100);
};

// consructor from 2d array
template<typename _Scalar, int _Rows, int _Cols>
Matrix<_Scalar,_Rows,_Cols>::Matrix(_Scalar** dat){
    for(int i=0; i<_Rows; i++){
        for(int j=0; j<_Cols; j++){
            data[i][j] = dat[i][j];
        }
    }
}

// constructor from nothing
template<typename _Scalar, int _Rows, int _Cols>
Matrix<_Scalar,_Rows,_Cols>::Matrix(){
    for(int i=0; i<_Rows; i++){
        for(int j=0; j<_Cols; j++){
            data[i][j] = 0;
        }
    }
}

// constructor from array (to create a vector)
template<typename _Scalar, int _Rows, int _Cols>
Matrix<_Scalar,_Rows,_Cols>::Matrix(_Scalar* vector_dat){
    if(_Cols!=1){
        cerr << "a vector must be an N x 1 Matrix (_Cols==1)\n";
        cerr << "returning uninitialized Matrix\n";
    } else {
        for(int i=0; i<_Rows; i++){
            data[i][0] = vector_dat[i];
        }
    }
}

// constructor from std::vector
template<typename _Scalar, int _Rows, int _Cols>
Matrix<_Scalar,_Rows,_Cols>::Matrix(vector<_Scalar> vec){
    if(_Cols!=1){
        cerr << "a vector must be an N x 1 Matrix (_Cols==1)\n";
        cerr << "returning uninitialized Matrix\n";
    } else {
        for(int i=0; i<_Rows; i++){
            data[i][0] = vec[i];
        }
    }
}

// random access operator.
// Use [i][j] for matrices
// use [i][0] for vectors
template<typename _Scalar, int _Rows, int _Cols>
_Scalar* Matrix<_Scalar,_Rows,_Cols>::operator[](unsigned int i){
    return data[i];
}

template<typename _Scalar, int _Rows, int _Cols>
Matrix<_Scalar,_Cols,_Rows> Matrix<_Scalar,_Rows,_Cols>::transpose(){
    _Scalar** transposed = new _Scalar*[_Cols];
    for(int i=0; i<_Cols; i++){
        transposed[i] = new _Scalar[_Rows];
    }
    // fill in transpose
    for(int i=0; i<_Cols; i++){
        for(int j=0; j<_Rows; j++){
            transposed[i][j] = data[j][i];
        }
    }
    Matrix<_Scalar,_Cols,_Rows> T(transposed);
    return T;
}

template<typename _Scalar, int _Rows, int _Cols>
Matrix<_Scalar,_Rows,1> Matrix<_Scalar,_Rows,_Cols>::gauss_solve(char verbose){
    // must be squared!
    if(_Rows!=_Cols){
        cerr << "matrix must be squared to be solved\n";
        _Scalar* pointer;
        Matrix<_Scalar,_Rows,1> nothing(pointer);
        return nothing;
    }

    // solve
    int i,j,k;
    int n = _Rows; // (==_Cols)
    _Scalar* x = new _Scalar[n];        //solution vector
    _Scalar a[n][n+1];                  //augmented matrix
    _Scalar* b = new _Scalar[n];        //known terms
    for(int i=0; i<n; i++){
        b[i] = 0;
    }
    for (i=0;i<n;i++)
        for (j=0;j<=n;j++)
            if(j<n)
                a[i][j] = data[i][j];    //input the elements of array
            else
                a[i][j] = b[i];
    for(i=0;i<n-1;i++){            //loop to perform the gauss elimination
        if(a[i][i]!=0){
            for(k=i+1;k<n;k++){
                _Scalar t=a[k][i]/a[i][i];
                for (j=0;j<=n;j++)
                    a[k][j]=a[k][j]-t*a[i][j];    //make the elements below the pivot elements equal to zero or elimnate the variables
            }
        }
    }
    if(verbose=='v'){
        cout.precision(5);        //set precision
        cout.setf(ios::fixed);
        cout<<"\n\nThe matrix after gauss-elimination is as follows:\n";
        for (i=0;i<n;i++)            //print the new matrix
        {
            for (j=0;j<=n;j++)
                cout<<a[i][j]<< " ";
            cout<<"\n";
        }
    }
    for(i=n-1;i>=0;i--){      //back-substitution
                                    //x is an array whose values correspond to the values of x,y,z..
        if(i==n-1 && nearlyEqual(a[n-1][n],0) && nearlyEqual(a[n-1][n-1],0)){
            x[i]=1;      //dim(ker(A))>=1, so I pick an arbitrary value for the free variable
        }else{
            x[i]=a[i][n];   //make the variable to be calculated equal to the rhs of the last equation
        }
        for (j=i+1;j<n;j++)
            if (j!=i)            //then subtract all the lhs values except the coefficient of the variable whose value                                   is being calculated
                x[i]=x[i]-a[i][j]*x[j];
        if(a[i][i]!=0){
            x[i]=x[i]/a[i][i];            //now finally divide the rhs by the coefficient of the variable to be calculated
        }
    }
    // if dim(ker(A))>=1, normalize the resulting vector
    if(nearlyEqual(a[n-1][n],0) && nearlyEqual(a[n-1][n-1],0)){
        // normalize to state 0 as reference, if you can
        if(x[0]!=0){
            _Scalar norm = x[0];
            for(i=0;i<n;i++){
                x[i]/=norm;
            }
        } else {
            cout << "x[0] != 0. Result is not normalized\n";
        }
    }
    if(verbose=='v'){
        cout<<"\nLinear system solution:\n";
        for (i=0;i<n;i++)
            cout<<x[i]<<endl;            // Print the values of x, y,z,....
    }

    // output resulting vector as n*1 Matrix
    Matrix<_Scalar,_Rows,1> X(x);
    return(X);
}

template<typename _Scalar, int _Rows, int _Cols>
_Scalar* Matrix<_Scalar,_Rows,_Cols>::to_Array(){
    _Scalar* x;
    if(_Rows==1){
        x = new _Scalar[_Cols];
        for(int j=0; j<_Cols; j++){
            x[j] = data[0][j];
        }
    } else if(_Cols==1){
        x = new _Scalar[_Rows];
        for(int i=0; i<_Rows; i++){
            x[i] = data[i][0];
        }
    } else {
        cerr << "matrix must be N x 1 or 1 x N in order to be converted to array\n";
        cerr << "returning uninitialized pointer\n";
    }
    return x;
}

template<typename _Scalar, int _Rows, int _Cols>
vector<_Scalar> Matrix<_Scalar,_Rows,_Cols>::to_Vector(){
    vector<_Scalar> x;
    if(_Rows==1){
        for(int j=0; j<_Cols; j++){
            x.push_back(data[0][j]);
        }
    } else if(_Cols==1){
        for(int i=0; i<_Rows; i++){
            x.push_back(data[i][0]);
        }
    } else {
        cerr << "matrix must be N x 1 or 1 x N in order to be converted to vector\n";
        cerr << "returning uninitialized pointer\n";
    }
    return x;
}

template<typename _Scalar, int _Rows, int _Cols>
Matrix<_Scalar,_Rows,1> Matrix<_Scalar,_Rows,_Cols>::leftPerron(){
    if(_Rows!=_Cols){
        cerr << "cannot solve Perron vector for non-squared matrix\n";
        Matrix<_Scalar,_Rows,1> nothing;
        return nothing;
    } else {
        // transpose
        Matrix<_Scalar,_Rows,_Cols> transposed = this->transpose();
        // subtract identity
        for(int i=0; i<_Rows; i++){
            transposed[i][i] -= 1;
        }
        // solve
        Matrix<_Scalar,_Rows,1> X = transposed.gauss_solve();
        return X;
    }
}


template<typename _Scalar, int _Rows, int _Cols>
int Matrix<_Scalar,_Rows,_Cols>::getSize(){
    if(_Rows!=_Cols){
        cerr << "use getSize() only on a square matrix!\n";
        cerr << "returning just getRows()\n";
    }
    return getRows();
}

template<typename _Scalar, int _Rows, int _Cols>
int Matrix<_Scalar,_Rows,_Cols>::getRows(){
    return _Rows;
}

template<typename _Scalar, int _Rows, int _Cols>
int Matrix<_Scalar,_Rows,_Cols>::getCols(){
    return _Cols;
}

template<typename _Scalar, int _Rows, int _Cols>
void Matrix<_Scalar,_Rows,_Cols>::dump(int precision){
    cout.precision(precision);        //set precision
    cout.setf(ios::fixed);
    for(int i=0; i<_Rows; i++){
        for(int j=0; j<_Cols; j++){
            cout << data[i][j] << " ";
        }
        cout << "\n";
    }
}

template<typename _Scalar, int _Rows, int _Cols>
bool Matrix<_Scalar,_Rows,_Cols>::nearlyEqual(double a, double b, double epsilon){
		double absA = std::abs(a);
		double absB = std::abs(b);
		double diff = std::abs(a - b);

		if (a == b) { // shortcut, handles infinities
			return true;
		} else if (a == 0 || b == 0 || diff < DBL_EPSILON) {
			// a or b is zero or both are extremely close to it
			// relative error is less meaningful here
			return diff < (epsilon * DBL_EPSILON);
		} else { // use relative error
			return diff / std::min((absA + absB), DBL_MAX) < epsilon;
		}
	}

#endif // MATRIX_H

