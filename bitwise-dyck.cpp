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

#include <iostream>

typedef unsigned long long integer;

/**
 * @brief A helper function to print the n least significant bits of a number as
 *        a string of n parentheses.
 * 
 * A bit one is transformed into an opening parentheses and a bit zero into a
 * closing one.
 * 
 * @param [in] w The input number.
 * @param [in] m The number of bits that are converted into parentheses.
 */
void print(integer w, unsigned m) {
  integer mask = (integer) 1u << (m - 1);
  do
    std::cout << (w & mask ? '(' : ')');
  while (mask >>= 1);
  std::cout << '\n';
}

/**
 * @brief Given a Dyck word w produces the succeding Dyck word of the same size
 *        which is greater than w.
 * 
 * @pre   w must be a Dyck word which is not the greatest of its size.
 * 
 * @param [in] w The input Dyck word.
 * 
 * @return The succeding Dyck word.
 */
integer next_dyck_word(integer w) {
  integer a = w & -w;
  integer b = w + a;
  integer c = w ^ b;
  c = (c / a >> 2) + 1;
  c = c * c - 1;
  c = (c & 12297829382473034410u) | b;
  return c;
}

int main() {
  
  unsigned n       = 4;
  unsigned two_n   = 2 * n;
  integer greatest = (1ull << n) * ((1ull << n) - 1);
  // In binary, this constant is this is "10...10" (32 pairs of "10").
  integer word     = 12297829382473034410ull >> (64 - 2 * n);
 
  do {
    print(word, two_n);
    word = next_dyck_word(word);
  } while (word <= greatest);
}
