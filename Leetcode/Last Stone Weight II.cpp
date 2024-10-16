int dp[31][3001];
vector <int> stones;
int sm = 0;
// state - level, positive sum till now

/*
let a,b,c,d be the weight of stones initially
all possible configurations like +a-b+c+d,-a-b-c+d etc can be achieved
i.e (+/-)a (+/-)b (+/-) c (+/-)d
so the problem now is by assigning a positive or neg sign in front of each number we have to get smallest positive sum
after finding the soln, we can backtrack and get the number which contribute positively and which contribute negatively
to simulate the process to get the answer what we can do is:
take largest from positive side and from negative side, say they are x1 and x2
we need x1-x2 so if x1>x2 we put x1-x2 in positive side , if x1<x2 we put x2-x1 in negative side so that it becomes x1-x2 in next step
so the process can be simulated in this way to assign the correct signs
*/

int rec(int level,int pos){
    if(level == stones.size()){
        int neg = sm-pos;
        if(pos<neg) return 1e9;
        return pos-neg;
    }
    if(dp[level][pos] != -1) return dp[level][pos];
    int ans = min(rec(level+1,pos),rec(level+1,pos+stones[level]));
    return dp[level][pos] = ans;
}

int lastStoneWeightII(vector<int>& _stones) {
    stones = _stones;
    for(auto val:stones) sm+=val;
    memset(dp,-1,sizeof(dp));
    return rec(0,0);
}
