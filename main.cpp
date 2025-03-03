#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cassert>
#include <stdexcept>

using namespace std;

class Item {
    public:
        static int nextId;
        static int objectCount;
        int numeris;
        string name;
        double price;
        int count;

    public:
        Item(const string& name, double price, int count = 0) {
            init(name, price, count);
            numeris = nextId++;
            objectCount++;
        }

        Item(const string& name) {
            init(name, 0, 0);
            numeris = nextId++;
            objectCount++;
        }

        // Destruktorius
        ~Item() {
            objectCount--;
        }
        

        // Getteriai
        int getId() const { 
            return numeris; 
        }

        string getName() const { 
            return name; 
        }

        double getPrice() const { 
            return price; 
        }

        int getCount() const {
            return count; 
        }

        static int getObjectCount() { 
            return objectCount; 
        }

        // Setteriai
        void setPrice(const double price) {
            if (price < 0) {
                throw invalid_argument("price negali buti neigiama");
            }
            this->price = price;
        }

        void setCount(const int count) {
            if (count < 0) {
                throw invalid_argument("count negali buti neigiamas");
            }
            this->count = count;
        }

    private: 
            void setName(const string name) {
                if(name.empty()) {
                    throw invalid_argument("name negali buti tuscias");
                }
                this->name = name;
            }

            void init(const string& name, double price, int count) {
                setName(name);
                setPrice(price);
                setCount(count);
            }

    public:
        // Metodai
        string toString() const {
            stringstream ss;
            ss << numeris << " " << name << " " <<  price << " " << count;
            return ss.str();
        }
};

int Item::nextId = 0;
int Item::objectCount = 0;

int main() {
    {
        // Testas 1: Objekto kūrimas ir getteriai
        Item p1("Obuolys", 0.99, 100);
        assert(p1.getName() == "Obuolys");
        assert(p1.getPrice() == 0.99);
        assert(p1.getCount() == 100);
        assert(p1.toString() == "0 Obuolys 0.99 100");

        // Testas 2: Setteriai
        Item p2("Vanduo", 1.5, 50);
        assert(p2.getName() == "Vanduo");
        p2.setCount(200);
        assert(p2.getCount() == 200);
        p2.setPrice(0.5);
        assert(p2.getPrice() == 0.5);

        // Testas su neteisinga price
        try {
            p2.setPrice(-1.0);
            assert(false); // Turi mesti išimtį
        } catch (const invalid_argument& e) {
            // Laukiama išimtis
        }

        // Testas su neteisingu likučiu
        try {
            p2.setCount(-1);
            assert(false); // Turi mesti išimtį
        } catch (const invalid_argument& e) {
            // Laukiama išimtis
        }

        // Testas 3: ID ir objektų kiekis
        Item* p3 = new Item("Sultys");
        assert(Item::getObjectCount() == 3);

        Item* p4 = new Item("Duona", 1.0, 10);
        assert(Item::getObjectCount() == 4);
        delete p4;
        assert(Item::getObjectCount() == 3);
        delete p3;

        // Objektų sąrašas
        vector<Item*> Items;
        Items.push_back(new Item("Duona", 2.49, 50));
        Items.push_back(new Item("Pienas", 1.79, 30));
        assert(Items[0]->toString() == "4 Duona 2.49 50");
        assert(Items[1]->toString() == "5 Pienas 1.79 30");

        delete Items[0];
        delete Items[1];
        Items.clear();

        // Testas su neteisingu konstruktoriumi
        try {
            Item p5("Neigiama price", -5.0, 10);
            assert(false);
        } catch (const invalid_argument& e) {
            // Laukiama išimtis
        }
    }
    assert(Item::getObjectCount() == 0);
    cout << "Visi testai sekmingi!" << endl;

    return 0;
}