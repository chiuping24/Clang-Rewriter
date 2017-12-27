#include <string>
#include <sstream>
#include <vector>
#include <fstream> 
#include <iostream>
#include <direct.h>
using namespace std;

int main(void) {

	//ofstream outputNoRewrite(std::string("NoRewriteFile.txt"));
	ifstream fin("compile_commands.json", ios::in);
	ofstream fout("Rewritefilelist.txt", ios::out);
	ofstream fout2("BackUpdoclist.txt", ios::out);
	string readStr;
	string readStr2;
	string pattern = "\"";
	//string::size_type pos;
	vector<string> result;
	vector<string> resultp;

	//fout.open;
	while (getline(fin, readStr)) {

		//cout << readStr << endl;
		// get file: path/name
		if (readStr.find("\"file\"", 0) != string::npos) {
			//cout << "File Str.size: " << readStr.size() << endl;
			int count = 0;
			string::size_type pos;
			for (int i = 0; i < readStr.size(); i++) {
				pos = readStr.find(pattern, i);
				count++;
				if (count == 4) {
					result.push_back(readStr.substr(i, pos - i));
				}
				i = pos + pattern.size() - 1;
			}
		}

		if (readStr.find("\"directory\"", 0) != string::npos) {
			int count = 0;
			string::size_type pos;
			//cout << "Dir Str.size: " << readStr.size() << endl;
			for (int i = 0; i < 30; i++) {
				pos = readStr.find(pattern, i);
				count++;
				if (count == 4) {
					resultp.push_back(readStr.substr(i, pos - i));
				}
				i = pos + pattern.size() - 1;
			}
		}
	}


	fin.close();

	//cout << result.size() << ", " << resultp.size() << endl;
	vector<string> path2;
	for (int i = 0; i < result.size(); ++i) {
		//cout << result[i] <<endl;
		//cout << result[i] <<", path: "<< resultp[i]<< endl;
		path2.push_back(result[i].substr(resultp[i].size() + 1, result[i].size()));
		fout << path2[i];
		fout << " ";
		//cout << "correlated path: " << path2[i]<<endl;
	}
	fout.close();
	fout2 << "mkdir BackUp";
	// mkdir BackUp folder according to project folder 
	for (int j = 0; j < path2.size(); ++j) {
		string dash = "/";
		string dash2 = "\\";
		int pathN = 0; //      src/src/x.cpp -> pathN=2 
		vector<int> position; // position of '/' in path
		for (int i = 0; i < path2[j].size(); ++i) {
			//cout << path2[j][i] << endl;
			if (path2[j][i] == dash[0]) {
				position.push_back(i); pathN++; //errs() << "\n !!!!!!!!!!pathN" << pathN; 
			}
		}
		//const int n = position[pathN - 1];
		if (pathN > 0) {
			string filepath = path2[j].substr(0, position[pathN - 1] + 1);
			string filepath2 = std::string("BackUp/" + filepath);
			for (int k = 0; k < filepath2.size(); ++k){
				if (filepath2[k] == dash[0]){ filepath2[k] = dash2[0]; }
			}
			//cout << "madir: " << filepath2.c_str()<<endl;
			fout2 << " && mkdir " << filepath2.c_str();
			//_mkdir(filepath2.c_str());
		}
		//if (pathN == 0) { string filepath2 = "BackUp/"; _mkdir(filepath2.c_str()); }
	}
	fout2.close();
	return 0;
}
