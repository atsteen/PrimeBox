#include "..\..\..\include\Viewstate_Element\Text_Elements\Viewstate_Element_Text_TEMPLATE.h"

Viewstate_Element_Text_TEMPLATE::Viewstate_Element_Text_TEMPLATE(const int start_index, const int imbricationLevel) : Viewstate_Element_Text(start_index, imbricationLevel){}
Viewstate_Element_Text_TEMPLATE::~Viewstate_Element_Text_TEMPLATE(){}

void Viewstate_Element_Text_TEMPLATE::emplace(char * target, const int targetlen)
{
	_Emplace(target, targetlen, DataModel_PX4::GetInstance().GetTEMPLATE());
}
