'''
Given N items with prices Pj
Coupons like (d_k, l_k).
    Get a discount of d_k as long as original cost was at least l_k.

What's the max total discount I can get?

*****

Seems like I could just greedily try to apply the best coupons.
I could do that with a std::set but maybe not Python-friendly?

'''
