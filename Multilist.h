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

enum {EMPTY_C = -1, REG = 0, STUD = -1, COURSE = 1, SIZE = 50, ERR = -1000};

class Multilist
{
public:
    //~Multilist();
    void READFILE(const char * filename_s, const char * filename_c); //Чтение данных из файлов студентов и курсов
    void ADD(const char * studname, unsigned int courseid); //Добавление студента на курс
    void DELETE(const char * studname, unsigned int courseid); //Удалениие студента с курса
    void REFSTUD(const char * studname); //Удалить студента со всех курсов
    void REFCOURSE(unsigned int courseid); //Удалить всех студентов с курса
    void GETSTUDLIST(unsigned int courseid) const; //Получить список студентов на курсе
    void GETCOURSELIST(const char * studname) const; //Получить список курсов у студента
    void PRINT() const;
private:
    course _carr[SIZE]; //Массив курсов
    student _sarr[SIZE]; //Массив студентов
    void insert_arr(int x); //вставка в массив курсов
    void insert_arr(const char * x); //вставка в массив студентов
    int getKey(const char * data) const; //Суммирует коды символов в строке
    int getFreePos(int key) const; //Получить позицию  для вставкки, путем повторного хеширования
    int getFreePosCourse(int key) const;
    int searchEl(const char * x) const; //Поиск элемента студента, если не нашли, вернуть ERR
    int searchEl(int x) const; //Поиск элемента курса, если не нашли, вернуть ERR
    int hash(int key, int iter) const; //хеширование (key + iter) % SIZE
    reg * get_last_course(reg * head) const; //Получить последнюю регистрационную запись курса
    reg * get_last_stud(reg * head) const; //Получить последнюю регистрационную запись студента
    reg * add_to_end(reg * head, reg * last) const; //Добавить регистрационную запись(с созданием новой записи)
    reg * add_to_end(reg * head, reg * last, reg * added) const;
    reg * get_prev_course(reg * cur) const; //Получить предыдущую регистрационную запись курса(идем по snext)
    reg * get_prev_stud(reg * cur) const; //Получить предыдущую регистрационную запись студента(идем по сnext)
    void ref_ptr_course(int course_pos, reg * prev_s, reg * cur);
    void ref_ptr_stud(int stud_pos, reg * prev_c, reg * cur);
};

#endif //ITMO_F_MULTILIST_MULTILIST_H
