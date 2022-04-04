
#pragma region  // next_combination
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
// // get all combinations of N nonnegative ints summing to S.
// // that's (N+S-1) choose (S-1).
// int N = 7;
// int S = 3;
// V<int> ch = rangeint(0, N+S-1);
// V<int> nums(N);
// int combs_ctr = 0;
// do {
//     nums[0] = ch[0]; nums[N-1] = N+S-2 - ch[N-2];
//     FOR(k,1,N-1) {
//         nums[k] = ch[k] - ch[k-1] - 1;
//     }
//     ++combs_ctr;
//     dbg(combs_ctr, nums);
//     // ! Do something with nums here.
// } while (next_combination(ch.begin(), ch.begin() + N-1, ch.end()));
#pragma endregion

#pragma endregion
