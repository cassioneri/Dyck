/*******************************************************************************

 Copyright (C) 2014 Cassio Neri.

 This work is licensed under a Creative Commons Attribution-ShareAlike 4.0
 International License. See
 http://creativecommons.org/licenses/by-sa/4.0/
 
 For a discussion about this code and latest version:
 http://github.com/cassioneri/Dyck

*******************************************************************************/

#include "dyck.h"

namespace dyck {

void print(integer const w, unsigned const n, char const one, char const zero) {
  integer mask = n == 0 ? 1 : static_cast<integer>(1) << (n - 1);
  do
    putchar(w & mask ? one : zero);
  while (mask >>= 1);
  putchar('\n');
}

std::string minimum(unsigned n, char const one, char const zero) {
  
  std::string w;
  w.reserve(2 * n);
  
  while(n-- != 0) {
    w += one;
    w += zero;
  }
  return w;
}

std::string& next(std::string& w) noexcept {
  
  unsigned const m    = w.size() - 1;
  unsigned       y    = 0;
  unsigned       x    = 0;
  char     const one  = w[0];
  char     const zero = w[m];

  for (unsigned i = m; i > 0; --i) {

    if (w[i] == zero)
      ++y; // Counter for trailing zeros.

    else if (w[i - 1] == zero) {
      
      // Found greatest i such that w[i] = zero and w[i + 1] = one.
      
      // Change these two chars.
      w[i - 1] = one;
      w[  i  ] = zero;
      
      // Overwrite the following next y - x chars to zero.
      for (y = y - x; y != 0; --y)
        w[++i] = zero;
      
      // Overwrite the remaining chars with alternating ones and zeros.
      while (i < m) {
        w[++i] = one;
        w[++i] = zero;
      }
      return w;
    }

    else
      ++x; // Counter for ones that precede the trailing zeros.
  }
  w.clear(); // Failed to produce a Dyck word, then clear w.
  return w;
}

} // namespace dyck
