/*******************************************************************************

 Copyright (C) 2014 Cassio Neri.

 This work is licensed under a Creative Commons Attribution-ShareAlike 4.0
 International License. See
 http://creativecommons.org/licenses/by-sa/4.0/
 
 For a discussion about this code and latest version:
 http://github.com/cassioneri/Dyck
 
 Compile with:
 g++ -O3 -std=c++14 -Wall -Wextra -pedantic -o dyck dyck-lib.cpp dyck.cpp
 or
 g++ -O3 -std=c++11 -Wall -Wextra -pedantic -o dyck dyck-lib.cpp dyck.cpp
 or
 g++ -O3 -std=c++98 -Wall -Wextra -pedantic -o dyck dyck-lib.cpp dyck.cpp
 
 If -DDYCK_POPCOUNT added to the compiler options, then bg
 a non-portable optmized
 version is generated.
*******************************************************************************/

#include <iostream>
#include <cstdlib>

#include "dyck.h"

void print_help_and_exit(char* name) {
  std::cout << "usage: " << name << " [-abhs] n\n"
  "Options:\n"
  "a\tIgnore n and print all Dyck words (for the binary algorithm only)\n"
   "\tIt will take forever (kill the process to finish).\n"
  "b\tPrint binary number instead of strings of parentheses.\n"
  "h\tPrint this message and exit.\n"
  "n\tPrint the decimal number instead of string of parentheses (for \n"
   "\tthe binary algorithm only).\n"
  "s\tRun the slow string based algorithm (rather than the fast binary\n"
    "\tbased one).\n";
  
  exit(0);
}

int main(int argc, char* argv[]) {
      
  // Not very robust parsing!
  long n          = 0;
  bool all        = false;
  bool use_01     = false;
  bool use_string = false;
  bool use_number = false;
  
  while (--argc) {
    
    if (argv[argc][0] == '-') {
      
      const char* p = argv[argc];
      
      while (*++p) {
        
        switch (*p) {
          
          case 'a' :
            all = true;
            break;
            
          case 'b' :
            use_01 = true;
            break;
            
          case 's' :
            use_string = true;
            break;
            
          case 'n' :
            use_number = true;
            break;
            
          case 'h' :
            print_help_and_exit(argv[0]);
        }
      }
    }
    
    else {
      char** end = nullptr;
      n = strtol(argv[argc], end, 0);
      if (n <= 0 || n > static_cast<long>(dyck::max_half_size)) {
        std::cerr <<
          argv[0] << ": invalid argument! " <<
          argv[0] << ": must be an integer in [1, " << dyck::max_half_size << "].\n";
        exit(-1);
      }
    }
  }
  
  if (!all && n == 0)
    print_help_and_exit(argv[0]);
  
  char const c0 = use_01 ? '0' : ')';
  char const c1 = use_01 ? '1' : '(';
    
  if (use_string) {
    for (std::string w = dyck::minimum(n, c1, c0); !w.empty(); dyck::next(w))
      std::cout << w << '\n';
  }
  
  else if (all) {
      
    n               = 1;
    dyck::integer w = 2;
    
    // Even with proper stop criterium the execution will take "forever" and
    // the user will have to kill the process. Hence, there's no point of
    // fixing the loop condition.
    while (true) {
        
        if (use_number) std::cout << w << '\n'; 
        else            dyck::print(w, n << 1, c1, c0);
        
        w  = dyck::next(w);
        dyck::integer const p = (w >> n) >> n;
        w += (3*p << n) << (n - 1);
        n += p;
    }
  }
  
  else {
      
    dyck::integer const last = dyck::maximum(n);
    
    for (dyck::integer w = dyck::minimum(n); w < last; w = dyck::next(w))
      dyck::print(w, n << 1, c1, c0);
    
    dyck::print(last, n << 1, c1, c0);
  }
}
