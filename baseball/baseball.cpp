// baseball.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;
class cards {
public:
    static void calculateBestSubset(int n, int W, vector<pair<string,int>> cardsVec, int sum, int profit, unordered_map<string,int> marketMap) {
        int maxProfit(0);
        if (sum <= W) {
            cout << "Profit: " << profit << endl;
            return;
        }
        for (int i = 0; i < pow(2, n); i++) {
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) {
                    //sum += cardsVec[j];
                }
            }
            if (sum <= W) {
                if (profit > maxProfit) {
                    maxProfit = profit;
                }
            }
        }
        printOutput();
        
    }
    static void printOutput() {

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
        cards::calculateBestSubset(j, W, cardsVec, sum, profit, marketMap);
    } while (!listRead.eof());
    listRead.close();
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
