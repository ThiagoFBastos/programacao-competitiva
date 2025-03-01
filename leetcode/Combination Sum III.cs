public class Solution {
    public IList<IList<int>> CombinationSum3(int k, int n) {
        IList<IList<int>> combinations = new List<IList<int>>();

        for(int i = 0; i < 512; ++i)
        {
            int sum = 0;
            IList<int> digits = new List<int>();

            for(int j = 0; j < 9; ++j)
            {
                if(((i >> j) & 1) == 1)
                {
                    sum += j + 1;
                    digits.Add(j + 1);
                }
            }

            if(sum == n && digits.Count() == k)
                combinations.Add(digits);
        }

        return combinations;
    }
}