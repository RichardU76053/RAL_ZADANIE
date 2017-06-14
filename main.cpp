#include <iostream>
#include <fstream>
#include <cstring>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_pXFactoring.h>
#include <conio.h>
#include <cstring>
#include <string>
#include <sstream>
#include <map>

NTL_CLIENT

ZZ ord(ZZ modulo,ZZ alpha){
	ZZ mul,i;
	set(mul);
	set(i);
	mul*=alpha;

	if(modulo==to_ZZ(1))
		return to_ZZ(1);
	else
		while(mul%modulo!=1){
			mul*=alpha;
			i++;
			}
	return i;
}

vec_ZZ numberDecomposition(ZZ number){
	ZZ divisor;
	long i=1,divisor1=2;
	vec_ZZ divisors;

	divisor=to_ZZ(divisor1);
    clear(divisors);
	divisors.SetLength(i);
	divisors(i)=1;
	i++;

	while(divisor<=number){
		if(number%divisor==0){
			divisors.SetLength(i);
			divisors(i)=divisor;
			divisor++;
			i++;
			}
		else
			divisor++;
		}
	 return divisors;
}

ZZ mobyFunction(ZZ n){
	ZZ m;
	long j=1;
	vec_ZZ div,primes;
	clear(primes);
	clear(m);
	set(m);

	if(n==1)
		return to_ZZ(1);
	else{
		div=numberDecomposition(n);
		for(long i=2;i<=div.length();i++){
			if(ProbPrime(div(i),10)){
				m*=to_ZZ(-1);
				primes.SetLength(j);
                primes(j)=div(i);
				j++;
				}
			else 
				for(long k=1;k<=primes.length();k++){
					if((div(i)%primes(k)==0) && ((div(i)/primes(k))%primes(k)==0))
						m*=to_ZZ(0);
					else
						m*=to_ZZ(-1);
					}
			}
		//cout<<endl<<endl<<"prvocisla: "<<endl<<endl<<primes;
		return m;
		}
}

ZZ_pX polynomialQ(ZZ n){
	ZZ len,quocient,e;
	ZZ_pX tmp,tmp2,polyQ;
	vec_ZZ div;
    
	clear(polyQ);
	clear(tmp2);
	SetCoeff(polyQ,0,1);
	div=numberDecomposition(n);
	len=div.length();

	SetCoeff(tmp2,0,1);

    for(long i=to_long(len); i>=1;i--){
		//nacitanie polynomu tvaru (x^n-1)
		clear(tmp);
		SetCoeff(tmp,0,-1); 
		SetCoeff(tmp,to_long(div(i)),1);
        quocient=n/div(i);
		e=mobyFunction(quocient); //vracia koeficient z mobyovej funkcie...
		//cout<<endl<<endl<<"e je pre "<<div(i)<<" : "<<e<<endl<<endl;
		if(e<0)
			tmp2*=tmp;
		else{
			power(tmp,tmp,to_long(e));  // x = a^e (e >= 0)
            polyQ*=tmp;
			}
		}
    polyQ/=tmp2;
    return polyQ;
}

string prettyPoly(ZZ_pX poly){
	std::ostringstream s;
	int counter = 1;
	for(int i=deg(poly); i>1; i--){
		if(coeff(poly,i) == 1){
			if(counter%9 == 0)
				s << "x^" << i << " + " << endl << " + ";
			else
				s << "x^" << i << " + ";
		}
		counter++;	
	}
	if(coeff(poly,1)==1)
		s<<"x + ";
	if(coeff(poly,0)==1)
		s<<"1 + ";
	return s.str().substr(0, s.str().size()-3);	
}

string prettyFactors(vec_pair_ZZ_pX_long factors){
	std::ostringstream s;
	if(factors.length()>0){
		s<<"("<<prettyPoly(factors[0].a)<<") * ";
		for(int i=1; i<factors.length(); i++){
				if(i%3 == 0)
					s << endl << " * ";	
				s<<"("<<prettyPoly(factors[i].a)<<") * ";
		}
	}
	return s.str().substr(0, s.str().size()-3);	
}

ZZ gcd(ZZ a, ZZ b){
    if (a == 0)
        return b;
    return gcd(b%a, a);
}

ZZ phi(ZZ n){
    ZZ result;
	result = 1;
	ZZ i;
    for (i=2; i < n; i++)
        if (gcd(i, n) == 1)
            result++;
    return result;
}

int main(){
	cout<<"******************************************************"<<endl;
	cout<<"*                                                    *"<<endl;
	cout<<"*               Zadanie z predmetu RAL               *"<<endl;
	cout<<"*              B. Jahodnikova & R. Uzik              *"<<endl;
	cout<<"*                                                    *"<<endl;
	cout<<"******************************************************"<<endl;
	cout<<"Tema : Faktorizacia x^n - 1 nad F_2"<<endl;
	cout<<"-----------------------------------"<<endl;
	cout<<"Zadanie : "<<endl;
	cout<<"Vstup - cislo n"<<endl;
	cout<<"Vystup - rozklad x^n - 1 na cyklotomicke polynomy,"<<endl;
	cout<<"rozklad x^n - 1 na ireducibilne faktory, tabulka s "<<endl;
	cout<<"poctami ireducibilnych polynomov jednotlivych stup-"<<endl;
	cout<<"nov v tomto rozklade"<<endl;
	cout<<endl<<"-----------------------------------"<<endl;
	char exit[10];
	long degree,index,lenVec;
	
	ZZ p,temp,mod,al,ordQ;
	ZZ_pX poly, F;
	vec_pair_ZZ_pX_long factors;
	vec_ZZ_p x;
	vec_ZZ div;
	
	while(strcmp(exit,"<exit>")!=0){
		clear(poly);
		clear(F);
		p = 2;
		
		ZZ_p::init(p);
		SetCoeff(poly,0,-1);
	
		cout << "Zadaj 'n' pre polynom f(x) = x^n - 1 : ";
	    cin>>index;
	
		SetCoeff(poly,index);
		cout << endl << "f(x) = x^"<< index << " - 1" << endl;
	
		degree=deg(poly);
		
		cout << endl << "Stupen polynomu deg f(x) = " << degree << endl; 
		
		int gcd_deg_p = GCD(degree,to_long(p));
		cout << endl << "GCD(deg f(x),2) = " << gcd_deg_p << endl; 
		
		if(GCD(degree,to_long(p))!=1){
			while(GCD(degree,to_long(p))!=1){
				degree/=to_long(p);
			}
			SetCoeff(F,0,-1);
			SetCoeff(F,degree);	 
			cout<<endl<<"Po zjednoduseni je polynom f(x) v tvare f(x) = ";
			cout << "x^" << degree << " - 1"<<endl<<"s najvyssim stupnom deg f(x) = "<<degree<<" lebo GCD(deg f(x), 2) musi byt rovne 1!"<<endl;
		}else
			F=poly;
		cout << "-----------------------------------" << endl;
	    CanZass(factors,F,0);
		cout<<"Rozklad f(x) na ireducibilne faktory : "<<endl<<"f(x) = ";
		cout<<prettyFactors(factors)<<endl;
		
		div=numberDecomposition(to_ZZ(degree));
	    lenVec=div.length();
	    
	    cout << "-----------------------------------" << endl;
	    cout<<"Rozklad f(x) na cyklotomicke polynomy : "<<endl<<"f(x) = ";
	    for(long i = 1;i <= lenVec; i++){
	    	if(i != lenVec)
				cout <<	"Q_" << div(i) << "(x) * ";
			else
				cout <<	"Q_" << div(i) << "(x)" << endl;
		}
		
		map<ZZ,ZZ*> tmp;
		
		for(long i=lenVec;i>=1;i--){
			factors.kill();
			cout<<endl<<endl<<"Q_"<<div(i)<<"(x) = ";
			cout<<prettyPoly(polynomialQ(div(i)))<<" = "<<endl<<" = ";
			CanZass(factors,polynomialQ(div(i)),0);
			cout<<prettyFactors(factors);
			ZZ* pole = new ZZ[2];
			pole[0] = phi(div(i));
			pole[1] =ord(div(i),p);
			tmp[div(i)] = pole;
			//cout<<endl<<"kde 'rad "<<p<<"' modulo "<<div(i)<<" \360 "<<ord(div(i),p);
	        //cout<<endl<<endl;
		}
		
		cout<<endl<<endl;
		for (map<ZZ,ZZ*>::iterator it=tmp.begin(); it!=tmp.end(); ++it){
    		cout << it->first << " => ";
			ZZ* pole = it->second;
			cout << "<" << pole[0] << ",";
			cout << pole[1] << ">" << endl;
    	}
		
		/*
		cout<<"kde hore vypocitane rady udavaju stupne ireducibilnych polynomov danych 'Q_n' !"<<endl<<endl;
		cout<<"***************************************";
	    cout<<"***************************************";
		cout<<endl<<endl;*/
		
		cout<<endl<<endl<<"Na ukoncenie zadaj '<exit>' inak '<cont>' !"<<endl;
	
		cin>>exit;
	}
	
	return 0;
}


