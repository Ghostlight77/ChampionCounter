#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void load_data(map<string, vector<int> >& championMap);
void display_data(map<string, vector<int> >& championMap);

int main()
{
	map<string, vector<int> > championMap;
	load_data(championMap);
	cout << "FIFA WORLD CUP WINNERS\n\n";
	display_data(championMap);
}

void load_data(map<string, vector<int> >& championMap)
{
	ifstream inputfile("world_cup_champions.txt");

	if (inputfile)
	{
		//skips first line
		string headers;
		getline(inputfile, headers);

		while (!inputfile.eof())
		{
			int year;
			inputfile >> year;
			inputfile.ignore(); //discards tab

			string country;
			inputfile >> country;

			string rest;
			getline(inputfile, rest); // discard rest of line (coach and captains)

			auto search = championMap.find(country);
			if (search == championMap.end()){ //if country not in map
				vector<int> years;
				years.push_back(year);
				championMap[country] = years;
			}
			else{ // country is in map
				championMap[country].push_back(year); // add year to vector
			}
		}
		inputfile.close();
	}
}

void display_data(map<string, vector<int> >& championMap)
{
	cout << left;
	cout << setw(16) << "COUNTRY" << setw(6) << "WINS" << setw(6) << "YEARS" << endl;
	cout << "---------------------------------------------\n";

	for (pair<string, vector<int> > p : championMap)
	{
		string country = p.first;
		vector<int> yearList = p.second;

		int wins = yearList.size();

		cout << setw(16) << country << setw(6) << wins;
		for (int i = 0; i < wins; i++)
		{
			cout << yearList.at(i);
			// as long as we are not at last year
			if (i != yearList.size() -1)
			{
				cout << ", ";
			}
		}
		cout << endl;
	}
}
