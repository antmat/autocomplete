//
//  string.hpp
//  PoiSearch
//
//  Created by Anton Matveenko on 22.02.13.
//  Copyright (c) 2013 Anton Matveenko. All rights reserved.
//

#ifndef AC_string_hpp
#define AC_string_hpp

#include <string>
namespace AC
{
    typedef std::string String;
    String urlencode(const String &c);
    String urldecode(const String &c);
}
#endif
