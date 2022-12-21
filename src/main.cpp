#include <iostream>
#include "chainhash.hpp"

void display(ChainHash const& hash) {
    using namespace std;
    for(int i = 0; i != hash.capacity; ++i) {
        std::cout << i;
        for(auto const& x : hash.table[i]) {
            std::cout << " --> " << x;
        }
        std::cout << std::endl;
    }
    std::cout << "count: " << hash.count() << std::endl;
}


int main() {

    std::vector<std::string> strs{"Hello world!", "Hello dlrow!", "Python is shit", "Linux Manjaro"};
    ChainHash hash(10);

    hash.add_item(strs[0]);
    hash.add_item(strs[1]);
    hash.add_item(strs[2]);
    hash.add_item(strs[3]);

    display(hash);
    std::cout << std::endl;


    hash.remove_item(strs[0]);
    hash.remove_item(strs[3]);

    display(hash);

    return 0;
}