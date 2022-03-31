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
    ListNode(T e, Posi(T) p = nullptr, Posi(T) s = nullptr) :data(e), pred(p), succ(p) {}

    ListNodePosi<T> insertAsPred(T const& e);//前插
    ListNodePosi<T> insertAsSucc(T const& e);//后插
};

