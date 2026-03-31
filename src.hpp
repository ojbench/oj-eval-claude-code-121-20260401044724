#ifndef SJTU_COMPLEX_HPP
#define SJTU_COMPLEX_HPP

#include <iostream> // 输入输出
#include <iomanip>  // 控制输出格式
#include <cmath>    // 数学函数
#include <stdexcept> // 异常处理
// 你不可以使用任何其他的头文件!


namespace sjtu {

// 异常类，你需要要添加一个函数 what() 来返回异常信息。
class divided_by_zero final : public std::exception {
  public:
    divided_by_zero()   = default;
    ~divided_by_zero()  = default;
    const char* what() const noexcept override {
        return "complex divided by zero!";
    }
};

// 用于判断浮点数的符号.
inline int sign(double x) {
    const double eps = 1e-6;
    return (x > eps) - (x < -eps);
}

// 请保留所有的接口声明，即使你没有实现它们。
// 否则可能出现编译错误，无法通过部分测试点。
// TODO 补全类的实现
class complex {
  private:
    double a, b; // a + bi
  public:

    // 默认构造函数 0+0i
    complex() : a(0.0), b(0.0) {}

    // 构造函数 a+0i
    complex(double a) : a(a), b(0.0) {}

    // 构造函数 a+bi
    complex(double a, double b) : a(a), b(b) {}

    // 返回实部
    double &real() { return a; }

    // 返回虚部
    double &imag() { return b; }

    // 返回负数
    complex operator - () const {
        return complex(-a, -b);
    }

    // 返回共轭复数
    complex operator ~ () const {
        return complex(a, -b);
    }

    // 加法
    complex operator + (const complex &rhs) const {
        return complex(a + rhs.a, b + rhs.b);
    }

    // 减法
    complex operator - (const complex &rhs) const {
        return complex(a - rhs.a, b - rhs.b);
    }

    // 乘法: (a+bi)*(c+di) = (ac-bd) + (ad+bc)i
    complex operator * (const complex &rhs) const {
        return complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a);
    }

    // 除法: (a+bi)/(c+di) = [(a+bi)*(c-di)] / (c^2+d^2)
    complex operator / (const complex &rhs) const {
        // 检查除数是否为0
        if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
            throw divided_by_zero();
        }
        double denominator = rhs.a * rhs.a + rhs.b * rhs.b;
        return complex((a * rhs.a + b * rhs.b) / denominator,
                      (b * rhs.a - a * rhs.b) / denominator);
    }

    complex &operator += (const complex &rhs) {
        a += rhs.a;
        b += rhs.b;
        return *this;
    }

    complex &operator -= (const complex &rhs) {
        a -= rhs.a;
        b -= rhs.b;
        return *this;
    }

    complex &operator *= (const complex &rhs) {
        double new_a = a * rhs.a - b * rhs.b;
        double new_b = a * rhs.b + b * rhs.a;
        a = new_a;
        b = new_b;
        return *this;
    }

    complex &operator /= (const complex &rhs) {
        // 检查除数是否为0
        if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
            throw divided_by_zero();
        }
        double denominator = rhs.a * rhs.a + rhs.b * rhs.b;
        double new_a = (a * rhs.a + b * rhs.b) / denominator;
        double new_b = (b * rhs.a - a * rhs.b) / denominator;
        a = new_a;
        b = new_b;
        return *this;
    }

    // 判断相等
    bool operator == (const complex &rhs) const {
        return (sign(a - rhs.a) == 0) && (sign(b - rhs.b) == 0);
    }

    // 转换为 bool
    explicit operator bool() const {
        return !(sign(a) == 0 && sign(b) == 0);
    }

    // 输出
    friend std::ostream &operator << (std::ostream &os, const complex &x) {
        // 设置输出精度为6位小数
        os << std::fixed << std::setprecision(6);

        // 处理实部和虚部，当绝对值小于eps时设为0
        double real_part = (sign(x.a) == 0) ? 0.0 : x.a;
        double imag_part = (sign(x.b) == 0) ? 0.0 : x.b;

        // 输出实部
        os << real_part;

        // 输出虚部
        if (sign(imag_part) < 0) {
            os << imag_part << "i";
        } else {
            os << "+" << imag_part << "i";
        }

        return os;
    }
};

}

#endif
