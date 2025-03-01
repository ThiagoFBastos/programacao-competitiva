public class Solution {

    delegate string CompressChar(char c, int total);

    public int Compress(char[] chars) {
        StringBuilder sb = new StringBuilder();
        int low = 0;

        CompressChar compress = (char c, int total) => total == 1 ? "" + c : c + total.ToString();

        sb.Capacity = chars.Length;

        for(int i = 0; i < chars.Length; ++i) {
            if(chars[i] != chars[low]) {
               sb.Append(compress(chars[low], i - low));
               low = i;
            }
        }

        sb.Append(compress(chars[low], chars.Length - low));

        string result = sb.ToString();

        for(int i = 0; i < result.Length; ++i)
            chars[i] = result[i];

        return result.Length;
    }
}