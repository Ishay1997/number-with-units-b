#include "NumberWithUnits.hpp"
#include <sstream>
#include <fstream>


const double EPS=0.00001;

using namespace std;
namespace ariel{
    static unordered_map<string,unordered_map<string,double>> convert_units;

    NumberWithUnits::NumberWithUnits(double num,const string &unit){
    	if(convert_units.count(unit)==0)
    	{
    	   throw invalid_argument("doesn't exist in convert map");
    	}
        this->unit=unit;
        this->num=num;
    }

////////////////////

    void NumberWithUnits::read_units(ifstream &units_file){
        char buff = '=';
        double number1=0, number2=0;
        string line, unit1, unit2;

        while (getline(units_file, line))
        {
            istringstream isr(line);
            isr >> number1 >> unit1 >> buff >> number2 >> unit2;
            convert_units[unit1][unit2] = number2 / number1;
            convert_units[unit2][unit1] = number1 / number2;

            for (auto &map : convert_units[unit2])
            {
                convert_units[unit1][map.first] = convert_units[unit1][unit2] * map.second;
                convert_units[map.first][unit1] = 1 / convert_units[unit1][map.first];
            }
            for (auto &map : convert_units[unit1])
            {
                convert_units[unit2][map.first] = convert_units[unit2][unit1] * map.second;
                convert_units[map.first][unit2] = 1 / convert_units[unit2][map.first];
            }
        }
    }

/////////////////
    double NumberWithUnits::conversion(const string &src, const string &dest) {
        if(convert_units.find(src)!=convert_units.end()&& convert_units[src].find(dest)!=convert_units[src].end())
        {
            return convert_units[src][dest];
        }
        throw invalid_argument("you cant convert between this units ["+src+"] ["+dest+"]");
        
    }
    NumberWithUnits NumberWithUnits::operator-() {
        return NumberWithUnits(-this->num, this->unit);
    }
    NumberWithUnits NumberWithUnits::operator+(){
        return NumberWithUnits(this->num,this->unit);
    }

    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits &b) {
        this->num-=conversion(b.unit, this->unit)* b.num;
        return *this;
    }
    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits &b){
        this->num+=conversion(b.unit, this->unit)*b.num;
        return *this;

    }
    NumberWithUnits operator-(const NumberWithUnits &a,const NumberWithUnits &b) {
        return NumberWithUnits(a.num-NumberWithUnits::conversion(b.unit, a.unit)*b.num, a.unit);
    }
    NumberWithUnits operator+(const NumberWithUnits &a,const NumberWithUnits &b){
        return NumberWithUnits(a.num+NumberWithUnits::conversion(b.unit, a.unit)* b.num, a.unit);
    }




//////////////
bool operator<(const NumberWithUnits &a,const NumberWithUnits &b) {
        return a!=b && a.num<NumberWithUnits::conversion(b.unit, a.unit)* b.num;
    }

    bool operator>(const NumberWithUnits &a,const NumberWithUnits &b) {
        return a!=b && a.num>NumberWithUnits::conversion(b.unit, a.unit)* b.num;
    }

     bool operator<=(const NumberWithUnits &a,const NumberWithUnits &b) {
        return (a<b)||(a==b);
    }

    bool operator>=(const NumberWithUnits &a,const NumberWithUnits &b) {
        return (a>b)||(a==b);

    }

    bool operator==(const NumberWithUnits &a,const NumberWithUnits &b) {
        return (abs(a.num-NumberWithUnits::conversion(b.unit, a.unit)* b.num)<=EPS);
    }

    bool operator!=(const NumberWithUnits &a,const NumberWithUnits &b) {
        return !(a==b);
    }

    
   
 //////////////////// 
    NumberWithUnits& operator++(NumberWithUnits &a){
        a.num++;
        return a;
    }


    NumberWithUnits& operator--(NumberWithUnits &a){
        a.num--;
        return a;
    }
    NumberWithUnits  NumberWithUnits::operator--(int ){
        NumberWithUnits deepcopy = NumberWithUnits(this->num,this->unit);
        this->num--;
        return deepcopy;
    }
    NumberWithUnits  NumberWithUnits::operator++(int ){
        NumberWithUnits deepcopy = NumberWithUnits(this->num,this->unit);
        this->num++;
        return deepcopy;
    }
    NumberWithUnits operator*(const double num, const NumberWithUnits &a) {
        return NumberWithUnits(num*a.num,a.unit);
    }

    NumberWithUnits operator*(const NumberWithUnits &a,const double num) {
        return NumberWithUnits(num*a.num,a.unit);
    }



////////////////////
    ostream &operator<<(ostream &os,const NumberWithUnits &a){
        char left='[';
        char right=']';
        return os<<a.num<<left<<a.unit<<right;
    }
    istream &operator>>(istream &is, NumberWithUnits &a){
        char left='[',right=']';
        double num=0;
        string unit;
        is >> num >> left >> unit;
        if(unit.find(right)==string::npos)
        {
            is>>right;
        }
        unit = unit.substr(0, unit.find(right));
        if(convert_units.count(unit)==0)
        {
            throw invalid_argument("unit doesn't exist in map");
        }
        a.num=num;
        a.unit=unit;
        return is;
    }
   
}
