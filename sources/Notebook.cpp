/**
 * Created by talko on 19/03/2022.
 */
#include "Notebook.hpp"

void ariel::Notebook::write(int page, int row, int column, ariel::Direction direction, string content) {
    if(row < 0 || row > ROW_CAPACITY-1){
        throw invalid_argument("Invalid Row");
    }

    if(column < 0 || column > ROW_CAPACITY-1){
        throw invalid_argument("Invalid Column");
    }

    int size = content.size();
    if(size <= 0 || size > ROW_CAPACITY-column || size > MAX){
        throw invalid_argument("Invalid Text");
    }

    if(page < FIRST_PAGE){
        throw invalid_argument("Invalid Page");
    }

    if (notebook_map.find(page) == notebook_map.end()) {
        vector<char> new_row(ROW_CAPACITY,'_');
        notebook_map[page].insert(pair<int,vector<char>>(FIRST_PAGE,new_row));
    }

    if (notebook_map[page].find(row) == notebook_map[page].end()) {
        addRow(row,page);
    }

    vector<char> s = {'\n','\t', ' ', '\r','\a','\b','\f','\v','_','~'};
    for (unsigned long i = 0; i < s.size(); ++i) {
        if (content.find(s[i]) != string::npos) {
            throw invalid_argument("Invalid Character");
        }
    }

    unsigned long new_row = 0;
    unsigned long new_col = 0;
    unsigned long j = 0;
    int sum = 0;

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
                sum = column+i;
                j = (unsigned long)i;
                new_row = (unsigned long)row;
                new_col = (unsigned long)sum;
                if(notebook_map[page][new_row][new_col] == '_'){ // changeV
                    notebook_map[page][new_row][new_col] = content[j]; // changeV
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
                sum = row+i;
                j = (unsigned long)i;
                new_row = (unsigned long)sum;
                new_col = (unsigned long) column;
                if(notebook_map[page][new_row][new_col] == '_'){ // changeV
                    notebook_map[page][new_row][new_col] = content[j]; // changeV
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
    if(row < 0 || row > ROW_CAPACITY+1){
        throw invalid_argument("Invalid Row");
    }

    if(column < 0 || column > ROW_CAPACITY){
        throw invalid_argument("Invalid Column");
    }

    if(page < FIRST_PAGE){
        throw invalid_argument("Invalid Page");
    }

    if(length > ROW_CAPACITY){
        throw invalid_argument("Out of Bound");
    }

    if(length <= 0 || length > ROW_CAPACITY-column){
        throw invalid_argument("Invalid Length");
    }

    if (notebook_map.find(page) == notebook_map.end()) {
        throw invalid_argument("This Page Is Not Existing");
    }

    if (notebook_map[page].find(row) == notebook_map[page].end()) {
        addRow(row,page);
    }

    string result;
    unsigned long new_row = 0;
    unsigned long new_col = 0;
    int sum = 0;

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
                sum = column+i;
                new_row = (unsigned long)row;
                new_col = (unsigned long)sum;
                result += notebook_map[page][new_row][new_col]; // changeV
            }
            break;
        case Direction::Vertical:
            for (int i = 0; i < length; ++i) {
                if(row+i >= notebook_map[page].rbegin()->first){
                    addRow(row+i,page);
                }
                sum = row+i;
                new_row = (unsigned long)sum;
                new_col = (unsigned long)column;
                result += notebook_map[page][new_row][new_col]; // changeV
            }
            break;
        default:
            throw invalid_argument("No Such Direction");
    }
    return result;
}

void ariel::Notebook::erase(int page, int row, int column, ariel::Direction direction, int length) {
    if(length <= 0 || length > ROW_CAPACITY-column || length > notebook_map[page].size()){
        throw invalid_argument("Invalid Length");
    }

    if(row < 0 || row > ROW_CAPACITY+1){
        throw invalid_argument("Invalid Row");
    }

    if(column < 0 || column > ROW_CAPACITY){
        throw invalid_argument("Invalid Column");
    }

    if(page < FIRST_PAGE){
        throw invalid_argument("Invalid Page");
    }

    if (notebook_map.find(page) == notebook_map.end()) {
        throw invalid_argument("This Page Is Not Existing");
    }

    if (notebook_map[page].find(row) == notebook_map[page].end()) {
        addRow(row,page);
    }

    unsigned long new_row = 0;
    unsigned long new_col = 0;
    unsigned long j = 0;
    int sum = 0;

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
                sum = column+i;
                new_row = (unsigned long)row;
                new_col = (unsigned long)sum;
                notebook_map[page][new_row][new_col] = '~'; // changeV
            }
            break;
        case Direction::Vertical:
            for (int i = 0; i < length; ++i) {
                if(row+i >= notebook_map[page].rbegin()->first){
                    addRow(row+i+1,page);
                }
                sum = row+i;
                new_row = (unsigned long)sum;
                new_col = (unsigned long) column;
                notebook_map[page][new_row][new_col] = '~'; // changeV
            }
            break;
        default:
            throw invalid_argument("No Such Direction");
    }
}

void ariel::Notebook::show(int page) {
    if(page <= FIRST_PAGE){
        throw invalid_argument("Invalid Page");
    }

    if (notebook_map.find(page) == notebook_map.end()) {
        throw invalid_argument("This Page Is Not Exists");
    }

    for(const auto& elem : notebook_map[page]){
        string result;
        for (char i : elem.second) {
            result += i;
        }
        cout << elem.first << ": " << result << endl;
    }
}

void ariel::Notebook::addRow(int row, int page) {
    vector<char> new_row(ROW_CAPACITY,'_');
    notebook_map[page].insert(pair<int, vector<char>>(row, new_row));
}
