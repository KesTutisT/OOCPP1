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

        void setPavadinimas(const string pavadinimas) {
            if(pavadinimas.empty()) {
                throw invalid_argument("Pavadinimas negali buti tuscias");
            }
            this->pavadinimas = pavadinimas;
        }

    public:
        Preke() : id(nextId++), pavadinimas(""), kaina(0.0), likutis(0) {
            objectCount++;
        }

        Preke(const string pavadinimas, const double kaina, const int likutis) {
            this->setPavadinimas(pavadinimas);
            if (kaina < 0) {
                throw invalid_argument("Kaina negali buti neigiama");
            }
            this->kaina = kaina;
            this->likutis = likutis;
            id = nextId++;
            objectCount++;
        }

        // Destruktorius
        ~Preke() {
            objectCount--;
        }

        // Getteriai
        int getId() const { return id; }
        string getPavadinimas() const { return pavadinimas; }
        double getKaina() const { return kaina; }
        int getLikutis() const { return likutis; }
        static int getObjectCount() { return objectCount; }

        // Setteriai
        void setKaina(const double kaina) {
            if (kaina < 0) {
                throw invalid_argument("Kaina negali buti neigiama");
            }
            this->kaina = kaina;
        }

        void setLikutis(const int likutis) {
            if (likutis < 0) {
                throw invalid_argument("Likutis negali buti neigiamas");
            }
            this->likutis = likutis;
        }

        // Metodai
        string toString() const {
            stringstream ss;
            ss << "ID: " << id << ", Pavadinimas: " << pavadinimas << ", Kaina: " << kaina << ", Likutis: " << likutis;
            return ss.str();
        }
};

int Preke::nextId = 0;
int Preke::objectCount = 0;

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}