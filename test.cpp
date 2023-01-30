//
// Created by giova on 1/30/2022.
//

#include "DSString.h"

#include "catch.hpp"

TEST_CASE( "Constructors", "[DSString]" ) {
    DSString test1("Hello World!"); // Call constructor with char pointer
    DSString test2(test1); // Call constructor with DSString object

    SECTION("Constructor with char pointer assigns the correct string") {
        REQUIRE(test1 == "Hello World!");
        REQUIRE(test2 == "Hello World!");
    }

    SECTION("Constructor with DSString object assigns the correct string") {
        REQUIRE(test1 == test2);
    }

    SECTION("Assignment operator with char") {
        test1 = "Hello"; // Assign new string with C-Style string
        test2 = "World"; // Assign new string with C-Style string
        REQUIRE(test1 == "Hello");
        REQUIRE(test2 == "World");
    }

    SECTION("Assignment operator with DSString") {
        test1 = test2; // Assign new string with DSString
        REQUIRE(test1 == test2);
    }

    SECTION("Recursive assignment operator") {
        test1 = test2 = "Hello World!"; // Set two DSString to a C-Style string
        REQUIRE(test1 == "Hello World!");
        REQUIRE(test2 == "Hello World!");
    }

    SECTION("Concatenate DSString with C-Style string and DSString") {
        DSString concat;
        test1 = " Hello"; // Reset
        test2 = " World!"; // Reset
        concat = test1+test2; // Concatenate two DSString
        REQUIRE(concat == " Hello World!");

        concat = concat + test1; // Concatenate with first DSString
        REQUIRE(concat == " Hello World! Hello");

        concat = concat + test2; // Concatenate with second DSString
        REQUIRE(concat == " Hello World! Hello World!");
    }

    SECTION("Greater than operator") {
        test1 = "Hello"; // Reset
        test2 = "World!"; // Reset
        REQUIRE(test2 > test1);
        REQUIRE(!(test1 > test2));
        test1 = "Hello"; // Reset
        test2 = "Hello"; // Reset
        REQUIRE(!(test1 > test2));
        REQUIRE(!(test2 > test1));
    }

    SECTION("Subscript operator") {
        test1 = "Hello World!"; // Reset
        REQUIRE(test1[0] == 'H');
        REQUIRE(test1[6] == 'W');
        REQUIRE(test1[11] == '!');
    }

    SECTION("Get length") {
        test1 = "Hello"; // Reset
        test2 = "World!"; // Reset
        REQUIRE(test1.getLength() == 5);
        REQUIRE(test2.getLength() == 6);

        test1 = test1 + " " + test2; // Concatenate the DSStrings
        REQUIRE(test1.getLength() == 12);
    }

    SECTION("Substring") {
        test1 = "Hello"; // Reset
        test2 = "World!"; // Reset
        REQUIRE(test1.substring(1, 2) == "el");
        REQUIRE(test2.substring(2, 3) == "rld");
        REQUIRE(test1.substring(0, 5) == "Hello");
        REQUIRE(test2.substring(5, 1) == "!");
        REQUIRE(test2.substring(0, 1) == "W");
    }

    SECTION("Find single character in DSString") {
        test1 = "Hello"; // Reset
        test2 = "World!"; // Reset
        REQUIRE(test1.find('H') == 0);
        REQUIRE(test2.find('l') == 3);
        REQUIRE(test2.find('!') == 5);
        REQUIRE(test1.find('?') == -1);
    }

    SECTION("Find C-Style string in DSString") {
        test1 = "Hello"; // Reset
        test2 = "World!"; // Reset
        REQUIRE(test1.find("ell") == 1);
        REQUIRE(test2.find("d!") == 4);
        REQUIRE(test1.find("l") == 2);
        REQUIRE(test2.find("World!") == 0);
        REQUIRE(test1.find("World!") == -1);
    }

    SECTION("Find DSString in DSString") {
        test1 = "Hello"; // Reset
        test2 = "World!"; // Reset

        DSString find; // Create temp variable
        find = "ell"; // Set
        REQUIRE(test1.find(find) == 1);

        find = "d!"; // Reset
        REQUIRE(test2.find(find) == 4);

        find = "l"; // Reset
        REQUIRE(test1.find(find) == 2);

        find = "World!"; // Reset
        REQUIRE(test2.find(find) == 0);

        find = "World!"; // Reset
        REQUIRE(test1.find(find) == -1);
    }

    SECTION("To lower case") {
        test1 = "HeLLo"; // Reset
        test2 = "WORLD!"; // Reset
        test1.toLower(); // Change to lower case
        test2.toLower(); // Change to lower case
        REQUIRE(test1 == "hello");
        REQUIRE(test2 == "world!");

        test1 = "hello"; // Reset
        test1.toLower(); // Change to lower case
        REQUIRE(test1 == "hello");
    }

    SECTION("To upper case") {
        test1 = "HeLLo"; // Reset
        test2 = "world!"; // Reset
        test1.toUpper(); // Change to upper case
        test2.toUpper(); // Change to upper case
        REQUIRE(test1 == "HELLO");
        REQUIRE(test2 == "WORLD!");

        test1 = "HELLO"; // Reset
        test1.toUpper(); // Change to upper case
        REQUIRE(test1 == "HELLO");
    }

    SECTION("Clean all non-alpha-numeric characters") {
        test1 = "...Hello & W-o-r-l-d!"; // Reset
        REQUIRE(test1.clean() == 11);
        REQUIRE(test1 == "Hello World");

        test1 = "00~!@#$%^a&*()_+-={1[}b]:;\"'<,>.c?/d"; // Reset
        REQUIRE(test1.clean() == 7);
        REQUIRE(test1 == "00a1bcd");

        test1 = "Hello World"; // Reset
        REQUIRE(test1.clean() == 11);
        REQUIRE(test1 == "Hello World");
    }
}
