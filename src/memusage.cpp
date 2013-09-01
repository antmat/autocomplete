#include "memusage.hpp"
#include <unistd.h>
#include <ios>
#include <iostream>
#include <fstream>
#include "util/string.hpp"

namespace AC {
    void process_mem_usage(unsigned int& vm_usage, unsigned int& resident_set) {
        double _vm_usage, _resident_set;
        process_mem_usage(_vm_usage, _resident_set);
        vm_usage = static_cast<unsigned int>(_vm_usage);
        resident_set = static_cast<unsigned int>(_resident_set);
    }
    void process_mem_usage(double& vm_usage, double& resident_set)
    {
        using std::ios_base;
        using std::ifstream;
        using std::string;

        vm_usage     = 0.0;
        resident_set = 0.0;

        // 'file' stat seems to give the most reliable results
        //
        ifstream stat_stream("/proc/self/stat",ios_base::in);

        // dummy vars for leading entries in stat that we don't care about
        //
        String pid, comm, state, ppid, pgrp, session, tty_nr;
        String tpgid, flags, minflt, cminflt, majflt, cmajflt;
        String utime, stime, cutime, cstime, priority, nice;
        String O, itrealvalue, starttime;

        // the two fields we want
        //
        unsigned long vsize;
        long rss;

        stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
                    >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
                    >> utime >> stime >> cutime >> cstime >> priority >> nice
                    >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

        stat_stream.close();

        long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
        vm_usage     = static_cast<double>(vsize) / 1024.0;
        resident_set = static_cast<double>(rss * page_size_kb);
    }
}
