public class SmallestInfiniteSet {
    private PriorityQueue<int, int> set;
    private HashSet<int> control;

    public SmallestInfiniteSet() {
        set = new PriorityQueue<int, int>();
        control = new HashSet<int>();
        for(int i = 1; i <= 1000; ++i) {
            set.Enqueue(i, i);
            control.Add(i);
        }
    }
    
    public int PopSmallest() {
        int result = set.Dequeue();
        control.Remove(result);
        return result;
    }
    
    public void AddBack(int num) {
        if(!control.Contains(num)) {
            control.Add(num);
            set.Enqueue(num, num);
        }
    }
}

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet obj = new SmallestInfiniteSet();
 * int param_1 = obj.PopSmallest();
 * obj.AddBack(num);
 */