#ifndef _XOR_H
#define _XOR_H
template <int XORSTART, int BUFLEN, int XREFKILLER>
class Asuna_Yuuki
{
private: 
	Asuna_Yuuki();
public: 
	char s[ BUFLEN ];
	Asuna_Yuuki( const char * xs );
	~Asuna_Yuuki()
	{
		for ( int i = 0; i < BUFLEN; i++ ) s[ i ]=0; 
	}
};

template <int XORSTART, int BUFLEN, int XREFKILLER>
Asuna_Yuuki<XORSTART,BUFLEN,XREFKILLER>::Asuna_Yuuki( const char * xs )
{
	int xvalue = XORSTART;
	int i = 0;
	for ( ; i < ( BUFLEN - 1 ); i++ ) 
	{
		s[ i ] = xs[ i - XREFKILLER ] ^ xvalue;
		xvalue += 1;
		xvalue %= 256;
	}
	s[ BUFLEN - 1 ] = 0;
}
#endif
