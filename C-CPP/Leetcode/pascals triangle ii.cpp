class Solution {
public:
    vector<int> getRow(int rowIndex) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<int> array;
        for(int i=0; i <= rowIndex; i++){
            for(int j = i-1; j >0; j--){
                array[j] = array[j-1] + array[j];
            }
            array.push_back(1);
        }
        return array;
    }

};
