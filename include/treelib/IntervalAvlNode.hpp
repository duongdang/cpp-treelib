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

#ifndef TREELIB_INTERVALAVLNODE_HPP_
#define TREELIB_INTERVALAVLNODE_HPP_

#include <vector>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <boost/tuple/tuple.hpp>

#include <treelib/bst.hpp>
#include <treelib/detail/avl_rotation.hpp>

namespace treelib {
namespace bst {

template <typename NumberT, typename DataT>
struct IntervalAvlNode {
    typedef std::pair<NumberT, NumberT> key_type;
    typedef boost::tuple<const NumberT, const NumberT, DataT> value_type;
    typedef boost::shared_ptr<IntervalAvlNode> node_ptr;
    typedef boost::shared_ptr<const IntervalAvlNode> node_cptr;

    DataT _data;
    node_ptr _left;
    node_ptr _right;
    unsigned char _height;
    // the height is limited to 255, tree size is limit to ~ 2^255 ~ 10^76
    // "almost" enough to store all the atoms in the universe
    NumberT _start;
    NumberT _end;
    NumberT _max;

    IntervalAvlNode() : _data(), _left(), _right(), _height(1), _start(), _end(), _max() {}
    IntervalAvlNode(const NumberT& iStart, const NumberT& iEnd, const DataT& iData)
        : _data(iData), _left(), _right(), _height(1), _start(iStart), _end(iEnd), _max(_end) {}
    IntervalAvlNode(const value_type& iValue)
        : _data(boost::get<2>(iValue)), _left(), _right(), _height(1)
        , _start(boost::get<0>(iValue)), _end(boost::get<1>(iValue)), _max(_end)
        {}

    virtual ~IntervalAvlNode() {}

    static const key_type getKey(const value_type& iValue) {
        return std::make_pair(boost::get<0>(iValue), boost::get<1>(iValue));
    }
    const key_type getKey() const { return std::make_pair(_start, _end); }

    /// \brief balance the tree, return the new root
    /// Could have been member function but would need shared_from_this
    static node_ptr balance(node_ptr ipRoot) { return detail::avl::balance(ipRoot); }

    void fixHeight() {
        unsigned char hl = _left ?  _left->_height : 0;
        unsigned char hr = _right ?  _right->_height : 0;
        _height = (hl > hr ? hl : hr)+1;

        if (_left &&  _left->_max > _max) { _max = _left->_max; }
        if (_right &&  _right->_max > _max) { _max = _right->_max; }
    }

    static node_cptr find(const node_cptr ipRoot, const NumberT& iStart, const NumberT& iEnd) {
        if (!ipRoot) {
            return ipRoot;
        }
        if (iStart <= ipRoot->_end && iEnd >= ipRoot->_start) {
            return ipRoot;
        }
        if (ipRoot->_left && ipRoot->_left->_max >= iStart) {
            return find(ipRoot->_left, iStart, iEnd);
        }
        if (ipRoot->_start <= iEnd) {
            return find(ipRoot->_right, iStart, iEnd);
        }
        return node_cptr();
    }

    static void findAll(const node_cptr ipRoot, const NumberT& iStart, const NumberT& iEnd,
                        std::vector<node_cptr>& oNodes) {
        if (!ipRoot) {
            return;
        }
        if (iStart <= ipRoot->_end && iEnd >= ipRoot->_start) {
            oNodes.push_back(ipRoot);
        }
        if (ipRoot->_left && ipRoot->_left->_max >= iStart) {
            findAll(ipRoot->_left, iStart, iEnd, oNodes);
        }
        if (ipRoot->_start <= iEnd) {
            findAll(ipRoot->_right, iStart, iEnd, oNodes);
        }
    }

    static std::vector<node_cptr> findAll(const node_cptr ipRoot, const NumberT& iStart,
                                          const NumberT& iEnd) {
        std::vector<node_cptr> oNodes;
        findAll(ipRoot, iStart, iEnd, oNodes);
        return oNodes;
    }
}; // class IntervalIntervalAvlNode
} // namespace bst
} // namespace treelib

#endif // TREELIB_INTERVALAVLNODE_HPP_
