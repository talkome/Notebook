/**
 * Created by talko on 19/03/2022.
 */
#include <map>
#include<iostream>
#include <string>
#include <vector>
#include "Direction.hpp"
#define COL_CAPACITY 100
#define FIRST_PAGE 0

using namespace std;

namespace ariel {

    class Notebook {

    public:
        map<int, map<int, vector<char>>> notebook_map;

        //Constructor
        Notebook(){
            vector<char> new_row(COL_CAPACITY+1,'_');
            notebook_map[FIRST_PAGE].insert(pair<int, vector<char>>(FIRST_PAGE, new_row));
        };

        //Destructor
        ~Notebook(){};

        void addRow(int row, int page);
        void write(int page, int row, int column, Direction direction, string content);
        string read(int page, int row, int column, Direction direction, int length);
        void erase(int page, int row, int column, Direction direction, int length);
        void show(int page);
    };
}
