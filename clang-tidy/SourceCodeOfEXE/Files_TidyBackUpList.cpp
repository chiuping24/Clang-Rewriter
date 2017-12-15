#include <string>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <fstream> 
#include <iostream>
#include <direct.h>
using namespace std;

int main(void) {

/*	char buffer[25];
	char buffer2[100];
	string STRING;
	string name;
	string rent;
	string s;
	string Str[10000];
	vector<string> S;
	stringstream ss;*/
	ifstream fin("compile_commands.json", ios::in);


	string readStr;

	string pattern = "\"";
	//string::size_type pos;
	//vector<string> result;
	vector<string> resultp;

	//fout.open;
	while (getline(fin, readStr)) {
/*		if (readStr.find("\"file\"", 0) != string::npos) {
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
		}*/

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
/*	while (getline(fin, readStr2)) {
		cout << "============" << endl;
		cout << readStr2 << endl;
		cout << "============" << endl;
		// get current directory: path/
		if (readStr2.find("directory", 0) != string::npos) {
			cout << "HHHH" << endl;
			int count = 0;
			//cout << count << endl;
			string::size_type pos;
			for (int i = 0; i < readStr2.size(); i++) {
				pos = readStr2.find(pattern, i);
				count++;
				//cout << count<<endl;
				if (count == 4) {
					resultp.push_back(readStr2.substr(i, pos - i));
				}
				i = pos + pattern.size() - 1;
			}
		}
	}*/
	fin.close();
	/*
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
	fout.close();*/

	// mkdir BackUp folder according to project folder 
	/*for (int j = 0; j < path2.size(); ++j) {
		int pathN = 0; //      src/src/x.cpp -> pathN=2 
		vector<int> position; // position of '/' in path
		for (int i = 0; i < path2[j].size(); ++i) {
			string dash = "/";
			//cout << path2[j][i] << endl;
			if (path2[j][i] == dash[0]) {
				position.push_back(i); pathN++; //errs() << "\n !!!!!!!!!!pathN" << pathN; 
			}
		}
		//const int n = position[pathN - 1];
		if (pathN > 0) {
			string filepath = path2[j].substr(0, position[pathN - 1] + 1);
			string filepath2 = std::string("BackUp/" + filepath);
			_mkdir(filepath2.c_str());
		}
		if (pathN == 0) { string filepath2 = "BackUp/"; _mkdir(filepath2.c_str()); }
	}*/

	// copy the file of clang-tidy applying before fix ====================================
	vector<string> TidyOldFile;
	ifstream fin2("output.log", ios::in);
	string readStr2;
	string currPath = resultp[0].substr(2, resultp[0].size());
	//string currPath = "c:/ClangTest";
	cout << currPath;
	while (getline(fin2, readStr2)) {
		//cout << "File Str.  " << readStr2 << endl;
		if (readStr2.find(currPath, 0) != string::npos) {
			int posB=-1;
			int posE=-1;
			int foundE = 0;
			string s = ":";
			for (int i = 0; i < readStr2.size(); i++) {
				posB = readStr2.find(currPath, i)+currPath.size();
				if (i > posB && posE < 0 && foundE == 0) {
					if (readStr2[i] == s[0]) { foundE++; posE = i; }
					//foundE++; posE = readStr2.find(":30", i);
				} // after path C:/ClangTidy  find:51:24 to end the path
				if (posB >= 0 && posE >= 0) { 
					i= readStr2.size(); 
					TidyOldFile.push_back(readStr2.substr(posB + 4, posE - posB - 4));
					//cout << "Need Backup fixing file===" << readStr2.substr(posB+4, posE- posB-4) <<"==="<< endl; 
				}
			}
		}

	}
	fin2.close();
	//system("pause");


	ofstream outputTidyCP(std::string("BackUp/TidyBackupFile.txt"));
	// check whether there is the files in BackUp folder, if not-> cp it, if y->nothing to do  ====
	int count = 0;
	for (int i = 0; i < TidyOldFile.size(); ++i) {
		string fileBackup = std::string("BackUp/" + TidyOldFile[i]);
		//cout << "!!: "<<fileBackup << endl;
		vector<int> position;
		string a = "/";
		for (int j = 0; j < fileBackup.size(); ++j) {
			//cout << "@@@" << fileBackup.find(a[0], j)<<endl;
			if (fileBackup[j] == a[0]) { position.push_back(j); }
		}
		for (int k = 0; k < position.size(); ++k) {
			//cout << "@@!!!" << position[k] << endl;
		}
		//cout << "@@!!!" << position[0] << endl;
		//cout << "--!!!" << position[position.size() - 1] << endl;
		string fileBackup2 = fileBackup.substr(0, position[position.size()-1]);
		//int count = 0;
		if ((_access(fileBackup.c_str(), 0)) != 0) { // this file doesn't exist in BackUp folder
			//cout <<" no exist file: "<< fileBackup << endl;
			if (count ==0 ) {
				outputTidyCP << "copy " << TidyOldFile[i] << " " << fileBackup2;
			}
			if (count >0 ) {
				outputTidyCP << " && copy " << TidyOldFile[i] << " " << fileBackup2;
			}
			count++;
			//printf("File not exists ");
		}
	}
	outputTidyCP.close();
	//system("pause");

	return 0;
}