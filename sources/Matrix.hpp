#include <string>
#include <map>
#include <iterator>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

namespace zich{
    class Matrix{
        std::vector<double> matrixData;
        int numCol;
        int numRow;
        
        public:

        Matrix();
        Matrix(std::vector<double> matrix, int rows , int columns){
            if(rows * columns != matrix.size()){
                throw invalid_argument( "rows and columns are not suitable to the matrix length");
            }
            if(columns< 0 || rows < 0){
               throw invalid_argument( "rows or columns are negative"); 
            }
            this->matrixData = matrix;
            this->numCol = columns;
            this->numRow = rows;
        }
        // ~Matrix(){}
        
        public:
            void static checkSizes(const Matrix& mat1 ,const Matrix& mat2 );
            double getVal(int row,int col)const;
            double static calculateSum(const Matrix& mat);
            double getLoc(int row, int column)const;
            bool is_number(const std::string& s);
        
            // Arithmetic Operators:
            

            Matrix operator-() const;
            Matrix operator-(const Matrix &matrix);
            Matrix operator-=(const Matrix &matrix);

            Matrix operator+() const;
            Matrix operator+(const Matrix &matrix);
            Matrix operator+=(const Matrix &matrix);

            Matrix operator*(double num) const;
            Matrix operator*=(const Matrix &mat);
            Matrix operator*(const Matrix &mat)const;
            Matrix operator*=(double num);

            
            // Comparison Operators:
            

            friend bool operator!=(const Matrix &mat1,const Matrix &mat2);

            friend bool operator==(const Matrix &mat1,const Matrix &mat2);

            friend bool operator<=(const Matrix &mat1,const Matrix &mat2);
            friend bool operator>=(const Matrix &mat1,const Matrix &mat2);

            friend bool operator<(const Matrix &mat1,const Matrix &mat2);
            friend bool operator>(const Matrix &mat1,const Matrix &mat2);


            
            // Increment Decrement Operators:
        

            Matrix operator--();
            Matrix operator--(int number);

            Matrix operator++();
            Matrix operator++(int number);

            
            // Friend Operators:
            

            friend Matrix operator*(double scalar,const Matrix &matrix);
            
                
                // I/O Operators:
                
            friend std::ostream& operator<<(std::ostream &out, const Matrix &matrix);
            friend std::istream& operator>>(std::istream& in, Matrix &matrix);
    };
}