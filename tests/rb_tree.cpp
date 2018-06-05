#include <catch.hpp>
#include <sstream>

#include "rb_tree.hpp"

TEST_CASE("creating rb tree") {
  rb_tree<int> tree;
  REQUIRE(tree.root() == nullptr);
}

TEST_CASE("elements can be inserted in rb tree") {
  rb_tree<int> tree;
  tree.insert(10);
  tree.insert(85);
  tree.insert(15);
  tree.insert(70);
  tree.insert(20);
  tree.insert(60);
  tree.insert(30);
  tree.insert(50);
  tree.insert(65);
  tree.insert(80);
  tree.insert(90);
  tree.insert(40);
  tree.insert(5);
  tree.insert(55);

  std::string out{
      "---------90R\n"
      "------85B\n"
      "---------80R\n"
      "---70B\n"
      "---------65B\n"
      "------60R\n"
      "------------55R\n"
      "---------50B\n"
      "------------40R\n"
      "30B\n"
      "------20B\n"
      "---15B\n"
      "------10B\n"
      "---------5R\n"};
  std::ostringstream stream;
  tree.print(stream);
  REQUIRE(stream.str() == out);
}

TEST_CASE("elements can be removde from rb tree") {
  rb_tree<int> tree;
  tree.insert(10);
  tree.remove(10);
  REQUIRE(tree.root() == nullptr);
  tree.insert(2);
  tree.insert(1);
  tree.insert(3);
  tree.insert(4);
  tree.insert(5);
  tree.insert(2);
  tree.remove(2);
  std::string out{
      "------5B\n"
      "---4R\n"
      "------3B\n"
      "2B\n"
      "---1B\n"};
  std::ostringstream stream;
  tree.print(stream);
  REQUIRE(stream.str() == out);
}
TEST_CASE("when brother is black and his sons") {
  rb_tree<int> tree;
  tree.insert(1);
  tree.insert(2);
  tree.insert(6);
  tree.insert(8);
  tree.insert(9);
  tree.insert(7);
  tree.insert(4);
  tree.insert(4);
  tree.insert(2);
  tree.insert(4);
  tree.insert(4);
  tree.remove(4);
  tree.remove(4);
  tree.remove(4);
  tree.remove(4);
  tree.remove(8);
  std::string out{
      "---9B\n"
      "------7B\n"
      "6B\n"
      "------2B\n"
      "---2B\n"
      "------1B\n"};
  std::ostringstream stream;
  std::ostringstream stream2;
  tree.print(stream);
  REQUIRE(stream.str() == out);
  std::string out2{
      "---7B\n"
      "6B\n"
      "------2B\n"
      "---2R\n"
      "------1B\n"};
  tree.remove(9);
  tree.print(stream2);
  REQUIRE(stream2.str() == out2);
}
TEST_CASE("when brother is black and his right son is red") {
  rb_tree<int> tree;
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  tree.insert(4);
  tree.insert(5);
  tree.insert(6);
  tree.insert(7);
  tree.insert(8);
  tree.insert(9);
  tree.insert(10);
  tree.insert(11);
  tree.insert(0);
  tree.remove(3);
  std::string out{
      "------------11R\n"
      "---------10B\n"
      "------------9R\n"
      "------8R\n"
      "---------7B\n"
      "---6B\n"
      "------5B\n"
      "4B\n"
      "---2B\n"
      "------1B\n"
      "---------0R\n"};
  std::ostringstream stream;
  std::ostringstream stream2;
  tree.print(stream);
  REQUIRE(stream.str() == out);
 tree.remove(2);
  std::string out2 {
      "---------11R\n"
      "------10B\n"
      "---------9R\n"
      "---8B\n"
      "------7B\n"
      "6B\n"
      "------5B\n"
      "---4B\n"
      "------1B\n"
      "---------0R\n"};
  
  tree.print(stream2);
  
  REQUIRE(stream2.str() == out2);
  
}
TEST_CASE("when brother is red") {
  rb_tree<int> tree;
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  tree.insert(4);
  tree.insert(5);
  tree.insert(6);
  tree.insert(7);
  tree.insert(8);
  tree.insert(9);
  tree.insert(10);
  tree.insert(11);
  tree.insert(0);
  tree.remove(3);
  tree.insert(5);
  tree.insert(5);
  tree.insert(5);
  tree.insert(5);
  tree.insert(5);
  std::string out{
      "------------11R\n"
      "---------10B\n"
      "------------9R\n"
      "------8B\n"
      "---------7B\n"
      "---6R\n"
      "---------------5R\n"
      "------------5B\n"
      "---------5R\n"
      "------------5B\n"
      "------5B\n"
      "---------5B\n"
      "4B\n"
      "---2B\n"
      "------1B\n"
      "---------0R\n"};
  std::ostringstream stream;
  std::ostringstream stream2;
  tree.print(stream);
  REQUIRE(stream.str() == out);
  std::string out1{
      "---------11R\n"
      "------10B\n"
      "---------9R\n"
      "---8B\n"
      "------7B\n"
      "6B\n"
      "------------5R\n"
      "---------5B\n"
      "------5B\n"
      "---------5B\n"
      "---5R\n"
      "---------5B\n"
      "------4B\n"
      "---------1B\n"
      "------------0R\n"};
  tree.remove(2);
    tree.print(stream2);
  REQUIRE(stream2.str() == out1);
}
