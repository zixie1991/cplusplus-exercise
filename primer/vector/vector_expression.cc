#include <vector>
#include <assert.h>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;
template<typename E>
class VecExpression {
    public:
        typedef vector<double> container_type;
        // 类型名是指这里最终要指出的是个类型名，而不是变量。
        // 例如container_type::size_type完全有可能是类container_type里
        // 的一个static对象。而且当我们这样写的时候，C++默认就是解释为
        // 一个变量的。所以，为了和变量区分，必须使用typename告诉编译器。
        typedef typename container_type::size_type size_type;
        typedef typename container_type::value_type value_type;
        typedef typename container_type::reference reference;
        size_type size() const { return static_cast<E const&>(*this).size(); }
        value_type operator[](size_type i) { return static_cast<E const&>(*this)[i]; }
        operator E&() { return static_cast<E&>(*this); }
        operator E const&() const { return static_cast<const E&>(*this); }
};
class Vec: public VecExpression<Vec> {
    public:
        Vec(size_type n): data_(n) {}
        template<typename E>
        Vec(VecExpression<E> const& vec) {
            E const& v = vec;
            data_.resize(vec.size());
            for (size_type i = 0; i != v.size(); i++) {
                data_[i] = v[i];
            }
        }
        
        size_type size() const { return data_.size(); }
        value_type operator[](size_type i) const { return data_[i]; }
        reference operator[](size_type i) { return data_[i]; }
    private:
        container_type data_;
};
template<typename E1, typename E2>
class VecDifference: public VecExpression<VecDifference<E1, E2> > {
    public:
        typedef Vec::size_type size_type;
        typedef Vec::value_type value_type;
        VecDifference(VecExpression<E1> const& u, VecExpression<E2> const& v): u_(u), v_(v) {
            assert(u.size() == v.size());
        }
        size_type size() const { return u_.size(); }
        value_type operator[](size_type i) const { return u_[i] - v_[i]; }
    private:
        E1 const& u_;
        E2 const& v_;
};
template<typename E>
class VecScaled: public VecExpression<VecScaled<E> > {
    public:
        typedef Vec::size_type size_type;
        typedef Vec::value_type value_type;
        VecScaled(double alpha, VecExpression<E> const& u): alpha_(alpha), u_(u) {}
        size_type size() const { return u_.size(); }
        value_type operator[](size_type i) const { return alpha_ * u_[i]; }
    private:
        double alpha_;
        E const& u_;
};
template<typename E1, typename E2>
VecDifference<E1, E2> operator-(VecExpression<E1> const& u, VecExpression<E2> const& v) {
    return VecDifference<E1, E2>(u, v);
}
template<typename E>
VecScaled<E> operator*(double alpha, VecExpression<E> const& u) {
    return VecScaled<E>(alpha, u);
}
int main() {
    Vec v1(10), v2(10);
    for (int i = 0; i < 10; i++) {
        v1[i] = i * i;
        v2[i] = i;
    }
    Vec v3 = 10 * (v1 - 2 * v2);
    for (int i = 0; i < 10; i++) {
        cout << v3[i] << " ";
    }
    cout << endl;
}
