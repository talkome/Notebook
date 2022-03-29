/**
 * Created by talko on 19/03/2022.
 */
#include "Notebook.hpp"

void ariel::Notebook::write(int page, int row, int column, ariel::Direction direction, string content) {
    if(row < 0 || row > ROW_CAPACITY){
        throw invalid_argument("Invalid Row");
    }

    if(column < 0 || column > ROW_CAPACITY){
        throw invalid_argument("Invalid Column");
    }

    if(page < FIRST_PAGE){
        throw invalid_argument("Invalid Page");
    }

    int size = content.size();
    if(size <= 0){
        throw invalid_argument("Invalid Text");
    }

    vector<char> s = {'\n','\t','\r','\a','\b','\f','\v','~'};
    for (unsigned long i = 0; i < s.size(); ++i) {
        if (content.find(s[i]) != string::npos) {
            throw invalid_argument("Invalid Character");
        }
    }

    if (notebook_map.find(page) == notebook_map.end()) {
        vector<char> new_row(ROW_CAPACITY,'_');
        notebook_map[page].insert(pair<int,vector<char>>(FIRST_PAGE,new_row));
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
            if (size > ROW_CAPACITY-column){
                throw invalid_argument("Out Of Bound");
            }
            for (int i = 0; i < size; ++i) {
                if(row > notebook_map[page].rbegin()->first){
                    addRow(row, page);
                }

                sum = column+i;
                if(column+i > notebook_map[page][row].size()){
                    row += 1;
                    column = 0;
                    sum = 0;
                }

                j = (unsigned long)i;
                new_row = (unsigned long)row;
                new_col = (unsigned long)sum;
                if(notebook_map[page][new_row][new_col] == '_'){
                    notebook_map[page][new_row][new_col] = content[j];
                } else {
                    throw invalid_argument("Cannot writing");
                }
            }
            break;
            
        case Direction::Vertical:
            if (column >= ROW_CAPACITY){
                throw invalid_argument("Out Of Bound");
            }
            for (int i = 0; i < size; ++i) {
                if(row+i > notebook_map[page].rbegin()->first){
                    addRow(row+i, page);
                }
                sum = row+i;
                j = (unsigned long)i;
                new_row = (unsigned long) sum;
                new_col = (unsigned long) column;
                if(notebook_map[page][new_row][new_col] == '_'){
                    notebook_map[page][new_row][new_col] = content[j];
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
    if(row < 0 || row > ROW_CAPACITY){
        throw invalid_argument("Invalid Row");
    }

    if(column < 0 || column > ROW_CAPACITY){
        throw invalid_argument("Invalid Column");
    }

    if(page < FIRST_PAGE){
        throw invalid_argument("Invalid Page");
    }

    if(length <= 0){
        throw invalid_argument("Invalid Length");
    }

    if (notebook_map.find(page) == notebook_map.end()) {
        vector<char> new_row(ROW_CAPACITY,'_');
        notebook_map[page].insert(pair<int,vector<char>>(FIRST_PAGE,new_row));
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
            if (length > ROW_CAPACITY-column){
                throw invalid_argument("Out Of Bound");
            }
            for (int i = 0; i < length; ++i) {
                if(row > notebook_map[page].rbegin()->first){
                    if (notebook_map[page].find(row) == notebook_map[page].end()) {
                        addRow(row,page);
                    }
                }

                sum = column+i;
                if(column+i > notebook_map[page][row].size()){
                    row += 1;
                    column = 0;
                    sum = 0;
                }

                new_row = (unsigned long)row;
                new_col = (unsigned long)sum;
                result += notebook_map[page][new_row][new_col];
            }
            break;

        case Direction::Vertical:
            if (column >= ROW_CAPACITY){
                throw invalid_argument("Out Of Bound");
            }
            for (int i = 0; i < length; ++i) {
                if(row+i > notebook_map[page].rbegin()->first){
                    if (notebook_map[page].find(row+i) == notebook_map[page].end()) {
                        addRow(row+i,page);
                    }
                }
                sum = row+i;
                new_row = (unsigned long)sum;
                new_col = (unsigned long)column;
                result += notebook_map[page][new_row][new_col];
            }
            break;

        default:
            throw invalid_argument("No Such Direction");
    }
    return result;
}

void ariel::Notebook::erase(int page, int row, int column, ariel::Direction direction, int length) {
    if(row < 0 || row > ROW_CAPACITY){
        throw invalid_argument("Invalid Row");
    }

    if(column < 0 || column > ROW_CAPACITY){
        throw invalid_argument("Invalid Column");
    }

    if(length <= 0){
        throw invalid_argument("Invalid Length");
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

    unsigned long new_row = 0;
    unsigned long new_col = 0;
    int sum = 0;

    switch (direction){
        case Direction::Horizontal:
            if (length > ROW_CAPACITY-column){
                throw invalid_argument("Out Of Bound");
            }
            for (int i = 0; i < length; ++i) {
                if(row > notebook_map[page].rbegin()->first){
                    if (notebook_map[page].find(row) == notebook_map[page].end()) {
                        addRow(row,page);
                    }
                }

                sum = column+i;
                if(column+i > notebook_map[page][row].size()){
                    row += 1;
                    column = 0;
                    sum = 0;
                }

                new_row = (unsigned long)row;
                new_col = (unsigned long)sum;
                notebook_map[page][new_row][new_col] = '~';
            }
            break;

        case Direction::Vertical:
            if (column >= ROW_CAPACITY){
                throw invalid_argument("Out Of Bound");
            }
            for (int i = 0; i < length; ++i) {
                if(row+i > notebook_map[page].rbegin()->first){
                    if (notebook_map[page].find(row+i) == notebook_map[page].end()) {
                        addRow(row+i,page);
                    }
                }
                sum = row+i;
                new_row = (unsigned long)sum;
                new_col = (unsigned long)column;
                notebook_map[page][new_row][new_col] = '~';
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
