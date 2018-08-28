/*
* This file is part of the PX series horticulture appliance codebase (https://github.com/atsteen/PrimeBox).
* Copyright (c) 2017-2018 Sound Venture Group LLC.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "..\include\ComponentModule_Imp_NvMemoryManager_Win32.h"

#if defined(TARGET_PLAT_WIN32)

ComponentModule_Imp_NvMemoryManager_Win32::ComponentModule_Imp_NvMemoryManager_Win32()
{
	// writes persistent data to file, ensure directory exists
	string cmdStr = "mkdir " + _persistentDataItemFileDir + " > nul 2>&1"; //supress output, including errors
	system(cmdStr.c_str());

	//build the map
	_persistentDataAliasNameMap[PersistentDataAlias::NOT_SET] = "UNKNOWN_PERSISTENT_DATA";

	//Env settings data alias
	_persistentDataAliasNameMap[PersistentDataAlias::LIGHTS_STATE_AUTO_CYCLE] = "LIGHTS_STATE_AUTO_CYCLE";
	_persistentDataAliasNameMap[PersistentDataAlias::ALARM_LOGFULL_STATE] = "ALARM_LOGFULL_STATE";
	_persistentDataAliasNameMap[PersistentDataAlias::EXHAUST_FANS_STATE_DUTY_CYCLE_DAY] = "EXHAUST_FANS_STATE_DUTY_CYCLE_DAY";
	_persistentDataAliasNameMap[PersistentDataAlias::EXHAUST_FANS_STATE_DUTY_CYCLE_NIGHT] = "EXHAUST_FANS_STATE_DUTY_CYCLE_NIGHT";
	_persistentDataAliasNameMap[PersistentDataAlias::EXHAUST_FANS_STATE_DUTY_CYCLE_DURATION] = "EXHAUST_FANS_STATE_DUTY_CYCLE_DURATION";
	_persistentDataAliasNameMap[PersistentDataAlias::EXHAUST_FANS_STATE_AUTO_CYCLE] = "EXHAUST_FANS_STATE_AUTO_CYCLE";
	_persistentDataAliasNameMap[PersistentDataAlias::CIRCULATION_FANS_STATE_DUTY_CYCLE_DAY] = "CIRCULATION_FANS_STATE_DUTY_CYCLE_DAY";
	_persistentDataAliasNameMap[PersistentDataAlias::CIRCULATION_FANS_STATE_DUTY_CYCLE_NIGHT] = "CIRCULATION_FANS_STATE_DUTY_CYCLE_NIGHT";
	_persistentDataAliasNameMap[PersistentDataAlias::CIRCULATION_FANS_STATE_DUTY_CYCLE_DURATION] = "CIRCULATION_FANS_STATE_DUTY_CYCLE_DURATION";
	_persistentDataAliasNameMap[PersistentDataAlias::CIRCULATION_FANS_STATE_AUTO_CYCLE] = "CIRCULATION_FANS_STATE_AUTO_CYCLE";
	_persistentDataAliasNameMap[PersistentDataAlias::ALARM_THRESHOLD_OVER_TEMP] = "ALARM_THRESHOLD_OVER_TEMP";
	_persistentDataAliasNameMap[PersistentDataAlias::ALARM_THRESHOLD_OVER_RH] = "ALARM_THRESHOLD_OVER_RH";
	_persistentDataAliasNameMap[PersistentDataAlias::LIGHTS_STATE_AUTO_SUNRISE] = "LIGHTS_STATE_AUTO_SUNRISE";
	_persistentDataAliasNameMap[PersistentDataAlias::LIGHTS_STATE_AUTO_SUNSET] = "LIGHTS_STATE_AUTO_SUNSET";

	//Task settings data alias
	_persistentDataAliasNameMap[PersistentDataAlias::SCHEDULED_TASK_POOL] = "SCHEDULED_TASK_POOL";

	//System settings data alias
	_persistentDataAliasNameMap[PersistentDataAlias::SYSTEM_SKU] = "SYSTEM_SKU";

	//PowerRelay items
	_persistentDataAliasNameMap[PersistentDataAlias::POWER_RELAY_STATE_CHANNEL_A] = "POWER_RELAY_STATE_CHANNEL_A";
	_persistentDataAliasNameMap[PersistentDataAlias::POWER_RELAY_STATE_CHANNEL_B] = "POWER_RELAY_STATE_CHANNEL_B";
	_persistentDataAliasNameMap[PersistentDataAlias::POWER_RELAY_STATE_CHANNEL_C] = "POWER_RELAY_STATE_CHANNEL_C";
	_persistentDataAliasNameMap[PersistentDataAlias::POWER_RELAY_STATE_CHANNEL_D] = "POWER_RELAY_STATE_CHANNEL_D";
}

ComponentModule_Imp_NvMemoryManager_Win32::~ComponentModule_Imp_NvMemoryManager_Win32(){}

bool ComponentModule_Imp_NvMemoryManager_Win32::DoSelfDiagnostic_Imp()
{
	ofstream fout(_persistentDataItemFileName);

	if (fout.is_open() && fout.good())
	{
		fout.close();
		return true;
	}

	fout.close();
	return false;
}

bool ComponentModule_Imp_NvMemoryManager_Win32::ReadPersistentItem(bool * dataItem, const PersistentDataAlias alias)
{
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	string line;
	vector<string> vec;

	if (address >= 0)
	{
		ifstream ifs(relativeFilePath);
		while (getline(ifs, line))
		{
			SsTokens(line, ',', &vec);

			if (vec.size() < 2) { continue; }
			if (std::stoi(vec[0]) == address)
			{
				if (vec[1] == "1") { *dataItem = true; }
				else { *dataItem = false; }
				return true;
			}
		}
	}

	return false;
}

bool ComponentModule_Imp_NvMemoryManager_Win32::ReadPersistentItem(int * dataItem, const PersistentDataAlias alias)
{
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	string line;
	vector<string> vec;

	if (address >= 0)
	{
		ifstream ifs(relativeFilePath);
		while (getline(ifs, line))
		{
			SsTokens(line, ',', &vec);

			if (vec.size() < 2) { continue; }
			if (std::stoi(vec[0]) == address)
			{
				*dataItem = std::stoi(vec[1]);
				return true;
			}
		}
	}

	return false;
}

bool ComponentModule_Imp_NvMemoryManager_Win32::ReadPersistentItem(TimeSignature * dataItem, const PersistentDataAlias alias)
{
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	string line;
	vector<string> vec;

	if (address >= 0)
	{
		ifstream ifs(relativeFilePath);
		while (getline(ifs, line))
		{
			SsTokens(line, ',', &vec);

			if (vec.size() < 2) { continue; }

			if (std::stoi(vec[0]) == address)
			{
				string timeSigStr = vec[1];
				SsTokens(timeSigStr, ':', &vec);

				if (vec.size() < 3) { return false; }

				dataItem->SetSignature(
					dataItem->year(),
					dataItem->month(),
					dataItem->day(),
					std::stoi(vec[0]),
					std::stoi(vec[1]),
					std::stoi(vec[2])
				);

				return true;
			}
		}
	}

	return false;
}

bool ComponentModule_Imp_NvMemoryManager_Win32::ReadPersistentItem(SystemSKU * dataItem, const PersistentDataAlias alias)
{
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	string line;
	vector<string> vec;

	if (address >= 0)
	{
		ifstream ifs(relativeFilePath);
		while (getline(ifs, line))
		{
			SsTokens(line, ',', &vec);

			if (vec.size() < 2) { continue; }

			if (std::stoi(vec[0]) == address)
			{
				string timeSigStr = vec[1];
				SsTokens(timeSigStr, '-', &vec);

				if (vec.size() < 3) { return false; }

				dataItem->platform = vec[0][0];
				dataItem->model = vec[1][0];
				dataItem->version = vec[2][0];

				return true;
			}
		}
	}

	return false;
}

bool ComponentModule_Imp_NvMemoryManager_Win32::ReadPersistentItem(PowerRelayStateData * dataItem, const PersistentDataAlias alias)
{
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	string line;
	vector<string> vec, vec2;

	if (address >= 0)
	{
		ifstream ifs(relativeFilePath);
		while (getline(ifs, line))
		{
			SsTokens(line, ',', &vec);

			if (vec.size() < 2) { continue; }

			if (std::stoi(vec[0]) == address)
			{
				SsTokens(vec[1], '-', &vec2);

				if (vec2.size() < 3) { return false; }

				dataItem->association.typeAssociation = (ComponentTypeAssociation)std::stoi(vec2[0]);
				dataItem->association.groupAssociation = (ComponentGroupAssociation)std::stoi(vec2[1]);
				dataItem->powerState = (ComponentPowerState)std::stoi(vec2[2]);
				return true;
			}
		}
	}

	return false;
}

bool ComponentModule_Imp_NvMemoryManager_Win32::ReadPersistentItem(ScheduledTaskDetail taskDetailCollection[SCHEDULED_TASK_DETAIL_COUNT], const PersistentDataAlias alias)
{
	int address = _persistentDataMap.GetAddress(taskDetailCollection, alias);
	string line;
	vector<string> schTskDetailsVec; //#(address) |,| n(#(relayIndex)_#(typeAcssiciation)_#(groupAssociation)@HH:MM:SS_#(taskAlias)_#(isEnabled)) |,| <AliasName>
	vector<string> schTskDetailVec; //n(#(relayIndex)_#(typeAcssiciation)_#(groupAssociation)@HH:MM:SS_#(taskAlias)_#(isEnabled))
	vector<string> singleSchTskDetailVec; //#(relayIndex)_#(typeAcssiciation)_#(groupAssociation) |@| HH:MM:SS_#(taskAlias)_#(isEnabled)
	vector<string> schTskDetailTargetVec; //#(address), #(relayIndex)-#(typeAcssiciation)-#(groupAssociation)
	vector<string> schTskDetailActionVec; //HH:MM:SS_#(taskAlias)_#(isEnabled)_
	vector<string> schTskDetailTimeVec; //HH:MM:SS

	for (int i = 0; i < SCHEDULED_TASK_DETAIL_COUNT; i++)
	{
		taskDetailCollection[i].ClearTaskDetailData();
	}

	if (address >= 0)
	{
		ifstream ifs(relativeFilePath);
		while (getline(ifs, line))
		{
			SsTokens(line, ',', &schTskDetailsVec);
			if (schTskDetailsVec.size() < 3) { continue; }

			if (std::stoi(schTskDetailsVec[0]) == address && !schTskDetailsVec[1].empty())
			{				
				int taskDetailIndex = 0;
				SsTokens(schTskDetailsVec[1], ' ', &schTskDetailVec);

				for (vector<string>::iterator it = schTskDetailVec.begin(); it != schTskDetailVec.end(); ++it)
				{
					SsTokens(*it, '@', &singleSchTskDetailVec);
					SsTokens(singleSchTskDetailVec[0], '_', &schTskDetailTargetVec);
					SsTokens(singleSchTskDetailVec[1], '_', &schTskDetailActionVec);
					

					bool taskDetailIsEnabled;
					SsTokens(schTskDetailActionVec[0], ':', &schTskDetailTimeVec);

					if (schTskDetailTimeVec.size() < 3) { continue; }

					TimeSignature taskTime{
						0,
						0, 
						0,
						static_cast<uint8_t>(std::stoi(schTskDetailTimeVec[0])),
						static_cast<uint8_t>(std::stoi(schTskDetailTimeVec[1])),
						static_cast<uint8_t>(std::stoi(schTskDetailTimeVec[2]))
					};

					istringstream(schTskDetailActionVec[2]) >> taskDetailIsEnabled;

					int relayIndex = std::stoi(schTskDetailTargetVec[0]);
					ComponentAssociation association;
					association.typeAssociation = (ComponentTypeAssociation)std::stoi(schTskDetailTargetVec[1]);
					association.groupAssociation = (ComponentGroupAssociation)std::stoi(schTskDetailTargetVec[2]);
					TaskAlias taskAlias = (TaskAlias)std::stoi(schTskDetailActionVec[1]);

					taskDetailCollection[taskDetailIndex].SetScheduledTaskrelayIndex(&relayIndex);
					taskDetailCollection[taskDetailIndex].SetScheduledTaskrelayAssociation(&association);
					taskDetailCollection[taskDetailIndex].SetScheduledTaskExecutionTime(&taskTime);
					taskDetailCollection[taskDetailIndex].SetScheduledTaskAlias(&taskAlias);
					taskDetailCollection[taskDetailIndex].SetScheduledTaskEnabledState(&taskDetailIsEnabled);

					++taskDetailIndex;
				}

				return true;
			}
		}
	}

	return false;
}

bool ComponentModule_Imp_NvMemoryManager_Win32::WritePersistentItem(const bool * dataItem, const PersistentDataAlias alias)
{
	bool madeEdit = false;	
	ostringstream outStr, appendStream;
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	string line;
	vector<string> vec;

	if (address >= 0)
	{
		ifstream ifs(relativeFilePath);
		while (getline(ifs, line))
		{
			SsTokens(line, ',', &vec);

			if (vec.size() < 2) { continue; }
			if (std::stoi(vec[0]) == address)
			{
				outStr << address << "," << *dataItem << "," << _persistentDataAliasNameMap[alias] << '\n';
				madeEdit = true;
			}
			else{ outStr << line << '\n'; }
		}

		if (madeEdit) //inline edit, truncate existing and rewrite edited contents
		{
			OverwritePersistentData(outStr.str());
		}
		else //wasnt found, append instead or re-write
		{
			appendStream << address << "," << *dataItem << "," << _persistentDataAliasNameMap[alias] << '\n';
			AppendPersistentData(appendStream.str());
		}

		return true;
	}

	return false;
}

bool ComponentModule_Imp_NvMemoryManager_Win32::WritePersistentItem(const int * dataItem, const PersistentDataAlias alias)
{
	bool madeEdit = false;
	ostringstream outStr, appendStream;
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	string line;
	vector<string> vec;

	if (address >= 0)
	{
		ifstream ifs(relativeFilePath);
		while (getline(ifs, line))
		{
			SsTokens(line, ',', &vec);

			if (vec.size() < 2) { continue; }
			if (std::stoi(vec[0]) == address)
			{
				outStr << address << "," << *dataItem << "," << _persistentDataAliasNameMap[alias] << '\n';
				madeEdit = true;
			}
			else { outStr << line << '\n'; }
		}

		if (madeEdit) //inline edit, truncate existing and rewrite edited contents
		{
			OverwritePersistentData(outStr.str());
		}
		else //wasnt found, append instead or re-write
		{
			appendStream << address << "," << *dataItem << "," << _persistentDataAliasNameMap[alias] << '\n';
			AppendPersistentData(appendStream.str());
		}

		return true;
	}

	return false;
}

bool ComponentModule_Imp_NvMemoryManager_Win32::WritePersistentItem(const TimeSignature * dataItem, const PersistentDataAlias alias)
{
	bool madeEdit = false;
	ostringstream outStr, appendStream;
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	string line;
	vector<string> vec;

	if (address >= 0)
	{
		ifstream ifs(relativeFilePath);
		while (getline(ifs, line))
		{
			SsTokens(line, ',', &vec);

			if (vec.size() < 2) { continue; }
			if (std::stoi(vec[0]) == address)
			{
				outStr << address << "," << (int)dataItem->hour() << ":" << (int)dataItem->minute() << ":" << (int)dataItem->day() << "," << _persistentDataAliasNameMap[alias] << '\n';
				madeEdit = true;
			}
			else { outStr << line << '\n'; }
		}

		if (madeEdit) //inline edit, truncate existing and rewrite edited contents
		{
			OverwritePersistentData(outStr.str());
		}
		else //wasnt found, append instead or re-write
		{
			appendStream << address << "," << (int)dataItem->hour() << ":" << (int)dataItem->minute() << ":" << (int)dataItem->day() << "," << _persistentDataAliasNameMap[alias] << '\n';
			AppendPersistentData(appendStream.str());
		}

		return true;
	}

	return false;
}

bool ComponentModule_Imp_NvMemoryManager_Win32::WritePersistentItem(const SystemSKU * dataItem, const PersistentDataAlias alias)
{
	bool madeEdit = false;
	ostringstream outStr, appendStream;
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	string line;
	vector<string> vec;

	if (address >= 0)
	{
		ifstream ifs(relativeFilePath);
		while (getline(ifs, line))
		{
			SsTokens(line, ',', &vec);

			if (vec.size() < 2) { continue; }
			if (std::stoi(vec[0]) == address)
			{
				outStr << address << "," << dataItem->platform << "-" << dataItem->model << "-" << dataItem->version << "," << _persistentDataAliasNameMap[alias] << '\n';
				madeEdit = true;
			}
			else { outStr << line << '\n'; }
		}

		if (madeEdit) //inline edit, truncate existing and rewrite edited contents
		{
			OverwritePersistentData(outStr.str());
		}
		else //wasnt found, append instead or re-write
		{
			appendStream << address << "," << dataItem->platform << "-" << dataItem->model << "-" << dataItem->version << "," << _persistentDataAliasNameMap[alias] << '\n';
			AppendPersistentData(appendStream.str());
		}

		return true;
	}

	return false;
}

bool ComponentModule_Imp_NvMemoryManager_Win32::WritePersistentItem(const PowerRelayStateData * dataItem, const PersistentDataAlias alias)
{
	bool madeEdit = false;
	ostringstream outStr, appendStream;
	int address = _persistentDataMap.GetAddress(*dataItem, alias);
	string line;
	vector<string> vec;

	if (address >= 0)
	{
		ifstream ifs(relativeFilePath);
		while (getline(ifs, line))
		{
			SsTokens(line, ',', &vec);

			if (vec.size() < 2) { continue; }
			if (std::stoi(vec[0]) == address)
			{
				outStr << address << "," << dataItem->association.typeAssociation << "-" << dataItem->association.groupAssociation << "-" << (int)dataItem->powerState << "," << _persistentDataAliasNameMap[alias] << '\n';
				madeEdit = true;
			}
			else { outStr << line << '\n'; }
		}

		if (madeEdit) //inline edit, truncate existing and rewrite edited contents
		{
			OverwritePersistentData(outStr.str());
		}
		else //wasnt found, append instead or re-write
		{
			//todo... the following line is poor code planning... refactor
			appendStream << address << "," << dataItem->association.typeAssociation << "-" << dataItem->association.groupAssociation << "-" << (int)dataItem->powerState << "," << _persistentDataAliasNameMap[alias] << '\n';
			AppendPersistentData(appendStream.str());
		}

		return true;
	}

	return false;
}

bool ComponentModule_Imp_NvMemoryManager_Win32::WritePersistentItem(const ScheduledTaskDetail taskDetailCollection[SCHEDULED_TASK_DETAIL_COUNT], const PersistentDataAlias alias)
{
	//#(relayIndex)_#(typeAcssiciation)_#(groupAssociation)@HH:MM:SS_#(taskAlias)_#(isEnabled)_

	bool madeEdit = false;
	ostringstream outStr, sTaskStr, appendStream;
	int address = _persistentDataMap.GetAddress(taskDetailCollection, alias);
	string line;
	vector<string> vec;

	if (address >= 0)
	{
		for (int i = 0; i < SCHEDULED_TASK_DETAIL_COUNT; ++i)
		{
			ScheduledTaskDetail sDetail = taskDetailCollection[i];
			TaskAlias alias = *sDetail.GetScheduledTaskAlias();

			if (alias != TASKALIAS_NOT_SET)
			{
				if (i > 0) { sTaskStr << ' '; }
				sTaskStr << (int)*sDetail.GetScheduledTaskrelayIndex() << "_" << (int)sDetail.GetScheduledTaskrelayAssociation()->typeAssociation << "_" << (int)sDetail.GetScheduledTaskrelayAssociation()->groupAssociation << "@";
				sTaskStr << (int)sDetail.GetScheduledTaskExecutionTime()->hour() << ":" << (int)sDetail.GetScheduledTaskExecutionTime()->minute() << ":" << (int)sDetail.GetScheduledTaskExecutionTime()->second() << "_";
				sTaskStr << (int)alias << "_" << *sDetail.GetScheduledTaskEnabledState();
			}
		}

		//if (sTaskStr.str().empty()) { return false; }

		ifstream ifs(relativeFilePath);
		while (getline(ifs, line))
		{
			SsTokens(line, ',', &vec);

			if (vec.size() < 2) { continue; }
			if (std::stoi(vec[0]) == address)
			{
				outStr << address << "," << sTaskStr.str() << "," << _persistentDataAliasNameMap[alias] << '\n';
				madeEdit = true;
			}
			else { outStr << line << '\n'; }
		}

		if (madeEdit) //inline edit, truncate existing and rewrite edited contents
		{
			OverwritePersistentData(outStr.str());
		}
		else //wasnt found, append instead or re-write
		{
			appendStream << address << "," << sTaskStr.str() << "," << _persistentDataAliasNameMap[alias] << '\n';
			AppendPersistentData(appendStream.str());
		}

		return true;
	}

	return false;
}

void ComponentModule_Imp_NvMemoryManager_Win32::SsTokens(const string str, const char delim, vector<string> * vecPtr)
{
	vecPtr->clear();
	string token;
	std::istringstream iss(str);

	while (getline(iss, token, delim))
	{
		vecPtr->push_back(token);
	}
}

void ComponentModule_Imp_NvMemoryManager_Win32::AppendPersistentData(const string appendStr)
{
	ofstream _ofile;
	_ofile.open(relativeFilePath, ios::out | ios::app);
	_ofile << appendStr;
	_ofile.close();
}

void ComponentModule_Imp_NvMemoryManager_Win32::OverwritePersistentData(const string overwriteStr)
{
	ofstream _ofile;
	_ofile.open(relativeFilePath, ios::out | ios::trunc);
	_ofile << overwriteStr;
	_ofile.close();
}

#endif