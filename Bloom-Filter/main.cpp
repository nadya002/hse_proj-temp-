#include <Bloom_filt.h>
#include <iostream>

int main() {

    size_t N = 1e6;
    BloomFilter<int> filt(N);
    
    for (int i = 0; i < N; i++) {
        filt.insert(i);
    }

    int flag = 0;
    for(int i = 0; i < N; i++) {
        if (!filt.lookup(i)) {
            flag = 1;
        }
    }

    if(flag == 1) {
        std::cout << "False Negative\n";
    } else {
        std::cout << "No False Negative\n";
    }

    size_t wr_numb = 0;
    for(int i = N; i < 2 * N; i++) {
        if (filt.lookup(i)) {
            wr_numb++;
        }
    }

    std::cout << "False positive rate " << (double) ((double)wr_numb / (double)N) * 100.0 << "%" << "\n";
    std::cout << filt.bitsPerItem() << "\n";
    return 0;
}