#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <vector>
#include "Matrix.hpp"


using namespace std;
using namespace zich;

void Matrix::checkSizes(const Matrix& mat1 ,const Matrix& mat2 ){
    if(mat1.numCol != mat2.numCol || mat1.numRow != mat2.numRow){
         throw invalid_argument( "The sizes of the matrix are differant");
    }
}
double Matrix::getVal(int row,int col)const{
    return this->matrixData[static_cast<std::vector<int>::size_type>(row*int(this->numCol) + col)];
}
 Matrix Matrix::operator-() const{
     std::vector<double> opcopy;
     for(double i : this->matrixData){
         opcopy.push_back(i *(-1));
     }
     return Matrix(opcopy,this->numRow,this->numCol);}
 
 Matrix Matrix::operator-(const Matrix &matrix){
     checkSizes(matrix , *this);
     std::vector<double> subvec;
     for(unsigned long i = 0 ; i < matrix.matrixData.size();i++){
         subvec.push_back(this->matrixData[i] - matrix.matrixData[i]);
     }
     return Matrix(subvec,this->numRow,this->numCol);}
 
 Matrix Matrix::operator-=(const Matrix &matrix){
     checkSizes(matrix , *this);
     std::vector<double> subvec;
     for(unsigned long i = 0 ; i < matrix.matrixData.size();i++){
         this->matrixData[i] =  this->matrixData[i] - matrix.matrixData[i];
     }
     return *this;}
 

 Matrix Matrix::operator+() const{
     return *this;
 }
 Matrix Matrix::operator+(const Matrix &matrix){
     checkSizes(matrix , *this);
     return *this;
 }
 Matrix Matrix::operator+=(const Matrix &matrix){
     checkSizes(matrix , *this);
     return *this;
 }

 Matrix Matrix::operator*(double num) const{
     return *this;
 }
 Matrix Matrix::operator*=(const Matrix &mat){
     if(this->numCol != mat.numRow){
        throw invalid_argument( "The multiplation is invalid");
    }
    return *this;
 }
 Matrix Matrix::operator*=(double num){
    return *this;
 }
 

            //-----------------------------
            // Comparison Operators
            //-----------------------------

bool zich::operator!=(const Matrix &mat1,const Matrix &mat2){
    Matrix::checkSizes(mat1 , mat2);
    return true;
}

bool zich::operator==(const Matrix &mat1,const Matrix &mat2){
    Matrix::checkSizes(mat1 , mat2);
    return true;
}

bool zich::operator<=(const Matrix &mat1,const Matrix &mat2){
    Matrix::checkSizes(mat1 , mat2);
    return true;
}
bool zich::operator>=(const Matrix &mat1,const Matrix &mat2){
    Matrix::checkSizes(mat1 , mat2);
    return true;
}

bool zich::operator<(const Matrix &mat1,const Matrix &mat2){
    Matrix::checkSizes(mat1 , mat2);
    return true;
}
bool zich::operator>(const Matrix &mat1,const Matrix &mat2){
    Matrix::checkSizes(mat1 , mat2);
    return true;
}


//-----------------------------
// Increment Decrement Operators
//-----------------------------

Matrix& Matrix::operator--(){return *this;}
Matrix Matrix::operator--(int number){return *this;}

Matrix& Matrix::operator++(){return *this;}
Matrix Matrix::operator++(int number){return *this;}

//-----------------------------
// Friend Operators
//-----------------------------

Matrix zich::operator*(double scalar,const Matrix &matrix){
    return matrix;
}
Matrix zich::operator*(const Matrix &matrix,double scalar){
    return matrix;
}
Matrix zich::operator*(const Matrix &matrix1,const Matrix &matrix2){
    if(matrix1.numCol != matrix2.numRow){
        throw invalid_argument( "The multiplation is invalid");
    }
    return matrix1;
}

    //-----------------------------
    // I/O Operators
    //-----------------------------
std::ostream& zich::operator<<(std::ostream &out, const Matrix &matrix){
    std::string result;
    for (int row = 0; row < matrix.numRow; row++)
    {
        result += "[";
        for (int col = 0; col < matrix.numCol; col++)
        {
            result += to_string(int(matrix.getVal(row,col)));
            if (col < matrix.numCol-1){
                result += " ";
            }
        }
        result += "]";
        if (row < matrix.numRow-1){
                result += "\n";
        }
    }
    out << result;
    return out;}

std::istream& zich::operator>>(std::istream &in, const Matrix &matrix){
    return in;}

    