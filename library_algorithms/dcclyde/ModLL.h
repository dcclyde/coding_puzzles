
// const ll MOD = 1'000'000'007;
// const ll MOD = 998'244'353;
// const ll MOD = 1234567891;  // WATCH OUT, this is bigger than 2^31 / 2!
#pragma region  // mll
/**
 * Description: modular arithmetic operations
 * Source:
	* KACTL
	* https://codeforces.com/blog/entry/63903
	* https://codeforces.com/contest/1261/submission/65632855 (tourist)
	* https://codeforces.com/contest/1264/submission/66344993 (ksun)
	* also see https://github.com/ecnerwala/cp-book/blob/master/src/modnum.hpp (ecnerwal)
 * Verification:
	* https://open.kattis.com/problems/modulararithmetic
 */

using ll = long long;  // ! Take this out later.

#ifndef DCCLYDE__MODLL
#define DCCLYDE_MODLL

template<ll MOD, ll MODPHI, ll RT> struct mll {
	static const ll mod = MOD;
	static const ll modphi = MODPHI;
	static constexpr mll rt() { return RT; } // primitive root for FFT
	ll v; explicit operator ll() const { return v; } // explicit -> don't silently convert to int
	// explicit operator int() const { return v; }  // ! Don't convert this to an int!
	mll():v(0) {}
	mll(ll _v) { v = ll((-MOD < _v && _v < MOD) ? _v : _v % MOD);
		if (v < 0) v += MOD; }
	bool operator==(const mll& o) const {
		return v == o.v; }
	friend bool operator!=(const mll& a, const mll& b) {
		return !(a == b); }
	friend bool operator<(const mll& a, const mll& b) {
		return a.v < b.v; }
	friend void re(mll& a) { ll x; re(x); a = mll(x); }
	friend str ts(mll a) { return ts(a.v); }
	friend str tsdbg(mll a) { return tsdbg(a.v); }

	mll& operator+=(const mll& o) {
		if ((v += o.v) >= MOD) v -= MOD;
		return *this; }
	mll& operator-=(const mll& o) {
		if ((v -= o.v) < 0) v += MOD;
		return *this; }
	mll& operator*=(const mll& o) {
		v = ll((__int128_t)v*o.v%MOD);
		// v = modMul(v, o.v, MOD);
		return *this; }
	mll& operator/=(const mll& o) { return (*this) *= inv(o); }
	friend mll pow(mll a, ll p) {
		mll ans = 1;
        if (p < 0) {return pow(inv(a), -p);}
		for (; p; p /= 2, a *= a) if (p&1) ans *= a;
		return ans; }
	friend mll inv(const mll& a) { assert(a.v != 0);
		return pow(a,modphi-1);
		// if MOD isn't prime use second version instead.
		// Alternatively, find totient of MOD and use pow(a, totient-1).
		// return (1<a) ? (MOD - ll(inv(MOD%a,a))*MOD/a) : (1);
	}
	mll operator-() const { return mll(-v); }
	mll& operator++() { return *this += 1; }
	mll& operator--() { return *this -= 1; }
	friend mll operator+(mll a, const mll& b) { return a += b; }
	friend mll operator-(mll a, const mll& b) { return a -= b; }
	friend mll operator*(mll a, const mll& b) { return a *= b; }
	friend mll operator/(mll a, const mll& b) { return a /= b; }
};

using mi = mll<MOD,MOD-1,5>; // 5 is primitive root for both common mods
using vmi = V<mi>;
using pmi = pair<mi,mi>;
using vpmi = V<pmi>;

V<vmi> scmb; // small combinations
void genComb(int SZ) {
	scmb.assign(SZ,vmi(SZ)); scmb[0][0] = 1;
	FOR(i,1,SZ) F0R(j,i+1)
		scmb[i][j] = scmb[i-1][j]+(j?scmb[i-1][j-1]:0);
}

template <int MOD, int RT>
string to_string(mll<MOD, RT> modint) {
    return to_string((int)modint);
}

#endif
#pragma endregion  // mll
