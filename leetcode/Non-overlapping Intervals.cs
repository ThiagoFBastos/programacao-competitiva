public class Solution {
    private int Compare(int[] a, int[] b) => a[1] - b[1];

    public int EraseOverlapIntervals(int[][] intervals) {
        int last = int.MinValue, result = 0;

        Array.Sort(intervals, Compare);
        
        foreach(var item in intervals) {
            if(last <= item[0])
                last = item[1];
            else
                ++result;
        }

        return result;
    }
}