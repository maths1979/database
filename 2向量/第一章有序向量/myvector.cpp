#include "myvector.h"
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
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1];
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
    for (Rank i = hi - lo;i >= ;i--)
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
    for (i = _size;r < i;i--) _elem[i] = _elem[i - 1];
    _elem[r] = e;
    _size++;
    return r;
}
template<typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
    if (low == hi) return 0;
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
        (find(_elem[i], 0, i) < 0) ? i++;remove(i);
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