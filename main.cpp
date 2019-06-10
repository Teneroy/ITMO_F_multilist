//
// Created by alexc on 5/22/2019.
//

#include "Multilist.h"

int main()
{
    Multilist a;
    a.READFILE("C:\\ITMO_F_multilist\\data.txt", "C:\\ITMO_F_multilist\\data2.txt");
    a.PRINT();
    a.ADD("Pit", 101);
    a.ADD("Alex", 101);
    std::cout << std::endl;
    std::cout << std::endl;
    a.ADD("Alex", 102);
    a.ADD("Alex", 102);
    a.PRINT();
    //a.GETSTUDLIST(102);
    a.GETCOURSELIST("Pit");
    //a.DELETE("Alex", 101);
    //a.GETSTUDLIST(101);
    a.GETCOURSELIST("Alex");
    a.GETSTUDLIST(102);
    a.DELETE("Pit", 101);
//    a.GETSTUDLIST(101);
    a.DELETE("Alex", 102);
//    a.GETSTUDLIST(102);
//    a.REFSTUD("Alex");
    a.GETSTUDLIST(101);
    a.GETSTUDLIST(102);
//    a.GETCOURSELIST("Pit");
   // a.REFCOURSE(102);
    //a.GETSTUDLIST(102);
//    a.PRINT();
//    a.GETCOURSELIST("Alex");
//    a.GETCOURSELIST("Pit");
//    a.GETSTUDLIST(102);
return 0;
}