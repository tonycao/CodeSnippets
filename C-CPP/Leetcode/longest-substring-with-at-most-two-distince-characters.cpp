class Solution{
public:

	int lengthOfLongestSubstringTwoDistinct(string s) {
		//http://www.danielbit.com/blog/puzzle/leetcode/leetcode-longest-substring-with-at-most-two-distinct-characters
		//http://blog.csdn.net/whuwangyi/article/details/42451289
		int i = 0, j = -1, maxLen = 0;
		for (int k = 1; k < s.length(); k++) {
			if (s[k] == s[k - 1]) {
				continue;
			}
			if (j >= 0 && s[j] != s[k]) {
				maxLen = max(maxLen, k - i);
				i = j + 1; // i is the begining of the substring
			}
			j = k - 1; // j is the prev index of the second char
		}
		return max((int) (s.length() - i), maxLen);
	}	
};
