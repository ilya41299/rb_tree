#include <catch.hpp>
#include <sstream>

#include "vector.hpp"

TEST_CASE("Сreating tree")
{
	tree_t<int> My_tree;
	REQUIRE( My_tree.root() == nullptr );
}

TEST_CASE("Add elements in tree left rotate")
{
	tree_t<int> My_tree{1, 2, 3, 4, 5, 6, 7};

	std::ostringstream ostream;
	My_tree.print(ostream, 0, My_tree.root());
	std::string output
	{
		"---------7\n"
		"------6\n"
		"---------5\n"
		"---4\n"
		"------3\n"
		"2\n"
		"---1\n"
	}
	REQUIRE(output == ostream.str());
}

TEST_CASE("Add elements in tree right rotate")
{
	tree_t<int> My_tree{7, 6, 5, 4, 3, 2, 1};
	
	std::ostringstream ostream;
	My_tree.print(ostream, 0, My_tree.root());
	std::string output
	{
		"---7\n"
		"6\n"
		"------5\n"
		"---4\n"
		"---------3\n"
		"------2\n"
		"---------1\n"
	}
	REQUIRE(output == ostream.str());
}
