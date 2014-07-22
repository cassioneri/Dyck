/*******************************************************************************
 
 Compile with:
 g++ -O3 -std=c++11 -Wall -Wextra -pedantic -o string-dyck string-dyck.cpp

 For a discussion about this code see
 http://github.com/cassioneri/Dyck

 Copyright (C) 2014 Cassio Neri.

 This work is licensed under a Creative Commons Attribution-ShareAlike 4.0
 International License. See
 http://creativecommons.org/licenses/by-sa/4.0/
 
*******************************************************************************/

#include <string>
#include <iostream>

/**
 * @brief Given a Dyck word w produces the succeding Dyck word of the same size
 *        which is greater than w, if it exists or an empty string otherwise.
 * 
 * @pre   w must be a Dyck word.
 * 
 * @param [in/out] w   On entry, the input Dyck word.
 *                     On exit the succeding Dyck word, if it exists or empty,
 *                     otherwise.
 * @param one          The char that appears more often in prefix substrings.
 * @param zero         The chat that appears less often in prefix substrings.
 */
void next_dyck_word(std::string& w, char one, char zero) {
  
  unsigned m = w.size() - 1;

  unsigned y = 0;
  unsigned x = 0;

  for (unsigned i = m; i > 0; --i) {

    if (w[i] == zero)
      ++y; // counter for trailing zeros.

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
      return;
    }

    else
      ++x; // counter for ones that precede the trailing zeros.
  }
  w.clear(); // Failed to produce a Dyck word, then clear w.
}

int main() {
  
  unsigned n = 7;
  
  std::string w;
  while(n-- != 0)
    w += "()";
  while (!w.empty()) {
    std::cout << w << '\n';
    next_dyck_word(w, '(', ')');
  }
}
