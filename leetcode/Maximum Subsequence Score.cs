public class Solution {
    public long MaxScore(int[] nums1, int[] nums2, int k) {
        int n = nums1.Length;
        var numsPairs = new KeyValuePair<int, int>[n];
        var pq = new PriorityQueue<int, int>();
        long sum = 0, maxValue = 0;

        for(int i = 0; i < n; ++i)
            numsPairs[i] = new KeyValuePair<int, int>(nums1[i], nums2[i]);
        
        Array.Sort(numsPairs, (KeyValuePair<int, int> L, KeyValuePair<int, int> R) => R.Value - L.Value);

        foreach(var pair in numsPairs) {
            sum += pair.Key;
            pq.Enqueue(pair.Key, pair.Key);

            while(pq.Count > k)
                sum -= pq.Dequeue();

            if(pq.Count >= k)
                maxValue = long.Max(maxValue, sum * pair.Value);
        }

        return maxValue;
    }
}