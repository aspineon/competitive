#include "bits/stdc++.h"
#define MODULO 1000000007
#define endl '\n'
#define m(a) ((a)%MODULO)
#define s(a) scanf("%d", &a)
#define sl(a) scanf("%lld", &a)
#define p(a) printf("%lld\n", a)
using namespace std;
#define LT  100000
#define TLT 1000000

typedef unsigned long long ull;
typedef long long ll;

ll primes[LT+1];
int ct=0;

ll lcms[LT+1];
ll cs[TLT], ds[TLT];
ll prods[LT+1];


ll PowMod(ll bs, int n){
    ll ret = 1;
    ll a = bs;
    while (n > 0) {
        if (n & 1) ret = ret * a % MODULO;
        a = a * a % MODULO;
        n >>= 1;
    }
    return ret;
}

void sieve(){ // not the traditional one though
	int i, j;
	int slt = ceil(sqrt(LT));
	fill_n(primes, LT+1, 1);

	primes[0] = 0; primes[1] = 0;

	for (i=2; i<=LT; i++){
		if (primes[i] == 1){
			if (i <= slt){
				j = i*i; // i^2 here (beware overflow)
				while (j <= LT){
					primes[j] = 0;
					j += i;
				}
				j = i*i;
				while (j <= LT){
					primes[j] = i;
					j *= i;
				}
			}
			primes[i] = i;
		}
	}
}

void makelcm(){
	// max lcm of F(N,k) series
	int i;
	lcms[0] = 0; lcms[1] = 1;
	for (i=2; i<=LT; i++){
		if (primes[i] > 0)
			lcms[i] = m(lcms[i-1] * primes[i]);
		else
			lcms[i] = lcms[i-1];
	}
}

void factorial(){
	ll i = 1;
	prods[0] = 1; prods[1] = 1;
	for (i=2; i<=LT; i++)
		prods[i] = m(prods[i-1] * i);
}

void init(){
	sieve();
	makelcm();
	factorial();
}


int main(){
	int t=0, loop, j; 
	ll n, k, a, b, m, c, d;
	init();

	s(t);
	scanf("%lld %lld", &n, &k);
	scanf("%lld %lld %lld", &a, &b, &m);
	for (j=1; j<t; j++)
		scanf("%lld", cs+j);
	for (j=1; j<t; j++)
		scanf("%lld", ds+j);

	ll n2, ub, i, dv, quot, num, ans, ht, ct, i2, temp, quot2;

	for (loop=1; loop<=t; loop++){
		n2 = ceil(n/2.0);
		if (k >= n2){
		// direct ans
			p(ans = lcms[n]);
		} else {
			ub = n-k+1;
			dv = 1;
			ht = ub-(k+1);
			if (ht<0) ht=0;
			ht = ht/10;
			if (ht >= k){
			// sqrt decom
				for (i=2; i<k; i++){ // kth will come 1 time
					if (primes[i] > 0){
						quot = floor( n / (double) i );
						quot2 = ceil( ub / (double) i );
						ct = quot - quot2 + 1;
						if (ct > 1) dv = m(dv * PowMod(primes[i], ct-1));
					}
				}
				ans = m(prods[n] * PowMod(prods[ub-1], MODULO-2));
				ans = m(ans * PowMod(dv, MODULO-2));
				// printf("hi ");
				p(ans);
			} else {
			// normal technique
				for (i=k+1; i<ub; i++){
					if (i > n2){ // i=6 , ub = 8 , n = 10
						num = m(lcms[ub-1] * PowMod(lcms[i-1], MODULO-2));
						dv = m(dv * num);
						break;
					}
					else if (primes[i] > 0){
						quot = ceil( n / (double) i);
						num = quot * i;
						if (num == n)
							continue;
						num -= i;
						if (num >= ub)
							continue;
						dv = m(dv * primes[i]);
					}
				}
				ans = m(lcms[n] * PowMod(dv, MODULO-2));
				p(ans);
			}
		}

		n = 1 + ((a * ans + cs[loop]) % m);
		k = 1 + ((b * ans + ds[loop]) % n);
		// printf("%lld %lld ", n, k);
	}

	return 0;
}

/*
3
2 1
0 0 3
2 2
0 1
*/

/*
4
5 2
2 3 6
4 2 3
2 4 2
*/

/*
10
9 3
12 15 19
1 3 4 5 1 2 3 4 4
2 3 4 1 6 7 2 1 5
*/

/*
10
40 5
12 14 40
1 2 3 4 5 6 7 8 9
1 2 3 4 5 6 7 8 9
*/

/*
19
100 21
12 14 100
1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9
1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9
*/