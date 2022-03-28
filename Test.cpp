/**
 * Created by talko on 19/03/2022.
 */
#include "doctest.h"
#include "Notebook.hpp"
#include <string>
using namespace ariel;
using namespace std;

/**
 * Returns the input string without the whitespace characters: space, newline and tab.
 * Requires std=c++2a.
 */
Notebook notebook;

TEST_CASE("1. Check Input") {
    CHECK_THROWS(notebook.write(-2, 4444, 5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(-2, 1777777, 5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(-2, 10, 5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(2, -10, 5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(2, 10, -5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(-2, -10, -5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.read(2, 10, 5, Direction::Vertical, 0));
    CHECK_THROWS(notebook.read(2, 10, 5, Direction::Vertical, -3));
    CHECK_THROWS(notebook.write(0, 10, 5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(2, 0, 5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(2, 10, 0, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(0, 0, 0, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.read(0, 0, 0, Direction::Vertical, 0));
}

TEST_CASE("2. Check Symbol") {
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, "\t"));
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, "\n"));
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, " "));
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, "\n\n\n"));
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, "\r"));
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, "_______"));
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, "                      "));
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, "~~~~~~~~~~"));
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, "\t\t\t\t\t\t\t"));
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, "\t~\t~\t~\t~\t~\t~\t~"));
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
                                                                                                 "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"));
}

TEST_CASE("3. Writing Check") {
    notebook.write(1, 66, 3, Direction::Horizontal, "abcded");
    CHECK(notebook.read(1, 66, 3, Direction::Horizontal, 5) == "abcde");

    notebook.write(3, 71, 51, Direction::Vertical, "aaaaaa");
    CHECK(notebook.read(3, 71, 51, Direction::Vertical, 3) == "aaa");

    notebook.write(20, 88, 4, Direction::Horizontal, "abcd");
    CHECK(notebook.read(20, 88, 2, Direction::Horizontal, 4) == "abcd");

    notebook.write(4, 35, 5, Direction::Horizontal, "aaaaaaaaaaa");
    CHECK(notebook.read(4, 34, 5, Direction::Vertical, 2) == "_a");

    notebook.write(5, 55, 5, Direction::Vertical, "abcd");
    CHECK(notebook.read(5, 54, 5, Direction::Vertical, 3) == "_ab");

    notebook.write(6, 99, 51, Direction::Vertical, "aaaaaa");
    CHECK(notebook.read(6, 99, 51, Direction::Horizontal, 2) == "a_");
}

TEST_CASE("4. Erasing Check") {
    notebook.write(11, 10, 3, Direction::Horizontal, "abcd");
    notebook.erase(11, 9, 4, Direction::Vertical, 3);
    CHECK(notebook.read(11, 10, 3, Direction::Vertical, 3) == "a__");
    CHECK(notebook.read(11, 9, 4, Direction::Horizontal, 2) == "~_");

    notebook.write(12, 10, 3, Direction::Horizontal, "abcd");
    notebook.erase(12, 10, 3, Direction::Horizontal, 4);
    CHECK(notebook.read(12, 10, 3, Direction::Horizontal, 3) == "~~~");
    CHECK(notebook.read(12, 9, 3, Direction::Vertical, 3) == "_~_");

    notebook.write(13, 10, 3, Direction::Horizontal, "12345678");
    notebook.erase(13, 10, 3, Direction::Horizontal, 8);
    CHECK(notebook.read(13, 10, 3, Direction::Horizontal, 5) == "~~~~~");
    CHECK(notebook.read(13, 9, 4, Direction::Vertical, 3) == "_~_");
}

TEST_CASE("4. Pages Check") {
    int a, b, max,i;
    max = 20;
    i = 0;
    string read_a,read_b;
    srand(time(0));
    while (i < 100) {

        a = rand() % max;
        b = rand() % max;

        if(a != b && a > 0 && b > 0){
            notebook.write(a, 10, 3, Direction::Horizontal, "abcd");
            notebook.write(b, 10, 3, Direction::Horizontal, "abcd");
            read_a = notebook.read(a, 10, 3, Direction::Horizontal, 4);
            read_b = notebook.read(b, 10, 3, Direction::Horizontal, 4);
            CHECK_NE(read_a, read_b);
        }

        i++;
    }

}