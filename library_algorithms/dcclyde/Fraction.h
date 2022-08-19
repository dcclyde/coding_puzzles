// super basic fraction functionality. cf PE 805, 786, 765, 165
// TODO idr why I stopped using benq's frac. Maybe it's just better?
#pragma region  // frac
using frac = pll;
void reduce(frac& a) {
    auto& [ax,ay] = a;
    ll g = gcd(ax, ay) * ((ay<0) ? (-1) : (1));
    ax /= g; ay /= g;
}
frac operator+(const frac& a, const frac& b) {
    auto& [ax, ay] = a; auto& [bx, by] = b;
    frac out = {ax*by + ay*bx, ay*by};
    reduce(out); return out;
}
frac operator-(const frac& a, const frac& b) {
    auto& [ax, ay] = a; auto& [bx, by] = b;
    frac out = {ax*by - ay*bx, ay*by};
    reduce(out); return out;
}
frac operator-(const frac& a) {return {-a.f, a.s};}
frac operator*(const frac& a, const frac& b) {
    auto& [ax, ay] = a; auto& [bx, by] = b;
    frac out = {ax*bx, ay*by};
    reduce(out); return out;
}
frac operator/(const frac& a, const frac& b) {
    auto& [ax, ay] = a; auto& [bx, by] = b;
    frac out = {ax*by, ay*bx};
    reduce(out); return out;
}
frac make_frac(ll x) {return {x, 1};}
#define mf make_frac
bool operator<(frac& a, frac& b) {return a.f * b.s < b.f * a.s;}
bool operator<=(frac& a, frac& b) {return a.f * b.s <= b.f * a.s;}
bool operator>(frac& a, frac& b) {return a.f * b.s > b.f * a.s;}
bool operator>=(frac& a, frac& b) {return a.f * b.s >= b.f * a.s;}
bool eq(const frac a, const frac b) {return a.f == b.f && a.s == b.s;}
// bool equal(frac& a, frac& b) {return a.f == b.f && a.s == b.s;}
const frac ONE = {1, 1};
const frac ZERO = {0, 1};
#pragma endregion
