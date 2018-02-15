/*******************************************************************************

 Copyright (C) 2014 Cassio Neri.

 This work is licensed under a Creative Commons Attribution-ShareAlike 4.0
 International License. See
 http://creativecommons.org/licenses/by-sa/4.0/
 
 For a discussion about this code and latest version:
 http://github.com/cassioneri/Dyck
 
*******************************************************************************/

#include <climits>
#include <cstdio>
#include <string>

namespace dyck {

#if __cplusplus >= 201103L

  typedef unsigned long long integer;
  
  #define DYCK_POPCOUNT_FUNCTION __builtin_popcountll
  #define DYCK_CTZ_FUNCTION      __builtin_ctzll

#else
  
  typedef unsigned long integer;

  #define DYCK_POPCOUNT_FUNCTION __builtin_popcountl
  #define DYCK_CTZ_FUNCTION      __builtin_ctzl

  // Fake C++11 features for C++98 compilers.
  #define nullptr   0
  #define noexcept  throw()
  #define constexpr
  
#endif
 
/**
 * @brief Print a given n-bits number in binary replacing 1 and 0 by c1 and c0,
 *        respectively.
 * 
 * @pre   w <= 2^n - 1.
 * 
 * @param [in] w  The number to be printed.
 * @param [in] n  The number of bits.
 * @param [in] c1 The character to be printed for each 1-bit.
 * @param [in] c0 The character to be printed for each 0-bit.
 */
void print(integer w, unsigned n, char c1, char const c0);

/**
 * Maximum allowed half size for a Dyck word.
 */
static unsigned constexpr max_half_size = sizeof(integer) * CHAR_BIT >> 1;

/**
 * @brief Get the minimum 2n-long Dyck word if n > 0 or zero if n = 0.
 * 
 * For backward compatibility with C++98, this is template meta-programming
 * function rather than a constexpr function.
 * 
 * @pre   n <= max_half_size.
 * 
 * @tparam n Zero or half size of the Dyck word.
 * 
 * @retval value  Zero if n = 0; or 2 * (4^n - 1) / 3 if n > 0.
 */
template <unsigned n>
struct minimum_t {
    static const integer value = (minimum_t<n - 1>::value << 2) | 2;
};

template <>
struct minimum_t<0> {
    static const integer value = 0;
};

static integer constexpr min_max_size = minimum_t<max_half_size>::value;

inline integer constexpr minimum(unsigned n) noexcept {
  return min_max_size >> (max_half_size - n) >> (max_half_size - n);
}

/**
 * @brief Get the maximum 2n-long Dyck word if n > 0 or zero if n = 0;
 * 
 * @pre   n <= max_half_size.
 * 
 * @param [in] n Zero or half size of the Dyck word.
 * 
 * @return 2^(2n) - 2^n.
 */
inline integer constexpr maximum(unsigned n) noexcept {
  return ((static_cast<integer>(1) << n) - 1) << n;
}

#if defined(DYCK_POPCOUNT)

inline unsigned constexpr popcount(integer c) {
  return DYCK_POPCOUNT_FUNCTION(c);
}

inline unsigned constexpr ctz(integer c) {
  return DYCK_CTZ_FUNCTION(c);
}

/**
 * @brief Count the 1-bits in a number of the form 2^m - 2^n with m > n.
 * 
 * @pre   The given number is of the form 2^m - 2^n with m > n.
 * 
 * @param [in] c The number whose 1-bits we want to count.
 * @param [in] a The number 2^n.
 * 
 * @return The number of 1-bits in c.
 */
inline unsigned constexpr get_count(integer c, integer a) {
  #if defined(__POPCNT__) || !defined(__x86_64__)
    return popcount(c);
  #else
    return ctz(c + a) - ctz(a);
  #endif
}

#endif // DYCK_POPCOUNT

/**
 * @brief Given a Dyck word w produces the next Dyck word of the same size.
 * 
 * @pre   w must be a Dyck word which is not the greatest of its size.
 * 
 * @param [in] w The input Dyck word.
 * 
 * @return The next Dyck word.
 */ 
inline integer next(integer w) noexcept {
  integer a = w & -w;
  integer b = w + a;
  integer       c = w ^ b;
  #if defined(DYCK_POPCOUNT)
                c = minimum(get_count(c, a) - 2);
  #else                
                c = (c / a >> 2) + 1;
                c = ((c * c - 1) & min_max_size);
  #endif
  return b | c;
}

/**
 * @brief Get the minimum 2n-long Dyck word.
 * 
 * @param [in] n    Half size.
 * @param [in] one  The character that appears more often in each prefix.
 * @param [in] zero The character that appears less often in each prefix.
 * 
 * @return The minimum 2n-long Dyck word.
 */
std::string minimum(unsigned n, char const one, char const zero);

/**
 * @brief Given a Dyck word w produces the next Dyck word of the same size, if
 *        it exists or an empty string otherwise.
 * 
 * @pre   w must be a Dyck word.
 * 
 * @param [in/out] w On entry, the input Dyck word.
 *                   On exit the succeding Dyck word, if it exists or empty
 *                   otherwise.
 */
std::string& next(std::string& w) noexcept;

} // namespace dyck
