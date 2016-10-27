#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<cmath>

using namespace std;

void splitString(string s, vector<string>& vss, char cs, bool need1col=true) {
	string::size_type start = 0;
	string::size_type last;
	while(true) {
		last = s.find_first_of(cs, start);
		if(last == string::npos) break;
		if(need1col) {
            need1col = false;
            continue;
		}else {
			vss.push_back(s.substr(start, last-start));
		}
		start = last + 1;
	}
	vss.push_back(s.substr(start));
}

void readxls(string filename, vector<vector<string>>& mtD, vector<string>& vHead, bool need1col=true) {
    fstream fsupermarket(filename);
    string s;

	getline(fsupermarket, s);
	splitString(s, vHead, '\t', need1col);
    while(getline(fsupermarket, s)) {
        vector<string> vLine;
        splitString(s, vLine, '\t', need1col);
        mtD.push_back(vLine);
    }
}



void mtToKk(vector<vector<string>>& mtD, vector<vector<int>>& vvKk) {
	for(auto x : mtD) {
		vector<int> vKk;
		for(int i = 0; i < x.size(); i++) {
			if(x[i] == "T") {
				vKk.push_back(i);
			}
		}
		vvKk.push_back(vKk);
	}
}


int main(int argc, char* argv[]) {
    string filename;
    if(argc ==1)    filename = "超市数据集.txt";
    else filename = argv[1];
    cout << filename;
    vector<vector<string>> mtDetails;
	vector<string> vHead;
    readxls(filename, mtDetails, vHead, false);
    cout << "read complete" << endl;
	vector<vector<int>> vvKk;
    mtToKk(mtDetails, vvKk);
    while(true) {
        int i;
        cin >> i;
        for(auto y : vvKk[i]) {
            cout << y << ' ';
        }
        cout << endl;
    }
}
