#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace AC {
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

    /**
     * @brief true when queries organized like(without spaces) "user_id1 \t query1 \n query2 \n query3 \n user_id2..."
     * false when input file is \n divided queries only
     */
    const bool USE_BY_USER_INPUT = false;

    /**
     * @brief Should we use memory to prune our tree or use fixed prunning coeff
     * WARNING! This relies on euristic memory consuption determination and periodic tree pruning.
     * That affects speed and lead to allocating more heap memory to process than it needs.
     */
    const bool USE_MEMORY_DEPENDENT_PRUNNING = false;

    /**
     * @brief Should we use memory consumption to determine chunk size or it is fixed
     * WARNING! This relies on euristic memory consuption determination and periodic tree pruning.
     * That affects speed and lead to allocating more heap memory to process than it needs.
     */
    const bool USE_MEMORY_DEPENDENT_CHUNK_SIZE = false;

    /**
     * @brief Default prunning limit for a tree
     */
    const unsigned int PRUNNING_LIMIT = 0;

    /**
     * @brief Applyy prunning each PRUNNING_FREQ steps
     */
    const unsigned int PRUNNING_FREQ = 500000;

    /**
     * @brief Default chunk size for compacting
     */
    const unsigned int CHUNK_SIZE = 5000000;
}
#endif // CONSTANTS_HPP
