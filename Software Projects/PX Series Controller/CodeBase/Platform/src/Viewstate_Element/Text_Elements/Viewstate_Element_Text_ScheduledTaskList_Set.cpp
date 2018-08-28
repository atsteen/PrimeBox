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

#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_ScheduledTaskList_Set.h"

Viewstate_Element_Text_ScheduledTaskList_Set::Viewstate_Element_Text_ScheduledTaskList_Set(const int start_index, const int imbricationLevel, IModelTaskData * taskData, IModelViewstateData * viewstateData)
	: Viewstate_Element_Text(start_index, imbricationLevel, SELECTABLE_SCHEDULED_TASKLIST_SET_ELEMENT), _taskData(taskData), _viewstateData(viewstateData){}

Viewstate_Element_Text_ScheduledTaskList_Set::~Viewstate_Element_Text_ScheduledTaskList_Set(){}

int Viewstate_Element_Text_ScheduledTaskList_Set::emplace(char * target, const int targetlen)
{
	//check and correct selectedListIndex against task list
	const uint8_t selectedListIndex = _viewstateData->GetViewstateSelectableElementIndex();
	const uint8_t lastTaskIndex = TASK_ITEM_POOL_SIZE - _taskData->GetFreeScheduledTaskDetailCount() - 1;
	if (selectedListIndex > lastTaskIndex) { _viewstateData->SetViewstateSelectableElementIndex(lastTaskIndex); }
	
	uint8_t emplacedChars = 0;
	
	if (selectedListIndex < 3)
	{
		//dynamically emplace first three ScheduledTaskDetails using Viewstate_Element_Text_ScheduledTaskList_Set_Row
		for (int i = 0; i < 3; i++)
		{
			ScheduledTaskDetail * taskDetail = _taskData->GetScheduledTaskDetailByIndex(i);
			if (*taskDetail->GetScheduledTaskAlias() == TASKALIAS_NOT_SET) { break; }
			else
			{
				Viewstate_Element_Text_ScheduledTaskList_Set_Row listRowVE_ScheduledTask(_startIndex + i*21, 1, taskDetail);
				if (i == selectedListIndex && _viewstateData->GetNavigationMap()->CurrentSelection()->selectedElement == SELECTABLE_ELEMENT_DYNAMIC)
				{//If current selectable element is SELECTABLE_ELEMENT_DYNAMIC, _selectArrowRight.emplaceLeft of listSelectIndex row
					Viewstate_Element_Text_SelectArrowRight selectArrow(-1, 1);
					emplacedChars += selectArrow.emplaceLeft(target, targetlen, &listRowVE_ScheduledTask);
				}
				
				emplacedChars += listRowVE_ScheduledTask.emplace(target, targetlen);
			}
		}			
	}
	else
	{		
		//dynamically emplace block of up to four ScheduledTaskDetails using Viewstate_Element_Text_ScheduledTaskList_Set_Row
		for (int i = (((selectedListIndex + 1)/4) * 4) -1; i < (((selectedListIndex + 1) / 4) * 4) + 3; ++i) //todo... yikes that is fugly
		{
			ScheduledTaskDetail * taskDetail = _taskData->GetScheduledTaskDetailByIndex(i);
			if (*taskDetail->GetScheduledTaskAlias() == TASKALIAS_NOT_SET) { break; }
			else
			{
				Viewstate_Element_Text_ScheduledTaskList_Set_Row listRowVE_ScheduledTask(_startIndex + (((i+1)%4) * 21), 1, taskDetail);
				if (i == selectedListIndex && _viewstateData->GetNavigationMap()->CurrentSelection()->selectedElement == SELECTABLE_ELEMENT_DYNAMIC)
				{//If current selectable element is SELECTABLE_ELEMENT_DYNAMIC, _selectArrowRight.emplaceLeft of listSelectIndex row
					Viewstate_Element_Text_SelectArrowRight selectArrow(-1, 1);
					emplacedChars += selectArrow.emplaceLeft(target, targetlen, &listRowVE_ScheduledTask);
				}
				
				emplacedChars += listRowVE_ScheduledTask.emplace(target, targetlen);
			}
		}
	}

	return emplacedChars;
}
