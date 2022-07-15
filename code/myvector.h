// typedef int Rank;
using Rank = int;
#define DEFAULT_CAPACITY 3

template <typename T>
class myVector
{
protected:
    Rank _size;
    int _capacity;
    T *_elem;

    void copyFrom(T const *A, Rank lo, Rank hi); //复制数组区间
    void expend();                               //空间不足时扩容，倍增策略
    void shrink();                               //空间太多时，如果使用率低于25%，减半策略

public:
    //构造、析构函数
    myVector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //容量为c，规模为s，所有元素初始为v
    {
        _elem = new T[_capacity = c];
        _size = 0;
    }
    myVector(T const *A, Rank n) { copyFrom(A, 0, n); }                                  //数组整体复制
    myVector(T const *A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }                      //数组区间复制
    myVector(myVector<T> const &V) { copyFrom(V._elem, 0, V.size()); }                   //向量整体复制
    myVector(myVector<T> const &V, Rank lo, Rank hi) { copyFrom(V._elem, 0, V.size()); } //向量区间复制
    ~myVector(){delete[] _elem};

    //只读访问接口
    Rank size() const { return _size; }   //规模
    bool empty() const { return !_size; } //判空
    //可写访问接口
    T &operator[](Rank r) const { return _elem[r]; } //重载下标操作符
    myVector<T> &operator=(myVector<T> const &);     //重载赋值运算符，深度赋值

}

template <typename T>
void myVector<T>::copyFrom(T const *A, Rank lo, Rank hi)
{
    _elem = new T[_capacity = 2 * (hi - lo)]; //分配空间
    _size = 0;                                //规模清零
    for (int i = 0; i < hi - lo; i++)         // A[lo,hi)整体复制
        _elem[size++] = A[i++];
    // while(lo<hi)
    //     _elem[size++] = A[lo++];
}

template <typename T>
myVector<T> &myVector<T>::operator=(myVector<T> const &V)
{
    if (_elem)
        delete[] _elem;
    copyFrom(V._elem, 0, V.size());
    return *this;
}

template <typename T>
void myVector<T>::expend()
{
    if (_size < _capacity)
        return;
    _capacity = max(_capacity, DEFAULT_CAPACITY);
    T *oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}

template <typename T>
void myVector<T>::shrink()
{
    if (_capacity < DEFAULT_CAPACITY)
        return;
    if (_size << 2 > _capacity)//以25%为界，使用率高于25%，不调整；
        return;
    T *oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}
