/*
You have a large text file containing words. Given any two words, 
find the shortest distance (in terms of number of words) between them in the file. 
Can you make the searching operation in O(1) time? What about the space complexity for your solution?
*/
	
int ShortestDist(string text[], int n, string word1, string word2){
    int min = n;
    int pos1 = -n;
    int pos2 = -n;

    for(int pos = 0; pos < n; pos++){
        if(text[pos] == word1){
            pos1 = pos;
            int dist = pos1 - pos2;
            if(dist < min) min = dist;
        }
        else if(text[pos] == word2){
            pos2 == pos;
            int dist = pos2 - pos1;
            if(dist < min) min = dist;
        }
    }
    return min;
}

