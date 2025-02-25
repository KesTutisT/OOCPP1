#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cassert>
#include <stdexcept>

using namespace std;

class Preke {
    private:
        static int nextId;
        static int objectCount;
        int id;
        string pavadinimas;
        double kaina;
        int likutis;

    public:

        
};

int Preke::nextId = 0;
int Preke::objectCount = 0;

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}