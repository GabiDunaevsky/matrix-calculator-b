#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include<vector>

#include "Matrix.hpp"


using namespace std;
using namespace zich;


bool is_number(const std::string& s)
{
    char* end = nullptr;
    strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0';
}

void Matrix::checkSizes(const Matrix& mat1 ,const Matrix& mat2 ){
    if(mat1.numCol != mat2.numCol || mat1.numRow != mat2.numRow){
         throw invalid_argument( "The sizes of the matrix are differant");
    }
}

double Matrix::getLoc(int row, int column)const{
    int loc = row * this->numCol + column;
    return this->matrixData.at((unsigned long)loc);
}

double Matrix::calculateSum(const Matrix& mat){
    double sum = 0;
    for(double i:mat.matrixData){
        sum+=i;
    }
    return sum;
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
     for(unsigned long i = 0 ; i < matrix.matrixData.size();i++){
         this->matrixData[i] =  this->matrixData[i] - matrix.matrixData[i];
     }
     return *this;}
 

 Matrix Matrix::operator+() const{
     return *this;
 }
 Matrix Matrix::operator+(const Matrix &matrix){
  checkSizes(matrix , *this);
     std::vector<double> addvec;
     for(unsigned long i = 0 ; i < matrix.matrixData.size();i++){
         addvec.push_back(this->matrixData[i] + matrix.matrixData[i]);
     }
     return Matrix(addvec,this->numRow,this->numCol);}

 Matrix Matrix::operator+=(const Matrix &matrix){
  checkSizes(matrix , *this);
     for(unsigned long i = 0 ; i < matrix.matrixData.size();i++){
         this->matrixData[i] =  this->matrixData[i] + matrix.matrixData[i];
     }
     return *this;}

 Matrix Matrix::operator*(double num) const{      
     std::vector<double> mulvec;
     for(unsigned long i = 0 ; i < this->matrixData.size();i++){
         mulvec.push_back(this->matrixData[i] * num);
     }
     return Matrix(mulvec,this->numRow,this->numCol);
 }

 Matrix Matrix::operator*=(const Matrix &mat){
     if(this->numCol != mat.numRow){
        throw invalid_argument( "The multiplation is invalid");
    }
    int matSize = this->numRow*mat.numCol;
    std::vector<double> mulvec;
    mulvec.assign((size_t) matSize, 0);

    for (int i = 0; i < this->numRow; i++) {
        for (int j = 0; j < mat.numCol; j++) {
            double ans = 0.0;
            for (int k = 0; k < this->numCol; k++){
                ans = ans + this->getLoc(i,k) * mat.getLoc(k,j);
            }
            mulvec.at((unsigned long)i * (unsigned long)mat.numCol + (unsigned long)j) = ans;
        }
    }

    this->matrixData = mulvec;
    this->numCol = mat.numCol;

    return *this;
}
// Note , i could make an external function but i think that this is mor understandable (only few lines).
 Matrix Matrix::operator*(const Matrix &mat)const{
     if(this->numCol != mat.numRow){
        throw invalid_argument( "The multiplation is invalid");
    }
    int matSize = this->numRow*mat.numCol;
    std::vector<double> mulvec;
    mulvec.assign((size_t) matSize, 0);
    for (int i = 0; i < this->numRow; i++){
        for (int j = 0; j < mat.numCol; j++) {
            double ans = 0.0;
            for (int k = 0; k < this->numCol; k++){
                ans = ans + this->getLoc(i,k) * mat.getLoc(k,j);
            }
            mulvec.at((unsigned long)i * (unsigned long)mat.numCol + (unsigned long)j) = ans;
        }
    }
    return Matrix(mulvec, this->numRow , mat.numCol);
 }

 Matrix Matrix::operator*=(double num){
  for(unsigned long i = 0 ; i < this->matrixData.size();i++){
         this->matrixData[i] =  this->matrixData[i] * num;
     }
     return *this;}
 

            
            // Comparison Operators:
            
bool zich::operator!=(const Matrix &mat1,const Matrix &mat2){
    Matrix::checkSizes(mat1 , mat2);
    for(unsigned long i = 0; i < mat1.matrixData.size(); i++){
        if(mat1.matrixData[i] != mat2.matrixData[i]){
            return true;
        }
    }
    return false;
}

bool zich::operator==(const Matrix &mat1,const Matrix &mat2){
    return !(mat1 != mat2);
}

bool zich::operator<=(const Matrix &mat1,const Matrix &mat2){
    Matrix::checkSizes(mat1 , mat2);
    double sumMat1 = Matrix::calculateSum(mat1);
    double sumMat2 = Matrix::calculateSum(mat2);
    return sumMat1 <= sumMat2;
}
bool zich::operator>=(const Matrix &mat1,const Matrix &mat2){
    Matrix::checkSizes(mat1 , mat2);
    double sumMat1 = Matrix::calculateSum(mat1);
    double sumMat2 = Matrix::calculateSum(mat2);
    return sumMat1 >= sumMat2;
}

bool zich::operator<(const Matrix &mat1,const Matrix &mat2){
    Matrix::checkSizes(mat1 , mat2);
    double sumMat1 = Matrix::calculateSum(mat1);
    double sumMat2 = Matrix::calculateSum(mat2);
    return sumMat1 < sumMat2;
}
bool zich::operator>(const Matrix &mat1,const Matrix &mat2){
   Matrix::checkSizes(mat1 , mat2);
    double sumMat1 = Matrix::calculateSum(mat1);
    double sumMat2 = Matrix::calculateSum(mat2);
    return sumMat1 > sumMat2;
}



// Increment Decrement Operators:

Matrix Matrix::operator--(){
    for(unsigned long i = 0; i < this->matrixData.size(); i++){
        this->matrixData.at(i) =this->matrixData.at(i)-1;
    }
    return *this;}
Matrix Matrix::operator--(int){
    Matrix copy = Matrix(this->matrixData,this->numRow,this->numCol);
    --*this;
    return copy;}

Matrix Matrix::operator++(){
    for(unsigned long i = 0; i < this->matrixData.size(); i++){
        this->matrixData.at(i) =this->matrixData.at(i)+1;
    }
    return *this;}
Matrix Matrix::operator++(int){
    Matrix copy = Matrix(this->matrixData,this->numRow,this->numCol);
    ++*this;
    return copy;}


// Friend Operators:

Matrix zich::operator*(double scalar,const Matrix &matrix){
    std::vector<double> mulvec;
    for(unsigned long i = 0; i < matrix.matrixData.size();i++){
        mulvec.push_back(scalar * matrix.matrixData.at(i)); 
    }
    return Matrix(mulvec,matrix.numRow,matrix.numCol);
}

   
    // I/O Operators:
    
std::ostream& zich::operator<<(std::ostream &out, const Matrix &matrix){
    std::string result;
    for (int row = 0; row < matrix.numRow; row++)
    {
        result += "[";
        for (int col = 0; col < matrix.numCol; col++)
        {
            result += to_string(int(matrix.getLoc(row,col)));
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

std::istream& zich::operator>>(std::istream& in, Matrix &matrix){
    
    string s;
    char ch = ' ';
    while((!in.eof())){
        in.get(ch);
        s+= ch;
    }

    if(s.find("] [")  != std::string::npos || s.find(",[")  != std::string::npos || s.find(",\n")  != std::string::npos ||
     s.find("  ")  != std::string::npos || s.find(",,")  != std::string::npos || s.find(" ]")  != std::string::npos ||
      s.find("[ ")  != std::string::npos || s.find("]]")  != std::string::npos || s.find("[[")  != std::string::npos){
        throw invalid_argument("input is not correct, 0");
    }

    string op1 = ", "; // between lines
    string op2 = " "; // between values
    string sign;
    string sNumber;
    double number = 0;

    if (s.find(op1) != std::string::npos){
        sign = s.substr(0, s.find(op1));
    }
    else{
        sign = s;
    }

    size_t columns = (unsigned long)std::count(sign.begin(), sign.end(), ' ')+(unsigned long)1;
    size_t rows = (unsigned long) std::count(s.begin(), s.end(), ']');

    std::vector<double> m;
    m.assign(rows*columns, 0);
    size_t location = 0;

    while(!s.empty()){
        if (s.find(op1) != std::string::npos){
           sign = s.substr(0, s.find(op1));
            if(sign.at(0) != '[' && sign.at(sign.length()-1) != ']'){
                throw invalid_argument("wrong input, 1");
            }
            sign=sign.substr(1, sign.length()-2);
        }
        else{
            sign = s;
            if(sign.at(0) != '[' && sign.at(sign.length()-2) != ']' && sign.at(sign.length()-1) != '\n'){
                throw invalid_argument("wrong input, 2");
            }
            sign = sign.substr(1, sign.find_first_of(']'));
            sign = sign.substr(0, sign.length()-1);
        }
        int counter = 0;
        while(!sign.empty()){
            if(counter >= columns){
                throw invalid_argument("wrong input");
            }
            sNumber = sign.substr(0, sign.find(op2));

            if (sign.find(op2) != std::string::npos){
                sNumber = sign.substr(0, sign.find(op2));
            }
            else{
                sNumber = sign;
            }
            if(!is_number(sNumber)){
                throw invalid_argument("wrong input");
            }
            number = stod(sNumber);
            m.at(location) = number;

            if (sign.find(op2) != std::string::npos){
                sign.erase(0, sign.find(op2) + op2.length());
            }
            else{
                sign= "";
            }
            counter++;
            location++;
        }
        if(counter < columns || !sign.empty()){
            throw invalid_argument("wrong input");
        }

        if (s.find(op1) != std::string::npos){
            s.erase(0, s.find(op1) + op1.length());   
        }
        else{
            s = "";
        }
    }
    matrix.numRow = rows;

    matrix.matrixData = m;

    matrix.numCol = columns;
    return in;
}

    