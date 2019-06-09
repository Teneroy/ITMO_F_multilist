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
        std::cout << studname << "_1step: " << added << std::endl;
    } else
    {
        temp = get_last_stud(_sarr[stud_pos].ptr);
        std::cout << "getLastStud - " << studname << ": " << temp << std::endl;
        added = add_to_end(_sarr[stud_pos].ptr, temp);
    }
    if(_carr[course_pos].ptr == nullptr)
    {
        added -> snext = (reg*)&_carr[course_pos];
        std::cout << courseid << ": " << "added_snext-" << added -> snext << ", course_addr-" << &_carr[course_pos] << std::endl;
        _carr[course_pos].ptr = added;
    } else
    {
        temp = get_last_course(_carr[course_pos].ptr);
        added -> snext = temp -> snext;
        temp -> snext = added;
        //std::cout << studname << ": " << temp << std::endl;
        //added = add_to_end(_carr[course_pos].ptr, temp, added);
    }
}

void Multilist::DELETE(const char * studname, unsigned int courseid)
{
    int key = getKey(studname);
    int stud_pos = searchEl(studname);
    int course_pos = searchEl(courseid);
    reg * c_addr = (reg*)&_carr[course_pos];
    reg * prev_c = (reg*)&_sarr[stud_pos];
    reg * cur = _sarr[stud_pos].ptr;
    reg * temp_s;
    student * temp_stud;
    while (cur != (reg*)&_sarr[stud_pos])
    {
        if(cur -> snext == c_addr)
            break;
        if(cur -> snext -> check() == COURSE)
        {
            cur = cur -> cnext;
            if(prev_c -> check() == STUD)
            {
                temp_stud = (student*)prev_c;
                prev_c = temp_stud -> ptr;
            } else
            {
                prev_c = prev_c -> cnext;
            }
            continue;
        }
        temp_s = cur -> snext;
        while (temp_s -> snext -> check() != COURSE)
        {
            temp_s = temp_s -> snext;
        }
        if(temp_s -> snext == c_addr)
            break;
        cur = cur -> cnext;
        prev_c = prev_c -> cnext;
    }
    reg * prev_s = get_prev_course(cur);
    if(prev_s -> check() == REG)
    {
        prev_s -> snext = cur -> snext;
    } else
    {
        //course * prev_s_course = (course*)prev_s;
        //prev_s_course -> ptr = nullptr;
        if(prev_s == cur -> snext)
            _carr[course_pos].ptr = nullptr;
        else
            _carr[course_pos].ptr = cur -> snext;
        //?????
    }
    if(prev_c -> check() == STUD)
    {
        if(cur -> cnext -> check() == STUD)
        {
            //student * prev_c_stud = (student*)prev_c;
            //prev_c_stud -> ptr = nullptr;
            _sarr[stud_pos].ptr = nullptr;
        } else
        {
            //student * prev_c_stud = (student*)prev_c;
            //prev_c_stud -> ptr = cur -> cnext;
            _sarr[stud_pos].ptr = cur -> cnext;
        }
    } else
    {
        prev_c -> cnext = cur -> cnext;
    }
    delete cur;
}

reg * Multilist::get_prev_course(reg * cur) const
{
    reg * temp = cur;
    course * c_temp;
    while (true)
    {
        if (temp -> check() == COURSE)
        {
            c_temp = (course*)temp;
            if(c_temp -> ptr == cur)
                return temp;
            temp = c_temp -> ptr;
        }
        if(temp -> snext == cur)
            return temp;
        temp = temp -> snext;
    }
}

void Multilist::GETSTUDLIST(unsigned int courseid) const
{
    std::cout << "Studlist: ";
    int course_pos = searchEl(courseid);
    if(_carr[course_pos].ptr == nullptr)
        return;
    reg * temp = _carr[course_pos].ptr;
    reg * temp_stud;
    student * temp2;
    while (temp -> check() != COURSE)
    {
        if(temp -> cnext -> check() == STUD)
        {
            temp2 = (student *)temp -> cnext;
            std::cout << temp2 -> name << ", ";
        } else
        {
            temp_stud = temp;
            while (temp_stud -> cnext -> check() != STUD)
            {
                temp_stud = temp_stud -> cnext;
            }
            temp2 = (student *)temp_stud -> cnext;
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
    if(_sarr[stud_pos].ptr == nullptr)
        return;
    reg * temp = _sarr[stud_pos].ptr;
    reg * temp_stud;
    course * temp2;
    while (temp -> check() != STUD)
    {
        if(temp -> snext -> check() == COURSE)
        {
            temp2 = (course *)temp -> snext;
            std::cout << temp2 -> number << ", ";
        } else
        {
            temp_stud = temp;
            while (temp_stud -> snext -> check() != COURSE)
            {
                temp_stud = temp_stud -> snext;
            }
            temp2 = (course *)temp_stud -> snext;
            std::cout << temp2 -> number << ", ";
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

reg * Multilist::get_last_course(reg * head) const
{
    reg * temp = head;
    reg * temp2;
    temp2 = head -> snext;
    while (temp2 -> check() != COURSE)
    {
        temp = temp -> snext;
        temp2 = temp2 -> snext;
    }
    return temp;
}

reg * Multilist::get_last_stud(reg * head) const
{
    reg * temp = head;
    reg * temp2;
    temp2 = head -> cnext;
    while (temp2 -> check() != STUD)
    {
        temp = temp -> cnext;
        temp2 = temp2 -> cnext;
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