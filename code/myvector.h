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
    T &operator[](Rank r) const { return _elem[r]; } //重载下标操作符，取代get()、set()操作
    myVector<T> &operator=(myVector<T> const &);     //重载赋值运算符，深度赋值
    //插入
    Rank insert(Rank r, T const &e);                     //插入元素
    Rank insert(T const &e) { return insert(_size, e); } //默认作为末元素插入
    //删除
    int remove(Rank lo, Rank hi); //删除区间[lo,hi)之内的元素
    T remove(Rank r);             //删除秩为r的元素
    //查找
    Rank find(T const &e, Rank lo, Rank hi) const;            //无序向量区间查找
    Rank find(T const &e) const { return find(e, 0, _size); } //无序向量整体查找

    //排序
    void sort(Rank lo, Rank hi);        //排序
    void unsort(Rank lo, Rank hi);      //以等概率随机置乱区间[lo,hi)
    void unsort() { unsort(0, _size); } //整体置乱
    int deduplicate();                  //无序向量去重
    int uniquify();                     //有序向量去重
    
    //遍历
    void traverse(void (*)(T &));//使用函数指针，只读或局部性修改
    template <typename VST>
    void traverse(VST &);//使用函数对象，可进行全局性修改
}//myVector

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
    if (_size << 2 > _capacity) //以25%为界，使用率高于25%，不调整；
        return;
    T *oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}

template <typename T>
void myVector<T>::unsort(Rank lo, Rank hi)
{
    T *V = _elem + lo;
    for (Rank i = hi - lo; i > 0; i--)
        swap(V[i--], V[rand() % i]); //随机置乱关键代码
}

template <typename T>
Rank myVector<T>::find(T const &e, Rank lo, Rank hi) const
{
    while ((lo < hi--) && e != _elem[hi])
        ;
    return hi;
}

template <typename T>
Rank myVector<T>::insert(Rank r, T const &e)
{
    expand();
    for (int i = _size; i > r; i--)
        _elem[i] = _elem[i - 1];
    _elem[r] = e;
    _size++;
    return r;
}

template <typename T>
int myVector<T>::remove(Rank lo, Rank hi)
{
    if (lo == hi)
        return 0;
    while (hi < _size)
    {
        _elem[lo++] = _elem[hi++];
    }
    _size = lo;
    shrink();
    return hi - lo;
}

template <typename T>
int myVector<T>::deduplicate()
{
    int oldSize = _size;
    Rank i = 1;
    while (i < _size)
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
    return oldSize - _size;
}

template <typename T>
void myVector<T>::traverse(void (*visit)(T &))
{
    for (int i = 0; i < _size;i++)
        visit(_elem[i]);
}

template<typename T>
template<typename VST>
void myVector<T>::traverse(VST& visit)
{
    for (int i = 0; i < _size;i++)
        visit(_elem[i]);
}