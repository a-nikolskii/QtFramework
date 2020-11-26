#ifndef QUADRATICEQUATION_H
#define QUADRATICEQUATION_H

#include "QtMath"
#include "vector"

enum RootCount {NO_REAL_ROOT,
                ONE_REAL_ROOT,
                TWO_REAL_ROOT,
                WRONG_SPECIFIE};

class QuadraticEquation
{
private:
    double m_a;
    double m_b;
    double m_c;
    double m_d;
    std::vector<double> m_roots;
    RootCount m_root_count;

    void getSolution();

public:
    QuadraticEquation(const double& a = 1, const double& b = 1, const double& c = 0);

    RootCount rootCount();
    std::vector<double> getRoot();

    void set_a(const double& a = 1);
    void set_b(const double& b = 1);
    void set_c(const double& c = 0);

    double get_a() const;
    double get_b() const;
    double get_c() const;

};

#endif // QUADRATICEQUATION_H
