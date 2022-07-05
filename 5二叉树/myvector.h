#include<stdlib.h>
using Rank = int;
#define DEFAULT_CAPACITY 3

template<typename T> 
class Vector
{
protected:
    Rank _size;//实际使用的空间数量
    Rank _capacity;//预分配可供使用的最大空间数量
    T* _elem;//指向实际分配空间
    void copyFrom(T const* A, Rank lo, Rank hi);//复制数组区间A[lo,hi)
    void expand();//空间不足时扩容
    void shrink();//装填因子过小时压缩

    void bubble(Rank lo, Rank hi);//扫描交换
    void bubbleSort(Rank lo, Rank hi);//起泡排序算法
    Rank maxItem(Rank lo, Rank hi);//选取最大元素
    void selectionSort(Rank lo, Rank hi);//选择排序算法
    void merge(Rank lo, Rank mi, Rank hi);//归并算法
    void mergeSort(Rank lo, Rank hi);//归并排序算法
    void heapSort(Rank lo, Rank hi);//堆排序
    Rank partition(Rank lo, Rank hi);//轴点构造算法
    void quickSort(Rank lo, Rank hi);//快速排序算法
    void shellSort(Rank lo, Rank hi);//希尔排序算法

public:
    //构析函数
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)//容量c,规模为s,所有元素设为v
    {
        _elem = new T[_capacity = c];
        for (_size = 0;_size < s;_elem[_size++]=v);
    }
    Vector(T const* A, Rank n) { copyFrom(A, 0, n); }//数组整体赋值
    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }//数组区间复制
    Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }//向量整体复制
    Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }//向量区间复制
    ~Vector() { delete[]_elem; }//释放内部空间

    
    Rank size() const { return _size; }//返回数据规模
    bool empty()const { return !_size; }//判断是否为空
    //实现get 、put(r,e)功能
    T& operator[](Rank r){ return _elem[r]; }//重载下标操作符
    const T& operator[](Rank r)const{ return _elem[r]; }//重载下标操作符，仅限做右值
    Vector<T>& operator=(Vector<T> const&);
    //实现insert(r,e)功能
    Rank insert(Rank r, T const& e);//插入元素
    Rank insert(T const& e) { return insert(_size, e); }//在末尾插入元素
    //remove(r)
    int remove(Rank lo, Rank hi);//删除秩在区间[lo,hi) 之内的元素
    T remove(Rank r);//删除秩为r的元素
    //sort()排序功能
    void sort(Rank lo, Rank hi);
    void sort() { sort(0, _size); }
    Rank disordered()const;//判断是否有序
    void unsort(Rank lo, Rank hi);//对[lo,hi)打乱
    void unsort() { unsort(0, _size); }//对整体打乱
    //find无序向量查找
    Rank find(T const& e)const { return find(e, 0, _size); }//无序向量整体查找
    Rank find(T const& e, Rank lo, Rank hi)const;//无序向量区间查找
    //search有序向量查找
    Rank search(T const& e, Rank lo, Rank hi)const;//无序向量区间查找
    Rank search(T const& e)const { return search(e, 0, _size); }//有序向量整体查找
    //去重
    Rank deduplicate();//无序向量去重
    Rank uniquify();//有序向量去重
    //遍历
    void traverse(void (*)(T&));//使用函数指针，只读或局部性修改
    template <typename VST> void traverse(VST&);//使用函数对象，可全局性修改
};
template<typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo<hi)
    {
        _elem[_size++] = A[lo++];
    }
    
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
    if (_elem) delete[] _elem;
    copyFrom(V._elem, 0, V.size());
    return *this;
}

template<typename T>
void Vector<T>::expand()
{
    if (_size < _capacity) return;
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;//_capacity = max(_capacity, DEFAULT_CAPACITY);
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0;i < _size;i++)
        _elem[i] = oldElem[i];
    delete[]  oldElem;
}

template<typename T>
void Vector<T>::shrink()
{
    if (_capacity < DEFAULT_CAPACITY << 1) return;
    if (_size << 2 > _capacity)return;
    T* oldElem = _elem;
    _elem = new T[_capacity >> 1];
    for (int i = 0;i < _size;i++)_elem[i] = oldElem[i];
    delete[] oldElem;
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
    T* V = _elem + lo;
    for (Rank i = hi - lo;i >=0;i--)
        swap(V[i], V[rand() % i]);
}

template<typename T>
Rank Vector<T>::disordered()const
{
    Rank n = 0;
    for (Rank i = 1;i < _size;i++)
        if (_elem[i - 1] > _elem[i]) n++;
    return n;
}
template<typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi)const
{
    while ((lo < hi--) && e != _elem[hi]);
    return hi;
}

template<typename T>
Rank Vector<T>::insert(Rank r, T const& e)
{
    expand();
    for (Rank i = _size;r < i;i--) _elem[i] = _elem[i - 1];
    _elem[r] = e;
    _size++;
    return r;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
    if (lo == hi) return 0;
    while (hi < _size) _elem[lo] = _elem[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}

template<typename T>
T Vector<T>::remove(Rank r)
{
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

template<typename T>
Rank Vector<T>::deduplicate()
{
    int oldSize = _size;
    Rank i = 1;
    while (i < _size)
        (find(_elem[i], 0, i) < 0) ? i++:remove(i);
    return oldSize - _size;
}

template<typename T>
void Vector<T>::traverse(void (*visit)(T&))
{
    for (int i = 0;i < _size;i++)
        visit(_elem[i]);
}

template<typename T>
template <typename VST>
void Vector<T>::traverse(VST& visit)
{
    for (int i = 0;i < _size;i++)
        visit(_elem[i]);
}