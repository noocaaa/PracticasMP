/**
 * @file Event.cpp
 * @author DECSAI && Manuel Fuentes Plaza && Noelia Carrasco Vilar
 * @date 22/03/2021
 */

#include <string>

#include "Event.h"

Event::Event() {
    initDefault();
}

void Event::initDefault() {
    set(EVENT_DEFAULT); 
}

Event::Event(const string line) {
    set(line);
}

DateTime Event::getDateTime() const {
    return _dateTime;
}

string Event::getType() const {
    return _type;
}

string Event::getProductID() const  {
    return _prod_id;
}

string Event::getCategoryID() const {
    return _cat_id;
}

string Event::getCategoryCode() const {
    return _cat_cod;
}

string Event::getBrand() const {
    return _brand;
}

double Event::getPrice() const{
    return _price;
}

string Event::getUserID() const {
    return _user_id;
}

string Event::getSession() const {
    return _session;
}

void Event::setDateTime(const string &time) {
    _dateTime.set(time);
}

void Event::setType(const string &type) {
    bool valid = false;

    for (int i=0; i < 4 && !valid; i++) {
        if (type == VALID_TYPES[i]) {
            valid = true;
        }
    }    
    
    if (!valid) {
        _type = VALID_TYPES[0];
    } else {
        _type = type;
    }
}

void Event::setProductID (const string &prod_id) {
    if (prod_id == "") {
       _prod_id = EMPTY_FIELD;   
    } else {
        _prod_id = prod_id;   
    }  
 }

void Event::setCategoryID(const string &cat_id) {
    _cat_id = cat_id; //allows ""
}

void Event::setCategoryCode(const string &cat_cod) {
    _cat_cod = cat_cod; //allows ""
}

void Event::setBrand(const string &brand) { //allows ""
    _brand = brand;
}

void Event::setPrice(const double &price) {
    if (price < 0) {
        _price = -1.000000;
    } else {
        _price = price;       
    }
}

void Event::setUserID(const string &user_id) {
    if (user_id == "") {
        _user_id = EMPTY_FIELD;
    } else {
        _user_id = user_id;
    }
}

void Event::setSession(const string &session) {
    if (session == "") {
        _session = EMPTY_FIELD;
    } else {
        _session = session;
    }    
}

void Event::set(const string &line) {
   
    int pos1 = line.find(",", 0);
    int pos2 = line.find(",", pos1+1);     
    int pos3 = line.find(",", pos2+1);
    int pos4 = line.find(",", pos3+1);
    int pos5 = line.find(",", pos4+1);
    int pos6 = line.find(",", pos5+1);
    int pos7 = line.find(",", pos6+1);
    int pos8 = line.find(",", pos7+1);
    int pos9 = line.size();
        
    setDateTime(line.substr(0, pos1));
    setType(line.substr(pos1+1, pos2 -pos1 -1));        
    setProductID(line.substr(pos2+1, pos3 -pos2 -1));   
    setCategoryID(line.substr(pos3+1, pos4 -pos3 -1));
    setCategoryCode(line.substr(pos4+1, pos5 -pos4 -1));
    setBrand(line.substr(pos5+1, pos6 -pos5 -1));
    
    string prix = line.substr(pos6+1, pos7 -pos6 -1);
    
    if (prix != "") {
        setPrice(atoi(prix.c_str()));       
    } else {
        setPrice(-1.000000);      
    }
    
    setUserID(line.substr(pos7+1, pos8 -pos7 -1));
    setSession(line.substr(pos8+1, pos9 -pos8 -1));
}

bool Event::isEmpty() const{
    //como se ha especificado, siempre habra estos DateTime, Product id, User id, y Session id. y por lo tanto no se comprueban.
    bool vacio = false;
    bool continuar = true;
    
    if (_cat_id == EMPTY_FIELD) {
        vacio = true;
    } else if (_cat_cod == EMPTY_FIELD) {
        vacio = true;
    } else if (_brand == EMPTY_FIELD) {
        vacio = true;
    } else if (_price == -1.000000) {
        vacio = true;
    } else if (_prod_id == EMPTY_FIELD) {
        vacio = true;
    }
    
    //para comprobar que el tipo este en el rango de valido
    for (int i=0; i < 5 && continuar; i++) {
        if (_type == VALID_TYPES[i]) {
            continuar = false;
        }
    }
    
    if (continuar) {
        vacio = true;
    }
    
    return vacio;
}

string Event::to_string() const {
    string salida;
    
    salida += _dateTime.to_string();
    salida += "," + _type;
    salida += "," + _prod_id;
    salida += "," + _cat_id;
    salida += "," + _cat_cod;
    salida += "," + _brand;
    salida += "," + std::to_string(_price);
    salida += "," + _user_id;
    salida += "," + _session;
    
    return salida;
}
