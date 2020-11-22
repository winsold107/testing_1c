//
// Created by akhtyamovpavel on 5/1/20.
//


#include "TreeTestCase.h"
#include "Tree.h"
#include <boost/filesystem.hpp>

#include <gtest/gtest.h>

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
        boost::filesystem::path("/Users/winsold/Desktop/phystech/english/lymphoma").filename().string(), false
      });
    return answer;
}


TEST(B, TREE) {
    ASSERT_THROW(GetTree("dsdsf", false), std::invalid_argument);
    ASSERT_THROW(GetTree("/Users/winsold/Desktop/IMG_0015.PNG", false), std::invalid_argument);
    ASSERT_NO_THROW(GetTree("/Users/winsold/Desktop/phystech/compmath", false));
    ASSERT_TRUE(createOne("/Users/winsold/Desktop/phystech/english") == GetTree("/Users/winsold/Desktop/phystech/english", true));
};

