
// usage: auto [g, coeffs] = gcdExtended(a, b);
pair<ll,pair<ll,ll>> gcdExtended(ll a, ll b) {
    if (b == 0) return {a, {1, 0}};
    auto [d, p] = gcdExtended(b, a % b);
    return {d, {p.second, p.first - p.second * (a / b)}};
}

// a * output = g (mod). Get more solutions by adding mod/g.
ll modinv(ll a, ll mod) {
    auto [g, p] = gcdExtended(a, mod);
    return (p.f % mod + mod) % mod;
}
