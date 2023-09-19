/**
 * @file DateTime.cpp
 * @author DECSAI && Manuel Fuentes Plaza && Noelia Carrasco Vilar
 *  @date 23/03/2021
 */

#include <iostream>
#include <sstream>
#include "DateTime.h"

/**
 * @brief auxiliary function to check if the date and the time are in correct 
 * format, taking into account, leap year etc.
 * @param year input
 * @param month input
 * @param day input
 * @param hour input
 * @param min input
 * @param sec input
 * @return true if is correct, false if not
 */
bool isCorrect(int year, int month, int day, int hour, int min, int sec);

/**
 * @brief split the first field in 6 components of the data time.
 * Please consider using string::substr(int, int)[https://en.cppreference.com/w/cpp/string/basic_string/substr] to cut the line
 * into the appropriate substrings and then convert it into integer values with 
 * the function stoi(string) [https://en.cppreference.com/w/cpp/string/basic_string/stol]
 * ~~~~
 *      YYYY-MM-dd hh:mm:ss UTC 
 *      +----+----+----+----+----+ 
 *      |    |    |    |    |    |
 *      0    5    10   15   20   25
 * ~~~~
 * @param line input string
 * @param y output int
 * @param m output int
 * @param d output int
 * @param h output int
 * @param mn output int
 * @param s output int
 */
void split(const string &line, int &y, int  &m, int  &d, int  &h, int &mn, int &s);

DateTime::DateTime() {
    initDefault();
}

DateTime::DateTime(const string  &date) {
    set(date);
}

int DateTime::year() const{
    return _year;
}

int DateTime::month() const {
     return _month;
}

int DateTime::day() const{
     return _day;
}

int DateTime::hour() const {
     return _hour;
}

int DateTime::min() const{
     return _min;
}

int DateTime::sec() const{
     return _sec;
}

void DateTime::set(const string  &line) {
  
    if (line.size() == 23) { //23 debido al UTC
        split(line, _year, _month, _day, _hour, _min, _sec);
        if (!isCorrect(_year, _month, _day, _hour, _min, _sec)) {
            initDefault();
        }
    } else {
        initDefault();
    }
}

bool DateTime::isBefore(const DateTime  &one) const{
    bool esta_antes = false;
    
    if (one.year() > year()) {
        esta_antes = true;
    } else if (one.month() > month()) {
         esta_antes = true;
    } else if (one.day() > day()) {
         esta_antes = true;
    } else if (one.hour() > hour()) {
         esta_antes = true;
    } else if (one.min() > min()) {
         esta_antes = true;
    } else if (one.sec() > sec()) {
         esta_antes = true;
    }

    return esta_antes;
}

int DateTime::weekDay() const{
    int a = (14 - _month) / 12;
    int y =  _year - a;
    int m = _month + 12*a - 2;
    return (_day + y + y/4 - y/100 + y/400 + (31*m)/12)% 7;
}

//método privado
void DateTime::initDefault() {
    _year = 1971;
    _month = 01;
    _day = 01;
    _hour = 00;
    _min = 00;
    _sec = 00;    
}

//FUNCIONES EXTERNAS

string DateTime::to_string() const {
    char local[64];
    sprintf(local, "%04i-%02i-%02i %02i:%02i:%02i UTC", _year, _month, _day, _hour, _min, _sec);
    return local;
}

void split(const string &line, int &y, int  &m, int  &d, int  &h, int &mn, int &s) {
    y = stoi(line.substr(0, 4));
    m = stoi(line.substr(5, 6));
    d = stoi(line.substr(8, 9));
    h = stoi(line.substr(11, 12));
    mn = stoi(line.substr(14, 15));
    s = stoi(line.substr(17, 18));
}

bool isCorrect(int year, int month, int day, int hour,int min,int sec) {
    bool formato_incorrecto = false;
    bool continuar = true;
    const int MESES30 [] = {4, 6, 9, 11};
    const int MESES31 [] = {1, 3, 5, 7, 8, 10, 12};

    /*if (year < 0) {
        formato_incorrecto = true;
    } else*/ if (month < 1 || month > 12) {
        formato_incorrecto = true;
    } else if (hour < 0 || hour > 23) {
        formato_incorrecto = true;
    } else if (min < 0 || min > 59) {
        formato_incorrecto = true;        
    } else if (sec < 0 || sec > 59) {
        formato_incorrecto = true; 
    } 
    
    //comprobamos el dia
    if (day < 0) {
        formato_incorrecto = true;
    } else {
        
        //comprobamos que los dias cumplan segun el mes
        
        for (int i=0; i < 4 && continuar; i++) { //comprobamos 30 dias
            if (month == MESES30[i]) {
                if (day > 30) {
                    formato_incorrecto = true;
                    continuar = false;
                }
            }
        }
        
        if (month == 2) { //comprobamos si es febrero, no consideramos años bisiestos
            if (day > 29) {
                formato_incorrecto = true;
            }
        }
        
        for (int i=0; i < 7 && continuar; i++) { //comprobamos 31 dias
            if (month == MESES31[i]) {
                if (day > 31) {
                    formato_incorrecto = true;
                    continuar = false;
                }
            }
        }
    }
        
    return !formato_incorrecto;
}
