// Copyright 2015 Duong Dang
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <AvlTreeTest.hpp>
#include <experimental/optional>

namespace stdexp = std::experimental;

namespace treelib {
namespace bst {


TEST(Dummy, Dummy) {
    ASSERT_TRUE(true);
}

bool operator== (stdexp::optional<int> iExpected, AvlTreeTest::NodeT::node_cptr ipNode) {
    if (iExpected) {
        if (!ipNode) {
            return false;
        }
        return *iExpected == ipNode->getKey();
    }
    else {
        return !ipNode;
    }
}

std::ostream& operator<< (std::ostream& os, AvlTreeTest::NodeT::node_cptr ipNode) {
    if (!ipNode) {
        return os << "none";
    }
    return os << ipNode->getKey();
}

void AvlTreeTest::SetUp() {
    /***
    * simple trees to test
    *   20+       20+           __20+__
    *  /         /  \          /       \
    * 4         4    26       4         26
    *          / \           / \       /  \
    *         3   9         3+  9    21    30
    *                      /   / \
    *                     2   7   11
    */
    _pTree1 = insertInt(_pTree1, 20);
    _pTree1 = insertInt(_pTree1, 4);

    _pTree2 = insertInt(_pTree2, 20);
    _pTree2 = insertInt(_pTree2, 26);
    _pTree2 = insertInt(_pTree2, 4);
    _pTree2 = insertInt(_pTree2, 9);
    _pTree2 = insertInt(_pTree2, 3);


    _pTree3 = insertInt(_pTree3, 20);
    _pTree3 = insertInt(_pTree3, 26);
    _pTree3 = insertInt(_pTree3, 4);

    _pTree3 = insertInt(_pTree3, 21);
    _pTree3 = insertInt(_pTree3, 30);
    _pTree3 = insertInt(_pTree3, 3);
    _pTree3 = insertInt(_pTree3, 9);

    _pTree3 = insertInt(_pTree3, 2);
    _pTree3 = insertInt(_pTree3, 7);
    _pTree3 = insertInt(_pTree3, 11);
}

TEST_F(AvlTreeTest, Construct1) {
    /***
    * simple trees to test
    *   20+       20+           __20+__
    *  /         /  \          /       \
    * 4         4    26       4         26
    *          / \           / \       /  \
    *         3   9         3+  9    21    30
    *                      /   / \
    *                     2   7   11
    */
    ASSERT_TRUE(_pTree1.get());
    ASSERT_EQ(2, _pTree1->_height);
    std::vector<NodeT::node_cptr> aArray;
    toArray(_pTree1, aArray);
    ASSERT_EQ(3, aArray.size());
    EXPECT_EQ(20, aArray[0]);
    EXPECT_EQ(4, aArray[1]);
    EXPECT_EQ(stdexp::nullopt, aArray[2]);
}

TEST_F(AvlTreeTest, Construct2) {
    /***
    * simple trees to test
    *   20+       20+           __20+__
    *  /         /  \          /       \
    * 4         4    26       4         26
    *          / \           / \       /  \
    *         3   9         3+  9    21    30
    *                      /   / \
    *                     2   7   11
    */
    ASSERT_TRUE(_pTree2.get());
    ASSERT_EQ(3, _pTree2->_height);

    std::vector<NodeT::node_cptr> aArray;
    toArray(_pTree2, aArray);

    ASSERT_EQ(7, aArray.size());

    EXPECT_EQ(20, aArray[0]);
    EXPECT_EQ(4, aArray[1]);
    EXPECT_EQ(26, aArray[2]);
    EXPECT_EQ(3, aArray[3]);
    EXPECT_EQ(9, aArray[4]);
    EXPECT_EQ(stdexp::nullopt, aArray[5]);
    EXPECT_EQ(stdexp::nullopt, aArray[6]);
}

TEST_F(AvlTreeTest, Construct3) {
    /***
    * simple trees to test
    *   20+       20+           __20+__
    *  /         /  \          /       \
    * 4         4    26       4         26
    *          / \           / \       /  \
    *         3   9         3+  9    21    30
    *                      /   / \
    *                     2   7   11
    */
    ASSERT_TRUE(_pTree3.get());
    ASSERT_EQ(4, _pTree3->_height);

    std::vector<NodeT::node_cptr> aArray;
    toArray(_pTree3, aArray);

    ASSERT_EQ(15, aArray.size());

    EXPECT_EQ(20, aArray[0]);
    EXPECT_EQ(4, aArray[1]);
    EXPECT_EQ(26, aArray[2]);
    EXPECT_EQ(3, aArray[3]);
    EXPECT_EQ(9, aArray[4]);
    EXPECT_EQ(21, aArray[5]);
    EXPECT_EQ(30, aArray[6]);

    EXPECT_EQ(2, aArray[7]);
    EXPECT_EQ(stdexp::nullopt, aArray[8]);
    EXPECT_EQ(7, aArray[9]);
    EXPECT_EQ(11, aArray[10]);
    EXPECT_EQ(stdexp::nullopt, aArray[11]);
    EXPECT_EQ(stdexp::nullopt, aArray[12]);
    EXPECT_EQ(stdexp::nullopt, aArray[13]);
    EXPECT_EQ(stdexp::nullopt, aArray[14]);
}

TEST_F(AvlTreeTest, Insert1a) {
    /***
    * Case 1a: insert 15
    *   20+      20++         20++      15
    *  /        /            /         /  \
    * 4     => 4-     =>   15+     => 4    20
    *           \         /
    *            15      4
    */
    _pTree1 = insertInt(_pTree1, 15);
    ASSERT_EQ(2, _pTree1->_height);
    std::vector<NodeT::node_cptr> aArray;
    toArray(_pTree1, aArray);
    ASSERT_EQ(3, aArray.size());
    EXPECT_EQ(15, aArray[0]);
    EXPECT_EQ(4, aArray[1]);
    EXPECT_EQ(20, aArray[2]);
}

TEST_F(AvlTreeTest, Insert1b) {
    /***
    *   Case 1b: insert 8
    *
    *   20+      20++        20++      8
    *  /        /           /         / \
    * 4     => 4-     =>   8+     => 4   20
    *           \         /
    *            8       4
    */
    _pTree1 = insertInt(_pTree1, 8);
    ASSERT_TRUE(_pTree1.get());
    ASSERT_EQ(2, _pTree1->_height);
    std::vector<NodeT::node_cptr> aArray;
    toArray(_pTree1, aArray);
    ASSERT_EQ(3, aArray.size());
    EXPECT_EQ(8, aArray[0]);
    EXPECT_EQ(4, aArray[1]);
    EXPECT_EQ(20, aArray[2]);
}

TEST_F(AvlTreeTest, Insert2a) {
    /***
    *     Case 2a: Insert 15
    *
    *     20+          20++           20++         9
    *    /  \         /  \           /  \         / \
    *   4    26 =>   4-   26 =>     9+   26 =>   4+  20
    *  / \          / \            / \          /   /  \
    * 3   9        3   9-         4+  15       3  15    26
    *                    \       /
    *                     15    3
    */
    _pTree2 = insertInt(_pTree2, 15);
    ASSERT_TRUE(_pTree2.get());
    ASSERT_EQ(3, _pTree2->_height);
    std::vector<NodeT::node_cptr> aArray;
    toArray(_pTree2, aArray);

    ASSERT_EQ(7, aArray.size());

    EXPECT_EQ(9, aArray[0]);
    EXPECT_EQ(4, aArray[1]);
    EXPECT_EQ(20, aArray[2]);
    EXPECT_EQ(3, aArray[3]);
    EXPECT_EQ(stdexp::nullopt, aArray[4]);
    EXPECT_EQ(15, aArray[5]);
    EXPECT_EQ(26, aArray[6]);
}

TEST_F(AvlTreeTest, Insert2b) {
    /***
    *     Case 2b: Insert 8
    *
    *     20+          20++           20++         9
    *    /  \         /  \           /  \         / \
    *   4    26 =>   4-   26 =>     9++  26 =>   4   20-
    *  / \          / \            /            / \    \
    * 3   9        3   9+         4            3   8    26
    *                 /          / \
    *                8          3   8
    */
    _pTree2 = insertInt(_pTree2, 8);
    ASSERT_TRUE(_pTree2.get());
    ASSERT_EQ(3, _pTree2->_height);
    std::vector<NodeT::node_cptr> aArray;
    toArray(_pTree2, aArray);

    ASSERT_EQ(7, aArray.size());

    EXPECT_EQ(9, aArray[0]);
    EXPECT_EQ(4, aArray[1]);
    EXPECT_EQ(20, aArray[2]);
    EXPECT_EQ(3, aArray[3]);
    EXPECT_EQ(8, aArray[4]);
    EXPECT_EQ(stdexp::nullopt, aArray[5]);
    EXPECT_EQ(26, aArray[6]);
}
TEST_F(AvlTreeTest, Insert3a) {
    /***
    *     Case 3a: Insert 15
    *
    *       __20+__                _20++_                  __20++_                ___9___
    *      /       \              /      \                /       \              /       \
    *     4         26    =>     4-       26    =>       9+        26    =>     4+      __20__
    *    / \       /  \         / \      /  \           / \       /  \         / \     /      \
    *   3+  9    21    30      3+  9-  21    30        4+  11-  21    30      3+  7  11-       26
    *  /   / \                /   / \                 / \   \                /         \      /  \
    * 2   7   11             2   7   11-             3+  7   15             2           15  21    30
    *                                  \            /
    *                                   15         2
    */
    _pTree3 = insertInt(_pTree3, 15);
    ASSERT_TRUE(_pTree3.get());
    ASSERT_EQ(4, _pTree3->_height);

    std::vector<NodeT::node_cptr> aArray;
    toArray(_pTree3, aArray);

    ASSERT_EQ(15, aArray.size());

    EXPECT_EQ(9, aArray[0]);
    EXPECT_EQ(4, aArray[1]);
    EXPECT_EQ(20, aArray[2]);
    EXPECT_EQ(3, aArray[3]);
    EXPECT_EQ(7, aArray[4]);
    EXPECT_EQ(11, aArray[5]);
    EXPECT_EQ(26, aArray[6]);

    EXPECT_EQ(2, aArray[7]);
    EXPECT_EQ(stdexp::nullopt, aArray[8]);
    EXPECT_EQ(stdexp::nullopt, aArray[9]);
    EXPECT_EQ(stdexp::nullopt, aArray[10]);
    EXPECT_EQ(stdexp::nullopt, aArray[11]);
    EXPECT_EQ(15, aArray[12]);
    EXPECT_EQ(21, aArray[13]);
    EXPECT_EQ(30, aArray[14]);
}

TEST_F(AvlTreeTest, Insert3b) {
    /***
    *     Case 3b: Insert 8
    *
    *       __20+__                _20++_                  __20++_                ___9___
    *      /       \              /      \                /       \              /       \
    *     4         26           4-       26             9+        26           4        _20-
    *    / \       /  \         / \      /  \           / \       /  \         / \      /    \
    *   3+  9    21    30 =>   3+  9+  21    30 =>     4   11   21    30 =>   3+  7-  11      26
    *  /   / \                /   / \                 / \                    /     \         /  \
    * 2   7   11             2   7-  11              3+  7-                 2       8      21    30
    *                             \                 /     \
    *                              8               2       8
    */
    _pTree3 = insertInt(_pTree3, 8);
    ASSERT_TRUE(_pTree3.get());
    ASSERT_EQ(4, _pTree3->_height);

    std::vector<NodeT::node_cptr> aArray;
    toArray(_pTree3, aArray);

    ASSERT_EQ(15, aArray.size());

    EXPECT_EQ(9, aArray[0]);
    EXPECT_EQ(4, aArray[1]);
    EXPECT_EQ(20, aArray[2]);
    EXPECT_EQ(3, aArray[3]);
    EXPECT_EQ(7, aArray[4]);
    EXPECT_EQ(11, aArray[5]);
    EXPECT_EQ(26, aArray[6]);

    EXPECT_EQ(2, aArray[7]);
    EXPECT_EQ(stdexp::nullopt, aArray[8]);
    EXPECT_EQ(stdexp::nullopt, aArray[9]);
    EXPECT_EQ(8, aArray[10]);
    EXPECT_EQ(stdexp::nullopt, aArray[11]);
    EXPECT_EQ(stdexp::nullopt, aArray[12]);
    EXPECT_EQ(21, aArray[13]);
    EXPECT_EQ(30, aArray[14]);
}

} // namespace bst
} // namespace treelib
