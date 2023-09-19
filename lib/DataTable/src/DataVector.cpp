/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <cassert>
#include "DataVector.h"
using namespace std;

const std::string SPECIAL_CHARS[] = {"┌┐└┘─│┬┴┼┤├▄", "++++-|", "▁▂▃▄▅▆▇█", "▏▎▍▌▋▊▉█"};

DataVector::DataVector() {
    clear();
}

DataVector::DataVector(int ndata) {
    clear();
    alloc(ndata);
}

DataVector & DataVector::clear() {
    _title = "";
    _nData = 0;
    for (int i = 0; i < MAX_WIDTH; i++) {
        _data[i]=0;
        _labels[i]="";
    }
    return *this;
}

DataVector DataVector::alloc(int n) {
    clear();
    _nData = n;
    return *this;
}

int DataVector::size() const {
    return _nData;
}

double DataVector::getValue(int pos) const {
    assert(0 <= pos && pos < size());
    return _data[pos];
}
string DataVector::getLabel(int pos) const {
    assert(0 <= pos && pos < size());
    return _labels[pos];
}

DataVector &DataVector::setValue(int pos, double data) {
    assert(0 <= pos && pos < size());
    _data[pos] = data;
    return *this;
}

DataVector &DataVector::setLabel(int pos, const string & label) {
    assert(0 <= pos && pos < size());
    _labels[pos] = label;
    return *this;
}

DataVector & DataVector::loadValues(const int values[]) {
    for (int i = 0; i < size(); i++)
        setValue(i, values[i]);
    return *this;
}

DataVector & DataVector::loadValues(const double values[]) {
    for (int i = 0; i < size(); i++)
        setValue(i, values[i]);
    return *this;
}

DataVector & DataVector::loadLabels(const std::string labels[]) {
    for (int i = 0; i < size(); i++)
        setLabel(i, labels[i]);
    return *this;
}

DataVector & DataVector::loadLabels(const char* const labels[]) {
    for (int i = 0; i < size(); i++)
        setLabel(i, labels[i]);
    return *this;
}

DataVector & DataVector::add(const string &label, double data) {
    assert(_nData < MAX_WIDTH);
    _labels[_nData] = label;
    _data[_nData++] = data;
    return *this;
}

DataVector & DataVector::setTitle(const string &title) {
    _title = title;
    return *this;
}

string DataVector::showPlainReportH(int decpos) const {
    string res = _title + "\n",
            fdata = (string) "%" + std::to_string(FIELD_WIDTH) + "." + std::to_string(decpos) + "f",
            flabel = (string) "%" + std::to_string(FIELD_WIDTH) + "s";
    double byrow;
    char aux [MAX_WIDTH];
    byrow = 0;
    for (int i = 0; i < size(); i++) {
        sprintf(aux, fdata.c_str(), getValue(i));
        res = res + aux;
        byrow += getValue(i);
    }
    sprintf(aux, fdata.c_str(), byrow);
    res = res + aux + "\n";
    for (int i = 0; i < size(); i++) {
        sprintf(aux, flabel.c_str(),getLabel(i).c_str());
        res = res + aux;
    }
    res += "\n";
    return res;
}

string DataVector::showPlainReportV(int decpos) const {
    string res = _title + "\n",
            fdata = (string) "%" + std::to_string(FIELD_WIDTH) + "." + std::to_string(decpos) + "f",
            flabel = (string) "%" + std::to_string(FIELD_WIDTH) + "s",
            axis("-", FIELD_WIDTH);
    double byrow;
    char aux [MAX_WIDTH];
    int i;

    byrow = 0;
    for (int i = 0; i < size(); i++) {
        sprintf(aux, flabel.c_str(), _labels[i].c_str());
        res = res + aux;
        sprintf(aux, fdata.c_str(), getValue(i));
        res += aux;
        byrow += getValue(i);
        res += "\n";
    }
    sprintf(aux, fdata.c_str(), byrow);
    res = res + aux + "\n";
    return res;
}

string DataVector::showFancyReportH(int decpos) const {
    string res = _title + "\n",
            fdata = (string) "%" + std::to_string(FIELD_WIDTH) + "." + std::to_string(decpos) + "f",
            flabel = (string) "%" + std::to_string(FIELD_WIDTH) + "s",
            axis="";
    double byrow;
    char aux [MAX_WIDTH];
    for (int i=0; i<FIELD_WIDTH; i++)
        axis = axis + "─";
    res += "┌";
    for (int i = 0; i < size(); i++) {
        res = res + axis;
        if (i < size()-1 )
            res += "┬";
    }
    res += "┐\n";

    for (int j = 0; j >= 0; j--) {
        res += "│";
        byrow = 0;
        for (int i = 0; i < size(); i++) {
            sprintf(aux, fdata.c_str(), getValue(i));
            res = res + aux + "│";
            byrow += getValue(i);
        }
        sprintf(aux, fdata.c_str(), byrow);
        res = res + aux + "\n";
    }
    res += "├";
    for (int i = 0; i < size(); i++) {
        res = res + axis;
        if (i < size() - 1)
            res += "┼";
    }
    res += "┤\n│";
    for (int i = 0; i < size(); i++) {
        sprintf(aux, flabel.c_str(), _labels[i].c_str());
        res = res + aux + "│";
    }
    res += "\n└";
    for (int i = 0; i < size(); i++) {
        res = res + axis + "┘";
    }
    res += "\n";
    return res;
}