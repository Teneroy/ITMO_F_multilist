//
// Created by alexc on 5/22/2019.
//

#ifndef ITMO_F_MULTILIST_DATA_TYPES_H
#define ITMO_F_MULTILIST_DATA_TYPES_H

enum {EMPTY = -1};

struct def
{
    virtual int check() = 0;
};

struct reg : def
{
    reg * cnext;
    reg * snext;
    reg()
    {
        cnext = nullptr;
        snext = nullptr;
    };
    int check() override
    {
        return 0;
    };
};

struct student : def
{
    char name[20];
    reg * ptr;
    student()
    {
        name[0] = '\0';
        ptr = nullptr;
    }
    int check() override
    {
        return -1;
    };
};

struct course : def
{
    int number;
    reg * ptr;
    course()
    {
        number = -1;
        ptr = nullptr;
    }
    int check() override
    {
        return 1;
    };
};

#endif //ITMO_F_MULTILIST_DATA_TYPES_H
