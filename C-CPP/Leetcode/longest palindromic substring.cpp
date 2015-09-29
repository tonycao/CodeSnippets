// algorithm 1

string longestPalindromeDP(string s) {
  int n = s.length();
  if (n == 0){
    return NULL;
  }

  int longestBegin = 0;
  int maxLen = 1;

  bool table[1000][1000] = {false};
  for (int i = 0; i < n; i++) {
    table[i][i] = true;
  }
  for (int i = 0; i < n-1; i++) {
    if (s[i] == s[i+1]) {
      table[i][i+1] = true;
      longestBegin = i;
      maxLen = 2;
    }
  }
  for (int len = 3; len <= n; len++) {
    for (int i = 0; i < n-len+1; i++) {
      int j = i+len-1;
      if (s[i] == s[j] && table[i+1][j-1]) {
        table[i][j] = true;
        longestBegin = i;
        maxLen = len;
      }
    }
  }
  return s.substr(longestBegin, maxLen);
}

// algorithm 2
string expandAroundCenter(string s, int c1, int c2){
    int l = c1, r = c2;
    int n = s.length();
    while(l >= 0 && r <= n-1 && s[l] == s[r]){
      l--;
      r++;
    }
    return s.substr(l+1, r-l-1);
}

string longestPalindromeSimple(string s){
  int n = s.length();
  if (n==0) return "";
  string longest = s.substr(0,1);
  for (int i=0; i < n-1; i++){
    string p1 = expandAroundCenter(s, i, i);
    if (p1.length() > longest.length())
      longest = p1;

    string p2 = expandAroundCenter(s, i, i+1);
    if (p2.length() > longest.length())
      longest = p2;
  }
  return longest;
}

// algorithm 3 O(n)
// Transform S into T.
// For example, S = "abba", T = "^#a#b#b#a#$".
// ^ and $ signs are sentinels appended to each end to avoid bounds checking
string preProcess(string s){
    int n = s.length();
    if (n == 0) return "^$";
    string ret = "^";
    for (int i = 0; i < n; i++){
        ret += "#" + s.substr(i, 1);
    }
    ret += "#$";
    return ret;
}

string longestPalindrome(string s){
    string T = preProcess(s);
    int n = T.length();
    int *p = new int[n];
    int C = 0, R = 0;
    for (int i = 1; i < n-1; i++){
      int i_mirror = 2*C-i; // equals to i' = c - (i-c)

      p[i] = (R > i) ? min(R-i, p[i_mirror]) : 0;

      // Attempt to expand palindrome centered at i
      while (T[i + 1 + p[i]] == T[i - 1 - p[i]])
        p[i]++;

      // If palindrome cented at i expand past R,
      // adjust center based on expanded palindrome
      if (i + p[i] > R){
        C = i;
        R = i + p[i];
      }

    }

    // Find the maximum element in P.
    int maxLen = 0;
    int centerIndex = 0;
    for (int i = 1; i < n-1; i++){
      if (p[i] > maxLen){
        maxLen = p[i];
        centerIndex = i;
      }
    }
    delete[] p;

    return s.substr((centerIndex - 1 - maxLen)/2, maxLen);
}







