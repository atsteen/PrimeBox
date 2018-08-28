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

#pragma once
#include "ViewstateAlias.h"
#include "SelectableViewstateElementAlias.h"
#include "SharedInterface\IDynamicData.h"

// primary template, should not be instantiated unless T_DynamicDataProxy is created using a type that is not specialized
template <class C, typename T>
class T_DynamicDataProxy : public IDynamicData
{
public:

	using getFunc_t = const T * const (C::*)(void);
	using setFunc_t = void(C::*)(const T * const);

	T_DynamicDataProxy(
		const ViewstateAlias returnViewstate,
		const SelectableViewstateElementAlias returnViewstateSelectedElement,
		const ViewstateStringAlias dynamicPromptTitle,
		const char * suffixSymbol,
		getFunc_t getFunct,
		setFunc_t setFunct,
		C * obj)
	:
		_returnViewstate(returnViewstate),
		_returnViewstateSelectedElement(returnViewstateSelectedElement),
		_suffixSymbol(suffixSymbol),
		_dynamicPromptTitle(dynamicPromptTitle),
		_getDynamicData(getFunct),
		_setDynamicData(setFunct),
		_obj(obj)
	{}

	virtual bool * const getDynamicBoolValue() override { return nullptr; }//todo... throw primary template usage exception
	virtual int * const getDynamicNumericValue() override { return nullptr; }//todo... throw primary template usage exception
	virtual TimeSignature * const getDynamicTimeValue() override { return nullptr; }//todo... throw primary template usage exception
	virtual const ViewstateStringAlias getDynamicPromptTitle() { return ViewstateStringAlias::EVENT_TEXT_NOT_SET; }
	virtual const char * getPromptValueSuffix() override { return _suffixSymbol; }
	virtual const ViewstateAlias getReturnViewstate() override { return _returnViewstate; }
	virtual const SelectableViewstateElementAlias getReturnSelectedElement() override { return _returnViewstateSelectedElement; }
	virtual void commit() override {}//todo... throw primary template usage exception;

private:
	const ViewstateAlias _returnViewstate;
	const SelectableViewstateElementAlias _returnViewstateSelectedElement;
	const char * _suffixSymbol;
	const ViewstateStringAlias _dynamicPromptTitle;
	T _tempDynamicDataValue;
	getFunc_t _getDynamicData;
	setFunc_t _setDynamicData;
	C * _obj;
};

// Int specialization
template <class C>
class T_DynamicDataProxy<C,int> : public IDynamicData
{
public:

	using getFunc_t = const int * const (C::*)(void);
	using setFunc_t = void(C::*)(const int * const);

	T_DynamicDataProxy(
		const ViewstateAlias returnViewstate,
		const SelectableViewstateElementAlias returnViewstateSelectedElement,
		const ViewstateStringAlias dynamicPromptTitle,
		const char * suffixSymbol,
		getFunc_t getFunct,
		setFunc_t setFunct,
		C * obj)
		:
		_returnViewstate(returnViewstate),
		_returnViewstateSelectedElement(returnViewstateSelectedElement),
		_dynamicPromptTitle(dynamicPromptTitle),
		_suffixSymbol(suffixSymbol),
		_getDynamicData(getFunct),
		_setDynamicData(setFunct),
		_obj(obj)
	{
		_tempDynamicDataValue = *(_obj->*_getDynamicData)();
	}

	virtual bool * const getDynamicBoolValue() override { return nullptr; }
	virtual int * const getDynamicNumericValue() override { return &_tempDynamicDataValue; }
	virtual TimeSignature * const getDynamicTimeValue() override { return nullptr; }
	virtual const ViewstateStringAlias getDynamicPromptTitle() { return _dynamicPromptTitle; }
	virtual const char * getPromptValueSuffix() override { return _suffixSymbol; }
	virtual const ViewstateAlias getReturnViewstate() override { return _returnViewstate; }
	virtual const SelectableViewstateElementAlias getReturnSelectedElement() override { return _returnViewstateSelectedElement; }
	virtual void commit() override { (_obj->*_setDynamicData)(&_tempDynamicDataValue); }

private:
	const ViewstateAlias _returnViewstate;
	const SelectableViewstateElementAlias _returnViewstateSelectedElement;
	const ViewstateStringAlias _dynamicPromptTitle;
	const char * _suffixSymbol;
	int _tempDynamicDataValue;
	getFunc_t _getDynamicData;
	setFunc_t _setDynamicData;
	C * _obj;
};

// bool specialization
template <class C>
class T_DynamicDataProxy<C, bool> : public IDynamicData
{
public:

	using getFunc_t = const bool * const (C::*)(void);
	using setFunc_t = void(C::*)(const bool * const);

	T_DynamicDataProxy(
		const ViewstateAlias returnViewstate,
		const SelectableViewstateElementAlias returnViewstateSelectedElement,
		const ViewstateStringAlias dynamicPromptTitle,
		const char * suffixSymbol,
		getFunc_t getFunct,
		setFunc_t setFunct,
		C * obj)
		:
		_returnViewstate(returnViewstate),
		_returnViewstateSelectedElement(returnViewstateSelectedElement),
		_dynamicPromptTitle(dynamicPromptTitle),
		_suffixSymbol(suffixSymbol),
		_getDynamicData(getFunct),
		_setDynamicData(setFunct),
		_obj(obj)
	{
		_tempDynamicDataValue = *(_obj->*_getDynamicData)();
	}

	virtual bool * const getDynamicBoolValue() override { return &_tempDynamicDataValue; }
	virtual int * const getDynamicNumericValue() override { return nullptr; }
	virtual TimeSignature * const getDynamicTimeValue() override { return nullptr; }
	virtual const ViewstateStringAlias getDynamicPromptTitle() { return _dynamicPromptTitle; }
	virtual const char * getPromptValueSuffix() override { return _suffixSymbol; }
	virtual const ViewstateAlias getReturnViewstate() override { return _returnViewstate; }
	virtual const SelectableViewstateElementAlias getReturnSelectedElement() override { return _returnViewstateSelectedElement; }
	virtual void commit() override { (_obj->*_setDynamicData)(&_tempDynamicDataValue); }

private:
	const ViewstateAlias _returnViewstate;
	const SelectableViewstateElementAlias _returnViewstateSelectedElement;
	const ViewstateStringAlias _dynamicPromptTitle;
	const char * _suffixSymbol;
	bool _tempDynamicDataValue;
	getFunc_t _getDynamicData;
	setFunc_t _setDynamicData;
	C * _obj;
};

// TimeSignature specialization
template <class C>
class T_DynamicDataProxy<C, TimeSignature> : public IDynamicData
{
public:

	using getFunc_t = const TimeSignature * const (C::*)(void);
	using setFunc_t = void(C::*)(const TimeSignature * const);

	T_DynamicDataProxy(
		const ViewstateAlias returnViewstate,
		const SelectableViewstateElementAlias returnViewstateSelectedElement,
		const ViewstateStringAlias dynamicPromptTitle,
		const char * suffixSymbol,
		getFunc_t getFunct,
		setFunc_t setFunct,
		C * obj)
		:
		_returnViewstate(returnViewstate),
		_returnViewstateSelectedElement(returnViewstateSelectedElement),
		_dynamicPromptTitle(dynamicPromptTitle),
		_suffixSymbol(suffixSymbol),
		_getDynamicData(getFunct),
		_setDynamicData(setFunct),
		_obj(obj)
	{
		_tempDynamicDataValue = *(_obj->*_getDynamicData)();
	}

	virtual bool * const getDynamicBoolValue() override { return nullptr; }
	virtual int * const getDynamicNumericValue() override { return nullptr; }
	virtual TimeSignature * const getDynamicTimeValue() override { return &_tempDynamicDataValue; }
	virtual const ViewstateStringAlias getDynamicPromptTitle() { return _dynamicPromptTitle; }
	virtual const char * getPromptValueSuffix() override { return _suffixSymbol; }
	virtual const ViewstateAlias getReturnViewstate() override { return _returnViewstate; }
	virtual const SelectableViewstateElementAlias getReturnSelectedElement() override { return _returnViewstateSelectedElement; }
	virtual void commit() override { (_obj->*_setDynamicData)(&_tempDynamicDataValue); }

private:
	const ViewstateAlias _returnViewstate;
	const SelectableViewstateElementAlias _returnViewstateSelectedElement;
	const ViewstateStringAlias _dynamicPromptTitle;
	const char * _suffixSymbol;
	TimeSignature _tempDynamicDataValue;
	getFunc_t _getDynamicData;
	setFunc_t _setDynamicData;
	C * _obj;
};