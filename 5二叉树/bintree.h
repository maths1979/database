#include"binnode.h"
#include"release.h"
#include"stack.h"



template<typename T> class BinTree {
protected:
    int _size;//规模
    BinNodePosi<T> _root;//根节点

    
    virtual int updateHeight(BinNodePosi<T> x);//更新节点x的高度，不同二叉树可能对高度的定义和更新有所不同，可能需要重写，因此定义为virtual
    void updateHeightAbove(BinNodePosi<T> x);//更新x及祖先的高度
public:

    //构析函数
    BinTree() :_size(0), _root(NULL) {}
    ~BinTree() { if (0 < _size)remove(_root); }
    int size()const { return _size; }//规模
    bool empty()const { return !_root; }//判空
    BinNodePosi<T> root() const { return _root; }//树根

    //子树接入、删除和分离接口
    BinNodePosi<T> insertAsRoot(T const&);//作为根节点插入
    BinNodePosi<T> insert(T const&, BinNodePosi<T>); //插入左孩子 insertAsLC
    BinNodePosi<T> insert(BinNodePosi<T>, T const&); //插入右孩子 insertAsRC
    BinNodePosi<T> attach(BinTree<T>*&, BinNodePosi<T>); //接入左子树
    BinNodePosi<T> attach(BinNodePosi<T>, BinTree<T>*&); //接入右子树
    int remove(BinNodePosi<T>);//子树删除
    static int removeAt(BinNodePosi<T>);//递归删除x及其后代
    BinTree<T>* secede(BinNodePosi<T>);//子树分离
    //遍历接口
    template<typename VST> void travLevel(VST& visit)//层次遍历
    {
        if (_root) _root->travLevel(visit);
    }
    template<typename VST> void travPre(VST& visit)//先序遍历
    {
        if (_root)_root->travPre(visit);
    }
    template<typename VST> void travIn(VST& visit)//中序遍历
    {
        if (_root)_root->travIn(visit);
    }
    template<typename VST> void travPost(vst& visit)//后续遍历
    {
        if (_root)_root->travPost(visit);
    }


    bool operator<(BinTree<T> const& t) {//比较器<
        return _root && t.root && lt(_root,t._root);
    }
        bool operator==(BinTree<T> const& t) {//比较器<
        return _root && t.root && _root==t._root;
    }
};//BinTree
template<typename T>
int BinTree<T>::updateHeight(BinNodePosi<T> x)
{
    return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
}
template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi<T> x)
{
    while (x)//可优化；一旦高度未变，即可终止
    {
        updateHeight(x);x = x->parent;
    }
}

template<typename T>
BinNodePosi<T> BinTree<T>::insertAsRoot(T const&)//作为根节点插入
{
    _size = 1;return _root = new BinNode<T>(e);
}

template<typename T>
BinNodePosi<T> BinTree<T>::insert(BinNodePosi<T> x, T const& e)
{
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rChild;
}
template<typename T>
BinNodePosi<T> BinTree<T>::insert(T const& e, BinNodePosi<T> x)
{
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lChild;
}

template<typename T>
BinNodePosi<T> BinTree<T>::attach(BinNodePosi<T> x, BinTree<T>*& S) {
    if (x->rChild = S->_root) x->rChild->parent = x;
    _size += S->_size;
    updateHeightAbove(x);

    S->_root = NULL;S->_size = 0;
    release(S);S = NULL;
    return x;
}

template<typename T>
BinNodePosi<T> BinTree<T>::attach(BinTree<T>*& S, BinNodePosi<T> x) {
    if (x->lChild = S->_root) x->lChild->parent = x;
    _size += S->_size;
    updateHeightAbove(x);

    S->_root = NULL;S->_size = 0;
    release(S);S = NULL;
    return x;
}
template<typename T>
static int BinTree<T>::removeAt(BinNodePosi<T> x)
{
    if (!x) return 0;
    int n = 1 + removeAt(x->lChild) + removeAt(x->rChild);
    release(x->data);release(x);
    return n;
}
template<typename T>
int BinTree<T>::remove(BinNodePosi<T> x)
{
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);
    int n = removeAt(x);_size -= n;return n;
}

template<typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi<T> x)
{
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);

    BinTree<T>* S = new BinTree<T>;
    S->_root = x;x->parent = NULL;
    S->_size = x->size();_size -= S->_size;
    return S;
}
// template<typename T>
// template<typename VST>
// void BinTree<T>::travPre(BinNodePosi<T> x, VST& visit)//先序遍历，递归形式
// {
//     if (!x) return;
//     visit(x->data);
//     travPre(x->lChild, visit);
//     travPre(x->rChild, visit);
// }

// template<typename T>
// template<typename VST>
// void BinTree<T>::travPre1(BinNodePosi<T> x, VST& visit)//先序遍历，迭代形式1
// {
//     Stack<BinNodePosi<T>> S;//辅助栈
//     if (x) S.push(x);//根节点入栈
//     while (!S.empty())
//     {
//         x = S.pop();visit(x->data);
//         if (hasRChild(x))S.push(x->rChild);
//         if (hasLChild(x))S.push(x->lChild);
//     }
// }

// template<typename T>
// template<typename VST>
// void BinTree<T>::travPre2(BinNodePosi<T> x, VST& visit)//先序遍历，迭代形式1
// {
//     Stack<BinNodePosi<T>> S;//辅助栈
//     while (true)
//     {
//         visitAlongLeftBranch(x, visit, S);
//         if (S.empty()) break;
//         x = S.pop();
//     }    
// }