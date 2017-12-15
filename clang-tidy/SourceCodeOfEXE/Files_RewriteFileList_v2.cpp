#include <string>
#include <sstream>
#include <vector>
#include <fstream> 
#include <iostream>
#include <direct.h>
using namespace std;

int main(void) {

	//ofstream outputNoRewrite(std::string("NoRewriteFile.txt"));

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
	ofstream fout("Rewritefilelist.txt", ios::out);
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

	// mkdir BackUp folder according to project folder 
	for (int j = 0; j < path2.size(); ++j) {
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
	}

/*
	int i = 0;
	//while(getline(file)){}
	while (file.eof() == 0)
	{
		//file >> Str[i];
		file.getline(buffer, 25);
		i++;
		cout << "i=" << i << ", Str[i]=" << buffer << endl;
		//cout << "i=" << i << ", Str[20]=" << buffer[8] << endl;
		//ss << buffer;
		//for (int k = 0; k < 8; ++k) { if (buffer[k] == "e") {} }
		//ss >> s;
		//string f = "file";
		//if (strcmp(buffer, "    \"file\":") == 0) { cout << "!!!!" << endl; }
		//if (s[8] == "e" && buffer[i + 1] = "i") {}
		system("pause");
	}

	file.close();*/
	//system("pause");

	/*ifstream fin2("RewriteFile.txt", ios::in);
	while (getline(fin2, readStr)) {
		//if (readStr.find("file", 0) != string::npos) {
			for (int i = 0; i < readStr.size(); i++) {
				pos = readStr.find(pattern, i);
				count++;
				if (count == 4) {
					result.push_back(readStr.substr(i, pos - i));
				}
				i = pos + pattern.size() - 1;
			}
		//}
	}
	fin2.close();*/


	return 0;
}