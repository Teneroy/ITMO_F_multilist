//
// Created by alexc on 5/22/2019.
//

#include "Multilist.h"

void Multilist::ADD(const char * studname, unsigned int courseid)
{
    int key = getKey(studname);
    int stud_pos = searchEl(studname);
    int course_pos = searchEl(courseid);
    reg * temp;
    reg * added;
    if(_sarr[stud_pos].ptr == nullptr)
    {
        _sarr[stud_pos].ptr = new reg((reg*)&_sarr[stud_pos], nullptr);
        added = _sarr[stud_pos].ptr;
    } else
    {
        temp = get_last(_sarr[stud_pos].ptr);
        added = add_to_end(_sarr[stud_pos].ptr, temp);
    }
    if(_carr[course_pos].ptr == nullptr)
    {
        added -> snext = (reg*)&_carr[course_pos];
        _carr[course_pos].ptr = added;
    } else
    {
        temp = get_last( _carr[course_pos].ptr);
        added = add_to_end(_carr[course_pos].ptr, temp, added);
    }
}

void Multilist::GETSTUDLIST(unsigned int courseid) const
{
    std::cout << "Studlist: ";
    int course_pos = searchEl(courseid);
    reg * temp = _carr[course_pos].ptr;
    while (temp != (reg*)&_carr[course_pos])
    {
        if(temp -> cnext -> check() == STUD)
        {
            student * temp2;
            temp2 = (student *)temp -> cnext;
            std::cout << temp2 -> name << ", ";
        }
        temp = temp -> snext;
    }
    std::cout << ";" << std::endl;
}

void Multilist::GETCOURSELIST(const char * studname) const
{
    std::cout << "Courselist: ";
    int stud_pos = searchEl(studname);
    reg * temp = _sarr[stud_pos].ptr;
    while (temp != (reg*)&_sarr[stud_pos])
    {
        if(temp -> snext -> check() == STUD)
        {
            student * temp2;
            temp2 = (student *)temp -> snext;
            std::cout << temp2 -> name << ", ";
        }
        temp = temp -> cnext;
    }
    std::cout << ";" << std::endl;
}


void Multilist::READFILE(const char * filename_s, const char * filename_c)
{
    std::cout << "READ START STUDENTS " << filename_s << std::endl;
    std::ifstream myReadFile;
    myReadFile.open(filename_s);
    if (myReadFile.is_open())
    {
        char data[20];
        while (!myReadFile.eof())
        {
            myReadFile >> data;
            insert_arr(data);
        }
        myReadFile.close();
    }

    std::cout << "READ START COURSES " << filename_s << std::endl;
    myReadFile.open(filename_c);
    if (myReadFile.is_open())
    {
        int x;
        while (!myReadFile.eof())
        {
            myReadFile >> x;
            insert_arr(x);
        }
        myReadFile.close();
    }
}

void Multilist::PRINT() const
{
    int i = 0;
    for(; i < SIZE; i++)
    {
        std::cout << std::setw(25) << (_sarr[i].name != nullptr ? _sarr[i].name : "") << "|";
        std::cout << std::setw(25) << (_carr[i].number != EMPTY_C ? _carr[i].number : 0) << std::endl;
    }
}

void Multilist::insert_arr(const char * x)
{
    int key = getKey(x);
    int hs = hash(key, 0);
    if(_sarr[hs].name == nullptr)
    {
        _sarr[hs].name = new char[20]; //отдельная функция?
        strcpy(_sarr[hs].name, x);
        return;
    }
    int fp = getFreePos(key);
    _sarr[fp].name = new char[20]; //отдельная функция?
    strcpy(_sarr[fp].name, x);
}

void Multilist::insert_arr(int x) {
    int hs = hash(x, 0);
    if (_carr[hs].number == EMPTY_C)
    {
        _carr[hs].number = x;
        return;
    }
    int fp = getFreePosCourse(x);
    _carr[fp].number = x;
}

int Multilist::hash(int key, int iter) const
{
    return (key + iter) % SIZE;
}

int Multilist::getKey(const char * data) const
{
    int i = 0;
    int key = 0;
    for(; i < strlen(data); i++)
    {
        key += data[i];
    }
    return key;
}

int Multilist::getFreePos(int key) const
{
    int iter = 0;
    int hs = hash(key, iter);
    int check = hs;
    while(_sarr[hs].name != nullptr)
    {
        iter++;
        hs = hash(key, iter);
        if(hs == check)
            return ERR;
    }
    return hs;
}

int Multilist::getFreePosCourse(int key) const
{
    int iter = 0;
    int hs = hash(key, iter);
    int check = hs;
    while(_carr[hs].number != EMPTY_C)
    {
        iter++;
        hs = hash(key, iter);
        if(hs == check)
            return ERR;
    }
    return hs;
}

int Multilist::searchEl(const char * x) const
{
    int iter = 0;
    int key = getKey(x);
    int hs = hash(key, iter);
    if(_sarr[hs].name == nullptr)
        return ERR;
    while (strcmp(_sarr[hs].name, x) != 0)
    {
        iter++;
        hs = hash(key, iter);
        if(_sarr[hs].name == nullptr)
            return ERR;
    }
    return hs;
}

int Multilist::searchEl(int x) const
{
    int iter = 0;
    int key = x;
    int hs = hash(key, iter);
    if(_carr[hs].number == EMPTY_C)
        return ERR;
    while (_carr[hs].number != key)
    {
        iter++;
        hs = hash(key, iter);
        if(_carr[hs].number == EMPTY_C)
            return ERR;
    }
    return hs;
}

reg * Multilist::get_last(reg * head) const
{
    reg * temp = head;
    reg * temp2;
    if(temp -> check() == STUD)
    {
        temp2 = head -> cnext;
        while (temp2 != head)
        {
            temp = temp -> cnext;
            temp2 = temp2 -> cnext;
        }
    } else
    {
        temp2 = head -> snext;
        while (temp2 != head)
        {
            temp = temp -> snext;
            temp2 = temp2 -> snext;
        }
    }
    return temp;
}

reg * Multilist::add_to_end(reg * head, reg * last) const
{
    reg * temp = new reg(last -> cnext, nullptr);
    last -> cnext = temp;
    return temp;
}

reg * Multilist::add_to_end(reg * head, reg * last, reg * added) const
{
    added -> snext = last -> snext;
    reg * temp = added;
    last -> snext = temp;
    return temp;
}