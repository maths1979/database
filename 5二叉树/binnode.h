#include "stack.h"
#include "queue.h"
#include"
//#define BinNodePosi(T) BinNode<T>*  //节点位置
template<typename T> using BinNodePosi = BinNode<T>*;
#define stature(p) ((p)?(p)->height:-1) //节点高度——约定空树高度为-1

/// 是否是根节点、是否是左子节点、是否是右子节点、是否是叶节点
#define isRoot(x) ( !( (x).parent ) )
#define isLChild(x) (!IsRoot(x) && ( & (x) == (x).parent->lChild ) )
#define isRChild(x) (!IsRoot(x) && ( & (x) == (x).parent->rChild ) )
#define hasParent(x) ( ! isRoot(x) )
//判断是否有孩子
#define hasLChild(x) ( (x).lChild!=NULL )  //判断节点x是否有左孩子
#define hasRChild(x) ( (x).rChild!=NULL ) //判断节点x 是否有右孩子
#define hasChild(x)  ( hasLChild(x) || hasRChild(x) )  //判断节点x是否有孩子（左、右至少有一个）
#define hasBothChild(x)  ( hasLChild(x) && hasRChild(x) ) //同时拥有两个孩子
//判断是否为叶节点
#define isLeaf(x)   ( ! hasChild(x) )   //判断节点x是否是叶子节点
#define sibling(p) ( isLChild( * (p)) ? (p)->parent->rChild : (p)->parent->lChild )//兄弟
#define uncle(x) ( isLChild( * (x)->parent )? (x)->parent->parent->rChild : (p)->parent->parent->lChild )//叔叔
#define FromParentTo(x) ( isRoot(x) ? _root : ( isLChild(x) ? (x)->parent->lChild : (x)->parent->rChild ) )
//typedef enum { RB_RED, RB_BLACK } RBColor;//节点颜色
template<typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi<T> x, VST& visit, Stack< BinNodePosi<T> >& S)
{///沿着左分支访问

    while (x)
    {
        visit(x->data);
        S.push(x->rChild);
        x = x->lChild;
    }    
}

template<typename T>
static void goAlongLeftBranch(BinNodePosi<T> x, Stack< BinNodePosi<T> >& S)
///
{
    while (x)
    {
        S.push(x);
        x = x->lChild;
    }
}

template<typename T>
static void gotoHLVFL(Stack< BinNodePosi<T> >& S)
///
{
    while (BinNodePosi<T> x=S.top())
    {
        if (hasLChild(*x)) {
            if (hasRChild(*x)) S.push(x->rChild);
            S.push(x->lChild);
        }
        else
            S.push(x->lChild);
    }
    S.pop();
}

template<typename T> struct BinNode
{
    T data;
    BinNodePosi<T> parent, lChild, rChild;//父节点及左右孩子
    int height;int size();//高度、子树规模
    //int npl;//Null Path Length （左式堆，也可直接用height代替）
    //构造函数
    BinNode() :parent(NULL), lChild(NULL), rChild(NULL), height(0) {}//会不会和下面的默认冲突？
    BinNode(T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL, BinNodePosi<T> rc = NULL, int h = 0) :
        data(e), parent(p), lChild(lc), rChild(rc), height(h) {}

    //操作接口
    BinNodePosi<T> insertAsLC(T const&);//作为左孩子插入新节点
    BinNodePosi<T> insertAsRC(T const&);//作为右孩子插入新节点
    BinNodePosi<T> succ();//（中序遍历意义下）当前节点的直接后继
    
    template<typename VST> void travPre_R(BinNodePosi<T>, VST&);//子树先序遍历(递归版)
    template<typename VST> void travPre_I1(BinNodePosi<T>, VST&);//子树先序遍历(迭代+栈)
    template<typename VST> void travPre_I2(BinNodePosi<T>, VST&);//子树先序遍历(迭代版2)    
    template<typename VST> void travPost_R(BinNodePosi<T>, VST&);//子树后续遍历(递归版)
    template<typename VST> void travPost_I(BinNodePosi<T>, VST&);//子树后续遍历(迭代版)
    template<typename VST> void travIn_R(BinNodePosi<T>, VST&);//子树中序遍历(递归版)
    template<typename VST> void travIn_I1(BinNodePosi<T>,VST&);//子树中序遍历(迭代版1)
    template<typename VST> void travIn_I2(BinNodePosi<T>, VST&);//子树中序遍历(迭代版2)
    template<typename VST> void travIn_I3(BinNodePosi<T>,VST&);//子树中序遍历(迭代版3)



    template<typename VST> void travLevel(VST&);//子树层次遍历
    template<typename VST> void travPre(VST&);//子树先序遍历    
    template<typename VST> void travIn(VST&);//子树中序遍历
    template<typename VST> void travPost(VST&);//子树后续遍历

    //比较器
    bool operator<(BinNode const& bn) { return data < bn.data; }//小于
    bool operator==(BinNode const& bn) { return data == bn.data; }//等于
};
template<typename T> 
BinNodePosi<T> BinNode<T>::insertAsLC(T const& e)//作为左孩子插入新节点
{
    return lChild = BinNode(e, this);
}
template<typename T> 
BinNodePosi<T> BinNode<T>::insertAsRC(T const& e)//作为右孩子插入新节点
{
    return rChild = BinNode(e, this);
}
template<typename T> 
int BinNode<T>::size()//后代总数，即以其为根的子树的规模
{
    int s = 1;
    if (lChild) s += lChild->size();
    if (rChild) s += rChild->size();
    return s;
}

template<typename T> 
BinNodePosi<T> BinNode<T>::succ()
{
    BinNodePosi<T> s = this;
    if (rChild) {
        s = rChild;
        while (hasLChild(*s)) s = s->lChild;
    }
    else {
        while (IsRChild(*s)) s = s->parent;        
        s = s->parent;
    }
    return s;
}

template<typename T>
template<typename VST>
void BinNode<T>::travPre_R(BinNodePosi<T> x , VST& visit)//子树先序遍历(递归版)
{
    if (!x) return;
    visit(x->data);
    travPre_R(x - lChild, visit);
    travPre_R(x->rChild, visit);
}

template<typename T>
template<typename VST>
void BinNode<T>::travPre_I1(BinNodePosi<T> x, VST& visit)//子树先序遍历(迭代+栈)
{
    Stack< BinNodePosi<T> > S;//辅助栈
    if (x) S.push(x);
    while (!S.empty())//在栈变为空之前反复循环
    {
        x = S.pop();visit(x->data);//弹出并访问当前节点
        if (hasRChild(*x)) S.push(x->rChild);//右孩子先进后出
        if (hasLChild(*x)) S.push(x->lChild);//左孩子后进先出
    }
}

template<typename T>
template<typename VST>
void BinNode<T>::travPre_I2(BinNodePosi<T> x, VST& visit)//子树先序遍历(迭代版2)
{
    Stack< BinNodePosi<T> > S;//辅助栈
    while (true)
    {
        visitAlongLeftBranch(x, visit, S);
        if (S.empty) break;
        x = S.pop();
    }    
}

template<typename T>
template<typename VST>
void BinNode<T>::travPost_R(BinNodePosi<T> x , VST& visit)//子树后序遍历(递归版)
{
    if (!x) return;    
    travPost_R(x - lChild, visit);
    travPost_R(x->rChild, visit);
    visit(x->data);
}

template<typename T>
template<typename VST>
void BinNode<T>::travPost_I(BinNodePosi<T> x , VST& visit)//子树后续遍历(迭代版)
{
    Stack< BinNodePosi<T>> S;
    if (x) S.push(x);
    while (!S.empty())
    {
        if (S.top != x->parent())
            gotoHLVFL(S);
        x = S.pop();visit(x->data);
    }
    
}

    
template<typename T>
template<typename VST>
void BinNode<T>::travIn_R(BinNodePosi<T> x , VST& visit)//子树中序遍历(递归版)
{
    if (!x) return;
    travIn_R(x - lChild, visit);
    visit(x->data);
    travIn_R(x->rChild, visit);
}

template<typename T>
template<typename VST>
void BinNode<T>::travIn_I1(BinNodePosi<T> x, VST& visit)//子树中序遍历(迭代版1)
{
    Stack< BinNodePosi<T> > S;
    while (true)
    {
        goAlongLeftBranch(x, S);
        if (S.empty()) break;
        x = S.pop();visit(x->data);
        x = x->rChild;
    }
    
}

template<typename T>
template<typename VST>
void BinNode<T>::travIn_I2(BinNodePosi<T> x, VST& visit)//子树中序遍历(迭代版2)
{
    Stack< BinNodePosi<T> > S;
    while (true)
    {
        if (x) {
            S.push(x);
            x = x->lChild;
        }
        else if (!S.empty()) {
            x=S.pop();
            visit(x->data);
            x = x->rChild;
        }
        else
            break;
    }
    
}

template<typename T>
template<typename VST>
void BinNode<T>::travIn_I3(BinNodePosi<T> x, VST& visit)//子树中序遍历(迭代版3)
{
    bool backtrack = false;
    while (true)
        if (!backtrack && hasLChild(*x)) x = x->lChild;
        else {
            visit(x->data);
            if (hasRChild(*x)) {
                x = x->rChild;
                backtrack = false;
            }
            else {
                if (!(x = x->succ()))break;
                backtrack = true;
            }
        }


}

template<typename T>
template<typename VST>
void BinNode<T>::travLevel(VST& visit)//子树层次遍历
{
    Queue< BinNodePosi<T> > Q;
    Q.enqueue(this);
    while (!Q.empty())
    {
        BinNodePosi<T> x = Q.dequeue();visit(x->data);
        if (hasLChild(*x)) Q.enqueue(x->lChild);//
        if (hasRChild(*x)) Q.enqueue(x->rChild);        
    }
    
}
