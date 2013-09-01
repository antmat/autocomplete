#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace AC {
    //const unsigned int MAX_LINE_SIZE = 256;
    /**
     * @brief number of chunks to process between checking memory consumption
     */
    const unsigned int TEST_MEM_EACH = 1000;
    /**
     * @brief approximate(!!!) memory amount after which program will try to reduce it.
     */
    const unsigned int MAX_ALLOWED_MEM = 2000000;
    /**
     * @brief amount of data to read from file during chunks merging
     */
    const unsigned int MERGE_CHUNK_SIZE = 10000;
    /**
     * @brief As memory manager does not return memory to os in several circumstances
     * we need to check if memory consumption still grow.
     * This value is an addition amount of memory we consider as growth
     *
     */
    const unsigned int MEMORY_STEP = 1000;
}
#endif // CONSTANTS_HPP
