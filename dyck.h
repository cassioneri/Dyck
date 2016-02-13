/*******************************************************************************

 Copyright (C) 2014 Cassio Neri.

 This work is licensed under a Creative Commons Attribution-ShareAlike 4.0
 International License. See
 http://creativecommons.org/licenses/by-sa/4.0/
 
 For a discussion about this code and latest version:
 http://github.com/cassioneri/Dyck
 
*******************************************************************************/

#include <cassert>
#include <climits>
#include <cstdio>
#include <string>

namespace dyck {

#if __cplusplus >= 201103L

  typedef unsigned long long integer;

#else
  
  typedef unsigned long integer;

  // Fake C++11 features
  #define static_assert(c, m) typedef char static_assert_cpp_98[c && m]
  #define nullptr             0
  #define noexcept            throw()
  #define constexpr
  
#endif
  
#if __cplusplus >= 201402L
  #define CONSTEXPR14 constexpr
#else
  #define CONSTEXPR14
#endif
 
/**
 * @brief Print a given 2n-bits word replacing 1 and 0 by c1 and c0, resp.
 * 
 * @param [in] w    The word.
 * @param [in] n    Half size.
 * @param [in] one  The character to be printed for each bit one.
 * @param [in] zero The character to be printed for each bit zero.
 */
void print(integer const w, unsigned const n, char const c1, char const c0);

static unsigned const max_size = sizeof(integer) * CHAR_BIT;

static_assert(max_size <= 64, "type 'integer' is too big!");

// 0xaaaaaaaaaaaaaaaa is the minimum 64-bits Dyck word.
static integer const minimum_of_max_size = 0xaaaaaaaaaaaaaaaa;

/**
 * @brief Get the maximum 2n-bits Dyck word, that is, (pow(2, n) - 1) * pow(2, n).
 * 
 * @pre   2n <= max_size.
 * 
 * @param [in] n Half size.
 * 
 * @return The maximum 2n-bits Dyck word.
 */
CONSTEXPR14 inline integer maximum(unsigned n) noexcept {
  assert(2 * n <= max_size && "n is too big!");
  return ((static_cast<integer>(1) << n) - 1) << n;
}

/**
 * @brief Get the minimum 2n-bits Dyck word, that is, 2 * (pow(4, n) - 1) / 3.
 * 
 * @pre   2n <= max_size.
 * 
 * @param [in] n Half size.
 * 
 * @return The minimum 2n-bits Dyck word.
 */
CONSTEXPR14 inline integer minimum(unsigned n) noexcept {
  assert(2 * n <= max_size && "n is too big!");
  return minimum_of_max_size >> (max_size - 2 * n);
}

/**
 * @brief Given a Dyck word w produces the next Dyck word of the same size.
 * 
 * @pre   w must be a Dyck word which is not the greatest of its size.
 * 
 * @param [in] w The input Dyck word.
 * 
 * @return The next Dyck word.
 */ 
CONSTEXPR14 inline integer next(integer w) noexcept {
  integer const a = w & -w;
  integer const b = w + a;
  integer       c = w ^ b;
                c = (c / a >> 2) + 1;
                c = ((c * c - 1) & minimum_of_max_size) | b;
  return c;
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
