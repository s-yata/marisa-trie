#include <iostream>
void add( short n, short *&v, int &size){
	short * aux = new short[size+1];
	for(int i=0; i<size; i++)
		aux[i] = v[i];
	if(size!=0)
		delete[] v;
	aux[size] = n;
	size++;
	v= aux;
	aux = nullptr;
}

void DecimalBinary(int num, short* &bin, int &size){
	if(num<2){
		add(num, bin , size);
		short * aux = new short[size];
		for(int i=0; i<size; i++)
			aux[i] = bin[size-1-i];
		delete [] bin;
		bin = aux;
		aux=nullptr;

	}else{
		if(num%2 ==1){
			add(1,bin,size);
		}else{
			add(0,bin,size);
		}
		num/=2;
		DecimalBinary(num,bin,size);
	}
}


