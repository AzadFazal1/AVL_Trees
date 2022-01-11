

#include "avl_tree.h"

template <class K, class V>
const V& avl_tree<K, V>::find(const K& key) const
{
    return find(root_.get(), key);
}

template <class K, class V>
const V& avl_tree<K, V>::find(const node* subtree, const K& key) const
{
    if (!subtree)
    {
        throw std::out_of_range{"invalid key"};
    }
    else if (key == subtree->key)
    {
        return subtree->value;
    }
    else if (key < subtree->key)
    {
        return find(subtree->left.get(), key);
    }
    else
    {
        return find(subtree->right.get(), key);
    }
}

template <class K, class V>
void avl_tree<K, V>::rotate_left(std::unique_ptr<node>& t)
{
        *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
auto k2 = std::move(t->right);
        t->right = std::move(k2->left);
        t->height = std::max(heightOrNeg1(t->left.get()), heightOrNeg1(t->right.get())) + 1;
        k2->height = std::max(heightOrNeg1(k2->right.get()), t->height) + 1;
        k2->left = std::move(t);
        t = std::move(k2);
    

    /// @todo Your code here
    
}

template <class K, class V>
void avl_tree<K, V>::rotate_left_right(std::unique_ptr<node>& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:
    rotate_left(t->left);
    rotate_right(t);
}

template <class K, class V>
void avl_tree<K, V>::rotate_right(std::unique_ptr<node>& t)
{
        *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    auto k1 = std::move(t->left);
        t->left = std::move(k1->right);
        t->height = std::max(heightOrNeg1(t->left.get()), heightOrNeg1(t->right.get())) + 1;
        k1->height = std::max(heightOrNeg1(k1->left.get()), t->height) + 1;
        k1->right = std::move(t);
        t = std::move(k1);
    /// @todo Your code here
}

template <class K, class V>
void avl_tree<K, V>::rotate_right_left(std::unique_ptr<node>& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    /// @todo Your code here
    rotate_right(t->right);
    rotate_left(t);

}

template <class K, class V>
void avl_tree<K, V>::insert(K key, V value)
{
    insert(root_, std::move(key), std::move(value));
}

template <class K, class V>
void avl_tree<K, V>::insert(std::unique_ptr<node>& subtree, K key, V value)
{
    /// @todo Your code here
    if (!subtree)
       {
subtree = std::make_unique<node>(std::move(key), std::move(value));
}
else if (key < subtree->key) {
insert(subtree->left, key, value);
}
else
{
    insert(subtree->right, key, value);
}
subtree->height = 1 + std::max(heightOrNeg1(subtree->left.get()), heightOrNeg1(subtree->right.get()));
rebalance(subtree);
}

template <class K, class V>
void avl_tree<K, V>::rebalance(std::unique_ptr<node>& subroot)
{
    /// @todo Your code here
    auto balance = heightOrNeg1(subroot->left.get()) - heightOrNeg1(subroot->right.get());
       if (balance == 2)
       {
rebalance_left(subroot);}
else if (balance == -2) {
rebalance_right(subroot);
}
subroot->height = 1 + std::max(heightOrNeg1(subroot->left.get()), heightOrNeg1(subroot->right.get()));
}

template <class K, class V>
void avl_tree<K, V>::rebalance_left(std::unique_ptr<node>& subroot)
{
    /// @todo Your code here
    auto c_balance = heightOrNeg1( subroot->left->left.get()) - heightOrNeg1(subroot->left->right.get());
    c_balance >= 0 ? rotate_right(subroot) :rotate_left_right(subroot);
}

template <class K, class V>
void avl_tree<K, V>::rebalance_right(std::unique_ptr<node>& subroot)
{
    /// @todo Your code here
    auto c_balance = heightOrNeg1( subroot->right->left.get()) - heightOrNeg1(subroot->right->right.get());
    c_balance <= 0 ? rotate_left(subroot) :rotate_right_left(subroot);
}
