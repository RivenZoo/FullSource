/* 二叉树（二叉树也可用于创建普通树）结点
 * QA Pass
 */

#ifndef _ENGINE_TREENODE_H_
#define _ENGINE_TREENODE_H_

template <class T>
class BinSTree;

template <class T>
class TreeNode
{
   protected:
      // 指向结点左右孩子的指针
      TreeNode<T> *left;
      TreeNode<T> *right;

   public:
      // 公有成员，允许外部修改的数据值
      T data;
   
      // 构造函数
	  TreeNode (const T& item, TreeNode<T> *lptr = NULL,
                TreeNode<T> *rptr = NULL);
   
      // 访问指针域的函数
      TreeNode<T>* Left() const;
      TreeNode<T>* Right() const;

      friend class BinSTree<T>;
};

// 构造函数，初始化结点的数据和指针域，对于空子树，将其指针域赋值为 NULL
template <class T>
TreeNode<T>::TreeNode (const T& item, TreeNode<T> *lptr,
    TreeNode<T> *rptr): data(item), left(lptr), right(rptr)
{}

// 允许用户访问左孩子
template <class T>
TreeNode<T>* TreeNode<T>::Left() const
{
   return left;
}

// 允许用户访问右孩子
template <class T>
TreeNode<T>* TreeNode<T>::Right() const
{
   return right;
}

#endif // _ENGINE_TREENODE_H_
