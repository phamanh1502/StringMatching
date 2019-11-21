#ifndef  _FUNCTION_H
#define _FUNCTION_H

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#define d 256  

using namespace std;

vector<string> List_UPDOWN(char** arr, int row, int column);

vector<string> List_LEFTRIGHT(char** arr, int row, int column);

int search(string pat, string txt, int q);

string Check(vector<string> arr_updown, string pat, int p);

void ReadandWriteFile(const char* read, const char* write);

#endif // ! _FUNCTION_H
