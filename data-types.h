//
// Created by alexc on 5/22/2019.
//

#ifndef ITMO_F_MULTILIST_DATA_TYPES_H
#define ITMO_F_MULTILIST_DATA_TYPES_H

enum {EMPTY_C = -1, REG = 0, STUD = -1, COURSE = 1};

struct def
{
    virtual int check() = 0;
};

struct reg : def
{
    reg * cnext; //Указатель на студента или себя
    reg * snext; //Указатель на курс или себя
    reg()
    {
        cnext = nullptr;
        snext = nullptr;
    };
    reg(reg * cn, reg * sn) : cnext(cn), snext(sn)
    {};
    int check() override
    {
        return REG;
    };
};

struct student : def
{
    char * name;
    reg * ptr;
    student()
    {
        name = nullptr;
        ptr = nullptr;
    }
    int check() override
    {
        return STUD;
    };
};

struct course : def
{
    int number;
    reg * ptr;
    course()
    {
        number = EMPTY_C;
        ptr = nullptr;
    }
    int check() override
    {
        return COURSE;
    };
};

#endif //ITMO_F_MULTILIST_DATA_TYPES_H
