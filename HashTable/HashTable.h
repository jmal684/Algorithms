#pragma once
#include <string>
#include <vector>
#include <forward_list>
#include <sstream>
#include <iostream>
#include "Utills.h"

using std::string;

template<typename T>
class HashTable {
private:
	std::vector<std::forward_list<std::pair<string, T>>> table;
	size_t size;

public:
    HashTable() : table(4), size(0) {};
	
    void Insert(const string& key, const T& data) {
        if (size/table.size() >= 0.75 )
        {
            Rehash();
        }

        std::pair<string, T> entry(key, data);

        int hashedIndex = Hash(key, table.capacity());

        if (!table[hashedIndex].empty())
        {
            bool overwritten = false;
            for (auto& pair : table[hashedIndex])
            {
                if (pair.first == key)
                {
                    pair.second = data;
                    overwritten = true;
                    break;
                }
            }
            if (!overwritten)
            {
                table[hashedIndex].push_front(entry);
                size++;
            }
        }
        else {
            table[hashedIndex].push_front(entry);
            size++;
        }      


    }
    std::pair<string, T>* Search(const string& key) {
        int hashedIndex = Hash(key, table.capacity());

        if (!table[hashedIndex].empty()) {
            for ( auto& pair : table[hashedIndex]) {
                if (pair.first == key) {
                    return &pair;
                }
            }
        }
        return nullptr;
    }
    bool Delete(const string& key) {
        std::pair<string, T>* temp = Search(key);
        if (size <= 0 ||temp == nullptr)
            return false;
        
        int hashedIndex = Hash(key, table.capacity());

        table[hashedIndex].remove_if([&temp](const auto& pair) {
            return &pair == temp; });

        --size;
        temp = nullptr;

        return true;
    }
    string toString() {

        int sizeLim = 10;
   
        std::ostringstream str;


        str << "hash table:\n\n";
        str << "  current_size: "<<size<<"\n\n  max_size: " << table.capacity() << "\n\n";

        if (size <= 0)
        {            
            return str.str();
        }

        str <<"  table:\n  {\n\n";
        if (size < sizeLim) {
            for (int i = 0; i < table.capacity(); i++)
            {
                if (!table[i].empty())
                {
                    str << "      " << i << ": ";
                    for (const auto& pair : table[i])
                    {
                        str << pair.first << " -> " << pair.second << "; ";
                    }
                    str << "\n";
                }
            }

            str << "  } \n";

        }
        else
        {
            for (int i = 0; i < sizeLim; i++)
            {
                if (!table[i].empty())
                {                    

                    str << "      " << i << ": ";
                    for (const auto& pair : table[i])
                    {
                        str << pair.first << " -> " << pair.second << "; ";
                    }
                    str << "\n";
                }
            }
            str << "      ...\n";
            str << "  } \n\n";
           

        }

        return str.str();

    }
    string PrintStatistics() {
        int nonEmptyLists = 0;
        int sumOfListSizes = 0;
        int minListSize = std::distance(table[0].begin(), table[0].end());;
        int maxListSize = 0;
        std::ostringstream str;

        for (int i = 0; i < table.capacity(); i++)
        {
            if (!table[i].empty())
            {
                ++nonEmptyLists;
                int listSize = std::distance(table[i].begin(), table[i].end());
                sumOfListSizes += listSize;
                if (listSize < minListSize)
                    minListSize = listSize;

                if (listSize > maxListSize)
                    maxListSize = listSize;               
            }
        }
        str << "stats: \n\n  list min size: " << minListSize << "\n  list max size: " << maxListSize << "\n  non-null lists: " << nonEmptyLists << "\n  list avg size: " << (float)sumOfListSizes / nonEmptyLists << "\n\n\n";
        return str.str();
    }
    void Clear() {
     
        table.clear();
        size = 0;
        table.resize(4);
        table.shrink_to_fit();

    }



private:
    int Hash(const string& slowo, int cap) {
        unsigned int output = int(slowo[0]);
        for (int i = 1; i < slowo.length(); i++) {
            output = output * 31 + int(slowo[i]);        
        }
        return output % cap;
    }
    void Rehash() {     
        std::vector<std::forward_list<std::pair<string, T>>> temp(table.size() * 2);

        for (int i = 0; i < table.capacity(); i++)
        {   
            for (const auto& pair : table[i])
            {
                std::pair<string, T> entry = pair;
                int newHashedIndex = Hash(entry.first, temp.capacity());
                                  
                temp[newHashedIndex].push_front(entry);
            }
        }
        table = temp;
    }  

};

string GenerateString(int len = 6) {
    string generated = "";
    for (int i = 0; i < len; i++)
    {
        generated += char(RandomInt(97, 122));
    }

    return generated;
}