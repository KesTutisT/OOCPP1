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
    // Testas 1: Objekto kūrimas ir getteriai
    Preke p1("Obuolys", 0.99, 100);
    assert(p1.getId() == 0);
    assert(p1.getPavadinimas() == "Obuolys");
    assert(p1.getKaina() == 0.99);
    assert(p1.getLikutis() == 100);
    assert(p1.toString() == "ID: 0, Pavadinimas: Obuolys, Kaina: 0.99, Likutis: 100");

    // Testas 2: Setteriai
    Preke p2("Vanduo", 1.5, 50);
    assert(p2.getPavadinimas() == "Vanduo");
    p2.setLikutis(200);
    assert(p2.getLikutis() == 200);
    p2.setKaina(0.5);
    assert(p2.getKaina() == 0.5);

    // Testas su neteisinga kaina
    try {
        p2.setKaina(-1.0);
        assert(false); // Turi mesti išimtį
    } catch (const invalid_argument& e) {
        // Laukiama išimtis
    }

    // Testas su neteisingu likučiu
    try {
        p2.setLikutis(-1);
        assert(false); // Turi mesti išimtį
    } catch (const invalid_argument& e) {
        // Laukiama išimtis
    }

    // Testas 3: ID ir objektų kiekis
    Preke p3;
    assert(Preke::getObjectCount() == 3);
    assert(p3.getId() == 2);

    Preke* p4 = new Preke();
    assert(Preke::getObjectCount() == 4);
    delete p4;
    assert(Preke::getObjectCount() == 3);

    // Objektų sąrašas
    vector<Preke> prekes;
    prekes.emplace_back("Duona", 2.49, 50);
    prekes.emplace_back("Pienas", 1.79, 30);
    assert(prekes[0].toString() == "ID: 4, Pavadinimas: Duona, Kaina: 2.49, Likutis: 50");
    assert(prekes[1].toString() == "ID: 5, Pavadinimas: Pienas, Kaina: 1.79, Likutis: 30");

    // Testas su neteisingu konstruktoriumi
    try {
        Preke p5("Neigiama kaina", -5.0, 10);
        assert(false);
    } catch (const invalid_argument& e) {
        // Laukiama išimtis
    }

    cout << "Visi testai sekmingi!" << endl;

    return 0;
}