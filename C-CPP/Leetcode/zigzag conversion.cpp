class Solution {
public:
    string convert(string s, int nRows) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(nRows <= 1) return s;
        string ret;
        int zigsize = 2 * nRows - 2;
        for(int i = 0; i < nRows; ++i) {
            for(int base = i; ;base += zigsize) {
                if(base >= s.size())
                    break;
                ret.append(1,s[base]);
                if(i > 0 && i < nRows - 1) {
                    //middle need add ziggggging char
                    int ti = base + zigsize - 2 * i;
                    if(ti < s.size())
                        ret.append(1,s[ti]);
                }
            }
        }
        return ret;
    }
};
//algorithm 2
public class Solution {
 public String convert(String s, int nRows) {
 int n = s.length();
 if(nRows<=1)
 return s;
 StringBuffer[] bs = new StringBuffer[nRows];
 for(int i=0; i<nRows; i++)
 bs[i] = new StringBuffer();

 int len = nRows*2-2;
 for(int i=0; i<n; i++) {
 int k = i%len;
 if(k<nRows) { // each normal column
 bs[k].append(s.substring(i,i+1));
 } else { // each zigzag part
 bs[2*nRows-k-2].append(s.substring(i,i+1));
 }
 }

 StringBuffer res = new StringBuffer();
 for(int i=0; i<nRows; i++)
 res.append(bs[i].toString());

 return res.toString();
 }
}
