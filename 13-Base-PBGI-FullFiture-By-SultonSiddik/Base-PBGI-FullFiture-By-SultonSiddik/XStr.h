/*Xstr.h D3D9 PBHacks Last Edit By Muhammad Zaki Mubarak*/
#ifndef XSTR_H
#define XSTR_H

#include <windows.h>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <conio.h>

/*-------------------------------------------------------------------------------------------------------------------*/
class XStr
{
public:
	XStr( int hashlen, int strlen, int key, ... );
	virtual ~XStr( );
	char * c();
private:
	DWORD_PTR * m_charList;
	DWORD_PTR * m_hashList;
	char * m_retBuf;
	int m_strLength;
	int m_hashLength;
	int m_key;
};

#endif
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef _XOR_H
#define _XOR_H

#pragma once

template <int XORSTART, int BUFLEN, int XREFKILLER>
class XorStr
{
private: 
    XorStr();
public: 
    char s[BUFLEN];

    XorStr(const char* xs);
    ~XorStr(){ for(int i=0;i<BUFLEN;i++)s[i]=0;}
};

template <int XORSTART, int BUFLEN, int XREFKILLER>
XorStr<XORSTART,BUFLEN,XREFKILLER>::XorStr(const char* xs)
{

    int xvalue = XORSTART;
    int i = 0;
    for(;i<(BUFLEN-1);i++) {
        s[i] = xs[i-XREFKILLER]^xvalue;
        xvalue += 1;
        xvalue %= 256;
    }
    s[BUFLEN-1] = 0;


}

#define XOR(a) a


#endif
/*-------------------------------------------------------------------------------------------------------------------*/