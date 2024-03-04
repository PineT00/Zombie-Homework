#include "pch.h"
#include "DataTableMgr.h"
#include "StringTable.h"
#include "ZombieTable.h"

DataTableMgr::DataTableMgr()
{
}

DataTableMgr::~DataTableMgr()
{
	Release();
}

void DataTableMgr::Init()
{
	Release();

	DataTable* table = new StringTable(DataTable::Types::String);
	table->Load();
	tables.insert({ DataTable::Types::String, table });

	ZombieTable* zombieTable = new ZombieTable(DataTable::Types::Zombie);
	zombieTable->Load();
	tables.insert({ DataTable::Types::Zombie, zombieTable });
}

void DataTableMgr::Release()
{
	for (auto pair : tables)
	{
		delete pair.second;
	}
	tables.clear();
}
