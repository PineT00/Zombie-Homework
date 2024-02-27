#include "pch.h"
#include "StringTable.h"
#include "rapidcsv.h"

StringTable::StringTable(Types t)
	: DataTable(t)
{
}

StringTable::~StringTable()
{
}

const std::string& StringTable::Get(const std::string& id)
{
	auto find = table.find(id);
	if (find == table.end())
		return "Undifined ID";
	return find->second;
}

bool StringTable::Load(Languages language)
{
	static std::vector <std::string> filePathArray = {
		"tables/StringTable_KR.csv",
		"tables/StringTable_EN.csv"
	};
	table.clear();

	currLang = language;

	rapidcsv::Document doc(filePathArray[(int)language], rapidcsv::LabelParams(0, -1));

	for (int i = 0; i < doc.GetRowCount(); ++i)
	{
		std::vector<std::string> pair = doc.GetRow<std::string>(i);
		table.insert({ pair[0], pair[1] });
	}
	return true;
}

bool StringTable::Load()
{
	return Load(currLang);
}

void StringTable::Release()
{
	table.clear();
}
