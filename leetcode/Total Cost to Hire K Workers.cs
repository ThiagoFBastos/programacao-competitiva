public class Solution {
    public long TotalCost(int[] costs, int k, int candidates) {
        var first = new PriorityQueue<int, int>();
        var last = new PriorityQueue<int, int>();
        int l = candidates, r = costs.Length - candidates - 1;
        long result = 0;

        for(int i = 0; i < candidates; ++i)
            first.Enqueue(costs[i], costs[i]);

        for(int i = int.Max(r + 1, candidates); i < costs.Length; ++i)
            last.Enqueue(costs[i], costs[i]);

        first.Enqueue(int.MaxValue, int.MaxValue);
        last.Enqueue(int.MaxValue, int.MaxValue);

        for(int i = 0; i < k; ++i) {
            if(first.Peek() <= last.Peek()) {
                result += first.Dequeue();
                if(l <= r) first.Enqueue(costs[l], costs[l]);
                ++l;
            } else {
                result += last.Dequeue();
                if(l <= r) last.Enqueue(costs[r], costs[r]);
                --r;
            }
        }

        return result;
    }
}