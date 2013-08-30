//
//  httpparam.cpp
//  PoiSearch
//
//  Created by Anton Matveenko on 13.05.13.
//  Copyright (c) 2013 Anton Matveenko. All rights reserved.
//

#include "httpparam.hpp"

namespace AC {
    const unsigned int HttpParam::DEFAULT_CNT = 20;
    HttpParam::HttpParam(const String& get_data, const String& post_data) :
        query(),
        uri_param(),
        count(HttpParam::DEFAULT_CNT) {
        this->parse_param(get_data);
        this->parse_param(post_data);
        this->fill_properties();
    }

    HttpParam::HttpParam(const String& get_data) :
        HttpParam(get_data, "") {
    }

    void HttpParam::fill_properties() {
        const String& q = this->get("q");
        if(q != "") {
            this->query = q;
        }
        const String& cnt = this->get("cnt");
        if(cnt != "") {
            this->count = std::stoi(cnt);
        }
    }

    void HttpParam::parse_param(String uri_params_raw) {
        auto pos = uri_params_raw.find_first_of('+');
        while ( pos != String::npos) {
            uri_params_raw[pos] = ' ';
            pos = uri_params_raw.find_first_of('+');
        }
        String key;
        size_t start_pos = 0;
        for(size_t i=0; i<=uri_params_raw.size(); i++) {
            if(uri_params_raw[i] == '=' && key == "") {
                key = String(urldecode(uri_params_raw.substr(start_pos, i-start_pos)));
                std::cerr << "key is " << key;
                start_pos = i+1;
            }
            if(uri_params_raw[i] == '&' || i==(uri_params_raw.size())) {
                if(key != "") {
                    this->uri_param[key] = urldecode(uri_params_raw.substr(start_pos, i-start_pos));
                    std::cerr << ", val is " << this->uri_param[key] << std::endl;
                    start_pos = i+1;
                    key = "";
                }
            }
        }
    }

}
