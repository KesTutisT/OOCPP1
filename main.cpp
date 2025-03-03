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
        Preke(const string& pavadinimas, double kaina, int likutis = 0) {
            init(pavadinimas, kaina, likutis);
            id = nextId++;
            objectCount++;
        }

        Preke(const string& pavadinimas) {
            init(pavadinimas, 0, 0);
            id = nextId++;
            objectCount++;
        }

        // Destruktorius
        ~Preke() {
            objectCount--;
        }
        

        // Getteriai
        int getId() const { 
            return id; 
        }

        string getPavadinimas() const { 
            return pavadinimas; 
        }

        double getKaina() const { 
            return kaina; 
        }

        int getLikutis() const {
            return likutis; 
        }

        static int getObjectCount() { 
            return objectCount; 
        }

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

    private: 
            void setPavadinimas(const string pavadinimas) {
                if(pavadinimas.empty()) {
                    throw invalid_argument("Pavadinimas negali buti tuscias");
                }
                this->pavadinimas = pavadinimas;
            }

            void init(const string& pavadinimas, double kaina, int likutis) {
                setPavadinimas(pavadinimas);
                setKaina(kaina);
                setLikutis(likutis);
            }

    public:
        // Metodai
        string toString() const {
            stringstream ss;
            ss << id << " " << pavadinimas << " " <<  kaina << " " << likutis;
            return ss.str();
        }
};

int Preke::nextId = 0;
int Preke::objectCount = 0;

int main() {
    {
        // Testas 1: Objekto kūrimas ir getteriai
        Preke p1("Obuolys", 0.99, 100);
        assert(p1.getId() == 0);
        assert(p1.getPavadinimas() == "Obuolys");
        assert(p1.getKaina() == 0.99);
        assert(p1.getLikutis() == 100);
        assert(p1.toString() == "0 Obuolys 0.99 100");

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
        Preke* p3 = new Preke("Sultys");
        assert(Preke::getObjectCount() == 3);
        assert(p3->getId() == 2);

        Preke* p4 = new Preke("Duona", 1.0, 10);
        assert(Preke::getObjectCount() == 4);
        delete p4;
        assert(Preke::getObjectCount() == 3);
        delete p3;

        // Objektų sąrašas
        vector<Preke*> prekes;
        prekes.push_back(new Preke("Duona", 2.49, 50));
        prekes.push_back(new Preke("Pienas", 1.79, 30));
        assert(prekes[0]->toString() == "4 Duona 2.49 50");
        assert(prekes[1]->toString() == "5 Pienas 1.79 30");

        delete prekes[0];
        delete prekes[1];
        prekes.clear();

        // Testas su neteisingu konstruktoriumi
        try {
            Preke p5("Neigiama kaina", -5.0, 10);
            assert(false);
        } catch (const invalid_argument& e) {
            // Laukiama išimtis
        }
    }
    assert(Preke::getObjectCount() == 0);
    cout << "Visi testai sekmingi!" << endl;

    return 0;
}