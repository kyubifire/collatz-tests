// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Collatz.h"

using namespace std;

// -----------
// TestCollatz
// -----------

// ----
// read
// ----

TEST(CollatzFixture, read1) {
    string s("1 10\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);}

TEST(CollatzFixture, read2) {
    string s("100 10\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(100, p.first);
    ASSERT_EQ(10, p.second);}

TEST(CollatzFixture, read3) {
    string s("901020 342432\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(901020, p.first);
    ASSERT_EQ(342432, p.second);}

/*
// -----
// cycle
// -----

TEST(CollatzFixture, cycle_1) {
    ASSERT_EQ(16, collatz_cycle(22));}

TEST(CollatzFixture, cycle_2) {
    ASSERT_EQ(85, collatz_cycle(567445));}

TEST(CollatzFixture, cycle_3) {
    ASSERT_EQ(1, collatz_cycle(1));}

TEST(CollatzFixture, cycle_4) {
    ASSERT_EQ(7, collatz_cycle(10));}

TEST(CollatzFixture, cycle_5) {
    ASSERT_EQ(8, collatz_cycle(3));}
*/

// ----
// eval
// ----

TEST(CollatzFixture, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_EQ(20, v);}

TEST(CollatzFixture, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_EQ(125, v);}

TEST(CollatzFixture, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_EQ(89, v);}

TEST(CollatzFixture, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_EQ(174, v);}

TEST(CollatzFixture, eval_5) {
    const int v = collatz_eval(22, 22);
    ASSERT_EQ(16, v);}

TEST(CollatzFixture, eval_6) {
    const int v = collatz_eval(1, 1);
    ASSERT_EQ(1, v);}

TEST(CollatzFixture, eval_7) {
    const int v = collatz_eval(565996, 256121);
    ASSERT_EQ(470, v);}

TEST(CollatzFixture, eval_8) {
    const int v = collatz_eval(668887, 818914);
    ASSERT_EQ(504, v);}

TEST(CollatzFixture, eval_9) {
    const int v = collatz_eval(22743, 234351);
    ASSERT_EQ(443, v);}


// -----
// print
// -----

TEST(CollatzFixture, print1) {
    ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}

TEST(CollatzFixture, print2) {
    ostringstream w;
    collatz_print(w, 36636, 128, 9);
    ASSERT_EQ("36636 128 9\n", w.str());}

TEST(CollatzFixture, print3) {
    ostringstream w;
    collatz_print(w, 1, 999999, 100);
    ASSERT_EQ("1 999999 100\n", w.str());}

// -----
// solve
// -----

TEST(CollatzFixture, solve1) {
    istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

TEST(CollatzFixture, solve2) {
    istringstream r("34335 992753\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("34335 992753 525\n", w.str());}

TEST(CollatzFixture, solve3) {
    istringstream r("745093 801238\n1 115907\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("745093 801238 468\n1 115907 354\n", w.str());}

/*
% g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread



% valgrind TestCollatz                                         >  TestCollatz.out 2>&1
% gcov -b Collatz.c++     | grep -A 5 "File 'Collatz.c++'"     >> TestCollatz.out
% gcov -b TestCollatz.c++ | grep -A 5 "File 'TestCollatz.c++'" >> TestCollatz.out



% cat TestCollatz.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestCollatz
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from Collatz
[ RUN      ] Collatz.read
[       OK ] Collatz.read (31 ms)
[ RUN      ] Collatz.eval_1
[       OK ] Collatz.eval_1 (5 ms)
[ RUN      ] Collatz.eval_2
[       OK ] Collatz.eval_2 (3 ms)
[ RUN      ] Collatz.eval_3
[       OK ] Collatz.eval_3 (3 ms)
[ RUN      ] Collatz.eval_4
[       OK ] Collatz.eval_4 (3 ms)
[ RUN      ] Collatz.print
[       OK ] Collatz.print (17 ms)
[ RUN      ] Collatz.solve
[       OK ] Collatz.solve (10 ms)
[----------] 7 tests from Collatz (88 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test case ran. (132 ms total)
[  PASSED  ] 7 tests.
==14225==
==14225== HEAP SUMMARY:
==14225==     in use at exit: 0 bytes in 0 blocks
==14225==   total heap usage: 495 allocs, 495 frees, 70,302 bytes allocated
==14225==
==14225== All heap blocks were freed -- no leaks are possible
==14225==
==14225== For counts of detected and suppressed errors, rerun with: -v
==14225== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
File 'Collatz.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Collatz.c++.gcov'
File 'TestCollatz.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestCollatz.c++.gcov'
*/
