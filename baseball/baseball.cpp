// baseball.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;
int temp = 0;
class cards {
public:
    static void calculateBestSubset(int n, int W, vector<pair<string,int>> cardsVec, int sum, int profit, unordered_map<string,int> marketMap,
        ofstream &f) {
        int maxProfit(0);
        vector<string> M;
        // if weight is more or equal to sum of all cards, buy them all
        if (sum <= W) {
            for (int i = 0; i < cardsVec.size(); i++) {
                M.push_back(cardsVec.at(i).first);
            }
            printOutput(n, profit, M, f);

            return;
        }
        // amount of subsets would be 2 to the power of n
        for (int i = 0; i < pow(2, n); i++) {
            int s = 0;
            int p = 0;
            vector<string> vec;
            
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) {
                    string str = cardsVec.at(j).first;
                    s += cardsVec.at(j).second;
                    p += marketMap[str] - s;
                    vec.push_back(str);
                }
            }
            // check if not going above given weight and change maxprofit if suffices condition
            if (s <= W) {
                if (p > maxProfit) {
                    maxProfit = p;
                    // clear if already filled
                    if (M.size() > 0) {
                        M.clear();
                    }
                    for (int i = 0; i < vec.size(); i++) {
                        M.push_back(vec[i]);
                    }
                }
            }
        }
        printOutput(n, maxProfit, M, f);
        
    }
    static void printOutput(int n, int maxProfit, vector<string> M, ofstream &f) {
        f << endl;
        f << n << endl << maxProfit << endl << M.size() << endl;
        for (int i = 0; i < M.size(); i++) {
            f << M[i] << endl;
        }
    }

};
int main(int argc, char *argv[])
{
    int i(0), W(0);
    unordered_map<string,int> marketMap;
    // Read marketprice file first
    ifstream marketRead(argv[2]);
    marketRead >> i;
    for (int j = 0; j < i; j++) {
        string s; int k(0);
        marketRead >> s >> k;
        marketMap.insert(make_pair(s, k));
    }
    marketRead.close();
    // Read Gertrude's cards now from pricelist.txt
    int j(0);
    ifstream listRead(argv[4]);
    ofstream f("output.txt");
    do {
        vector<pair<string,int>> cardsVec;
        listRead >> j >> W;
        int sum(0), profit(0);
        for (int k = 0; k < j; k++) {
            string s; int v(0);
            listRead >> s >> v;
            cout << s <<endl;
            sum += v;
            profit += marketMap[s] - v;
            if (marketMap.count(s) == 0) {
                cout << "No such player in Market"<< endl;
                return 0;
            }
            cardsVec.push_back(make_pair(s, v));
        }
        cards::calculateBestSubset(j, W, cardsVec, sum, profit, marketMap, f);
    } while (!listRead.eof());
    listRead.close();
    f.close();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
