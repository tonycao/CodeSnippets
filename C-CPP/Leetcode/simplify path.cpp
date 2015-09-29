class Solution {
public:
    string simplifyPath(string path) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        //Remove double "//"
        int i=0;
        while (i<path.size()-1){
            if (path[i]=='/' && path[i+1]=='/'){
                path.erase(i,1);
            }else{ i++; }
        }
        //Add a '/' in the end.
        if (path[path.size()-1]!='/'){path=path+"/";}

        //main part
        stack<string> dirs;
        string str="";
        int flag =0;
        for (int i=0;i<path.size();i++){
            if (path[i]=='/'){flag++;}
            if (flag==1){ str+=path[i];}
            if (flag==2){
                if (str=="/.." && !dirs.empty()){
                    dirs.pop();
                }
                if (str!="/." && str!="/.."){
                    dirs.push(str);
                }
                flag=1;
                str="/";
            }
        }

        //Output Result
        if (dirs.empty()){return "/";}
        str="";
        while (!dirs.empty()){
            str=dirs.top()+str;
            dirs.pop();
        }
        return str;
    }
};
