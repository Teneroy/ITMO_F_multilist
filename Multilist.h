//
// Created by alexc on 5/22/2019.
//
#ifndef ITMO_F_MULTILIST_MULTILIST_H
#define ITMO_F_MULTILIST_MULTILIST_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include "string.h"
#include "data-types.h"

enum {SIZE = 50, ERR = -1000};

class Multilist
{
public:
    //~Multilist();
    void READFILE(const char * filename_s, const char * filename_c);
    void ADD(const char * studname, unsigned int courseid);
    void DELETE(const char * studname, unsigned int courseid);
    void REFSTUD(const char * studname);
    void REFCOURSE(unsigned int courseid);
    void GETSTUDLIST(unsigned int courseid) const;
    void GETCOURSELIST(const char * studname) const;
    void PRINT() const;
private:
    course _carr[SIZE];
    student _sarr[SIZE];
    void insert_arr(int x); //вставка в массив курсов
    void insert_arr(const char * x); //вставка в массив студентов
    int getKey(const char * data) const; //Суммирует коды символов в строке
    int getFreePos(int key, int iter) const; //Получить позицию  для вставкки, путем повторного хеширования
    int getFreePosCourse(int key, int iter) const;
    int searchEl(const char * x, int key, int iter) const; //Поиск элемента студента, если не нашли, вернуть ERR
    int searchEl(int x, int iter) const; //Поиск элемента курса, если не нашли, вернуть ERR
    int hash(int key, int iter) const; //хеширование (key + iter) % SIZE
};

#endif //ITMO_F_MULTILIST_MULTILIST_H
