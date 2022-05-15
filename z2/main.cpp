#include <algorithm>
#include <iostream>
#include <functional>
#include <utility>
#include <vector>
using std::string; using std::vector;

struct Person {
    string name;
    string nickname;
    int birthYear;
};

struct Name {
    string name;
    vector<Person> pers;
};

Name* checkName(vector<Name>& names, const string& name) {
    for (int i = 0; i < names.size(); ++i) {
        if(names[i].name == name)
            return names.data() + i;
    }
    return nullptr;
}

vector<Name> groupByName(const vector<Person>& persons,
                         std::function<bool(Name,Name)> pred) {
    vector<Name> result{};
    for (int i = 0; i < persons.size(); ++i) {
        Name* pName = checkName(result, persons[i].name);
        //jezeli imie sie powtarza to dodajemy je do wektora przypisanego dla tego imienia
        if(pName){
            pName->pers.push_back(persons[i]);
        } else{
            //jezeli imie sie nie powtarza to tworzymy nowa strukture name ze swoim wlasnym wketorem
            // ktory bedzie zbieral wszystkie takie same imiona
            Name* neoName = new Name();
            neoName->name = persons[i].name;
            neoName->pers.push_back(persons[i]);
            result.push_back(*neoName);
        }
    }
    std::sort(result.begin(), result.end(), pred); //sortujemy wyniki
    //w tym momencie siegamy do fukcji z argumentu metody "pred" - std::function<bool(Name,Name)> pred
    //ktora sortuje nam patrzac ktore imie ma mniej powtorzen i dajac je na poczatek
    return result;//zwracamy wektor wynikow
}

void printNames(const vector<Name>& names) {
    for (int i = 0; i < names.size(); ++i) {
        std::cout << names[i].name <<" ( ";
        for (int j = 0; j < names[i].pers.size(); ++j) {
            std::cout << names[i].pers[j].nickname << "-" << names[i].pers[j].birthYear << " ";
        }
        std::cout << " ) " << std::endl;
    }
}

int main() {
    vector<Person> persons {
            {"Zara", "Crazy", 1989}, {"Zara", "Sugar", 2014},
            {"John", "Old", 1980}, {"Mary", "Sweet", 2004},
            {"Bill", "Fatso", 1990}, {"John", "Retard", 2010},
            {"Mary", "Redhead", 2001}, {"Mary", "Little", 2013},
            {"Bill", "Jojo", 2000}, {"Mary", "Bunny", 2020},
            {"Kate", "Honey", 1998}
    };



    vector<Name> res = groupByName(persons, [](const Name& a, const Name& b)-> bool {
        if (a.pers.size() == b.pers.size()) {
        std::cout << "rowne ";
        return a.name < b.name;
    }
        else{
        std::cout << " nie-rowne";
        return a.pers.size() < b.pers.size();
    }
    });

 //   printNames(res);
}