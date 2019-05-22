//
// Created by alexc on 5/22/2019.
//
#ifndef ITMO_F_MULTILIST_MULTILIST_H
#define ITMO_F_MULTILIST_MULTILIST_H
#include <iostream>
#include "data-types.h"

enum {SIZE = 10};

class Multilist
{
public:
    //~Multilist();
    void READFILE(const char * filename);
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
};

#endif //ITMO_F_MULTILIST_MULTILIST_H
