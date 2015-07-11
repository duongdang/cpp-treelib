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

#ifndef TREELIB_BST_HPP_
#define TREELIB_BST_HPP_

#include <memory>
#include <treelib/detail/bst_detail.hpp>
#include <stdexcept>
namespace treelib {
namespace bst {

/// \brief find any node that match the given key
template <typename NodePtr, typename KeyT>
inline NodePtr find(NodePtr ipRoot, const KeyT& iKey) {
    if (!ipRoot) {
        return ipRoot;
    }
    if (iKey == ipRoot->getKey()) {
        return ipRoot;
    }
    if (iKey < ipRoot->getKey()){
        return find(ipRoot->_left, iKey);
    }
    if (iKey > ipRoot->getKey()){
        return find(ipRoot->_right, iKey);
    }
}

/// \brief insert a pair (key, data) to the tree
/// \return the new root
template <typename T, typename ValueT>
inline std::shared_ptr<T> insert(std::shared_ptr<T> ipRoot, const ValueT& iPair) {
    if( ! ipRoot ) {
        return std::make_shared<T>(iPair);
    }
    if ( T::getKey(iPair) < ipRoot->getKey() ) {
        ipRoot->_left = insert(ipRoot->_left, iPair);
    }
    else {
        ipRoot->_right = insert(ipRoot->_right, iPair);
    }
    return T::balance(ipRoot);
}

template <class NodePtr, class ContainerT>
inline void toArray(NodePtr ipRoot, ContainerT& oNodes){
    if (!ipRoot) {
        return;
    }
    if (ipRoot->_height >= 64) {
        throw std::runtime_error("The tree is too big.");
    }
    size_t aMaxSize = 1 << ipRoot->_height;
    aMaxSize -= 1;
    // std::cout << "aMaxSize: " << aMaxSize << std::endl;
    oNodes.resize(aMaxSize);
    detail::toArray(ipRoot, oNodes, 0);
}

} // namespace bst
} // namespace treelib

#endif // TREELIB_BST_HPP_
