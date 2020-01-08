//
// Created by 3529866 on 2019/12/12.
//

#ifndef LargeInteger_h
#define LargeInteger_h

#include <iostream>
#include <cstring>
#include <string>
using namespace std ;

class LargeInteger {
    friend LargeInteger operator+(const LargeInteger &a1,const LargeInteger &a2)  ;
    friend LargeInteger operator*(const LargeInteger &a1,const LargeInteger &a2)  ;
    friend LargeInteger operator-(const LargeInteger &a1,const LargeInteger &a2)  ;
    friend LargeInteger operator/(const LargeInteger &a1,const LargeInteger &a2)  ;
    friend LargeInteger operator%(const LargeInteger &a1,const LargeInteger &a2)  ;
    friend bool operator>(const LargeInteger &a1,const LargeInteger &a2)  ;
    friend bool operator<(const LargeInteger &a1,const LargeInteger &a2)  ;
    friend bool operator==(const LargeInteger &a1,const LargeInteger &a2)  ;
    friend istream & operator>>(istream & in , LargeInteger & obj ) ;
    friend ostream & operator<<(ostream & os , const LargeInteger & obj) ;
    friend class EvalVisitor ;

private :
    int len ;
    bool flag ;
    char *p ;

public :
    LargeInteger (char *s)
    {
        len = strlen(s) ;
        if (s[0] == '-')
        {
            len-- ;
            p = new char [len] ;
            flag = false ;
            for (int i = 1 ; i <= len ; ++i)
                p[i] = s[i] ;
        }
        else
        {
            flag = true ;
            p = new char [len] ;
            flag = true ;
            for (int i = 0 ; i < len ; ++i)
                p[i] = s[i] ;
        }
    }
    LargeInteger (int size)
    {
        flag = true ;
        len = size ;
        p = new char [len] ;
        for (int i = 0 ; i < len ; ++i)
            p[i] = '0' ;
    }

    LargeInteger()
    {
        flag = true ;
        len = 1 ;
        p = new char [1] ;
        p[0] = '0' ;
    }

    LargeInteger(const LargeInteger &s)
    {
        len = s.len ;
        flag = s.flag ;
        p = new char[len] ;
        for (int i = 0 ; i < len ; ++i)
            p[i] = s.p[i] ;
    }

    LargeInteger &operator=(const LargeInteger &right)
    {
        if (this == &right) return *this ;

        delete [] p ;

        flag = right.flag ;
        len = right.len ;
        p = new char [len] ;
        for (int i = 0 ; i < len ; ++i)
            p[i] = right.p[i] ;

        return *this ;
    }

    operator float  () const
    {
        float x ;
        float j = 1 ;
        for (int i = 0 ; i < len ; ++i)
        {
            x += (float)(p[i] - '0') * j ;
            j *= 10 ;
        }
        return x ;
    }

    operator double  () const
    {
        double x ;
        double j = 1 ;
        for (int i = 0 ; i < len ; ++i)
        {
            x += (double)(p[i] - '0') * j ;
            j *= 10 ;
        }
        return x ;
    }

    operator string  () const
    {
        string s ;
        for (int i = 0 ; i < len ; ++i)
            s += p[i] ;
        return s ;
    }

    operator bool () const
    {
        bool x ;
        if (p[0] == 0 && len == 1)
            x = false ;
        else x = true ;
        return x ;
    }

    ~LargeInteger()
    {
        if (p) delete [] p ;
    }

};

#endif //INT_INT_H

