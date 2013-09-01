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
    /**
     * @brief urlencode a string
     * @param c
     * @return encoded string
     */
    String urlencode(const String &c);

    /**
     * @brief urldecode a string
     * @param c
     * @return decoded string
     * @throw std::logic_error on invalid encoded string
     */
    String urldecode(const String &c);
}
#endif
