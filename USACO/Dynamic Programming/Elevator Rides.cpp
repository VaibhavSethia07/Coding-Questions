// Problem: Elevator Rides
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1653
// Memory Limit: 512 MB
// Time Limit: 1000 ms

#include <bits/stdc++.h>
using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using l = long;
using ll = long long;
using ld = long double;
using db = double;
using str = string;

using pi = pair<int,int>;
using pl = pair<ll,ll>;
using pd = pair<db,db>;

using vi = vector<int>;
using vl = vector<long>;
using vll = vector<ll>;

#define mp make_pair
#define f first
#define s second

#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rsz resize
#define ins insert
#define ft front()
#define bk back()
#define pf push_front
#define pb push_back
#define modinv(a,m) modEx(a,m-2,m)
#define moddiv(a,b,m) (a*modinv(b,m))%m
const ll mod=1e9+7;

/* These template codes have been taken from cp-algorithms */
ll extEuclid(ll a,ll b,ll& x,ll& y){
	if(b==0){
		x=1;
		y=0;
		return a;
	}
	
	ll x1,y1;
	ll d=extEuclid(b,a%b,x1,y1);
	x=y1;
	y=x1-(a/b)*y1;
	return d;
}

ll modInverse(ll a,ll n){
	ll x,y;
	extEuclid(a,n,x,y);
	return x;
}

ll linearCong(ll a,ll b,ll n){
	ll d=__gcd(a,n);
	
	if(b%d)
		return -1;
	a/=d;b/=d;n/=d;
	ll a_inv=modInverse(a,n);
	ll ans=(b*a_inv)%n;
	if(ans<0)
		ans+=n;
	return ans;
}

void divisors(map<int,int>& d,ll N){
	for(int div : {2,3,5}){
		int cnt=0;
		if(N%div==0){
			while((N%div)==0){
				N/=div;
				cnt++;
			}
			d[div]=cnt;
		}
	}
	static array<int,8> increments = {4,2,4,2,4,6,2,6};
	int i=0;
	for(ll div=7;div*div<=N;div+=increments[i++]){
		if((N%div)==0){
			int cnt=0;
			while((N%div)==0){
				N/=div;
				cnt++;
			}
			d[div]=cnt;
		}
		if(i==8)
			i=0;
	}
	if(N>1)
		d[N]=1;
}

/* Print the string of digits without leading zero */
void norm(string& str){
	bool zero=true;
	
	for(auto& c:str){
		if(c!='0')
			zero=false;
		if(c!='0' || !zero)
			cout<<c;
	}
}

void input(vl& v,int N){
	for(int i=0;i<N;i++){
		cin>>v[i];
	}
}

void solve(vl& v,int N){
	
}

pair<ll,ll> best[(1<<20)+1];
int main(){
	ios_base::sync_with_stdio(false);
    	cin.tie(NULL);
    
	int n;
	ll x;
	cin>>n>>x;
	ll weight[n];
	for(int i=0;i<n;++i)
		cin>>weight[i];
	
	best[0]={1,0};
	
	for(int s=1;s<(1<<n);++s){
		best[s]={n+1,0};
		for(int p=0;p<n;++p){
			if(s&(1<<p)){
				auto option=best[s^(1<<p)];
				if(option.s+weight[p]<=x)
					option.s+=weight[p];
				else{
					option.f++;
					option.s=weight[p];
				}
				best[s]=min(best[s],option);
			}
		}
	}
	cout<<best[(1<<n)-1].f;
	
	/*The idea is to convert the iteration over permutation to iteration over subset
	For each subset we calculate 2 values, rides(S)->minimum no of rides needed for the set S
	last(S)->minimum weight of last group
	For the base case best[0]={1,0} (1 ride needed to ferry empty elevator with the last weight as 0)
	Now for each subset, we consider every person as the last person to enter the elevator, then we have a subproblem of the set not containing this person
	if option.weight+person's weight<=x
		we include in the last ride and update the weight
	otherwise we increase the no of rides by 1 and fill the last ride by the weight of this person
	At last we minimize the number of rides
	*/
	
	return 0;	
}
