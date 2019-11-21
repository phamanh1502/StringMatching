#include"Function.h"

void CreateMatrix(char** arr, int row, int column, char x)
{
	arr = new char* [row];
	for (int i = 0; i < row; i++)
	{
		arr[i] = new char[column];
		for (int j = 0; j < column; j++)
		{
			arr[i][j] = x; //lưu mỗi phần tử char vào mảng 2 chiều
		}
	}
}

vector<string> List_UPDOWN(char** arr, int row, int column)
{
	vector<string> list_updown;
	for (int i = 1; i <= column; i++)
	{
		string temp = "";
		for (int j = 1; j <= row; j++)
		{
			temp += arr[j][i];
		}
		list_updown.push_back(temp);
	}
	return list_updown;
}

vector<string> List_LEFTRIGHT(char** arr, int row, int column)
{
	vector<string> list_leftright;
	for (int i = 1; i <= row; i++)
	{
		string temp = "";
		for (int j = 1; j <= column; j++)
		{
			temp += arr[i][j];
		}
		list_leftright.push_back(temp);
	}
	return list_leftright;
}

int search(string pat, string txt, int q)
{
	int M = pat.length();
	int N = txt.length();
	int i, j;
	int p = 0; // hash value for pattern  
	int t = 0; // hash value for txt  
	int h = 1;

	// The value of h would be "pow(d, M-1)%q"  
	for (i = 0; i < M - 1; i++)
		h = (h * d) % q;

	// Calculate the hash value of pattern and first  
	// window of text  
	for (i = 0; i < M; i++)
	{
		p = (d * p + pat[i]) % q;
		t = (d * t + txt[i]) % q;
	}

	// Slide the pattern over text one by one  
	for (i = 0; i <= N - M; i++)
	{

		// Check the hash values of current window of text  
		// and pattern. If the hash values match then only  
		// check for characters on by one  
		if (p == t)
		{
			/* Check for characters one by one */
			for (j = 0; j < M; j++)
			{
				if (txt[i + j] != pat[j])
					break;
			}

			// if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]  
			if (j == M)
			{
				return i;
				break;
			}

		}

		// Calculate hash value for next window of text: Remove  
		// leading digit, add trailing digit  
		if (i < N - M)
		{
			t = (d * (t - txt[i] * h) + txt[i + M]) % q;

			// We might get negative value of t, converting it  
			// to positive  
			if (t < 0)
				t = (t + q);
		}
	}
	return -1;
}

string Check(vector<string> arr_updown, vector<string> arr_leftright, string pat, int p)
{
	stringstream writer;
	int value1 = -1, value2=-1;
	for (int i = 0; i < arr_updown.size(); i++)
	{
		value1 = search(pat, arr_updown[i], p);
		if (value1 != -1)
		{
			writer << pat << " " << "(" << value1 + 1 << "," << i + 1 << ")" << " " << "TD";
			break;
		}
	}

	for(int i = 0; i < arr_leftright.size(); i++)
	{
		value2 = search(pat, arr_leftright[i], p);
		if (value2 != -1)
		{
			writer<< pat << " " << "(" << i+1 << "," << value2+1 << ")" << " " << "LR";
			break;
		}
	}
	
	if (value1 == -1 && value2 == -1)
		writer << pat << " " << "(" << 0 << "," << 0 << ")" << " " << "NF";

	return writer.str();
}


void ReadandWriteFile(const char* read,const char* write)
{
	ifstream fin;
	ofstream fout;

	fin.open(read);
	fout.open(write);
	if (!fin.is_open() || !fout.is_open())
		return;

	char temp;
	int H_height, W_weight;
	char** arr;


	for (int i = 0; i < 1; i++)
	{
		fin >> H_height;
		cout << H_height << endl;
		fin >> W_weight;
		cout << W_weight << endl;
	}


	arr = new char* [H_height];

	for (int i = 1; i <= H_height; i++)
	{
		arr[i] = new char[W_weight];

		for (int j = 1; j <= W_weight; j++)
		{
			fin >> temp;
			if (temp != ' ')
				arr[i][j] = temp;

		}
	}

	
	vector<string> updown = List_UPDOWN(arr, H_height, W_weight);

	vector<string> leftright = List_LEFTRIGHT(arr, H_height, W_weight);


	string data;
	string result;
	for (int i = H_height + 2; ; i++)
	{
		fin >> data;
		if (data == "#")
			break;
		cout << data << endl;
		result = Check(updown, leftright, data, 13);
		fout << result << endl;
	}

	fin.close();
	fout.close();
}

