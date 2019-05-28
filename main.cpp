//
// Created by alexc on 5/22/2019.
//

#include "Multilist.h"

int main()
{
    Multilist a;
    a.READFILE("C:\\Users\\Teneroy\\YandexDisk\\ITMO_F_multilist\\data.txt", "C:\\Users\\Teneroy\\YandexDisk\\ITMO_F_multilist\\data2.txt");
    a.PRINT();
    a.ADD("Pit", 101);
    a.ADD("Alex", 101);
    std::cout << std::endl;
    std::cout << std::endl;
    a.ADD("Alex", 102);
    a.PRINT();
    //a.GETSTUDLIST(101);
return 0;
}