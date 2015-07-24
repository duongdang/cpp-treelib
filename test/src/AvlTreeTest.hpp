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

#ifndef TREELIB_AVLTREETEST_HPP_
#define TREELIB_AVLTREETEST_HPP_

#include <treelib/AvlNode.hpp>
#include "gtest/gtest.h"

namespace treelib {
namespace bst {

class AvlTreeTest : public ::testing::Test {
public:
    AvlTreeTest() : _pTree1(), _pTree2(), _pTree3() {}
    virtual ~AvlTreeTest() {}
    typedef AvlNode<int, int> NodeT;

protected:
    virtual void SetUp();

    NodeT::node_ptr insertInt(NodeT::node_ptr ipNode, int iVal) {
        return insert(ipNode, std::make_pair(iVal, iVal));
    }

    NodeT::node_ptr _pTree1, _pTree2, _pTree3;

}; // class AvlTreeTest

} // namespace bst
} // namespace treelib

#endif // TREELIB_AVLTREETEST_HPP_
