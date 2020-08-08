/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#include <memory>
#include <mutex>
#include <vector>

#include "xcoordinate.h"

namespace proj_devs
{
class xpolygon
{
private:
    std::vector<std::unique_ptr<xcoordinate>> _Mycoordinates;
    
public:
    xpolygon() = default;
    ~xpolygon() = default;

    void clear()
    {
        this->_Mycoordinates.clear();
    }    
    bool empty()
    {
        this->_Mycoordinates.empty();
    }
    void set_wkt(const std::string &_WKT)
    {
        // WKT(Well-Known Text) Geometry
        // POLYGON((1 1,2 1,2 2,1 2,1 1))
        // MULTIPOLYGON(((1 1,2 1,2 2,1 2,1 1)),((3 3,3 5,5 5,5 3,3 3)))
        this->clear();
        
    }
    
    xcoordinate *get_coordinateN (std::size_t _Num)
    {
        xcoordinate *_Ptr = nullptr;
        // Notice that the first element has a position of 0 (not 1).
        if (this->_Mycoordinates.size() > _Num )
        {
            _Ptr = this->_Mycoordinates.at(_num).get();
        }
        return _Ptr;
    }

    void push_back(std::int32_t _X, std::int32_t _Y)
    {
        this->_Mycoordinates.push_back( std::make_unique<proj_devs::xcoordinate>(_X, _Y) );
    }
    void push_back(std::unique_ptr<xcoordinate> _Uptr)
    {
        this->_Mycoordinates.push_back( std::move(_Uptr) );
    }
    
    std::float64_t area()
    {
        std::float64_t _Val = 0.0;
        std::int32_t _Max = this->_Mycoordinates.size();
        
        for (std::int32_t _Num = 0, _Num < _Max; ++_Num)
        {
            // _Num is the index of the first vertex, _Next is the next one.
            std::int32_t _Next = (_Num + 1) % _Max;
            
            // The vertices of the edge we are checking.
            std::int32_t _X0 = this->_Mycoordinates[_Num]->x();
            std::int32_t _Y0 = this->_Mycoordinates[_Num]->y();
            std::int32_t _X1 = this->_Mycoordinates[_Next]->x();
            std::int32_t _Y1 = this->_Mycoordinates[_Next]->y();
   
            _Val += (0.5 * (_X0*_Y1 - _X1*_Y0));  
        }
        return _Val;        
    }
    
    std::float64_t length();
    {
        std::float64_t _Val = 0.0;
        std::int32_t _Max = this->_Mycoordinates.size();
        
        for (std::int32_t _Num = 0, _Num < _Max; ++_Num)
        {
            // _Num is the index of the first vertex, _Next is the next one.
            std::int32_t _Next = (_Num + 1) % _Max;
            
            // The vertices of the edge we are checking.
            std::int32_t _X0 = this->_Mycoordinates[_Num]->x();
            std::int32_t _Y0 = this->_Mycoordinates[_Num]->y();
            std::int32_t _X1 = this->_Mycoordinates[_Next]->x();
            std::int32_t _Y1 = this->_Mycoordinates[_Next]->y();
   
            _Val += (sqrt(pow(_X1 - _X0, 2) + pow(_Y1 - _Y0, 2)));
        } 
        return _Val;
    }

    // https://en.wikipedia.org/wiki/Point_in_polygon#Ray_casting_algorithm
    // https://wrf.ecse.rpi.edu//Research/Short_Notes/pnpoly.html
    bool within(std::int32_t _X, std::int32_t _Y)
    {
        // If we never cross any lines we're inside.
        bool _Inside = false;
        std::int32_t _Max = this->_Mycoordinates.size();
    
        for (std::int32_t _Num = 0, _Num < _Max; ++_Num)
        {
            // _Num is the index of the first vertex, _Next is the next one.
            std::int32_t _Next = (_Num + 1) % _Max;
            
            // The vertices of the edge we are checking.
            std::int32_t _X0 = this->_Mycoordinates[_Num]->x();
            std::int32_t _Y0 = this->_Mycoordinates[_Num]->y();
            std::int32_t _X1 = this->_Mycoordinates[_Next]->x();
            std::int32_t _Y1 = this->_Mycoordinates[_Next]->y();

            // First check if the line crosses the horizontal line at _Y in either direction.
            if (((_Y0 <= _Y) && (_Y1 > _Y)) || ((_Y1 <= _Y) && (_Y0 > _Y)))
            {
                // If so, get the point where it crosses that line. This is a simple solution
                // to a linear equation. Note that we can't get a division by zero here -
                // if _Y1 == _Y0 then the above if be false.
                std::float64_t _Cross = (_X1 - _X0) * (_Y - _Y0) / (_Y1 - _Y0) + _X0;
                
                // Finally check if it crosses to the left of our test point. You could equally
                // do right and it should give the same result.
                if (_Cross < _X)
                {
                    _Inside = !_Inside;
                }
            }
        } /* for */
        
    }
 
};
    
} /* namespace proj_devs */
