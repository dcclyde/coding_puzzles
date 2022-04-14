#pragma region  // IntervalUnion
/*
    Track a collection of intervals.
    Example usage: codeforces/2022-02-23/E_working_on_data_structure.cpp
*/

template<class T, bool MERGE_ADJACENT = true>
struct IntervalUnion {
    set<pair<T, T>> x;
    // internal helper
    pair<T, T> merge_intervals(const pair<T,T>& a, const pair<T,T>& b) {
        return { min(a.first, b.first) , max(a.second, b.second) };
    }
    void insert(pair<T, T> pr) {
        while ( true ) {
            auto it = x.lower_bound( pr );
            if ( it != x.end() && it->first <= pr.second + MERGE_ADJACENT ) {
                // found an adjacent interval that's ">=" mine.
                pr = merge_intervals(pr, *it);
                x.erase( it );
                continue;
            }
            if ( it == x.begin() ) {break;}
            --it;
            if ( it->second >= pr.first - MERGE_ADJACENT ) {
                pr = merge_intervals(pr, *it);
                x.erase(it);
                continue;
            }
            break;
        }
        x.insert( pr );
    }
    set<pair<T,T>>::const_iterator query(T p) {
        auto it = x.lower_bound(MP(p,p));
        if ( it != x.end() && it->first == p ) {return it;}
        if ( it == x.begin() ) {return x.end();}
        --it;
        if ( it->second >= p ) {return it;}
        return x.end();
    }
    // If pr \subseteq *this, return INF.
    // Otherwise, return a point in *this \ pr.
    T test_contained(pair<T,T> pr) {
        auto& [a,b] = pr;
        auto it = query(a);
        if ( it == x.end() ) {return a;}
        if ( it->second >= b ) {return INF;}
        return it->second + 1;
    }
    // What parts of the query interval are missing from the data structure?
    vector<pair<T,T>> missing_sections(pair<T,T> pr) {
        // dbgc("ms", pr);
        auto& [a, b] = pr;
        vector<pair<T,T>> out;
        auto itpre = query(a);
        T pos = (itpre == x.end()) ? (a) : (itpre->second + MERGE_ADJACENT);
        // dbg(pos, *itpre);
        while ( true ) {
            if ( pos >= b ) {break;}
            // find the next relevant interval.
            auto it = x.lower_bound(MP(pos,pos));
            // don't pick the same interval again though.
            if ( it != x.end() && it->second == pos ) {++it;}
            T last = b;
            if ( it != x.end() && it->first <= b ) {last = it->first - MERGE_ADJACENT;}
            out.emplace_back( pos , last );
            if ( it != x.end() && it->second < b ) {pos = it->second + MERGE_ADJACENT;}
            else {break;}
        }
        return out;
    }
};
#pragma endregion  // IntervalUnion
