/*
Implemente una función C++ denominada Suprimir que reciba dos listas de elementos y devuelva una
nueva lista con los elementos de la primera que no están en la segunda:
*/

#include <list>
#include <algorithm>

template<class T>
std::list<T> suprimir(std::list<T>& list1, std::list<T>& list2){
    std::list<T> ret_list;
    for (auto& element1 : list1){
        auto matched = std::find(list2.begin(), list2.end(), element1);
        if (matched == list2.end())
            ret_list.emplace_back(element1);
    }
    return ret_list;
}
