#include <algorithm>
#include <gmp.h>
#include <stdio.h>
#include <iostream>
#include <gmpxx.h>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
using namespace std;

mpq_t* num=NULL;
int size=0;
int prec=0;
double alpha=0;

void write(mpq_t number)
{
	mpz_t n,d,digit;
	mpz_init(digit);
	mpz_init_set(n,mpq_numref(number));
	mpz_init_set(d,mpq_denref(number));
	if (mpz_cmp_si(d,1)==0){
		gmp_printf("%Zd",n);
	}
	else{
		for (int i=0; i<=prec; i++){
			mpz_div(digit,n,d);
			gmp_printf("%Zd",digit);
			if(i==0) printf(".");
			mpz_mul(digit,digit,d);
			mpz_sub(n,n,digit);
			mpz_mul_si(n,n,10);
			if(mpz_cmp_si(n,0)==0) break;
		}
		printf(";");
	}
}

void qsort(int l,int r)
{
	mpq_t q;
	int i=l;
	int j=r;
	mpq_init(q);
	mpq_set(q,num[(i+j) >> 1]);
	do{
		while(mpq_cmp(num[i],q)<0) i++;
		while(mpq_cmp(num[j],q)>0) j--;
		if(i<=j){
			mpq_swap(num[i],num[j]);
			i++;
			j--;
		}
	}
	while(i<=j);
	if(l<j) qsort(l,j);
	if(r>i) qsort(i,r);
}

int length(mpq_t l,mpq_t r)
{
	int start=-1,len=0;
	for(int i=1; i<=size && start==-1; i++){
		start=mpq_cmp(num[i],l)>=0 ? i : -1;
	}
	for(int i=start; i<=size; i++){
		if(mpq_cmp(num[i],r)>=0){
			return len;
		}
		len++;
	}
	return len;
}

double dystrybuanta(mpq_t k)
{
    mpf_t digit;
	mpf_init2(digit, 256);
	mpf_set_q(digit, k);
    double ulamek = mpf_get_d(digit);
    double potega = ulamek*ulamek * (-2);
    double e_do_potegi = pow(M_E, potega);
    double wynik = 1 - e_do_potegi + (2 / (3 * sqrt(size))) * e_do_potegi;
    cout << wynik << ";";
}

double KPlus()
{
	mpq_t k,jn;
	mpq_init(k);
	mpq_init(jn);
	mpq_set_si(k,0,1);
	for(int i=1; i<=size; i++){
		mpq_set_si(jn,i,size);
		mpq_sub(jn,jn,num[i]);
		if(mpq_cmp(k,jn)<0){
			mpq_set(k,jn);
		}
	}
	write(k);
	double d = dystrybuanta(k);
	return d;
}

double KMinus()
{
	mpq_t k,jn;
	mpq_init(k);
	mpq_init(jn);
	mpq_set_si(k,0,1);
	for(int i=1; i<=size; i++){
		mpq_set_si(jn,i-1,size);
		mpq_sub(jn,num[i],jn);
		if(mpq_cmp(k,jn)<0){
			mpq_set(k,jn);
		}
	}
	write(k);
	double d = dystrybuanta(k);
	return d;
}

int main(int argc,char* argv[])
{
    mpq_t divisor;
    mpq_init(divisor);
    mpq_set_ui(divisor, 4294967295, 1);
	char input[256];
	alpha=0.05;//atoi(argv[1]); //pierwszy parametr to alfa
	prec=10;
	num=new mpq_t[100000000];
	mpq_init(num[0]);
	while(scanf("%255s",input) != EOF){
		size++;
		mpq_init(num[size]);
		gmp_sscanf(input,"%Qi",num[size]);
//		char* KplusChars = NULL;
//		char* KplusChars2 = NULL;
//        KplusChars = mpq_get_str(KplusChars, 10, num[size]);
//        string KplusStr(KplusChars);
		mpq_div(num[size], num[size], divisor); //podziel przez 2^32 zeby bylo <0;1>
//			KplusChars2 = mpq_get_str(KplusChars2, 10, num[size]);
//	string KplusStr2(KplusChars2);
//	cout << KplusStr << " " << KplusStr2 << ";";
	}

	qsort(0,size);
	double d1 = KPlus();
	double d2 = KMinus();
	double jeden_minus_alpha = 1 - alpha;
	if((d1 > jeden_minus_alpha) || (d2 > jeden_minus_alpha))
	{
        cout << "NOT PASSED" << endl;
	}
	else
	{
        cout << "ok" << endl;
	}
	delete[] num;
	return 0;
}
