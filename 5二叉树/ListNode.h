//#define Posi(T) ListNode<T>*  //列表结点位置，别名,不推荐
using Rank = int;
template <typename T> using ListNodePosi = ListNode<T>*; //推荐
template<typename T>
struct ListNode//列表结点模板类
{
    T data;
    ListNodePosi<T> pred;
    ListNodePosi<T> succ;
    //构造器
    ListNode() {}
    ListNode(T e, ListNodePosi<T> p = nullptr, Posi(T) s = nullptr) :data(e), pred(p), succ(p) {}

    ListNodePosi<T> insertAsPred(T const& e);//前插
    ListNodePosi<T> insertAsSucc(T const& e);//后插
};

//以下为实现
template<typename T>
ListNodePosi<T> ListNode<T>::insertAsPred(T const& e) {
    ListNodePosi<T> x = new ListNode(e, pred, this);
    pred->succ = x;pred = x;
    return x;
}
ListNodePosi<T> ListNode<T>::insertAsSucc(T const& e) {
    ListNodePosi<T> x = new ListNode(e, this, succ);
    succ->pred = x;succ = x;
    return x;
}

