#include <cmath>
#include <iostream>
#define SPACE ' '

 class Vector3{
public:
    double x, y, z;

    Vector3(double x, double y, double z) : x(x), y(y), z(z) {};

    friend double abs(const Vector3 &v);


    Vector3 operator+ (const Vector3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vector3 operator- (const Vector3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vector3 operator* (double a) const {
        return {a * x, a * y, a * z};
    }

    friend Vector3 operator* (double a, const Vector3 &v) {
        return {a * v.x, a * v.y, a * v.z};
    }

     Vector3 operator/ (double a) const {
        if (a == 0)
            throw std::runtime_error("Zero division error.");
        else
            return {x/a, y/a, z/a};
    }

    friend std::istream& operator>>(std::istream& is, Vector3& v){
        is >> v.x >> v.y >> v.z;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3& v){
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }

    [[nodiscard]] Vector3 cross(const Vector3& other) const {
        double minor1 = y * other.z - z * other.y;
        double minor2 = x * other.z - z * other.x;
        double minor3 = x * other.y - y * other.x;
        return {minor1, -minor2, minor3};
    }

    [[nodiscard]] double dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

     [[nodiscard]] double norm() const{
         return sqrt(x*x + y*y + z*z);
     }

 };

class Matrix3{
public:
    Vector3 v1, v2, v3;

    Matrix3(Vector3 v1, Vector3 v2, Vector3 v3): v1(v1), v2(v2), v3(v3){};


    static Matrix3 ZeroMatrix(){
        return {Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0)};
    }

    static Matrix3 OneMatrix(){
        return {Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1)};
    }

    friend double abs(const Matrix3& M);

    Matrix3 operator+ (const Matrix3& other) const {
        return {v1 + other.v1, v2 + other.v2, v3 + other.v3};
    }

    Matrix3 operator- (const Matrix3& other) const {
        return {v1 - other.v1, v2 - other.v2, v3 - other.v3};
    }

    Matrix3 operator* (const Matrix3& other) const {
        Vector3 row1(v1.x, v2.x, v3.x);
        Vector3 row2(v1.y, v2.y, v3.y);
        Vector3 row3(v1.z, v2.z, v3.z);

        double a11 = row1.dot(other.v1);
        double a12 = row1.dot(other.v2);
        double a13 = row1.dot(other.v3);

        double a21 = row2.dot(other.v1);
        double a22 = row2.dot(other.v2);
        double a23 = row2.dot(other.v3);

        double a31 = row3.dot(other.v1);
        double a32 = row3.dot(other.v2);
        double a33 = row3.dot(other.v3);

        return {Vector3(a11, a21, a31), Vector3(a12, a22, a32), Vector3(a13, a23, a33)};
    }

    Vector3 operator*(const Vector3& vec) const{
        double c1 = v1.x * vec.x + v2.x * vec.y + v3.x * vec.z;
        double c2 = v1.y * vec.x + v2.y * vec.y + v3.y * vec.z;
        double c3 = v1.z * vec.x + v2.z * vec.y + v3.z * vec.z;
        return {c1, c2, c3};
    }

    Matrix3 operator*(double a) const{
        return {a * v1, a * v2, a * v3};
    }

    friend Matrix3 operator*(double a, const Matrix3& M) {
        return {M.v1 * a, M.v2 * a, M.v3 * a};
    }

    [[nodiscard]] double frobenius_norm() const {
        return sqrt(v1.x * v1.x + v2.x * v2.x + v3.x * v3.x + v1.y * v1.y + v2.y * v2.y + v2.z * v2.z + v3.x * v3.x
        + v3.y * v3.y + v3.z * v3.z);
    }

    [[nodiscard]] double det() const {
        double minor1 = v1.x * (v2.y * v3.z - v2.z * v3.y);
        double minor2 = -v2.x * (v1.y * v3.z - v3.y * v1.z);
        double minor3 = v3.x * (v1.y * v2.z - v1.z * v2.y);
        return minor1 + minor2 + minor3;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix3& M){
        os << M.v1.x << SPACE << M.v2.x << SPACE << M.v3.x << '\n' << M.v1.y << SPACE << M.v2.y << SPACE << M.v3.y << '\n'
        << M.v1.z << SPACE << M.v2.z << SPACE << M.v3.z;
        return os;
    }
};

double abs(const Vector3 &v){
    return v.norm();
}

double abs(const Matrix3 &M){
    return M.frobenius_norm();
}

int main(){
    Vector3 v1(1, 2, 3);
    Vector3 v2(4, 5, 6);
    Vector3 v3(1, 2, 3);




    Matrix3 M1(v1, v2, v3);
    Matrix3 Identity = Matrix3::OneMatrix();
    Matrix3 Nilpotent = Matrix3::ZeroMatrix();



    std::cout << abs(v1) << std::endl;
    //std::cout << v1 + v2;
    std::cout << v1.cross(v2) << std::endl;
    std::cout << v1.dot(v2) << std::endl;

    std::cout << M1.det() << std::endl;
    //std::cout << M1 << std::endl;
    std::cout << M1.frobenius_norm() << std::endl;

    std::cout << abs(M1) << std::endl;
    std::cout << M1 * Identity << std::endl;
    std::cout << M1 * Nilpotent << std::endl;
    std::cout << Nilpotent.det() << std::endl;
    std::cout << Identity.det() << std::endl;
    std::cout << Identity * v1 << std::endl;
    std::cout << 4 * Identity << std::endl;
    std::cout << Identity * 4 << std::endl;

}