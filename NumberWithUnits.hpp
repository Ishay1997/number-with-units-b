#pragma once
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;
namespace ariel{
    class NumberWithUnits{
        private:
            string unit;
            double num;
        public :
            NumberWithUnits(double num, const string &unit);
            static void read_units(ifstream& units_file);
            static double conversion(const string &src, const string &dest);

        friend NumberWithUnits operator+(const NumberWithUnits &a,const NumberWithUnits &b); 
        friend NumberWithUnits operator-(const NumberWithUnits &a,const NumberWithUnits &b); 
        friend NumberWithUnits& operator++(NumberWithUnits &a);
        friend NumberWithUnits& operator--(NumberWithUnits &a);
         NumberWithUnits operator++(int );
         NumberWithUnits operator--(int );
         NumberWithUnits operator+(); 
         NumberWithUnits operator-();
         NumberWithUnits& operator+=(const NumberWithUnits &b); 
         NumberWithUnits& operator-=(const NumberWithUnits &b); 

         friend NumberWithUnits operator*(const NumberWithUnits &a,const double num);
         friend NumberWithUnits operator*(const double num,const NumberWithUnits &a);

        friend bool operator==(const NumberWithUnits &a,const NumberWithUnits &b);
        friend bool operator!=(const NumberWithUnits &a,const NumberWithUnits &b);
        friend bool operator<(const NumberWithUnits &a,const NumberWithUnits &b);
        friend bool operator>(const NumberWithUnits &a,const NumberWithUnits &b);
        friend bool operator>=(const NumberWithUnits &a,const NumberWithUnits &b);
        friend bool operator<=(const NumberWithUnits &a,const NumberWithUnits &b);

        friend ostream &operator<<(ostream &os,const NumberWithUnits &a);
        friend istream &operator>>(istream &is, NumberWithUnits &a);
    };
}
