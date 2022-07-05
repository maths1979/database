#include"list.h"
#include<list>
template<typename T>
class Stack2 :public List<T> {//由向量派生的模板类
public://size()、empty()可直接沿用
    void push(T const& e) { insertAsFirst(e); }//入栈
    T pop() { return remove(header->succ); }//出栈
    T& top() { return header->succ->data; }//取顶
};