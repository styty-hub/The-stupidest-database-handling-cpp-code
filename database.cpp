#include "database.hpp"

void DATABASE database::init()
{
	while(!this->file.eof())
	{
		std string line;
		std getline(this->file, line);
		this->lines.push_back(line);
	}
}

template<typename outtype, typename arraytype> inline void DATABASE database::insertarray(outtype& outtypes, arraytype _array)
{
	for(auto& __arr : _array)
	{
		outtypes << __arr << "	";
		outtypes << std endl;
	}
}

int DATABASE database::count(std string& _input, char _chara)
{
	if(_input.find(_chara) == _input.npos)
	{
		return -1;
	} else
	{
		int* count = new int;
		*count = 0;
		for(int i = 0; i < _input.size(); i++)
		{
			if(_input.at(i) == _chara)
			{
				*count = *count + 1;
			}
		}
		return *count;
	}
}

void DATABASE database::analize()
{
	vs tableheader;
	std string table;
	vs field;
	for(std string __lines : this->lines)
	{
		if(__lines.find('(') == __lines.npos && __lines != "endtable")
		{
			field.push_back(__lines);
		} else if(__lines.find('(') != __lines.npos)
		{
			table = __lines.substr(0, __lines.find('('));
			__lines.erase(0, __lines.find('(') + 1);
			__lines.erase(__lines.size() - 1, 1);
			for(int i = 0; i <= this->count(__lines, ',') + 1; i++)
			{
				tableheader.push_back(__lines.substr(0, __lines.find(',')));
				__lines.erase(0, __lines.find(',') + 1);
			}
			tableheader.push_back(__lines);
		}
		if(__lines == "endtable")
		{
			halfdatamap* hdm = new halfdatamap;
			for(int i = 0; i < tableheader.size(); i++)
			{
				vs* ___field = new vs;
				for(auto& __field : field)
				{
					if(field.size() != 1)
					{
						___field->push_back(__field.substr(0, __field.find(';')));
						__field.erase(0, __field.find(';') + 1);

					} else
					{
						___field->push_back(__field);
					}
				}
				hdm->insert(std make_pair(tableheader.at(i), *___field));
				___field->clear();
				delete ___field;
			}
			this->data.insert(std make_pair(table, *hdm));
			hdm->clear();
			table.clear();
			field.clear();
			tableheader.clear();
			delete hdm;
		}
	}
}

void DATABASE database::print()
{
	for(const auto& [key, value] : this->data)
	{
		std cout << "Table : " << key << std endl;
		std cout << "Columns : " << std endl;
		for(const auto& [_key, _value] : value)
		{
			std cout << _key << ": ";
			for(const auto& __value : _value)
			{
				std cout << __value << " ";
			}
			std cout << std endl;
		}
	}
}


DATABASE database::database(std string _filename)
{
	try
	{
		if(std filesystem::exists(_filename))
		{
			this->file.open(_filename);
		} else
		{
			throw - 1;
		}
	} catch(int& exc)
	{
		std wcerr << exc;
	}
}

DATABASE database::database(const char* _filename)
{
	try
	{
		if(std filesystem::exists(_filename))
		{
			this->file.open(_filename);
		} else
		{
			throw - 1;
		}
	} catch(int& exc)
	{
		std wcerr << exc;
	}
}

DATABASE database::~database()
{
	this->file.close();
}