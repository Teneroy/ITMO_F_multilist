//
// Created by alexc on 5/22/2019.
//

#ifndef ITMO_F_MULTILIST_DATA_TYPES_H
#define ITMO_F_MULTILIST_DATA_TYPES_H

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
        return 0;
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
