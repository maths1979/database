#include"myvector.h"

template<typename T>
class Stack :public Vector<T> {//由向量派生的模板类
public://size()、empty()可直接沿用
    void push(T const& e) { this->insert(this->size(), e); }//入栈
    T pop() { return this->remove(this->size() - 1); }//出栈
    T& top() { return (*this)[this->size() - 1]; }//取顶
};