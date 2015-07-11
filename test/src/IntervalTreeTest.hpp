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

#ifndef TREELIB_INTERVALTREETEST_HPP_
#define TREELIB_INTERVALTREETEST_HPP_

#include <vector>
#include <treelib/IntervalAvlNode.hpp>
#include <boost/optional.hpp>
#include "gtest/gtest.h"

namespace treelib {
namespace bst {
class IntervalTreeTest : public ::testing::Test{
public:
    IntervalTreeTest() : _intervals(), _pTree() {}
    virtual ~IntervalTreeTest() {}
    typedef IntervalAvlNode<int, char> NodeT;

protected:
    virtual void SetUp();

    std::vector<NodeT::value_type> _intervals;
    NodeT::node_ptr _pTree;
}; // class IntervalTreeTest
} // namespace bst
} // namespace treelib

#endif // TREELIB_INTERVALTREETEST_HPP_
