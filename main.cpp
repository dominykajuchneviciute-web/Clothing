#include <iostream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <assert.h>
#include <vector>

using namespace std;
class Clothing
{
    int id;
    static int lastId;
    static int objectCount;
    string name, material, color;
    int sizes;
public:
    Clothing(string name, string material, string color)
    {
        init(name, material, color, 40);
    }
    Clothing(string name, string material, string color, int sizes)
    {
        init(name, material, color, sizes);
    }
    ~Clothing()
    {
        --objectCount;
    }
    void init(string name, string material, string color, int sizes)
    {
        ++objectCount;
        id = lastId++;
        setName(name);
        setMaterial(material);
        setColor(color);
        setSizes(sizes);
    }

    void setName(string name)
    {
        this->name = name;
    }
    void setMaterial(string material)
    {
        this->material = material;
    }
    void setColor(string color)
    {
        this->color = color;
    }
    void setSizes(int sizes)
    {
        if((sizes >= 34) && (sizes <= 52))
            this->sizes = sizes;
        else
            throw invalid_argument("Exception in Clothing: the size should be of European standarts.");
    }
    string getName()
    {
        return name;
    }
    string getMaterial()
    {
        return material;
    }
    string getColor()
    {
        return color;
    }
    int getSizes()
    {
        return sizes;
    }
    static int getObjectCount()
    {
        return objectCount;
    }
    int getId()
    {
        return id;
    }
    string toString()
    {
        stringstream ss;
        ss << getName() << " " << getMaterial() << " " << getColor() << " " << getSizes()<< " " << getId() << " " << getObjectCount() << endl;
        return ss.str();
    }

};
int Clothing::lastId = 0;
int Clothing::objectCount = 0;

int main()
{
    Clothing *item0 = new Clothing ("Pants", "Wool", "Black");
    assert(item0->getName() == "Pants");
    assert(item0->getSizes() == 40);
    cout << item0->toString();
    //test1
    Clothing *item1 = new Clothing ("T-shirt", "Cotton", "Blue", 42);
    cout << item1->toString();
    //test2
    item1->setName("Shoes");
    item1->setMaterial("Leather");
    item1->setColor("Brown");
    item1->setSizes(38);
    assert(item1->getName() == "Shoes");
    assert(item1->getMaterial() == "Leather");
    assert(item1->getColor() == "Brown");
    assert(item1->getSizes() == 38);
    //test3
    try
    {
        item1->setSizes(30);
        assert(false);
    }
    catch (const invalid_argument& e)
    {
        cout<<"Unexpected error occured. "<< e.what() <<endl;
        assert(true);
    }
    //test4
    assert(item1->getId() > item0->getId());
    //test5
    int n = 3;
    Clothing **items = new Clothing*[n];
    items[0] = new Clothing ("Gloves", "Silk", "White", 38);
    items[1] = new Clothing ("Shoes", "Leather", "Brown", 45);
    items[2] = new Clothing ("Socks", "Cotton", "Yellow", 47);
    assert(Clothing::getObjectCount() == 5);
    for (int i = 0; i < n; ++i)
    {
        cout << items[i]->toString();
    }
    for (int i = 0; i < n; ++i)
    {
        delete items[i];
    }
    delete[] items;
    delete item0;
    delete item1;
    assert(Clothing::getObjectCount() == 0);
    return 0;
}
