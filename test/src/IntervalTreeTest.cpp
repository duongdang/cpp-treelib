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

#include <IntervalTreeTest.hpp>
#include <vector>
#include <algorithm>
#include <experimental/optional>

namespace stdexp = std::experimental;

namespace treelib {
namespace bst {
void IntervalTreeTest::SetUp() {
    /***
     * Test case base on Introduction to Algorithms, MIT press, 3rd edition, pg 350
     * j                                                       26||26
     * i                                                     25|----------|30
     * h                                         19|--|20
     * g                                     17|----|19
     * f                                   16|----------|21
     * e                                 15|--------------|23
     * d                   8|--|9
     * c               6|--------|10
     * b             5|------|8
     * a  0|------|3
     *
     * A interval tree based on Avl
     *
     *                                    [16,21]
     *                            ---------  30  ------------
     *                           /                           \
     *                          /                             \
     *                         /                               \
     *                      [8,9]                           [25,30]
     *                        23                              30
     *                       /  \                           /   \
     *                      /    \                         /     \
     *                     /      \                       /       \
     *               [5,8]         [15,23]         [17,19]         [26,26]
     *                 10             23              20             26
     *                / \                               \
     *               /   \                               \
     *              /     \                               \
     *          [0,3]     [6,10]                        [19,20]
     *            3         10                            20
     *
     */

    // list of interval in bfs treversal order
    _intervals.reserve(10);
    _intervals.push_back(std::make_tuple(16, 21, 'f'));
    _intervals.push_back(std::make_tuple( 8,  9, 'd'));
    _intervals.push_back(std::make_tuple(25, 30, 'i'));
    _intervals.push_back(std::make_tuple( 5,  8, 'b'));
    _intervals.push_back(std::make_tuple(15, 23, 'e'));
    _intervals.push_back(std::make_tuple(17, 19, 'g'));
    _intervals.push_back(std::make_tuple(26, 26, 'j'));
    _intervals.push_back(std::make_tuple( 0,  3, 'a'));
    _intervals.push_back(std::make_tuple( 6, 10, 'c'));
    _intervals.push_back(std::make_tuple(19, 20, 'h'));
    for (const auto& aTuple : _intervals) {
        _pTree = insert(_pTree, aTuple);
    }
}

bool operator== (const stdexp::optional<std::tuple<int, int, int, int, char> >& iExpected,
                 IntervalTreeTest::NodeT::node_cptr ipNode) {
    if (iExpected) {
        if (!ipNode) {
            return false;
        }
        return *iExpected == std::make_tuple(ipNode->_start, ipNode->_end, ipNode->_max,
                                             static_cast<int>(ipNode->_height),
                                             ipNode->_data);
    }
    else {
        return !ipNode;
    }
}

std::ostream& operator<< (std::ostream& os, IntervalTreeTest::NodeT::node_cptr ipNode) {
    if (!ipNode) {
        return os << "none";
    }
    return os << "( [" << ipNode->_start << ", " << ipNode->_end << "], "
              << ipNode->_max << ", " << static_cast<int>(ipNode->_height)  << ", "
              << ipNode->_data
              << ")";
    return os;
}

TEST_F(IntervalTreeTest, Construct) {
    ASSERT_TRUE(_pTree.get());
    ASSERT_EQ(4, _pTree->_height);

    std::vector<NodeT::node_cptr> aNodes;
    toArray(_pTree, aNodes);
    ASSERT_EQ(15, aNodes.size());
    EXPECT_EQ(std::make_tuple(16, 21, 30, 4, 'f'), aNodes[0]);
    EXPECT_EQ(std::make_tuple( 8,  9, 23, 3, 'd'), aNodes[1]);
    EXPECT_EQ(std::make_tuple(25, 30, 30, 3, 'i'), aNodes[2]);
    EXPECT_EQ(std::make_tuple( 5,  8, 10, 2, 'b'), aNodes[3]);
    EXPECT_EQ(std::make_tuple(15, 23, 23, 1, 'e'), aNodes[4]);
    EXPECT_EQ(std::make_tuple(17, 19, 20, 2, 'g'), aNodes[5]);
    EXPECT_EQ(std::make_tuple(26, 26, 26, 1, 'j'), aNodes[6]);
    EXPECT_EQ(std::make_tuple( 0,  3,  3, 1, 'a'), aNodes[7]);
    EXPECT_EQ(std::make_tuple( 6, 10, 10, 1, 'c'), aNodes[8]);
    EXPECT_EQ(stdexp::nullopt,                           aNodes[9]);
    EXPECT_EQ(stdexp::nullopt,                           aNodes[10]);
    EXPECT_EQ(stdexp::nullopt,                           aNodes[11]);
    EXPECT_EQ(std::make_tuple(19, 20, 20, 1, 'h'), aNodes[12]);
    EXPECT_EQ(stdexp::nullopt,                           aNodes[13]);
    EXPECT_EQ(stdexp::nullopt,                           aNodes[14]);
}

TEST_F(IntervalTreeTest, Find) {
    ASSERT_EQ(std::make_tuple( 0,  3,  3, 1, 'a'), NodeT::find(_pTree, 1,2));
    ASSERT_TRUE(NodeT::find(_pTree, 6, 8).get());
    ASSERT_FALSE(NodeT::find(_pTree, 12,12).get());
}

bool operator== (const std::string& aStr,
                 const std::vector<IntervalTreeTest::NodeT::node_cptr>& iNodes) {
    if (aStr.size() != iNodes.size()){
        return false;
    }
    std::string aStrCopy(aStr);
    for(auto aNode: iNodes){
        if (!aNode) {
            return false;
        }
        size_t aPos = aStrCopy.find(aNode->_data);
        if (std::string::npos == aPos) {
            std::cerr << "Could not find char " << aNode->_data
                      << " in string '" << aStrCopy << "'" <<  std::endl;
            return false;
        }
        // aStrCopy.erase(aPos);
    }

    // if (aStrCopy.size() != 0){
    //     return false;
    // }

    return true;
}


TEST_F(IntervalTreeTest, FindAll){
    EXPECT_EQ("a", NodeT::findAll(_pTree, 1,1));
    EXPECT_EQ("a", NodeT::findAll(_pTree, 1,3));
    EXPECT_EQ("a", NodeT::findAll(_pTree, 3,3));
    EXPECT_EQ("", NodeT::findAll(_pTree, 4,4));
    EXPECT_EQ("ab", NodeT::findAll(_pTree, 3, 5));
    EXPECT_EQ("abcd", NodeT::findAll(_pTree, 1, 8));
    EXPECT_EQ("", NodeT::findAll(_pTree, 11, 14));
    EXPECT_EQ("ij", NodeT::findAll(_pTree, 26, 26));
    EXPECT_EQ("efgh", NodeT::findAll(_pTree, 12, 19));
}
} // namespace bst
} // namespace treelib
