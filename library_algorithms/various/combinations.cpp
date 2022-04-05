#pragma region  // next_combination
// SEO combs comb itertools.comb
template <typename Iterator>
bool next_combination(const Iterator first, Iterator k, const Iterator last)
{
   /* Credits: Mark Nelson http://marknelson.us */
   if ((first == last) || (first == k) || (last == k))
      return false;
   Iterator i1 = first;
   Iterator i2 = last;
   ++i1;
   if (last == i1)
      return false;
   i1 = last;
   --i1;
   i1 = k;
   --i2;
   while (first != i1)
   {
      if (*--i1 < *i2)
      {
         Iterator j = k;
         while (!(*i1 < *j)) ++j;
         std::iter_swap(i1,j);
         ++i1;
         ++j;
         i2 = k;
         std::rotate(i1,j,last);
         while (last != j)
         {
            ++j;
            ++i2;
         }
         std::rotate(k,i2,last);
         return true;
      }
   }
   std::rotate(first,k,last);
   return false;
}

#pragma region  // example

// std::string s = "abcde";
// int comb_size = 2;
// do {
//     std::cout << std::string(s.begin(),s.begin() + i) << std::endl;
// }
// while(next_combination(s.begin(),s.begin() + i,s.end()));

#pragma endregion

#pragma region  // N ints summing to S
// // get all combinations of combN nonnegative ints summing to combS.
// // that's (N+S-1) choose (S-1).
// int combN = 7;
// int combS = 3;
// V<int> ch = rangeint(0, combN+combS-1);
// V<int> nums(combN);
// int combs_ctr = 0;
// do {
//     nums[0] = ch[0]; nums[combN-1] = combN+combS-2 - ch[combN-2];
//     FOR(k,1,combN-1) {
//         nums[k] = ch[k] - ch[k-1] - 1;
//     }
//     ++combs_ctr;
//     dbg(combs_ctr, nums);
//     // ! Do something with nums here.
// } while (next_combination(ch.begin(), ch.begin() + (combN-1), ch.end()));
#pragma endregion

#pragma endregion
