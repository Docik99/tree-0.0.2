#include <catch.hpp>
#include "tree.hpp"
#include <sstream>

TAST_CASE("insert and print")
{
  tree_t<int> tree;
  string print {
    "--------12\n"
    "----8\n"
    "--------5\n"
    "------------1\n"
  };
  tree.insert(8);
  tree.insert(12);
  tree.insert(5);
  tree.insert(1);
  ostringstream ostream;
  tree.print(ostream);
  REQUIRE(ostream.str() == print);
}

TAST_CASE("find key in tree")
{
  tree_t<int> tree;
  tree.insert(8);
  tree.insert(12);
  tree.insert(5);
  tree.insert(1);
  REQUIRE(tree.find(12) == true);
  REQUIRE(tree.find(1) == true);
  REQUIRE(tree.find(122) == false);
  REQUIRE(tree.find(0) == false);
}

TAST_CASE("remove type 1")
{
  tree_t<int> tree;
  tree.insert(8);
  tree.insert(9);
  tree.insert(10);
  tree.insert(11);
  tree.insert(7);
  tree.insert(3);
  tree.insert(12);
  string tree_before {
    "--------------------12\n"
    "----------------11\n"
    "------------10\n"
    "--------9\n"
    "----8\n"
    "--------7\n"
    "------------3\n"
  };
  ostringstream ostream;
  tree.print(ostream);
  REQUIRE(ostream.str() == tree_before);
  string tree_after {
    "---------------12\n"
    "-----------11\n"
    "-------10\n"
    "----9\n"
    "-------7\n"
    "----------3\n"
  };
  REQUIRE(tree.remove(1) == false);
  REQUIRE(tree.remove(23) == false);
  REQUIRE(tree.remove(8) == true);
  tree.print(ostream);
  REQUIRE(ostream.str() == tree_before + tree_after);
}

TAST_CASE(" remove type 2")
{
  tree_t<int> tree;
  tree.insert(8);
  tree.insert(20);
  tree.insert(19);
  tree.insert(18);
  tree.insert(15);
  tree.insert(16);
  tree.insert(7);
  tree.insert(3);
  string tree_before {
    "--------20\n"
    "------------19\n"
    "----------------18\n"
    "------------------------16\n"
    "--------------------15\n"
    "----8\n"
    "--------7\n"
    "------------3\n"
  };
  ostringstream ostream;
  tree.print(ostream);
  REQUIRE(ostream.str() == tree_before);
  string tree_after {
    "--------20\n"
    "------------19\n"
    "--------------------16\n"
    "----------------18\n"
    "----15\n"
    "--------7\n"
    "------------3\n"
  };
  REQUIRE(tree.remove(11) == false);
  REQUIRE(tree.remove(13) == false);
  REQUIRE(tree.remove(8) == true);
  tree.print(ostream);
  REQUIRE(ostream.str() == tree_before + tree_after);
}

TAST_CASE(" remove type 3")
{
  tree_t<int> tree;
  tree.insert(12);
  tree.insert(3);
  tree.insert(20);
  tree.insert(17);
  tree.insert(22);
  string tree_before {
    "------------22\n"
    "--------20\n"
    "------------17\n"
    "----12\n"
    "--------3\n"
  };
  ostringstream ostream;
  tree.print(ostream);
  REQUIRE(ostream.str() == tree_before);
  string tree_after {
    "--------22\n"
    "------------17\n"
    "----12\n"
    "--------3\n"
  };
  REQUIRE(tree.remove(11) == false);
  REQUIRE(tree.remove(13) == false);
  REQUIRE(tree.remove(20) == true);
  tree.print(ostream);
  REQUIRE(ostream.str() == tree_before + tree_after);
}
  
TAST_CASE("remove type 4")
{
  tree_t<int> tree;
  tree.insert(8);
  tree.insert(7);
  tree.insert(20);
  tree.insert(19);
  tree.insert(17);
  tree.insert(18);
  tree.insert(13);
  tree.insert(14);
  string tree_before {
    "--------20\n"
    "------------19\n"
    "--------------------18\n"
    "----------------17\n"
    "------------------------14\n"
    "--------------------13\n"
    "----8\n"
    "--------7\n"
  };
  string tree_after {
    "--------20\n"
    "------------19\n"
    "--------------------18\n"
    "------------------------14\n"
    "----------------17\n"
    "----13\n"
    "--------7\n"
  };
  ostringstream ostream;
  tree.print(ostream);
  REQUIRE(ostream.str() == tree_before);
  REQUIRE(tree.remove(11) == false);
  REQUIRE(tree.remove(27) == false);
  REQUIRE(tree.remove(8) == true);
  tree.print(ostream);
  REQUIRE(ostream.str() == tree_before + tree_after);
}

TAST_CASE("remove type 5") 
{
  tree_t<int> tree;
  tree.insert(12);
  tree.insert(7);
  tree.insert(20);
  tree.insert(17);
  tree.insert(16);
  string tree_before {
    "--------20\n"
    "------------17\n"
    "----------------16\n"
    "----12\n"
    "--------7\n"
  };
  string tree_after {
  "--------17\n"
  "------------16\n"
  "----12\n"
  "--------7\n"
  };
  ostringstream ostream;
  tree.print(ostream);
  REQUIRE(ostream.str() == tree_before);
  REQUIRE(tree.remove(11) == false);
  REQUIRE(tree.remove(27) == false);
  REQUIRE(tree.remove(20) == true);
  tree.print(ostream);
  REQUIRE(ostream.str() == tree_before + tree_after);
}

TAST_CASE("remove type 6")
{
  tree_t<int> tree;
  tree.insert(12);
  tree.insert(7);
  tree.insert(20);
  string tree_before {
    "--------20\n"
    "----12\n"
    "--------7\n"
  };
  string tree_after {
  "----12\n"
  "--------7\n"
  };
  ostringstream ostream;
  tree.print(ostream);
  REQUIRE(ostream.str() == tree_before);
  REQUIRE(tree.remove(11) == false);
  REQUIRE(tree.remove(27) == false);
  REQUIRE(tree.remove(20) == true);
  tree.print(ostream);
  REQUIRE(ostream.str() == tree_before + tree_after);
}
  
TAST_CASE("compare")
{
  tree_t<int> tree1{23,12,3,45,57,33}, tree2{23,45,33,57,12,3};
  REQUIRE((tree1==tree2) == true);
  tree1.remove(23);
  tree2.insert(8);
  REQUIRE((tree1==tree2) == false);
}

TAST_CASE("initializer_list")
{
  tree_t<int> tree {0,2,4,61,120} ;
    string keys {
        "--------------------120\n"
        "----------------61\n"
        "------------4\n"
        "--------2\n"
        "----0\n"     
    };
    ostringstream ostream;
    tree.print(ostream);
    REQUIRE(ostream.str()==keys);
}
  
TAST_CASE("exception")
{
  tree<int> tree;
  REQUIRE_THROWS (tree.print(cout));
}
