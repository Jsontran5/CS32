#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Set test1;
    Set test2;
    

    assert(test1.empty()); //constructed correctly
    assert(test2.empty());

    test1.insert(1); //empty insert
    test1.insert(3); //normal insert
    test1.insert(2);
    test1.insert(4);
    test1.insert(2);

    assert(test1.size() == 4); //correctly updates size
    //contains functions works correctly
    assert(test1.contains(1) && test1.contains(2) && test1.contains(3)
        && test1.contains(4)); //inserts only unique numbers
    //get and sorting correctly
   unsigned long x = 9;
    test1.get(0, x); 
    assert(x == 1); //get functions returns lowest value if pos =0
    test1.get(20, x);
    assert(x == 1); //x stays the same since pos is out of range
    test1.get(3, x);
    assert(x == 4); //x gets the highest value of the linked list 

    //checking assignment operator
    test2 = test1;
    assert(test2.size() == 4); //same size
    assert(test2.contains(1) && test2.contains(2) && test2.contains(3)
        && test2.contains(4));  //same items
    //get and sorting correctly
    unsigned long y = 9;
    test2.get(0, y);
    assert(y == 1); //get functions returns lowest value if pos =0
    test2.get(20, y);
    assert(y == 1); //x stays the same since pos is out of range
    test2.get(3, y);
    assert(y == 4); //x gets the highest value of the linked list 

    //checking copy contructor
    Set test3 = test1;
    assert(test3.size() == 4); //same size
    assert(test3.contains(1) && test3.contains(2) && test3.contains(3)
        && test3.contains(4));  //same items
    //get and sorting correctly with the copy constructor
    unsigned long z = 9;
    test2.get(0, z);
    assert(z == 1); //get functions returns lowest value if pos =0
    test2.get(20, z);
    assert(z == 1); //x stays the same since pos is out of range
    test2.get(3, z);
    assert(z == 4); //x gets the highest value of the linked list 

    
    Set test4;

    test4.insert(1); //empty insert
    test4.insert(3); //normal insert
    test4.insert(2);
    test4.insert(4);
    test4.insert(2);
    test4.insert(5);
    test4.insert(7);
    test4.insert(6);

    assert(test4.size() == 7);//inserts only unique
    assert(test4.contains(1) && test4.contains(2) && test4.contains(3)
        && test4.contains(4) && test4.contains(5) && test4.contains(6) && test4.contains(7)); //expected numbers are inserted in
    unsigned long g = 9;
    test2.get(2, g); //get, transfers the 3rd biggest in to g.
    assert(g == 3); //correctly sorted check
    //erase
    test4.erase(2);
    test4.erase(5);
    test4.erase(7);
    test4.erase(6);
    assert(test4.size() == 3); //erased these 4 numbers correctly
    assert(test4.contains(7) == false); //contains is correct
    assert(!test4.erase(6) && test4.size() == 3); //doesn't erase 6 and keeps same size

    Set test5;
    Set test6;

    test5.insert(1); //empty insert
    test5.insert(2); //normal insert
    test5.insert(3);
    test5.insert(4);

    test6.insert(6); //empty insert
    test6.insert(7); //normal insert
    test6.insert(8);
    test6.insert(9);
    test6.insert(10);
    //swap
    test5.swap(test6);
    assert(test5.size() == 5); //sizes swapped
    assert(test6.size() == 4);
    assert(test5.contains(6) && test5.contains(7) && test5.contains(8) && test5.contains(9) && test5.contains(10)); //test5 now contains tes6 items
    assert(test6.contains(1) && test6.contains(2) && test6.contains(3) && test6.contains(4)); //test 6 now contains test5 items

    //unite
    Set test7;
    Set test8;
    //1,2,3,4
    test7.insert(1); 
    test7.insert(2); 
    test7.insert(3);
    test7.insert(4);
    assert(test7.size() == 4);
    //6,7,8,9,10
    test8.insert(6);
    test8.insert(7); 
    test8.insert(8);
    test8.insert(3);
    test8.insert(4);
    test8.insert(9);
    test8.insert(10);
    assert(test8.size() == 7);

    Set result1;
    unite(test7, test8, result1);
   
    assert(result1.size() == 9); //only unites the unique numbers
    assert(result1.contains(1) && result1.contains(2) && result1.contains(3) && result1.contains(4) && result1.contains(6) && result1.contains(7)
        && result1.contains(8) && result1.contains(9) && result1.contains(10)); //result1 contains the expected numbers

    //unite aliasing check
    unite(test7, test8, test7); //first set and result set are the same
    assert(test7.size() == 9); //still needs to add in the unique numbers of the second set
    assert(test7.contains(1) && test7.contains(2) && test7.contains(3) && test7.contains(4) && test7.contains(6) && test7.contains(7)
        && test7.contains(8) && test7.contains(9) && test7.contains(10)); //test7 should also include #s from test8

    //butNot
    Set test9;
    Set test10;
    //1,2,3,4
    test9.insert(1);
    test9.insert(2);
    test9.insert(3);
    test9.insert(4);
    //3,4,5,6
    test10.insert(3);
    test10.insert(4);
    test10.insert(5);
    test10.insert(6);

    Set result2;
    butNot(test9, test10, result2);
    assert(result2.size() == 2); //only includes 1st set unique items
    assert(result2.contains(1) && result2.contains(2));//which are 1 and 2

    //aliasing check
    butNot(test9, test9, test9); 
    assert(test9.size() == 0);//if set1 and set 2 are the same then the result has to be nothing
    
    //reinsert the #s
    test9.insert(1);
    test9.insert(2);
    test9.insert(3);
    test9.insert(4);
    
    test10.insert(3);
    test10.insert(4);
    test10.insert(5);
    test10.insert(6);
    //aliasing check for s1 and result
    butNot(test9, test10, test9);
    assert(test9.size() == 2); //should still only contain the 2 unique and make sure none of s2 is in it.



}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
