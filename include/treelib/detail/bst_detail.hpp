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

#ifndef TREELIB_BST_DETAIL_HPP_
#define TREELIB_BST_DETAIL_HPP_

namespace treelib {
namespace bst {
namespace detail {
/// output the tree to tree to a sufficently sized array
template <class NodePtr, class ContainerT>
inline void toArray(NodePtr ipRoot, ContainerT& oNodes, size_t iIdx){
    if (!ipRoot) {
        return;
    }
    oNodes[iIdx] = ipRoot;
    toArray(ipRoot->_left, oNodes, 2*iIdx + 1);
    toArray(ipRoot->_right, oNodes, 2*iIdx + 2);
}

template <typename NodePtr>
inline const int bfactor(NodePtr ipNode) {
    if (!ipNode) {
        return 0;
    }
    unsigned char hr = ipNode->_right ?  ipNode->_right->_height : 0;
    unsigned char hl = ipNode->_left ?  ipNode->_left->_height : 0;

    return hr - hl;
}

} // namespace detail
} // namespace bst
} // namespace treelib

#endif // TREELIB_BST_DETAIL_HPP_
