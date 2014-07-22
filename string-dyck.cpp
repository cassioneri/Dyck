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
 * @brief Given a Dyck word w produces the next Dyck word of the same size, if
 *        it exists or an empty string otherwise.
 * 
 * @pre   w must be a Dyck word.
 * 
 * @param [in/out] w On entry, the input Dyck word.
 *                   On exit the succeding Dyck word, if it exists or empty
 *                   otherwise.
 * @param [in] c1    The character that appears more often in each prefix.
 * @param [in] c0    The character that appears less often in each prefix.
 */
void next_dyck_word(std::string& w, char const c1, char const c0) {
  
  unsigned const m = w.size() - 1;
  unsigned       y = 0;
  unsigned       x = 0;

  for (unsigned i = m; i > 0; --i) {

    if (w[i] == c0)
      ++y; // Counter for trailing zeros.

    else if (w[i - 1] == c0) {
      
      // Found greatest i such that w[i] = c0 and w[i + 1] = c1.
      
      // Change these two chars.
      w[i - 1] = c1;
      w[  i  ] = c0;
      
      // Overwrite the following next y - x chars to c0.
      for (y = y - x; y != 0; --y)
        w[++i] = c0;
      
      // Overwrite the remaining chars with alternating ones and zeros.
      while (i < m) {
        w[++i] = c1;
        w[++i] = c0;
      }
      return;
    }

    else
      ++x; // Counter for ones that precede the trailing zeros.
  }
  w.clear(); // Failed to produce a Dyck word, then clear w.
}

int main() {
  
  unsigned n = 4;
  
  std::string w;
  while(n-- != 0)
    w += "()";
  
  while (!w.empty()) {
    std::cout << w << '\n';
    next_dyck_word(w, '(', ')');
  }
}
