#include <bits/stdc++.h>
using namespace std;



bool isprime(int n){
	if(n == 2)return true;
	for(int i = 2; i < n; i++){
		if(n % i == 0)return false;
	}
	return true;
}



int next_prime(int n){
	++n;
	while(!isprime(n))++n;
	return n;
}



int32_t main(){
	int n; cin>>n;
	if(n%2){
		cout<<"-1\n";
		return 0;
	}

	for(int i = 2; i <= n; i+=2){
		cout<<i<<" "<<i - 1<<" ";
	}
	cout<<"\n";

}
