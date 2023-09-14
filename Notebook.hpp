/**
 * Created by talko on 19/03/2022.
 */
#include <map>
#include<iostream>
#include <string>
#include <vector>
#include "Direction.hpp"
using namespace std;

namespace ariel {

    class Notebook {

    public:
        int highest_key;
        map<int, vector<char>> paper;
        map<int, map<int, vector<char>>> notebook;

        //Constructor
        Notebook(){
            vector<char> new_row(101,'_');
            paper.insert(pair<int, vector<char>>(0,new_row));
            highest_key = 0;
        };

        //Destructor
        ~Notebook(){};

        void addRow(int row);
        void write(int page, int row, int column, Direction direction, string content);
        string read(int page, int row, int column, Direction direction, int length);
        void erase(int page, int row, int column, Direction direction, int length);
        void show(int row);
    };
}
