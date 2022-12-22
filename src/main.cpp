#include <iostream>
#include "chainhashset.hpp"


using Hash = ChainHashSet<std::string, Hash_Std>;

void display(Hash const& hash) {
    using namespace std;
    for(int i = 0; i != hash._capacity; ++i) {
        std::cout << i;
        for(auto const& x : hash.table[i]) {
            std::cout << " --> " << x;
        }
        std::cout << std::endl;
    }
    std::cout << "count: " << hash.count() << std::endl;
}


int main() {

    std::vector<std::string> strs{
        "Hello world!", 
        "Hello dlrow!", 
        "Python is shit", 
        "Linux Manjaro",
        "Something else",
        "First try in hash tables"
    };
    Hash hash(10);

    for(auto const& str : strs)
        hash.add_item(str);

    display(hash);
    std::cout << std::endl;

    hash.remove_item(strs[0]);
    hash.remove_item(strs[3]);

    display(hash);

    return 0;
}