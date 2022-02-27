
/*
    Track a collection of intervals.
    Example usage: codeforces/2022-02-23/E_working_on_data_structure.cpp
*/

template<class T, bool MERGE_ADJACENT = true>
struct IntervalUnion {
    set<pair<T, T>> x;
    set<pair<T, T>>::iterator it;  // avoid reallocating.

    // internal helper
    pair<T, T> merge_intervals(const pair<T,T>& a, const pair<T,T>& b) {
        return { min(a.first, b.first) , max(a.second, b.second) };
    }

    void insert(pair<T, T> pr) {
        while ( true ) {
            it = x.lower_bound( pr );
            if ( it != x.end() && it->first <= pr.second + MERGE_ADJACENT ) {
                // found an adjacent interval that's ">=" mine.
                pr = merge_intervals(pr, *it);
                x.erase( it );
                continue;
            }
            if ( it == x.begin() ) {
                break;
            }
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
        it = x.lower_bound(MP(p,p));
        if ( it != x.end() && it->first == p ) {
            return it;
        }
        if ( it == x.begin() ) {
            return x.end();
        }
        --it;
        if ( it->second >= p ) {
            return it;
        }
        return x.end();
    }
};
