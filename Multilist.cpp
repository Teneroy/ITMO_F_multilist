//
// Created by alexc on 5/22/2019.
//

#include "Multilist.h"

Multilist::~Multilist()
{
    int i = 0;
    for(; i < SIZE; i++)
    {
        if(_sarr[i].name != nullptr)
        {
            REFSTUD(_sarr[i].name);
        }
        delete [] _sarr[i].name;
    }
}

void Multilist::ADD(const char * studname, unsigned int courseid)
{
    int stud_pos = searchEl(studname);
    if(stud_pos == ERR)
        return;
    int course_pos = searchEl(courseid);
    if(course_pos == ERR)
        return;
    if(_sarr[stud_pos].ptr != nullptr && _carr[course_pos].ptr != nullptr)
    {
        if(search_on_course(course_pos, stud_pos))
            return;
    }
    reg * temp;
    reg * added;//Указатель на добавленную запись
    if(_sarr[stud_pos].ptr == nullptr) //Если у студента нет курсов
    {
        _sarr[stud_pos].ptr = new reg((reg*)&_sarr[stud_pos], nullptr); //Добавляем новую регистрационную запись
        added = _sarr[stud_pos].ptr;//Указываем на новую запись
        std::cout << studname << "_1step: " << added << std::endl;
    } else
    {
        temp = get_last_stud(_sarr[stud_pos].ptr); //Получаем последнюю регистрационную запись студента
        std::cout << "getLastStud - " << studname << ": " << temp << std::endl;
        added = add_to_end(_sarr[stud_pos].ptr, temp); //Добавляем в конец новую запись
    }
    if(_carr[course_pos].ptr == nullptr) //Если на курсе нет людей
    {
        added -> snext = (reg*)&_carr[course_pos]; //Последеяя рег запись указывает на курс
        std::cout << courseid << ": " << "added_snext-" << added -> snext << ", course_addr-" << &_carr[course_pos] << std::endl;
        _carr[course_pos].ptr = added; //Курс указывает на последнюю запись
    } else
    {
        temp = get_last_course(_carr[course_pos].ptr); //Получаем последнюю рез запись курса
        added -> snext = temp -> snext; //Последняя запись указывает на курс
        temp -> snext = added; //Последняя рег-запись курса указывает на добавленную запись
        //std::cout << studname << ": " << temp << std::endl;
        //added = add_to_end(_carr[course_pos].ptr, temp, added);
    }
}

void Multilist::DELETE(const char * studname, unsigned int courseid)
{
    int stud_pos = searchEl(studname);
    if(stud_pos == ERR)
        return;
    int course_pos = searchEl(courseid);
    if(course_pos == ERR)
        return;
    if(!search_on_course(course_pos, stud_pos))
        return;
    reg * c_addr = (reg*)&_carr[course_pos];
    reg * prev_c = (reg*)&_sarr[stud_pos];
    reg * cur = _sarr[stud_pos].ptr;
    reg * temp_s;
    student * temp_stud;
    while (cur != (reg*)&_sarr[stud_pos]) //Идем по списку(по студентам cnext), получая текущую регистрационную запись студента и запоминая предыдудшую
    {
        if(cur -> snext == c_addr) //Если указатель на курс равен теущему курсу, то мы нашли элемент и выходим из цикла
            break;
        if(cur -> snext -> check() == COURSE) //Если указатель на следующую рег запись курса это сам курс, но не текущий курс
        {
            cur = cur -> cnext; //Переходим на следующую регистрационную запись студента
            if(prev_c -> check() == STUD)//Если предыдущая запись является структурой студента
            {
                temp_stud = (student*)prev_c;
                prev_c = temp_stud -> ptr;//Смещаем указатель
            } else
            {
                prev_c = prev_c -> cnext; //Смещаем указатель
            }
            continue; //Новая итерация
        }
        temp_s = get_last_course(cur -> snext);//Идем регистрационным записям курса, пока запись не будет ссылаться нна курс
        if(temp_s -> snext == c_addr) //Если запись ссылается на текущий курс, то мы выбрали нужную запись и можно выходить из цикла
            break;
        cur = cur -> cnext;
        prev_c = prev_c -> cnext;
    }

    reg * prev_s = get_prev_course(cur); //Получить предыдущую регистрационную запись с текущего курса
    //начинаем убирать связи
    //__убираем связи с курсами__//
    ref_ptr_course(course_pos, prev_s, cur);
    //___//
    //__убираем связи со студентами__//
    ref_ptr_stud(stud_pos, prev_c, cur);
    delete cur;
}

void Multilist::REFSTUD(const char * studname)
{
    int stud_pos = searchEl(studname);
    if(stud_pos == ERR)
        return;
    if(_sarr[stud_pos].ptr == nullptr)
        return;
    reg * temp = _sarr[stud_pos].ptr;
    reg * prev;
    reg * temp_del;
    while (temp != (reg*)&_sarr[stud_pos])
    {
        prev = get_prev_course(temp);
        if(temp -> snext == prev) //на курсе 1 человек
        {
            change_course_ptr(prev, nullptr);
        } else if(prev -> check() != REG) //prev это не reg
        {
            change_course_ptr(prev, temp -> snext);
        } else
        {
            prev -> snext = temp -> snext;
        }
        temp_del = temp;
        temp = temp -> cnext;
        delete temp_del;
    }
    _sarr[stud_pos].ptr = nullptr;
}

void Multilist::REFCOURSE(unsigned int courseid)
{
    int course_pos = searchEl(courseid);
    if(course_pos == ERR)
        return;
    if(_carr[course_pos].ptr == nullptr)
        return;
    reg * temp = _carr[course_pos].ptr;
    reg * prev;
    reg * temp_del;
    while (temp != (reg*)&_carr[course_pos])
    {
        prev = get_prev_stud(temp);//stud
        if(temp -> cnext == prev) //на у человека 1 курс
        {
            change_stud_ptr(prev, nullptr);
        } else if(prev -> check() != REG) //prev это не reg
        {
            change_stud_ptr(prev, temp -> cnext);
        } else
        {
            prev -> cnext = temp -> cnext;
        }
        temp_del = temp;
        temp = temp -> snext;
        delete temp_del;
    }
    _carr[course_pos].ptr = nullptr;
}


void Multilist::GETSTUDLIST(unsigned int courseid) const
{
    std::cout << "Studlist: ";
    int course_pos = searchEl(courseid);
    if(course_pos == ERR)
        return;
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
            temp_stud = get_last_stud(temp);
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
    if(stud_pos == ERR)
        return;
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
            temp_stud = get_last_course(temp);
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

bool Multilist::search_on_course(int cpos, int spos) const
{
    reg * temp = _carr[cpos].ptr;
    reg * s_addr = (reg*)&_sarr[spos];
    if(temp -> cnext == s_addr)
        return true;
    temp = temp -> snext;
    course * c_temp;
    reg * temp2;
    while (temp != _carr[cpos].ptr)
    {
        if (temp -> check() == COURSE)
        {
            c_temp = (course*)temp;
            temp = c_temp -> ptr;
            continue;
        }
        if(temp -> cnext == s_addr)
            return true;
        if(temp -> cnext -> check() != STUD)
        {
            temp2 = get_last_stud(temp);
            if(temp2 -> cnext == s_addr)
                return true;
        }
        temp = temp -> snext;
    }
    return false;
}

void Multilist::ref_ptr_stud(int stud_pos, reg * prev_c, reg * cur)
{
    if(prev_c -> check() == STUD)
    {
        if(cur -> cnext -> check() == STUD)
        {
            _sarr[stud_pos].ptr = nullptr;
        } else
        {
            _sarr[stud_pos].ptr = cur -> cnext;
        }
    } else
    {
        prev_c -> cnext = cur -> cnext;
    }
}

void Multilist::ref_ptr_course(int course_pos, reg * prev_s, reg * cur)
{
    if(prev_s -> check() == REG)
    {
        prev_s -> snext = cur -> snext;
    } else
    {
        if(prev_s == cur -> snext)
            _carr[course_pos].ptr = nullptr;
        else
            _carr[course_pos].ptr = cur -> snext;
    }
}

void Multilist::change_course_ptr(reg * struct_ptr, reg * nptr)
{
    course * c_temp = (course*)struct_ptr;
    int course_pos = searchEl(c_temp -> number);
    _carr[course_pos].ptr = nptr;
}

void Multilist::change_stud_ptr(reg * struct_ptr, reg * nptr)
{
    student * s_temp = (student*)struct_ptr;
    int stud_pos = searchEl(s_temp -> name);
    _sarr[stud_pos].ptr = nptr;
}

reg * Multilist::get_prev_stud(reg * cur) const
{
    reg * temp = cur;
    student * s_temp;
    while (true)
    {
        if (temp -> check() == STUD)
        {
            s_temp = (student*)temp;
            if(s_temp -> ptr == cur)
                return temp;
            temp = s_temp -> ptr;
        }
        if(temp -> cnext == cur)
            return temp;
        temp = temp -> cnext;
    }
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
    //int fp = getFreePos(key);
    int iter = 0;
    int check = hs;
    while(_sarr[hs].name != nullptr)
    {
        if(strcmp(_sarr[hs].name, x) == 0)
            return;
        iter++;
        hs = hash(key, iter);
        if(hs == check)
            return;
    }
    _sarr[hs].name = new char[20]; //отдельная функция?
    strcpy(_sarr[hs].name, x);
}

void Multilist::insert_arr(int x) {
    int hs = hash(x, 0);
    if (_carr[hs].number == EMPTY_C)
    {
        _carr[hs].number = x;
        return;
    }
    int iter = 0;
    int check = hs;
    while(_carr[hs].number != EMPTY_C)
    {
        if(_carr[hs].number == x)
            return;
        iter++;
        hs = hash(x, iter);
        if(hs == check)
            return;
    }
    _carr[hs].number = x;
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