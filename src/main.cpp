/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#include <string>
#include <map>
#include <list>
#include <algorithm>


// // 
// MISRA_CPP_03_09_02 기본 숫자 타입 대신 크기와 부호를 나타내는 typedef를 사용해야 함
#include "../include/xmanager.h"
#include "../include/geometry/xmulti_polygon.h"

std::int32_t main(std::int32_t argc, std::char_t *argv[])
{
	/// TEST
 
    { // 빈나 참조
        std::shared_ptr<my::xobject> _Uptr = std::make_shared<my::xmaneuver>();
        std::shared_ptr<my::xmaneuver> _Dptr = std::dynamic_pointer_cast<my::xmaneuver>(_Uptr);
        if (nullptr == _Dptr)
        {
            // error
        }
    }
    
    { // MISRA_CPP_18_04_01 동적 힙 메모리 할당은 사용하면 안됨 
        std::shared_ptr<my::xobject> _Pptr;
 
        // weak_ptr lock() 함수로 shared_ptr 로 변환
        _Pptr = my::xmanager::instance().insert(std::make_shared<my::xmaneuver>()).lock();  
        if (nullptr != _Pptr)
        {
            std::shared_ptr<my::xobject> _Ptr = my::xmanager::instance().insert(std::make_shared<my::xsupport>()).lock();  
            if (nullptr != _Ptr)
            {
                // something
                _Ptr->set_parent( _Pptr.get() );
            }
        }
  
    }
    { // MISRA_CPP_05_02_03 상위(base) 클래스를 하위(derived)클래스로 변환하는 것은 다형(polymorphic) 타입 간에 이루어져서는 안됨
        for (auto &_Elem : my::xmanager::instance().xobjects())
        { 
            // down casting, cross casting 해결방안 ?
            // my::xground *_Ptr = std::dynamic_cast<my::xground *>(_Elem.second.get());
            std::shared_ptr<my::xground> _Ptr = std::dynamic_pointer_cast<my::xground>(_Elem.second);
            if (nullptr != _Ptr)
            {
                // MISRA_CPP_10_03_01 상속 계층을 따라 각 virtual function 정이는 하나씩만 존재해야 함
                // 하위(derived)클래스의 함수를 상위(base)클래스 pure virtual 로 만든다.
                _Ptr->refresh();
            }
        }
        my::xmanager::instance().erase( 1 );        
    }
    { // MISRA_CPP_00_01_07 함수 반환 값 미사용 금지
          std::int32_t _Key = 1;
          std::map<std::int32_t, std::int32_t> _Map;
          _Map.insert(std::make_pair(_Key, 0));
          auto _Pair = _Map.insert(std::make_pair(_Key, 0));
          if (!_Pair.second) {
                // error
          }
          if (0==_Map.erase( _Key )) {
                // error
          }
    }
    { // MISRA_CPP_00_01_07 함수 반환 값 미사용 금지
          std::int32_t _Key = 1;
          std::list<std::int32_t> _List;
          _List.push_back(_Key);
          auto _Iter = std::find(_List.begin(), _List.end(), _Key);
          if ( _Iter != _List.end() )
          {
                _Iter = _List.erase( _Iter );
                // _Iter 변수 >>> MISRA_CPP_00_01_06 변수 값 할당 후에 한 번도 사용하지 않는 프로세스 금지 
                // 해결방안 ?
          }
    }

     {// POLYGON || MULTIPOLYGON
        /*
        std::unique_ptr<my::xpolygon> _Puptr = std::make_unique<my::xpolygon>();
         
        _Puptr->push_back(0, 0);
        _Puptr->push_back(2, 0);
        _Puptr->push_back(2, 2);
        _Puptr->push_back(0, 2);
        _Puptr->push_back(0, 0);
         // _Puptr->read_wkt("POLYGON((0 0,2 0,2 2,0 2,0 0))");
        std::cout << "POLYGON area: " << _Puptr->area() << std::endl;
        std::cout << "POLYGON length: " << _Puptr->length() << std::endl;
        std::cout << "POLYGON within: " << _Puptr->within(10, 10) << ", " << _Puptr->within(0, 0) << ", " << _Puptr->within(1, 1) << std::endl;
        
        std::unique_ptr<my::xmulti_polygon> _MPuptr = std::make_unique<my::xmulti_polygon>();
        _MPuptr->push_back( std::move(_Puptr) );
        std::cout << "MULTIPOLYGON area: " << _MPuptr->area() << std::endl;
        std::cout << "MULTIPOLYGON length: " << _MPuptr->length() << std::endl;
        std::cout << "MULTIPOLYGON within: " << _MPuptr->within(10, 10) << ", " << _MPuptr->within(0, 0) << ", " << _MPuptr->within(1, 1) << std::endl;      
        */
         
    }
  
    std::cout << ">>>>> application quit " << std::endl;
 
    return 1;
}
