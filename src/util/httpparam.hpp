//
//  httpparam.h
//  AC
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

        /**
         * @brief fill custom properties which can be got through their getters
         */
        void fill_properties();

        /**
         * @brief parse_param parsing string to key value pairs of param names, param values and stores them in uri_params var.
         * @param uri_params_raw a string with valid http params.  N.B. string is not being checked for validity!
         */
        void parse_param(String uri_params_raw);

        /**
         * @brief get arbitrary param in string representation.
         * @param key
         * @return
         */
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
        /**
         * @brief Construct from GET data and POST data. All parameters will be parsed.
         * If post_data will have the same keys with different values they will be overwritten
         * @param get_data
         * @param post_data
         */
        HttpParam(const String& get_data, const String& post_data);

        /**
         * @brief Construct only from GET string.
         * @param get_data
         */
        HttpParam(const String& get_data);

        virtual ~HttpParam() {};


        /**
         * @brief get arbitrary param in string representation.
         * The same as internal get, but returns a copy.
         * @param key
         * @return
         */
        inline String operator[] (const String& key) const {
            return this->get(key);
        }

        /**
         * @brief get query parameter
         * @return query as string
         */
        inline String get_query() const {
            return this->query;
        }

        /**
         * @brief get count parameter
         * @return count as unsigned integer
         */
        inline unsigned int get_count() const {
            return this->count;
        }
    };
}
#endif
