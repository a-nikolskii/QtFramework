#include "quadraticequation.h"

QuadraticEquation::QuadraticEquation(const double& a,
                                     const double& b,
                                     const double& c) :  m_a(a), m_b(b), m_c(c)
{
    getSolution();
}


RootCount QuadraticEquation::rootCount(){return m_root_count;};


std::vector<double> QuadraticEquation::getRoot(){return m_roots;};


void QuadraticEquation::set_a(const double& a){
    m_a = a;
    getSolution();
};


void QuadraticEquation::set_b(const double& b){
    m_b = b;
    getSolution();
};


void QuadraticEquation::set_c(const double& c){
    m_c = c;
    getSolution();
};


double QuadraticEquation::get_a(){return m_a;};
double QuadraticEquation::get_b(){return m_b;};
double QuadraticEquation::get_c(){return m_c;};


void QuadraticEquation::getSolution(){

    m_roots.clear();

    m_d = pow(m_b,2) - 4 * m_a * m_c;

    if (m_a == 0) {
        if (m_b == 0) {
            m_root_count = WRONG_SPECIFIE;
            return;
        }
        else {
            m_roots.push_back( -m_c / m_b);
            m_root_count = ONE_REAL_ROOT;
            return;
        }
    }

    else if (m_d < 0) {
        m_root_count = NO_REAL_ROOT;
        return;
    }

    else if (m_d == 0) {
        m_roots.push_back( -m_b / (2 * m_a) );
        m_root_count = ONE_REAL_ROOT;
        return;
    }

    else {
        m_roots.push_back( (-m_b + sqrt(m_d)) / (2 * m_a) );
        m_roots.push_back( (-m_b - sqrt(m_d)) / (2 * m_a) );
        m_root_count = TWO_REAL_ROOT;
        return;
    }
}
