/*******************************************************************************
 
 Compile with:
 g++ -O3 -std=c++11 -Wall -Wextra -pedantic -o bitwise-dyck bitwise-dyck.cpp

 For a discussion about this code see
 http://github.com/cassioneri/Dyck

 Copyright (C) 2014 Cassio Neri.

 This work is licensed under a Creative Commons Attribution-ShareAlike 4.0
 International License. See
 http://creativecommons.org/licenses/by-sa/4.0/
 
*******************************************************************************/

#include <cstdio>

// For C++03 use unsigned long
typedef unsigned long long integer;

/**
 * @brief A helper function to print the n least significant bits of a number as
 *        a string of n c1's and c0's(where c1 and c0 are parameters).
 * 
 * A bit one is transformed into an opening parentheses and a bit zero into a
 * closing one.
 * 
 * @param [in] w  The input number.
 * @param [in] m  The number of bits that are converted into parentheses.
 * @param [in] c1 The character to be printed for each bit one.
 * @param [in] c0 The character to be printed for each bit zero.
 */
void print(integer const w, unsigned const m, char const c1, char const c0) {
  integer mask = static_cast<integer>(1u) << (m - 1);
  do
    putchar(w & mask ? c1 : c0);
  while (mask >>= 1);
  putchar('\n');
}

namespace {
  // Minimum 64-bits Dyck word, in binary, 10...10 (with 32 pairs of 10).
  static integer const min_64_bits_dyck_word =
    static_cast<integer>(12297829382473034410u);
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
integer next_dyck_word(integer w) {
  integer const a = w & -w;
  integer const b = w + a;
  integer       c = w ^ b;
                c = (c / a >> 2) + 1;
                c = ((c * c - 1) & min_64_bits_dyck_word) | b;
  return c;
}

int main() {

  unsigned const n     = 4;
  unsigned       two_n = static_cast<integer>(1) << n; // pow(2, n)
  integer const  max   = two_n * (two_n - 1);
                 two_n = 2 * n;
  
  // Variable word is initialised with minimum 2n-Dyck word.
  for (integer word = min_64_bits_dyck_word >> (64 - two_n); word <= max; ) {
    print(word, two_n, '(', ')');
    word = next_dyck_word(word);
  }
}
