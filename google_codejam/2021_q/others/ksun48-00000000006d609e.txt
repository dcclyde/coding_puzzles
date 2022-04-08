#include <bits/stdc++.h>
using namespace std;

void solve(int t){
	int n;
	cin >> n;
	vector<int> a(n);
	int cost = 0;
	for(int& x : a){
		cin >> x;
		x--;
	}
	for(int i = 0; i < n; i++){
		int j = i;
		while(a[j] != i) j++;
		cost += (j-i+1);
		reverse(a.begin() + i, a.begin() + j + 1);
	}
	cout << "Case #" << t << ": ";
	cout << (cost-1) << '\n';
}

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++) solve(t);
}