## doxygen tags(for commenting function descriptions):

# tags
 * @file
 * @brief
 * @author
 * @version
 * @date
 * @details
 * @brief
 * @param
 * @param
 * @return
 * @pre
 * @post
 * @note
 * @warning

# examples
/**
 * @file math_operations.h
 * @brief Basic math functions for integer calculations.
 * @author John Doe
 * @version 1.0
 * @date December 14, 2024
 *
 * @details Provides a set of basic math operations such as addition, subtraction, etc.
 */

/**
 * @brief Adds two integers.
 * @param a The first integer.
 * @param b The second integer.
 * @return The sum of the two integers.
 * @pre a and b must be non-negative.
 * @post The result is always non-negative.
 * @note This function does not handle overflow.
 * @warning Passing very large integers may cause undefined behavior.
 */