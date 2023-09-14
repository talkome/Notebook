/**
 * Created by talko on 19/03/2022.
 */
#include "Notebook.hpp"

void ariel::Notebook::write(int page, int row, int column, ariel::Direction direction, string content) {
    cout << "writing" << endl;
//    if(row > 101 || row < 0){
//        throw invalid_argument("Invalid Row");
//    }
//
//    if(page < 0){
//        throw invalid_argument("Invalid Page");
//    }
//
//
//    if (paper.find(row) == paper.end()) {
//        addRow(row);
//    }
//
//    int size = content.size();
//    if(direction == Direction::Horizontal){
//        for (int i = 0; i < size; ++i) {
//            if(column+i >= paper[row].size()){
//                row += 1;
//                addRow(row);
//                column = 0;
//            }
//
//            if(paper[row][column+i] == '_'){
//                paper[row][column+i] = content[i];
//            } else {
//                throw invalid_argument("Cannot writing");
//            }
//        }
//    } else {
//        for (int i = 0; i < size; ++i) {
//            if(row+i >= highest_key){
//                addRow(row+i+1);
//            }
//
//            if(paper[row+i][column] == '_'){
//                paper[row+i][column] = content[i];
//            } else {
//                throw invalid_argument("Cannot writing");
//            }
//        }
//    }
//
//    notebook.insert(pair<int,map<int, vector<char>>>(page,paper));
}

string ariel::Notebook::read(int page, int row, int column, ariel::Direction direction, int length) {
    return "reading";
//    if(row > 101 || row < 0){
//        throw invalid_argument("Invalid Row");
//    }
//
//    if(page < 0){
//        throw invalid_argument("Invalid Page");
//    }
//
//    string result;
//
//    if (paper.find(row) == paper.end()) {
//        addRow(row);
//    }
//
//    if(direction == Direction::Horizontal){
//        for (int i = 0; i < length-1; ++i) {
//            if(column+i >= paper[row].size()){
//                row += 1;
//                addRow(row);
//                column = 0;
//            }
//
//            result += paper[row][column+i];
//
//        }
//    } else {
//        for (int i = 0; i < length; ++i) {
//            if(row+i >= highest_key){
//                addRow(row+i+1);
//            }
//
//            result += paper[row+i][column];
//        }
//    }
//
//    return result;
}

void ariel::Notebook::erase(int page, int row, int column, ariel::Direction direction, int length) {
    cout << "erasing" << endl;
//    if(row > 101 || row < 0){
//        throw invalid_argument("Invalid Row");
//    }
//
//    if(page < 0){
//        throw invalid_argument("Invalid Page");
//    }
//
//    if(direction == Direction::Horizontal){
//        for (int i = 0; i < length; ++i) {
//            if(column+i >= paper[row].size()){
//                row += 1;
//                addRow(row);
//                column = 0;
//            }
//
//            paper[row][column+i] = '~';
//
//        }
//    } else {
//        for (int i = 0; i < length; ++i) {
//            if(row+i >= highest_key){
//                addRow(row+i+1);
//            }
//
//            paper[row+i][column] = '~';
//
//        }
//    }
//
//    notebook.insert(pair<int,map<int, vector<char>>>(page,paper));

}

void ariel::Notebook::show(int row) {
    cout << "print notebook" << endl;
//    cout << (row-2) << ": " << paper[row][] << endl;
//    cout << (row-1) << ": " << paper[row-1] << endl;
//    cout << (row) << ": " << paper[row] << endl;
//    cout << (row+1) << ": " << paper[row+1] << endl;
//    cout << (row+2) << ": " << paper[row+2] << endl;
}

void ariel::Notebook::addRow(int row) {
    cout << "adding row" << endl;
//    vector<char> new_row(100,'_');
//    paper.insert(pair<int, vector<char>>(row,new_row));
//    if(row > highest_key){
//        highest_key = row;
//    }
}
