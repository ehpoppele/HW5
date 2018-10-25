#include <assert.h>
#include "tree.hh"

tree_ptr_t create_tree(const key_t& key,
                       const value_t& value,
                       tree_ptr_t left,
                       tree_ptr_t right)
{
    return new Tree({key, value, left, right});
}
                       
void destroy_tree(tree_ptr_t tree)
{
    if (tree->left_) 
    {
        destroy_tree(tree->left_);
    }
    if (tree->right_) 
    {
        destroy_tree(tree->right_);
    }
    delete tree;
}

bool contains_key(tree_ptr_t tree, key_t key)
{
    if (tree == nullptr) 
    {
        return false;
    }
    else if (tree->key_ == key) 
    {
        return true;
    }
    else if (contains_key(tree->left_, key) or contains_key(tree->right_, key)) 
    {
        return true;
    } 
    else 
    {
        return false;
    }
}   

std::string path_to(tree_ptr_t tree, key_t key)
{
    if (contains_key(tree->left_, key))
    {
        return "L" + path_to(tree->left_, key);
    }
    else if (tree->key_ == key) 
    {
        return "";
    }
    else if (contains_key(tree->right_, key))        
    {
        return "R" + path_to(tree->right_, key);
    }
    else
    {    
    assert(false);
    }
    return ""; //This will never happen, but the case is needed to satisfy the compiler
}   

tree_ptr_t node_at(tree_ptr_t tree, std::string path)
{
    auto current_node = tree;
    for (auto c : path) 
    {
        if (c == 'L') 
        {
            current_node= current_node->left_;
        } 
        else if (c == 'R')
        {
            current_node= current_node->right_;
        }
        else
        {
            return nullptr;
        }
    }
    return current_node;
}










