#pragma once
#include "..\Viewstate_Element_Text.h"
#include "..\..\DataModel\DataModel_PX4.h"

class Viewstate_Element_TEMPLATE :
	public Viewstate_Element_Text
{
public:
	Viewstate_Element_Text_TEMPLATE(const int, const int);
	~Viewstate_Element_Text_TEMPLATE();

	virtual void emplace(char *, const int) override;
};