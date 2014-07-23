/*******************************************************************************

 Copyright (C) 2014 Cassio Neri.

 This work is licensed under a Creative Commons Attribution-ShareAlike 4.0
 International License. See
 http://creativecommons.org/licenses/by-sa/4.0/
 
 For a discussion about this code and latest version:
 http://github.com/cassioneri/Dyck
 
 Compile with:
 g++ -O3 -std=c++11 -Wall -Wextra -pedantic -o dyck dyck-lib.cpp dyck.cpp
 or
 g++ -O3 -std=c++98 -Wall -Wextra -pedantic -o dyck dyck-lib.cpp dyck.cpp

*******************************************************************************/

#include <iostream>
#include <cstdlib>

#include "dyck.h"

void print_help_and_exit(char* name) {
  std::cout << "usage: " << name << " [-hs] n\n";
  exit(0);
}

int main(int argc, char* argv[]) {
  
  // Not very robust parsing!
  long n          = 0;
  bool use_string = false;
  
  while (--argc) {
    
    if (argv[argc][0] == '-') {
      
      const char* p = argv[argc];
      
      while (*++p) {
        
        switch (*p) {
          
          case 's' :
            use_string = true;
            break;
            
          case 'h' :
            print_help_and_exit(argv[0]);
        }
      }
    }
    
    else {
      char** end = nullptr;
      n = strtol(argv[argc], end, 0);
      if (n <= 0 || n > static_cast<long>(dyck::max_size)) {
        std::cerr <<
          argv[0] << ": invalid argument! " <<
          argv[0] << ": must be an integer in [1, " << dyck::max_size << "].\n";
        exit(-1);
      }
    }
  }
  
  if (n == 0)
    print_help_and_exit(argv[0]);
    
  if (use_string) {
    for (std::string w = dyck::minimum(n, '(', ')'); !w.empty(); dyck::next(w))
      std::cout << w << '\n';
  }
  else {
    dyck::integer const last = dyck::maximum(n);
    for (dyck::integer w = dyck::minimum(n); w <= last; w = dyck::next(w))
      dyck::print(w, n, '(', ')');
  }
}
