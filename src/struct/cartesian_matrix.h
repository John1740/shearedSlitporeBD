#ifndef CARTESIAN_MATRIX_H
#define CARTESIAN_MATRIX_H

#include "real_coordinate.h"

class CARTESIAN_MATRIX{
    //This is completely hard-coded to improve performance. Another (slower) concept, that has been tried, is:
    //CARTESIAN_COORDINATE x, y, z, accessing via (*this).x.x
    //Access of single components is fast, but any operator or constructor that uses a function of CARTESIAN_COORDINATE
    //is much slower.
    //
    //Same goes for the fact that the members here are public. Making them private and using getter- and
    //setter-functions slows down the program harshly.
    //
    //Arithmetic operators also don't refer to each other, which might seem redundant, but this also improves calculation
    //speed roughly by a factor 2.
public:
    double xx, xy, xz;
    double yx, yy, yz;
    double zx, zy, zz;

    //constructors
    CARTESIAN_MATRIX(): xx(0), xy(0), xz(0), yx(0), yy(0), yz(0), zx(0), zy(0), zz(0){}
    CARTESIAN_MATRIX(const double c): xx(c), xy(c), xz(c), yx(c), yy(c), yz(c), zx(c), zy(c), zz(c){}
    CARTESIAN_MATRIX(const REAL_C& col);
    CARTESIAN_MATRIX(const REAL_C& col1, const REAL_C& col2, const REAL_C& col3);
    CARTESIAN_MATRIX(const REAL_C& r1, const REAL_C& r2);
    CARTESIAN_MATRIX(const CARTESIAN_MATRIX& other);
    
    //functions
    double determinant() const;
    REAL_C diag() const;
    CARTESIAN_MATRIX& transposeInPlace();
    CARTESIAN_MATRIX transpose() const;
    CARTESIAN_MATRIX dot(const CARTESIAN_MATRIX& rhs);
    REAL_C dot(const REAL_C& rhs);
    
    //type cast operators?
    
    //index operators
    double operator()(unsigned int row, unsigned int col) const;
    double& operator()(unsigned int row, unsigned int col);
    //read-only
    REAL_C operator[](unsigned int row) const;
    REAL_C row(unsigned int i) const;
    REAL_C col(unsigned int i) const;
    
    //assignment operators
    CARTESIAN_MATRIX& operator=(const CARTESIAN_MATRIX& other);
    CARTESIAN_MATRIX& operator=(const double& c);
    
    CARTESIAN_MATRIX& operator+=(const CARTESIAN_MATRIX& other);
    CARTESIAN_MATRIX& operator+=(const double& c);
    
    CARTESIAN_MATRIX& operator-=(const CARTESIAN_MATRIX& other);
    CARTESIAN_MATRIX& operator-=(const double& c);
    
    CARTESIAN_MATRIX& operator*=(const CARTESIAN_MATRIX& other);
    CARTESIAN_MATRIX& operator*=(const double& c);
    
    CARTESIAN_MATRIX& operator/=(const CARTESIAN_MATRIX& other);
    CARTESIAN_MATRIX& operator/=(const double& c);
    
    //arithmetic operators
    friend CARTESIAN_MATRIX operator+(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs);
    friend CARTESIAN_MATRIX operator+(const double& lhs, const CARTESIAN_MATRIX& rhs);
    friend CARTESIAN_MATRIX operator+(const CARTESIAN_MATRIX& lhs, const double& rhs);
    
    friend CARTESIAN_MATRIX operator-(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs);
    friend CARTESIAN_MATRIX operator-(const double& lhs, const CARTESIAN_MATRIX& rhs);
    friend CARTESIAN_MATRIX operator-(const CARTESIAN_MATRIX& lhs, const double& rhs);
    
    friend CARTESIAN_MATRIX operator*(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs);
    friend CARTESIAN_MATRIX operator*(const double& lhs, const CARTESIAN_MATRIX& rhs);
    friend CARTESIAN_MATRIX operator*(const CARTESIAN_MATRIX& lhs, const double& rhs);
    
    friend CARTESIAN_MATRIX operator/(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs);
    friend CARTESIAN_MATRIX operator/(const double& lhs, const CARTESIAN_MATRIX& rhs);
    friend CARTESIAN_MATRIX operator/(const CARTESIAN_MATRIX& lhs, const double& rhs);
    
    //logical operators
    friend bool operator==(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs);
    friend bool operator!=(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs);
    
    //conversions
    //quiet slow
    boost::array<boost::array<double, 3>, 3> asArray() const;
    boost::array<double, 9> asFlatArray() const;
    //quiet fast
    vector<vector<double>> asVector() const;
    vector<double> asFlatVector() const;
    
    //stream handling
    friend ostream& operator<<(ostream& os, const CARTESIAN_MATRIX& A);
};

#endif // CARTESIAN_MATRIX_H
