#include <assert.h> 
#include "tree.hh"

//Creates a new tree with given data values and returns a pointer to that tree
tree_ptr_t create_tree(const key_t& key,
                       const value_t& value,
                       tree_ptr_t left,
                       tree_ptr_t right)
{
    return new Tree({key, value, left, right}); //This will simply return a pointer to the newly created tree
}

//Destroys a given tree as well as all trees that branch from it, acting recursively
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

//Helper function for path_to. The following function checks if the given key is contained within the given tree.
bool contains_key(tree_ptr_t tree, key_t key)
{
    if (tree == nullptr) //This is our base case, indicating that we have run to the end of the branch
    {
        return false;
    }
    else if (tree->key_ == key) //We're not interested in if it contains duplicates/where any of the values are, so once we see our key, we're done.
    {
        return true;
    }
    else if (contains_key(tree->left_, key) or contains_key(tree->right_, key))//As long as one branch of the tree contains the value then we're set.
    {
        return true;
    } 
    else 
    {
        return false;
    }
}   

//Recursive function traces path to a given key in the tree, favoring the strictly leftmost occurence of that key.
std::string path_to(tree_ptr_t tree, key_t key)
{
    if (contains_key(tree->left_, key)) //We check the left branch before we check the actual value of the node we're looking at,
    //as we want to find the leftmost value, and not the uppermost left value.
    {
        return "L" + path_to(tree->left_, key);
    }
    else if (tree->key_ == key)//For our base case we return the empty string now that we're at the nodes we're looking for
    {
        return "";
    }
    else if (contains_key(tree->right_, key))
    {
        return "R" + path_to(tree->right_, key);
    }
    else
    {    
    assert(false); //Crash/end program if the key is not contained in the tree.
    }
    return ""; //This will never happen, but the case is needed to satisfy the compiler
}   

//Iteratively follows an input path through a tree and returns the key of the node at the end of the path
tree_ptr_t node_at(tree_ptr_t tree, std::string path)
{
    auto current_node = tree;
    for (auto c : path) //Loops through each element of the string we feed it; easier than writing this func. recursively
    {
        if (current_node == nullptr) //If the path leads us off the tree, then we return a nullptr
        {
            return nullptr;
        }
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
            return nullptr; //This case covers any input of a character that isn't L or R
        }
    }
    return current_node;
}










