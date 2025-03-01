public class Solution {
    private string[] keyboard;

    public Solution() {
        keyboard = new string[10];
        keyboard[2] = "abc";
        keyboard[3] = "def";
        keyboard[4] = "ghi";
        keyboard[5] = "jkl";
        keyboard[6] = "mno";
        keyboard[7] = "pqrs";
        keyboard[8] = "tuv";
        keyboard[9] = "wxyz";
    }

    private void Backtrack(string digits, List<string> words, int k = 0, string word = "") {
        if(k == digits.Length) {
            words.Add(word);
            return;
        }
        int option = digits[k] - '0';
        foreach(char digit in keyboard[option])
            Backtrack(digits, words, k + 1, word + digit);
    }

    public IList<string> LetterCombinations(string digits) {
        List<string> words = new List<string>();
        if(digits.Length > 0)
            Backtrack(digits, words);
        return words;
    }
}