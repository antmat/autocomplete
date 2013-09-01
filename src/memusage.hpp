//
//  memusage.h
//  PoiSearch
//
//  Created by Anton Matveenko on 10.04.13.
//  Copyright (c) 2013 Anton Matveenko. All rights reserved.
//

#ifndef __PoiSearch__memusage__
#define __PoiSearch__memusage__

namespace AC {

    /**
     * @brief takes two unsigned ints by reference,
     * attempts to read the system-dependent data for a process' virtual memory
     * size and resident set size, and return the results in KB. On failure, returns 0, 0
     * @param vm_usage
     * @param resident_set
     */
    void process_mem_usage(unsigned int& vm_usage, unsigned int& resident_set);

    /**
     * @brief takes two doubles by reference,
     * attempts to read the system-dependent data for a process' virtual memory
     * size and resident set size, and return the results in KB. On failure, returns 0.0, 0.0
     * @param vm_usage
     * @param resident_set
     */
    void process_mem_usage(double& vm_usage, double& resident_set);
}
#endif /* defined(__PoiSearch__memusage__) */
