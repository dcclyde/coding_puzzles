using MDAT = ll;
#pragma region  // matrix (mat) and simple operations. TODO is benq's Matrix just better?
using mat = V<V<MDAT>>;

mat matmat(const mat& A, const mat& B) {
    mat out(A.size(), V<MDAT>(B[0].size()));
    FOR(j, 0, A.size()) FOR(k, 0, A[0].size()) FOR(l, 0, B[0].size()) {
        out[j][l] += A[j][k] * B[k][l];
    }
    return out;
}
mat zero(ll N) {
    return mat(N, V<MDAT>(N));
}
mat eye(ll N) {
    mat out(N, V<MDAT>(N));
    FOR(k, 0, N) {out[k][k] = 1;}
    return out;
}
mat matpow(mat A, ll e) {
    ll N = A.size();
    mat out = eye(N);
    while(e) {
        if (N >= 500) {dbgcR("matmat", TIME(), N, e);}
        if (e&1) {out = matmat(out, A);}
        A = matmat(A, A); e>>=1;
    }
    return out;
}
V<MDAT> matvec(const mat& A, const V<MDAT>& x) {
    V<MDAT> out(A.size());
    FOR(j, 0, A.size()) FOR(k, 0, A[0].size()) {out[j] += A[j][k] * x[k];}
    return out;
}
#pragma endregion
