// Problem: Problem 3. 248
// Contest: USACO - USACO 2016 US Open Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=647
// Memory Limit: 256 MB
// Time Limit: 4000 ms

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

void input(vi& v,int N){
	for(int i=0;i<N;i++){
		cin>>v[i];
	}
}

int dp[250][250];
bool is_equal[250][250];
void solve(vi& v,int N){
	
	for(int j=0;j<(int)v.size();j++){
		for(int i=0;i+j<(int)v.size();i++){
			if(j==0){
				dp[i][i+j]=v[i];
				is_equal[i][i+j]=1;
			}
			else if(j==1){
				if(v[i]==v[i+j]){
					dp[i][i+j]=v[i]+1;
					is_equal[i][i+j]=1;
				}
				else
					dp[i][i+j]=max(v[i],v[i+j]);
			}else{
				for(int k=i;k<i+j;k++){
					if(is_equal[i][k] && is_equal[k+1][i+j] && dp[i][k]==dp[k+1][i+j]){
						// cout<<i<<" "<<k<<" "<<i+j<<"\n";
						is_equal[i][i+j]|=1;
						dp[i][i+j]=max(dp[i][i+j],max(dp[i][k],dp[k+1][i+j])+1);
					}else
						dp[i][i+j]=max(dp[i][i+j],max(dp[i][k],dp[k+1][i+j]));	
				}
			}
		}
	}
	
	// for(int i=0;i<(int)v.size();i++){
		// for(int j=0;j<(int)v.size();j++)
			// cout<<dp[i][j]<<" ";
		// cout<<"\n";
	// }
	// cout<<"\n";
	// for(int i=0;i<(int)v.size();i++){
		// for(int j=0;j<(int)v.size();j++)
			// cout<<is_equal[i][j]<<" ";
		// cout<<"\n";
	// }
	
	cout<<dp[0][(int)v.size()-1];
}

int main(){
	ios_base::sync_with_stdio(false);
    	cin.tie(NULL);
    
	freopen("248.in","r",stdin);
	freopen("248.out","w",stdout);
	
	int N;
	cin>>N;
	vi v(N);
	input(v,N);
	solve(v,N);
	
	
	return 0;	
}