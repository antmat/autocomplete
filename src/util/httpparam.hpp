//
//  httpparam.h
//  PoiSearch
//
//  Created by Anton Matveenko on 13.05.13.
//  Copyright (c) 2013 Anton Matveenko. All rights reserved.
//

#ifndef __AC__httpparam__
#define __AC__httpparam__

#include <iostream>
#include <map>
#include <set>
#include "util/string.hpp"
#include <vector>

namespace AC {
    class HttpParam {
    protected:
        String query;
        std::map<String, String> uri_param;
        unsigned int count;

        void fill_properties();
        void parse_param(String uri_params_raw);

        inline const String& get(const String& key) const {
            static String empty_string("");
            auto pos = this->uri_param.find(key);
            if(pos == this->uri_param.end()) {
                return empty_string;
            }
            return pos->second;
        }

    public:
        const static unsigned int DEFAULT_CNT;
        HttpParam(const String& get_data, const String& post_data);
        HttpParam(const String& get_data);
        virtual ~HttpParam() {};


        inline String operator[] (const String& key) const {
            return this->get(key);
        }

        inline String get_query() const {
            std::cerr << "query is " << this->query << std::endl;
            return this->query;
        }

        inline unsigned int get_count() const {
            return this->count;
        }
    };
}
#endif
