
#include <cassert>
#include "Vacuum-Filter/vacuum.h"

#include <iostream>


int main() {
    VacuumFilter<int, 14> vf;

    // vf.init(max_item_numbers, slots per bucket, max_kick_steps)
    int n = 100000;
    vf.init(1e9, 4, 400);
    
    for(int i = 1; i < n; i++) {
        vf.insert(i);
    }

     if (vf.lookup(1)) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    std::cout << "Bits per key = " << vf.get_bits_per_item() << endl;

   
   
    return 0;
}