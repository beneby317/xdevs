/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#include "../include/xmanager.h"

namespace my
{
std::unique_ptr<xmanager> xmanager::_Myinstance;
std::once_flag xmanager::_Myonce_flag;
int32_t xmanager::_Myunique_identifier;
    
xmanager::xmanager()
{
}

xmanager& xmanager::instance()
{
    std::call_once(_Myonce_flag, []() {
        _Myinstance.reset(new xmanager);
    });
    return *(_Myinstance.get());
}

int32_t xmanager::generate_unique_identifier()
{
    return ++_Myunique_identifier;
} 
const std::map<int32_t, std::shared_ptr<xobject>>& xmanager::xobjects()
{
    return this->_Myxobjects;
}
 
std::weak_ptr<xobject> xmanager::insert( std::shared_ptr<xobject> _Ptr)
{
    std::weak_ptr<xobject> _Wptr = _Ptr;
    if (0==_Ptr->key())
    {
        _Ptr->set_key( generate_unique_identifier() );
        _Ptr->set_name( std::to_string(_Ptr->key()));
    }
    auto _Pair = this->_Myxobjects.insert(std::make_pair(_Ptr->key(), std::move(_Ptr)));
    if (!_Pair.second) {
        // error
        _Ptr = nullptr;
    }
    return _Wptr;
}
void xmanager::erase( std::int32_t _Key)
{
    std::cout << ">>>>> xmanager::erase " << std::endl;
    std::cout << " - key " << _Key << std::endl;
    if (0 == this->_Myxobjects.erase(_Key))
    {
        // error
    }
}

// api
xmanager* get_xmanager_ptr()
{
    return &xmanager::instance();
}
 
} /* namespace proj_devs */
