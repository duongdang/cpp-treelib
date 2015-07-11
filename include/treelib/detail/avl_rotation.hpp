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

#ifndef TREELIB_AVL_ROTATION_HPP_
#define TREELIB_AVL_ROTATION_HPP_
#include <treelib/detail/bst_detail.hpp>
namespace treelib {
namespace bst {
namespace detail {
namespace avl {
template <class NodePtr>
inline void fixHeight(NodePtr p) {
    if (p) { p->fixHeight(); }
}

template <class NodePtr>
inline NodePtr rotateRight(NodePtr p) {
    NodePtr q = p->_left;
    p->_left = q->_right;
    q->_right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}

template <class NodePtr>
inline NodePtr rotateLeft(NodePtr q) {
    NodePtr p = q->_right;
    q->_right = p->_left;
    p->_left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}

template <typename NodePtr>
inline NodePtr balance(NodePtr p){
    if (!p) {
        return p;
    }

    fixHeight(p);

    if (bfactor(p) == 2 ){
        if(bfactor(p->_right) < 0) {
            p->_right = avl::rotateRight(p->_right);
        }
        return avl::rotateLeft(p);
    }
    if (bfactor(p) == -2) {
        if(bfactor(p->_left) > 0  ) {
            p->_left = avl::rotateLeft(p->_left);
        }
        return avl::rotateRight(p);
    }
    return p; // balancing is not required
}
} // namespace detail
} // namespace avl
} // namespace bst
} // namespace treelib

#endif // TREELIB_AVL_ROTATION_HPP_
