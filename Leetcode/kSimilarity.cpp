class Solution {
public:
    int kSimilarity(string A, string B) {
      for (int i=0; i<A.size(); i++) {
        if (A[i]==B[i]) continue;
        // Assume that all the position from the beginning to the (i - 1)th position is are match;
        // i is the position where A[i] != B[i];
        // We need to find to the position j >  sastified A[j] == B[i] && A[j] != B[j]
        // there are 2 case:
        // if we find a position where A[i] == B[j], the optimal answer is 1 + kSimilarity (A.substr(i + 1), B.substr(i + 1))
        // else we need to check all the possible anwser to find the optimal answer
        vector<int> matches;
        for (int j=i+1;j<A.size();j++) { 
          if (A[j]==B[i] && A[j]!=B[j]) {
            matches.push_back(j);
            if (A[i]==B[j]) {
              swap(A[i],A[j]);
              return 1+kSimilarity(A.substr(i+1),B.substr(i+1));
            }
          }
        }
        int best=A.size()-1;
        for (int j: matches) {
            swap(A[i],A[j]);
            best = min(best, 1+kSimilarity(A.substr(i+1),B.substr(i+1)));
            swap(A[i],A[j]);
        }
        return best;
      }
      return 0;
    }
};
