
#include<iostream>
using namespace std ;
#include"LargeInteger.h"

LargeInteger operator+(const LargeInteger &a1,const LargeInteger &a2)
{
    if ((a1.flag && a2.flag) )
    {
        int *p1 , *p2 , *p3;
        int l = max(a1.len,a2.len) ;
        p1 = new int [l+1] ;
        p2 = new int [l+1] ;
        p3 = new int [l+1] ;

        for (int i = 0 ; i < l+1 ; ++i)
        {
            p1[i] = p2[i] = p3[i] = 0 ;
        }

        for (int i = 0 ; i < a1.len ; ++i)
        {
            p1[i] = a1.p[a1.len-i-1] - '0' ;
        }
        for (int i = 0 ; i < a2.len ; ++i)
        {
            p2[i] = a2.p[a2.len-i-1] - '0' ;
        }
     //   for (int i = 0 ; i < l ; ++i)
     //         cout << p2[i] ;
      //  cout << endl ;
        int j = 0 , x = 0 ;

        while (j <= a1.len || j <= a2.len)
        {
            p3[j] = p1[j] + p2[j] + x ;
            x = p3[j] / 10 ;
            p3[j] %= 10 ;
            j++ ;
        }

 /*      for (int i = 0 ; i < j ; ++i)
       {
           cout << p3[i] << endl ;
       }*/

        if (x == 0)
        {
            LargeInteger tmp(j) ;
            for (int i = 0 ; i < j ; ++i)
            {
                tmp.p[i] = p3[j-i-1] + '0';
            }
            if (a1.flag && a2.flag)
                tmp.flag = true ;
            else tmp.flag = false ;
            return tmp ;
        }
        else
        {
            LargeInteger tmp(j + 1) ;
            tmp.p[0] = x ;
            for (int i = 1 ; i <= j ; ++i)
            {
                tmp.p[i] = p3[j-i] + '0';
            }
            if (a1.flag && a2.flag)
                tmp.flag = true ;
            else tmp.flag = false ;
            if (p1) delete [] p1 ;
            if (p2) delete [] p2 ;
            if (p3) delete [] p3 ;
            return tmp ;
        }
    }
    if (a1.flag && !a2.flag)
    {
        LargeInteger A2 = a2 ;
        A2.flag = true ;
    //    cout << A2 << " " << a1 - A2 << endl ;
        return (a1 - A2) ;
    }
    if (!a1.flag && a2.flag)
    {
        LargeInteger A1 = a1 ;
        A1.flag = true ;
        return (a2 - A1) ;
    }
    if (!a1.flag && !a2.flag)
    {
        LargeInteger A1 = a1 , A2 = a2 , tmp ;
        A1.flag = true ;
        A2.flag = true ;
        tmp = A1 + A2 ;
        tmp.flag = false ;
        return tmp ;
    }

}

LargeInteger operator-(const LargeInteger &a1,const LargeInteger &a2)
{

    if (a1.flag && a2.flag)
    {
        if (a1 > a2)
        {
            int *p1, *p2, *p3;
            int l = max(a1.len, a2.len);
            p1 = new int[l + 1] ;
            p2 = new int[l + 1] ;
            p3 = new int[l + 1] ;
            for (int i = 0; i < l + 1; ++i)
            {
                p1[i] = p2[i] = p3[i] = 0 ;
            }
            for (int i = 0; i < a1.len; ++i)
            {
                p1[i] = a1.p[a1.len - i - 1] - '0' ;
            }
            for (int i = 0; i < a2.len; ++i) {
                p2[i] = a2.p[a2.len - i - 1] - '0' ;
            }

            int i = 0, x = 0;

            while (i <= a1.len)
            {
                if (p1[i] < p2[i])
                {
                    p3[i] = p1[i] + 10 - p2[i] ;
                    p1[i + 1]-- ;
                } else p3[i] = p1[i] - p2[i] ;
              // cout << p3[i] << " ";
                ++i;

            }
            int length = 0;
            for (int i = l ; i >= 0; i--)
            {
                if (p3[i] != 0)
                {
                    length = i + 1 ;
                    break ;
                }
            }

     /*       for (int i = 0 ; i < length ; ++i)
            {
                cout << p3[i] << " " ;
            }*/
           // cout << length ;
            LargeInteger tmp(length);
            for (int i = 0; i < length; i++) {
                tmp.p[i] = p3[length - i - 1] + '0';
            }
            tmp.flag = true;
            if (p1) delete[] p1;
            if (p2) delete[] p2;
            if (p3) delete[] p3;
            return tmp ;
        }
        if (a1 == a2)
        {
            LargeInteger tmp ;
            return tmp ;
        }
        else
        {
            LargeInteger tmp ;
            tmp = a2 - a1 ;
            tmp.flag = false ;
            return tmp ;
        }

    }
    if (!a1.flag && !a2.flag)
    {
        LargeInteger tmp ;
        LargeInteger A1 = a1 ;
        LargeInteger A2 = a2 ;
        A1.flag = true ;
        A2.flag = true ;
        tmp = A2 - A1 ;
        tmp.flag = false ;
        return tmp ;
    }
    if (a1.flag && !a2.flag)
    {
        LargeInteger A2 = a2 ;
        A2.flag = true ;
        return (a1 + A2) ;
    }
    if (!a1.flag && a2.flag)
    {
        LargeInteger A1 = a1 , tmp;
        A1.flag = true ;
        tmp = A1 + a2 ;
        tmp.flag = false ;
        return tmp ;
    }
}

LargeInteger operator*(const LargeInteger &a1,const LargeInteger &a2)
{

    int *p1 , *p2 , *p3;
    int l = max(a1.len,a2.len) ;
    p1 = new int [l+1] ;
    p2 = new int [l+1] ;
    p3 = new int [2*l+1] ;
    for (int i = 0 ; i < l + 1 ; ++i)
    {
        p1[i] = p2[i] = 0 ;
    }
    for (int i = 0 ; i < 2*l + 1 ; ++i)
    {
        p3[i] = 0 ;
    }
    for (int i = 1 ; i <= a1.len ; ++i)
    {
        p1[i] = a1.p[a1.len-i] - '0' ;
    }
    for (int i = 1 ; i <= a2.len ; ++i)
    {
        p2[i] = a2.p[a2.len-i] - '0' ;
    }
    for(int i = 1 ;i <= a1.len; ++i)
    {
        for(int j = 1; j <= a2.len; ++j)
        {
            p3[i+j-1] += p1[i] * p2[j] ;
        }
    }

    for(int i = 1;i <= a1.len + a2.len - 1; ++i)
    {
        p3[i+1] += p3[i] / 10 ;
        p3[i] %= 10 ;
    }

    int k = (p3[a1.len+a2.len] > 0) ? (a1.len+a2.len) : (a1.len+a2.len-1) ;
    LargeInteger tmp(k) ;
    //cout << k <<endl;
    /*for (int i = k ; i >= 1 ; i--)
    {
        cout << p3[i] ;
    }*/
    //cout << endl ;
    for (int i = 0 ; i < k ; ++i)
    {
        tmp.p[i] = p3[k-i] + '0' ;
    }
    if((a1.flag && a2.flag) || (!a1.flag && !a2.flag))
        tmp.flag = true ;
    else tmp.flag = false ;
    if (p1) delete [] p1 ;
    if (p2) delete [] p2 ;
    if (p3) delete [] p3 ;
    return tmp ;
}

LargeInteger operator/(const LargeInteger &a1,const LargeInteger &a2)
{
    LargeInteger a0 ;
    if (a1 == a0)
    {
        return a0 ;
    }
    if (a1.flag && a2.flag)
    {
        if (a1 < a2)
        {
            LargeInteger tmp ;
            return tmp;
        }
        int *p3 ;
        p3 = new int [a1.len] ;
        for (int i = 0 ; i < a1.len ; ++i)
        {
            p3[0] = 0 ;
        }
        LargeInteger c = a1 ;

        int k = 0 ;
        while (c.len >= a2.len && k < a1.len - a2.len + 1)
        {
            LargeInteger a(a1.len-k) ;   //a为a2补零而得
            for (int i = 0 ; i < a2.len ; ++i)
            {
                a.p[i] = a2.p[i] ;
            }
            if (a2.len < c.len - k)
            {
                for (int i = a2.len ; i < c.len - k ; ++ i )
                {
                    a.p[i] = '0' ;
                }
            }
    //        cout << a << " " ;
            int t = 0 ;
            while (c > a || c == a)
            {
                c = c - a ;
                ++t ;
            //    cout << c << " " << t << " " ;
            }
            p3[k] = t ;
            ++ k ;
        }

        int start = 0 , l;
    //    for (int i = 0 ; i < k ; ++i )
    //        cout << p3[i]   ;
    //    cout << endl;
        for (int i = 0 ; i < k ; ++i )
        {
            if (p3[i] != 0)
            {
                start = i  ;
                break ;
            }
        }
    //    cout << start << " " << endl ;
        l = k  - start  ;
    //    cout << l << " ";
        LargeInteger tmp(l) ;
        for (int i = start ; i < start + l ; ++i )
        {
            tmp.p[i-start] = p3[i] + '0' ;
        }
         delete p3 ;
        return tmp ;
    }
    if (!a1.flag && !a2.flag)
    {
        LargeInteger A1 = a1 , A2 = a2 , tmp;
        A1.flag = true ;
        A2.flag = true ;
        tmp = A1 / A2 ;
        return tmp ;
    }
    if (!a1.flag && a2.flag)
    {
        LargeInteger A1 = a1 , tmp , e0(1),e1(1);
        e0.p[0] = '0' ;
        e1.p[0] = '1' ;
        A1.flag = true ;
        tmp = A1 / a2 ;
        tmp.flag = false ;
        if (A1 % a2 == e0) return tmp ;
        else return tmp - e1 ;
    }
    if (a1.flag && !a2.flag)
    {
        LargeInteger A2 = a2, tmp, e0(1), e1(1);
        e0.p[0] = '0' ;
        e1.p[0] = '1' ;
        e1.flag = true ;
        A2.flag = true;
        tmp = a1 / A2;
        tmp.flag = false ;
    //   cout << e1 << " " << tmp - e1  << " " ;
        if (a1 % A2 == e0) return tmp;
        else return tmp - e1;
    }
}

LargeInteger operator%(const LargeInteger &a1,const LargeInteger &a2)
{
    LargeInteger t1 , t2 ;
    t1 = a1 / a2 ;
    t2 = t1 * a2 ;
    t2 = a1 - t2 ;
    return t2 ;
}

bool operator>(const LargeInteger &a1,const LargeInteger &a2)
{
    if (a1.flag && !a2.flag)
        return true ;
    if (!a1.flag && a2.flag)
        return false ;
    if (a1.flag && a2.flag)
    {
        if (a1.len > a2.len) return true ;
        if (a1.len < a2.len) return false ;
        if (a1.len == a2.len)
        {
            for (int i = 0 ; i < a1.len ; ++i)
            {
                if (a1.p[i] < a2.p[i]) return false ;
                if (a1.p[i] > a2.p[i]) return true ;
            }
             return false ;
        }
    }
    if (!a1.flag && !a2.flag)
    {
        if (a1.len > a2.len) return false ;
        if (a1.len < a2.len) return true ;
        if (a1.len == a2.len)
        {
            int num = 0;
            for (int i = 0 ; i < a1.len ; ++i)
            {
                if (a1.p[i] > a2.p[i]) return false ;
                else if (a1.p[i] == a2.p[i]) ++num ;
            }
            if (num == a1.len) return false ;
            return true ;
        }
    }
}

bool operator<(const LargeInteger &a1,const LargeInteger &a2)
{
    if (!a1.flag && a2.flag)
        return true ;
    if (a1.flag && !a2.flag)
        return false ;
    if (a1.flag && a2.flag)
    {
        if (a1.len < a2.len) return true ;
        if (a1.len > a2.len) return false ;
        if (a1.len == a2.len)
        {
            for (int i = 0 ; i < a1.len ; ++i)
            {
                if (a1.p[i] > a2.p[i]) return false ;
                if (a1.p[i] < a2.p[i]) return true ;
            }
            return false ;
        }
    }
    if (!a1.flag && !a2.flag)
    {
        if (a1.len < a2.len) return false ;
        if (a1.len > a2.len) return true ;
        if (a1.len == a2.len)
        {
            int num = 0;
            for (int i = 0 ; i < a1.len ; ++i)
            {
                if (a1.p[i] < a2.p[i]) return false ;
                else if (a1.p[i] == a2.p[i]) ++num ;
            }
            if (num == a1.len) return false ;
            return true ;
        }
    }
}

bool operator==(const LargeInteger &a1,const LargeInteger &a2)
{
    if (a1.flag != a2.flag || a1.len != a2.len)
        return false ;
    for (int i = 0 ; i < a1.len ; ++i)
        if (a1.p[i] != a2.p[i]) return false ;
    return true ;
}

ostream & operator<<(ostream & os , const LargeInteger & obj)
{
    int start = 0 ;
    for (int i = 0 ; i < obj.len ; ++i)
    {
        if (obj.p[i] != '0') break ;
        ++start ;
    }
    if (start == obj.len) os << "0" ;
    else
    {
        if (obj.flag == false) os << "-" ;
        for (int i = start; i < obj.len; ++i)
            os << obj.p[i];
        return os;
    }
}

istream & operator>>(istream & in , LargeInteger & obj)
{
    string s ;
    int l ;
    in >> s ;
    l = s.length() ;
    obj.p = new char [l] ;
    if (s[0] == '-')
    {
        obj.len = l - 1 ;
        obj.flag = false ;
        for (int i = 1 ; i < l ; ++i)
            obj.p[i-1] = s[i] ;
    }
    else
    {
        obj.len = l ;
        obj.flag = true ;
        for (int i = 0 ; i < l ; ++i)
            obj.p[i] = s[i] ;
    }
    return in;
}

int max(int a, int b)
{
    if (a > b) return a ;
    return b ;
}


