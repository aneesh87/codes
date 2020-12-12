// Recursion:
// can be done bottom up too
class Solution {
private:
    // mapping to the alphabets 0 and 1 are unmapped
    vector<string>cmap = {"", "", "abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
    vector<string> combos(string &digits, int idx) {
        vector<string> result;
        vector<string> new_result;
        
        if (idx == digits.length()) {
            new_result.push_back("");
            return new_result;
        }

        result = combos(digits, idx+1);
        
        int digit =digits.at(idx) - '0';
        for(int i =0; i< cmap[digit].length(); i++) {
            for (int j=0; j< result.size(); j++) {
                new_result.push_back(cmap[digit].at(i) + result[j]);
            }
        }
        return new_result;
    }
public:
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        if (digits.length() == 0) {
            return result;
        }
        result = combos(digits, 0);
        return result;
    }
};
