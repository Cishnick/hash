#include <iostream>
#include <list>
#include <algorithm>
#include <vector>



class ChainHash {
public:
    ChainHash(size_t size) : 
        capacity(size),
        _count(0)
    {
        table = new std::list<std::string>[capacity];
    }

    ~ChainHash() {
        delete[] table;
    }

    void add_item(std::string const& item) {
        _count++;
        auto key = hash_func(item);
        table[key].push_back(item);
    }

    void remove_item(std::string const& item) {
        _count--;
        auto key = hash_func(item);
        table[key].remove(item);
    }

    size_t count() const {
        return _count;
    }

    bool containing(std::string const& item) const {
        auto key = hash_func(item);
        auto chain = table[key];
        return std::find(chain.cbegin(), chain.cend(), item) != chain.cend();
    }

    void display() {
        using namespace std;
        for(int i = 0; i != capacity; ++i) {
            cout << i;
            for(auto const& x : table[i]) {
                cout << " --> " << x;
            }
            cout << endl;
        }
        cout << "count: " << count() << endl;
    }

private:
    using hash_t = unsigned long;

    hash_t hash_func(std::string const& data) const{
        hash_t i = 0;
        for(auto sym : data)
            i += sym;
        return i % capacity;
    }

    std::list<std::string> *table;
    const size_t capacity = 10000;
    size_t _count;
};


int main() {

    std::vector<std::string> strs{"Hello world!", "Hello dlrow!", "Python is shit", "Linux Manjaro"};
    ChainHash hash(10);

    hash.add_item(strs[0]);
    hash.add_item(strs[1]);
    hash.add_item(strs[2]);
    hash.add_item(strs[3]);

    hash.display();
    std::cout << std::endl;


    hash.remove_item(strs[0]);
    hash.remove_item(strs[3]);

    hash.display();

    return 0;
}