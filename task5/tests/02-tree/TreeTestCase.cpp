//
// Created by akhtyamovpavel on 5/1/20.
//

#include "TreeTestCase.h"
#include "Tree.h"
#include <boost/filesystem.hpp>

#include <gtest/gtest.h>
using boost::filesystem::create_directory;
using boost::filesystem::remove_all;
using boost::filesystem::ofstream;

::testing::AssertionResult IsTrue(FileNode& val1, FileNode& val2)
{
	if (val1 == val2)
		return ::testing::AssertionSuccess();
	else
		return ::testing::AssertionFailure() << " is not equal";
}

FileNode createOne(const std::string& path) {
    return {boost::filesystem::path(path).filename().string(), true};
}

FileNode createTwo(const std::string& path) {
    FileNode answer;
    answer.name = boost::filesystem::path(path).filename().string();
    answer.is_dir = true;
    answer.children.push_back({
        boost::filesystem::path("in_inner").filename().string(), true
      });
    return answer;
}


TEST(B, TREE) {
    create_directory("inner");
    ofstream file("file.txt");
    file << "Hello World!";
    file.close();
    create_directory("inner/in_inner");

    ASSERT_THROW(GetTree("dsdsf", false), std::invalid_argument);
    ASSERT_THROW(GetTree("inner/file.txt", false), std::invalid_argument);
    ASSERT_NO_THROW(GetTree("inner", false));
    ASSERT_TRUE(createOne("inner/in_inner") == GetTree("inner/in_inner", true));
    ASSERT_TRUE(createTwo("inner") == GetTree("inner", true));

    remove_all("inner");
};

