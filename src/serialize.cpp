#include<sys/socket.h>
#include<arpa/inet.h>
#include<cstring>
#include<string>
#include"serialize.hpp"
#include<stdarg.h>
int GetRangeValue(unsigned int target,int l,int r){
	/*
	   Function to get a int's Big Endian in range [l,r]
	   ** Caution **
	   1. l should no bigger than r;
	   2. l,r should in range [1,32]
	*/
	if(r==32) return (target&(-1))>>(l-1);
	return (target&((1<<r)-1))>>(l-1);
}
int Serial_IntToChar(char *CharTarget,int TargetLength,unsigned int FirstNumber,...){
	va_list ap;
	va_start(ap,FirstNumber);
	memset(CharTarget,0,TargetLength*4);
	unsigned int CurrentNum=FirstNumber;
	for(int i=0,Position=-1;i<TargetLength;i++){
		for(int j=4;j;j--) CharTarget[++Position]=char(GetRangeValue(CurrentNum,(j-1)*8+1,j*8));
		if(i!=TargetLength-1) CurrentNum=va_arg(ap,unsigned int);
	}
	va_end(ap);
	return 0;
}
