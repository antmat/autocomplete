#include "util/string.hpp"
#include <sstream>
namespace AC {
    String urlencode(const String &c) {
        std::ostringstream escaped;
        size_t max = c.size();
        for(size_t i=0; i<max; i++) {
            if ( (48 <= c[i] && c[i] <= 57) ||//0-9
                 (65 <= c[i] && c[i] <= 90) ||//abc...xyz
                 (97 <= c[i] && c[i] <= 122) || //ABC...XYZ
                 (c[i]=='~' || c[i]=='!' || c[i]=='*' || c[i]=='(' || c[i]==')' || c[i]=='\'')
                 ) {
                escaped << c[i];
            }
            else {
                escaped << "%" << std::hex << static_cast<int>(c[i]);
            }
        }
        return escaped.str();
    }
    String urldecode(const String &c) {
        return c;//todo : implement!!!
    }
}
