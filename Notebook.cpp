/**
 * Created by talko on 19/03/2022.
 */
#include "Notebook.hpp"

void ariel::Notebook::write(int page, int row, int column, ariel::Direction direction, string content) {
    if(row > COL_CAPACITY+1 || row < 0){
        throw invalid_argument("Invalid Row");
    }

    if(page < FIRST_PAGE){
        throw invalid_argument("Invalid Page");
    }

    if (notebook_map.find(page) == notebook_map.end()) {
        vector<char> new_row(COL_CAPACITY,'_');
        notebook_map[page].insert(pair<int,vector<char>>(FIRST_PAGE,new_row));
    }

    if (notebook_map[page].find(row) == notebook_map[page].end()) {
        addRow(row,page);
    }

    int size = content.size();
    switch (direction){
        case Direction::Horizontal:
            for (int i = 0; i < size; ++i) {
                if(row >= notebook_map[page].rbegin()->first){
                    addRow(row+1, page);
                }
                if(column+i >= notebook_map[page][row].size()){
                    row += 1;
                    column = 0;
                }
                if(notebook_map[page][row][column+i] == '_'){
                    notebook_map[page][row][column+i] = content[i];
                } else {
                    throw invalid_argument("Cannot writing");
                }
            }
            break;
        case Direction::Vertical:
            for (int i = 0; i < size; ++i) {
                if(row+i >= notebook_map[page].rbegin()->first){
                    addRow(row+i, page);
                }

                if(notebook_map[page][row+i][column] == '_'){
                    notebook_map[page][row+i][column] = content[i];
                } else {
                    throw invalid_argument("Cannot writing");
                }
            }
            break;
        default:
            throw invalid_argument("No Such Direction");
    }
}

string ariel::Notebook::read(int page, int row, int column, ariel::Direction direction, int length) {
    if (notebook_map.find(page) == notebook_map.end()) {
        throw invalid_argument("This Page Is Not Existing");
    }

    if(row > COL_CAPACITY+1 || row < 0){
        throw invalid_argument("Invalid Row");
    }

    if(page < FIRST_PAGE){
        throw invalid_argument("Invalid Page");
    }

    if (notebook_map[page].find(row) == notebook_map[page].end()) {
        addRow(row,page);
    }

    string result;
    switch (direction){
        case Direction::Horizontal:
            for (int i = 0; i < length; ++i) {
                if(row >= notebook_map[page].rbegin()->first){
                    addRow(row+1,page);
                }
                if(column+i >= notebook_map[page][row].size()){
                    row += 1;
                    column = 0;
                }
                result += notebook_map[page][row][column+i];
            }
            break;
        case Direction::Vertical:
            for (int i = 0; i < length; ++i) {
                if(row+i >= notebook_map[page].rbegin()->first){
                    addRow(row+i,page);
                }
                result += notebook_map[page][row+i][column];
            }
            break;
        default:
            throw invalid_argument("No Such Direction");
    }
    return result;
}

void ariel::Notebook::erase(int page, int row, int column, ariel::Direction direction, int length) {
    if (notebook_map.find(page) == notebook_map.end()) {
        throw invalid_argument("This Page Is Not Existing");
    }

    if(row > COL_CAPACITY+1 || row < 0){
        throw invalid_argument("Invalid Row");
    }

    if(page < FIRST_PAGE){
        throw invalid_argument("Invalid Page");
    }

    if (notebook_map[page].find(row) == notebook_map[page].end()) {
        addRow(row,page);
    }

    switch (direction){
        case Direction::Horizontal:
            for (int i = 0; i < length; ++i) {
                if(row >= notebook_map[page].rbegin()->first){
                    addRow(row+1,page);
                }
                if(column+i >= notebook_map[page][row].size()){
                    row += 1;
                    column = 0;
                }
                notebook_map[page][row][column+i] = '~';
            }
            break;
        case Direction::Vertical:
            for (int i = 0; i < length; ++i) {
                if(row+i >= notebook_map[page].rbegin()->first){
                    addRow(row+i+1,page);
                }
                notebook_map[page][row+i][column] = '~';
            }
            break;
        default:
            throw invalid_argument("No Such Direction");
    }
}

void ariel::Notebook::show(int page) {
    for(const auto& elem : notebook_map[page]){
        string result;
        for (char i : elem.second) {
            result += i;
        }
        cout << elem.first << ": " << result << endl;
    }
}

void ariel::Notebook::addRow(int row, int page) {
    vector<char> new_row(COL_CAPACITY,'_');
    notebook_map[page].insert(pair<int, vector<char>>(row, new_row));
}
