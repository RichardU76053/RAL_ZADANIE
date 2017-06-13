#include <iostream>
#include <fstream>
#include <cstring>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_pXFactoring.h>
#include <conio.h>

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
	cout<<"Vystup - rozklad x^n - 1 na cyklotomicke"<<endl;
	cout<<"polynomy, rozklad x^n - 1 na ireducibilne faktory, tabulka s "<<endl;
	cout<<"poctami ireducibilnych polynomov jednotlivych stupnov v tomto rozklade"<<endl;
	
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
	
		cout << endl << "Zadaj 'n' pre polynom v tvare x^n - 1 : ";
	    cin>>index;
	
		SetCoeff(poly,index);
		cout << endl << poly << endl;
	
		degree=deg(poly);
		
		cout << endl << "Stupen polynomu deg f = " << degree << endl; 
		
		/*
		cout<<"V prvom kroku sa treba pozriet ci najvyssi stupen polynomu je nesudelitelny s p!"<<endl;
		cout<<"\t"<<"a) V pripade sudelitelnosti polynom rozlozime na tvar '(x^k-1)^l',"<<endl;
		cout<<"\t   "<<"pricom plati ze k*l=n a zaroven GCD(p,k)=1!"<<endl;
		cout<<"\t"<<"b) V pripade nesudelitelnosti pokracujeme s druhym krokom!"<<endl<<endl;
		*/
		
		int gcd_deg_p = GCD(degree,to_long(p));
		cout << endl << "GCD(deg f,2) = " << gcd_deg_p << endl; 
		
		if(GCD(degree,to_long(p))!=1){
			while(GCD(degree,to_long(p))!=1){
				degree/=to_long(p);
			}
			SetCoeff(F,0,-1);
			SetCoeff(F,degree);	
			cout<<endl<<"Po zjednoduseni je polynom v tvare : "<<endl;
			cout<<endl<<F<<endl<<"s najvyssim stupnom deg f = "<<degree<<" lebo GCD(deg f, 2) musi byt rovne 1!"<<endl<<endl;
		}else
			F=poly;
	
	    CanZass(factors,F,0);
		cout<<"Faktory polynomu su:";
		cout<<factors<<endl;
	     
		cout<<"V druhom kroku najdeme vsetky delitele cisla n!"<<endl;
		cout<<"\t"<<"Pre vsetky delitele 'd' plati ze x^n-1 = \343 Q_d,"<<endl;
		cout<<"\t"<<"kde Q_n = \343 (x^d-1)^(\346(n/d))!"<<endl;
		cout<<"\t"<<"a \346(n) je mobiova funkcia, ktora moze nadobudnut hodnoty:"<<endl; 
		cout<<"\t"<<"1,-1 a 0 v zavislosti od vstupnej hodnoty 'n'."<<endl<<endl;
		cout<<"Aplikovanim hore uvedenych rovnic na vsetky Q_n dostaneme: "<<endl<<endl;
	
		div=numberDecomposition(to_ZZ(degree));
	    lenVec=div.length();
	    
		for(long i=lenVec;i>=1;i--){
			factors.kill();
			cout<<"Polynom Q indexom "<<div(i)<<" je: "<<endl;
			cout<<polynomialQ(div(i))<<" = "<<endl;
			cout<<" = ";
	
			CanZass(factors,polynomialQ(div(i)),0);
	
			cout<<factors<<endl;
			cout<<"kde 'rad "<<p<<"' modulo "<<div(i)<<" \360 "<<ord(div(i),p);
	        cout<<endl<<endl;
			}
	
		cout<<"kde hore vypocitane rady udavaju stupne ireducibilnych polynomov danych 'Q_n' !"<<endl<<endl;
		cout<<"***************************************";
	    cout<<"***************************************";
		cout<<endl<<endl;
		cout<<"Na ukoncenie zadaj '<exit>' inak '<cont>' !"<<endl;
	
		cin>>exit;
	}
	
	return 0;
}


