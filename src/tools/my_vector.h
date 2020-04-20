//
// Created by mhuels on 4/16/20.
//

#ifndef SHEAREDSLITPOREBD_MY_VECTOR_H
#define SHEAREDSLITPOREBD_MY_VECTOR_H

#include <vector>

using namespace std;

template<typename T, typename Alloc = std::allocator<T>>
class my_vector: public vector<T, Alloc> {
private:
    //copied from stl_vector.h
    typedef _Vector_base<T, Alloc>			_Base;
    typedef typename _Base::_Tp_alloc_type		_Tp_alloc_type;
    typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type>	_Alloc_traits;
    typedef typename _Alloc_traits::reference		reference;

public:
    //allows reading negative indices (e.g. at(-1) reads the last element)
    reference at2(int i){
        if(i < 0){
            i = this->size() + i;
        }
        return this->at(i);
    };
};
#endif //SHEAREDSLITPOREBD_MY_VECTOR_H
