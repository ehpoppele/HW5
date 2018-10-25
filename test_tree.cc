#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "tree.cc"

TEST_CASE( "Trees! Trees should be able to store data, and all four relevant functions should work", "[Tree]" ) 
{
    /*First we set up our trees. We build from the leaves up, so the code looks a bit strange, but it follows:
    Tree tree_key_identity is a tree with key "key" and an identifying integer, which is then assigned to value,
    because value is not actually used in the tree structure anywhere but is still part of it. 
    Once we have built our tree, we should end up with something like:
            126
           /   \
          /     \
         4       7
        / \       \
      -3   2       5
      / \   \     / \ 
     4   5   7   0   4
     
    Which should be sufficient to test all of our features.
    [This could have been made better/more modular by replacing all the values in the tree with variables, thus 
    allowing for easy editing of the values in the tree; but it's too late now and the current values are (probably) fine.
    */
    tree_ptr_t tree_4_01   = create_tree(  4,  1);
    tree_ptr_t tree_5_02   = create_tree(  5,  2);
    tree_ptr_t tree_n3_03  = create_tree( -3,  3,   tree_4_01, tree_5_02); //n here stands for negative
    tree_ptr_t tree_7_04   = create_tree(  7,  4);
    tree_ptr_t tree_2_05   = create_tree(  2,  5,     nullptr, tree_7_04);
    tree_ptr_t tree_4_06   = create_tree(  4,  6,  tree_n3_03, tree_2_05);
    tree_ptr_t tree_0_07   = create_tree(  0,  7);
    tree_ptr_t tree_4_08   = create_tree(  4,  8);
    tree_ptr_t tree_5_09   = create_tree(  5,  9,   tree_0_07, tree_4_08);
    tree_ptr_t tree_7_10   = create_tree(  7, 10,     nullptr, tree_5_09);
    tree_ptr_t tree_126_11 = create_tree(126, 11,   tree_4_06, tree_7_10);
    
    SECTION( "Data used in tree creation should be assigned properly." )
    {
        //This section just tests to make sure that everything we set up actually went into the intended values, and that the trees exist.
        REQUIRE( tree_n3_03->key_ == -3);
        REQUIRE( tree_4_01->value_ == 1);
        REQUIRE( tree_2_05->left_ == nullptr);
        REQUIRE( tree_126_11->right_ == tree_7_10);
    }
    
    SECTION( "Path_to function should return a path in terms of L and R to the leftmost of a given key in the tree." )
    {
        //This section tests that path_to functions as expected
        REQUIRE( path_to(tree_126_11, 4) == "LLL");
        REQUIRE( path_to(tree_126_11, 5) == "LLR");
        REQUIRE( path_to(tree_126_11, 2) == "LR");
        REQUIRE( path_to(tree_126_11, 7) == "LRR");
        REQUIRE( path_to(tree_126_11, 0) == "RRL");
        REQUIRE( path_to(tree_126_11, 126) == "");
        //Next we test a few other paths, this time starting from somewhere other than the root of our tree
        REQUIRE( path_to(tree_4_06, 4) == "LL");
        REQUIRE( path_to(tree_4_06, 7) == "RR");
        REQUIRE( path_to(tree_7_10, 4) == "RR");
    }

    SECTION( "Node_at function should be able to take a path from the input node and return the key at the node that path leads to." )
    {
        //First we test all the cases from our last test, only now we use path_to as the input and confirm that node_at functions
        //Effectively as an inverse of path_to, that is, that node_at( path_to( x ) ) == x.
        REQUIRE( node_at(tree_126_11, ( path_to(tree_126_11, 4))) == tree_4_01);
        REQUIRE( node_at(tree_126_11, ( path_to(tree_126_11, 5))) == tree_5_02);
        REQUIRE( node_at(tree_126_11, ( path_to(tree_126_11, 2))) == tree_2_05);
        REQUIRE( node_at(tree_126_11, ( path_to(tree_126_11, 7))) == tree_7_04);
        //And then we're going to switch it up, instead manually inputting the path and checking it returns the expected value.
        REQUIRE( node_at(tree_126_11, "RRL") == tree_0_07);
        REQUIRE( node_at(tree_126_11, "") == tree_126_11);
        REQUIRE( node_at(tree_4_06, "LL") == tree_4_01);
        REQUIRE( node_at(tree_4_06, "RR") == tree_7_04);
        REQUIRE( node_at(tree_7_10, "RR") == tree_4_08);
        //And then we're also going to test other paths, leading to duplicate values
        REQUIRE( node_at(tree_126_11, "L") == tree_4_06);
        REQUIRE( node_at(tree_126_11, "RRR") == tree_4_08);
        REQUIRE( node_at(tree_126_11, "LRR") == tree_7_04);
        REQUIRE( node_at(tree_126_11, "R") == tree_7_10);
        //And finally testing an invalid input:
        REQUIRE( node_at(tree_126_11, "HOW DO I EXIT VI") == nullptr);
    }
    
    SECTION( "Destorying trees should remove them and clear the memory space." )
    {
        //First we will delete some trees, and then test path_to and node_at to make sure
        destroy_tree(tree_n3_03);
        destroy_tree(tree_5_09);
}
        
        
        
        
        
        
        
        