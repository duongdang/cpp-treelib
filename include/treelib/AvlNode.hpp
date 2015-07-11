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

#ifndef TREELIB_AVLNODE_HPP_
#define TREELIB_AVLNODE_HPP_

#include <vector>
#include <memory>
#include <iostream>

#include <treelib/bst.hpp>
#include <treelib/detail/avl_rotation.hpp>

namespace treelib {
namespace bst {

template <typename KeyT, typename DataT>
struct AvlNode {
    typedef KeyT key_type;
    typedef std::pair<const KeyT,  DataT> value_type;
    typedef std::shared_ptr<AvlNode> node_ptr;
    typedef std::shared_ptr<const AvlNode> node_cptr;

    DataT _data;
    node_ptr _left;
    node_ptr _right;
    unsigned char _height;
    // the height is limited to 255, tree size is limit to ~ 2^255 ~ 10^76
    // "almost" enough to store all the atoms in the universe

    AvlNode() : _data(), _left(), _right(), _height(1), _key() {}
    AvlNode(const key_type& iKey, const DataT& iData)
        : _data(iData), _left(), _right(), _height(1), _key(iKey) {}
    AvlNode(const value_type& iPair)
        : _data(iPair.second), _left(), _right(), _height(1), _key(iPair.first) {}

    virtual ~AvlNode() {}

    static const key_type getKey(const value_type& iPair){ return iPair.first; }
    const key_type getKey() const { return _key; }

    /// \brief balance the tree, return the new root
    /// Could have been member function but would need shared_from_this
    static node_ptr balance(node_ptr ipRoot) { return detail::avl::balance(ipRoot); }

    void fixHeight() {
        unsigned char hl = _left ?  _left->_height : 0;
        unsigned char hr = _right ?  _right->_height : 0;
        _height = (hl > hr ? hl : hr)+1;
    }

private:
    KeyT _key;
}; // class AvlNode

// template <typename KeyT, typename DataT>
// inline std::ostream& operator<< (std::ostream& os, const AvlNode<KeyT, DataT>& aNode) {
//     os << "{";
//     if (aNode._left) {
//         os << *aNode._left;
//     }
//     else {
//         os << "None";
//     }
//     os << ", ";
//     os << aNode.getKey();
//     os << ", ";
//     if (aNode._right) {
//         os << *aNode._right;
//     }
//     else {
//         os << "None";
//     }

//     os << "}";
//     return os;
// }
} // namespace bst
} // namespace treelib

#endif // TREELIB_AVLNODE_HPP_
