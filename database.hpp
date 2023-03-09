#pragma once
#ifndef DATABASE_H
#define DATABASE
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <map>
#define std ::std::

typedef std vector<std string > vs;
typedef std map < std string, std map <std string, vs>> datamap;
typedef std map <std string, vs> halfdatamap;

class database
{
	private:
	vs lines;
	template<typename outtype, typename arraytype>void insertarray(outtype& outtypes, arraytype _array);
	public:
	datamap data;
	std ifstream file;
	void init();
	int count(std string&, char);
	void analize();
	void print();
	database(std string);
	database(const char*);
	~database();
};
#endif // !DATABASE_H