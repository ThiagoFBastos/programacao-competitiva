public class Trie {

    private class Node {
        private Dictionary<char, int> next;
        private bool _isLeaf = false;
        public bool IsLeaf {get => _isLeaf;}

        public Node() {
            next = new Dictionary<char, int>();
        }

        public int Next(char c) {
            if(next.ContainsKey(c))
                return next[c];
            return -1;
        }

        public void Add(char c, int id) {
            next[c] = id;
        }

        public void SetLeaf() {
            _isLeaf = true;
        }
    }

    private List<Node> nodes;

    public Trie() {
        nodes = new List<Node>();
        nodes.Add(new Node());
    }
    
    public void Insert(string word) {
        int cur = 0;
        foreach(char c in word) {
            int next = nodes[cur].Next(c);
            if(next == -1) {
                next = nodes.Count;
                nodes[cur].Add(c, nodes.Count);
                nodes.Add(new Node());
            }
            cur = next;
        }
        nodes[cur].SetLeaf();
    }

    private int FindLastNode(string word) {
        int cur = 0;
        foreach(char c in word) {
            int next = nodes[cur].Next(c);
            if(next < 0)
                return -1;
            cur = next;
        }
        return cur;
    }
    
    public bool Search(string word) {
        int id = FindLastNode(word);
        return id >= 0 && nodes[id].IsLeaf;
    }
    
    public bool StartsWith(string prefix) {
        int id = FindLastNode(prefix);
        return id != -1;
    }
}

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.Insert(word);
 * bool param_2 = obj.Search(word);
 * bool param_3 = obj.StartsWith(prefix);
 */