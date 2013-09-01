#include <iostream>
#include <cstring>
#include "util/httpparam.hpp"
#include "blizzard/plugin.hpp"
#include "preprocessor.hpp"
namespace AC {
    class Plugin : public blz_plugin
    {
    protected:
        Tree tree;
    public:

        inline Plugin() :
            tree()
        {
        }
        virtual ~Plugin() throw()
        {}
        virtual int load(const char* fname)
        {
            String tree_data(fname);
            Preprocessor::load_tree(this->tree, tree_data);
            return BLZ_OK;
        }

        virtual int easy(blz_task* task)
        {
            try
            {
                std::string post_data (reinterpret_cast<const char*>(task->get_request_body()), task->get_request_body_len());
                std::string get_data(task->get_request_uri_params());
                HttpParam http_param(get_data, post_data);
                std::vector<String> suggests;
                this->tree.fill_suggests(http_param.get_query(), suggests, http_param.get_count());
                String response;
                for(auto& suggest : suggests) {
                    response += suggest + "<br>";
                }
                task->add_response_header("Content-type", "text/html; charset=utf-8");
                task->add_response_buffer(response.c_str(),response.size());
                task->set_response_status(200);
                std::cerr << "request done. Results count " + std::to_string(suggests.size()) + "\n";
                return BLZ_OK;
            }
            catch (std::exception& e)
            {
                task->set_response_status(500);
                task->add_response_buffer(e.what(), strlen(e.what()));
                return BLZ_ERROR;
            }
        }

        int hard(blz_task* task)
        {
            task->set_response_status(500);
            return BLZ_OK;
        }
    };
    extern "C" blz_plugin* get_plugin_instance()
    {
        return new Plugin();
    }

}

