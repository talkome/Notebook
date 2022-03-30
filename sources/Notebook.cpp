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
    for (char i : s) {
        if (content.find(i) != string::npos) {
            throw invalid_argument("Invalid Character");
        }
    }

    const int magic_num1 = 32;
    const int magic_num2 = 126;
    for (size_t i = 0; i < size; ++i) {
        char c = content[i];
        if (c < magic_num1 || c > magic_num2) {
            throw invalid_argument("Invalid Character");
        }
    }

    if (papers_map.find(page) == papers_map.end()) {
        addRow(0,page);
    }

    if (papers_map[page].find(row) == papers_map[page].end()) {
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

            if(row > papers_map[page].rbegin()->first){
                addRow(row, page);
            }

            for (int i = 0; i < size; ++i) {
                sum = column+i;
                if(column+i > papers_map[page][row].size()){
                    row += 1;
                    column = 0;
                    sum = 0;
                }

                j = (unsigned long)i;
                new_row = (unsigned long)row;
                new_col = (unsigned long)sum;
                if(papers_map[page][new_row][new_col] == '_'){
                    papers_map[page][new_row][new_col] = content[j];
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
                if(row+i > papers_map[page].rbegin()->first){
                    addRow(row+i, page);
                }
                sum = row+i;
                j = (unsigned long)i;
                new_row = (unsigned long) sum;
                new_col = (unsigned long) column;
                if(papers_map[page][new_row][new_col] == '_'){
                    papers_map[page][new_row][new_col] = content[j];
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

    if (papers_map.find(page) == papers_map.end()) {
        string new_row(ROW_CAPACITY,'_');
        papers_map[page].insert(pair<int,string>(FIRST_PAGE,new_row));
    }

    if (papers_map[page].find(row) == papers_map[page].end()) {
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

            if(row > papers_map[page].rbegin()->first){
                if (papers_map[page].find(row) == papers_map[page].end()) {
                    addRow(row,page);
                }
            }

            for (int i = 0; i < length; ++i) {
                sum = column+i;
                if(column+i > papers_map[page][row].size()){
                    row += 1;
                    column = 0;
                    sum = 0;
                }

                new_row = (unsigned long)row;
                new_col = (unsigned long)sum;
                result += papers_map[page][new_row][new_col];
            }
            break;

        case Direction::Vertical:
            if (column >= ROW_CAPACITY){
                throw invalid_argument("Out Of Bound");
            }
            for (int i = 0; i < length; ++i) {
                if(row+i > papers_map[page].rbegin()->first){
                    if (papers_map[page].find(row+i) == papers_map[page].end()) {
                        addRow(row+i,page);
                    }
                }
                sum = row+i;
                new_row = (unsigned long)sum;
                new_col = (unsigned long)column;
                result += papers_map[page][new_row][new_col];
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

    if (papers_map.find(page) == papers_map.end()) {
        string new_row(ROW_CAPACITY,'_');
        papers_map[page].insert(pair<int,string>(FIRST_PAGE,new_row));
    }

    if (papers_map[page].find(row) == papers_map[page].end()) {
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
                if(row > papers_map[page].rbegin()->first){
                    if (papers_map[page].find(row) == papers_map[page].end()) {
                        addRow(row,page);
                    }
                }

                sum = column+i;
                if(column+i > papers_map[page][row].size()){
                    row += 1;
                    column = 0;
                    sum = 0;
                }

                new_row = (unsigned long)row;
                new_col = (unsigned long)sum;
                papers_map[page][new_row][new_col] = '~';
            }
            break;

        case Direction::Vertical:
            if (column >= ROW_CAPACITY){
                throw invalid_argument("Out Of Bound");
            }
            for (int i = 0; i < length; ++i) {
                if(row+i > papers_map[page].rbegin()->first){
                    if (papers_map[page].find(row+i) == papers_map[page].end()) {
                        addRow(row+i,page);
                    }
                }
                sum = row+i;
                new_row = (unsigned long)sum;
                new_col = (unsigned long)column;
                papers_map[page][new_row][new_col] = '~';
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

    for(const auto& elem : papers_map[page]){
        string result;
        for (char i : elem.second) {
            result += i;
        }
        cout << elem.first << ": " << result << endl;
    }
}

void ariel::Notebook::addRow(int row, int page) {
    string new_row(ROW_CAPACITY,'_');
    papers_map[page].insert(pair<int, string>(row, new_row));
}
