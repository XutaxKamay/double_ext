/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod Double Extension
 * Copyright (C) 2004-2008 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#include "extension.h"
#include "IHandleSys.h"
#include "smsdk_ext.h"
#include <cmath>
#include <string>
#include <limits>

HandleType_t g_DoubleType = 0;


/**
 * @file extension.cpp
 * @brief Implement extension code here.
 */

Double g_Double; /**< Global singleton for extension's main interface */

const sp_nativeinfo_t g_DoubleNatives[] = 
{
	{"Double.IsNaN.get",		native_DoubleIsNaN},
	{"Double.Double",			native_DoubleConstructor},
	{"Double.FromString",		native_DoubleFromString},
	{"Double.FromFloat",		native_DoubleFromFloat},
	{"Double.FromInt",			native_DoubleFromInt},
	{"Double.ToString",			native_DoubleToString},
	{"Double.ToInt",			native_DoubleToInt},
	{"Double.ToFloat",			native_DoubleToFloat},
	{"Double.GreaterThan",		native_DoubleGreaterThan},
	{"Double.LessThan",			native_DoubleLessThan},
	{"Double.EqualTo",			native_DoubleEqualTo},
	{"Double.Clone",			native_DoubleClone},
	{"Double.AbsoluteRef",		native_DoubleAbsoluteRef},
	{"Double.Absolute",			native_DoubleAbsolute},
	{"Double.ModuloRef",		native_DoubleModuloRef},
	{"Double.Modulo",			native_DoubleModulo},
	{"Double.AddRef",			native_DoubleAddRef},
	{"Double.Add",				native_DoubleAdd},
	{"Double.SubtractRef",		native_DoubleSubtractRef},
	{"Double.Subtract",			native_DoubleSubtract},
	{"Double.MultiplyRef",		native_DoubleMultiplyRef},
	{"Double.Multiply",			native_DoubleMultiply},
	{"Double.DivideRef",		native_DoubleDivideRef},
	{"Double.Divide",			native_DoubleDivide},
	{"Double.PowRef",			native_DoublePowRef},
	{"Double.Pow",				native_DoublePow},
	{"Double.SquareRootRef",	native_DoubleSquareRootRef},
	{"Double.SquareRoot",		native_DoubleSquareRoot},
	{"Double.AtanRef",			native_DoubleAtanRef},
	{"Double.Atan",				native_DoubleAtan},
	{"Double.Atan2Ref",			native_DoubleAtan2Ref},
	{"Double.Atan2",			native_DoubleAtan2},
	{"Double.SineRef",			native_DoubleSineRef},
	{"Double.Sine",				native_DoubleSine},
	{"Double.ArcSineRef",		native_DoubleArcSineRef},
	{"Double.ArcSine",			native_DoubleArcSine},
	{"Double.TangentRef",		native_DoubleTangentRef},
	{"Double.Tangent",			native_DoubleTangent},
	{"Double.CosineRef",		native_DoubleCosineRef},
	{"Double.Cosine",			native_DoubleCosine},
	{"Double.ArcConsineRef",	native_DoubleArcCosineRef},
	{"Double.ArcConsine",		native_DoubleArcCosine},

	{"Double_IsNaN",			native_Double_IsNaN},
	{"Double_FromString",		native_Double_FromString},
	{"Double_FromFloat",		native_Double_FromFloat},
	{"Double_FromInt",			native_Double_FromInt},
	{"Double_ToString",			native_Double_ToString},
	{"Double_ToInt",			native_Double_ToInt},
	{"Double_ToFloat",			native_Double_ToFloat},
	{"Double_GreaterThan",		native_Double_GreaterThan},
	{"Double_LessThan",			native_Double_LessThan},
	{"Double_EqualTo",			native_Double_EqualTo},
	{"Double_Absolute",			native_Double_Absolute},
	{"Double_Modulo",			native_Double_Modulo},
	{"Double_Add",				native_Double_Add},
	{"Double_Subtract",			native_Double_Subtract},
	{"Double_Multiply",			native_Double_Multiply},
	{"Double_Divide",			native_Double_Divide},
	{"Double_Pow",				native_Double_Pow},
	{"Double_SquareRoot",		native_Double_SquareRoot},
	{"Double_Atan",				native_Double_Atan},
	{"Double_Atan2",			native_Double_Atan2},
	{"Double_Sine",				native_Double_Sine},
	{"Double_ArcSine",			native_Double_ArcSine},
	{"Double_Tangent",			native_Double_Tangent},
	{"Double_Cosine",			native_Double_Cosine},
	{"Double_ArcConsine",		native_Double_ArcCosine},

	{nullptr,					nullptr},
};

bool Double::SDK_OnLoad(char *error, size_t maxlen, bool late)
{
	HandleError err;
	g_DoubleType = handlesys->CreateType("Double", this, 0, nullptr, nullptr, myself->GetIdentity(), &err);

	if (g_DoubleType == 0)
	{
		snprintf(error, maxlen, "Could not create Double handle type (err: %d)", err);
	}

	sharesys->AddNatives(myself, g_DoubleNatives);
	sharesys->RegisterLibrary(myself, "double_ext");

	return true;
}

void Double::OnHandleDestroy(HandleType_t type, void *object)
{
	if (type == g_DoubleType)
	{
		delete static_cast<pdouble_t>(object);
	}
}

cell_t Double::CreateHandle(IPluginContext* const pContext, pdouble_t value)
{
	auto pDouble = new double;

	if (value)
	{
		*pDouble = *value;
	}

	HandleError handleError;
	auto handle = handlesys->CreateHandle(g_DoubleType, pDouble, pContext->GetIdentity(), myself->GetIdentity(), &handleError);

	if (handle == BAD_HANDLE)
	{
		delete pDouble;
		return pContext->ThrowNativeError("Cannot create double handle (err: %d)", handleError);
	}

	return static_cast<cell_t>(handle);
}

HandleError Double::ReadHandle(IPluginContext* const pContext, const Handle_t& handle, pdouble_t* value)
{
	HandleSecurity security(pContext->GetIdentity(), myself->GetIdentity());

	return handlesys->ReadHandle(handle, g_DoubleType, &security, reinterpret_cast<void**>(value));
}

double Double::ReadArray(IPluginContext *const pContext, const cell_t param)
{
	cell_t *value;
	pContext->LocalToPhysAddr(param, &value);

	double returnValue;
	memcpy(&returnValue, value, sizeof(double));

	return returnValue;
}

void Double::ToArray(IPluginContext *const pContext, const cell_t param, double value)
{
	cell_t *address;
	pContext->LocalToPhysAddr(param, &address);

	memcpy(address, &value, sizeof(double));
}

cell_t native_DoubleConstructor(IPluginContext *pContext, const cell_t *)
{
	return Double::CreateHandle(pContext);
}

cell_t native_DoubleFromString(IPluginContext *pContext, const cell_t *params)
{
	char *str;
	pContext->LocalToString(params[1], &str);

	auto value = std::atof(str);

	return Double::CreateHandle(pContext, &value);
}

cell_t native_DoubleFromFloat(IPluginContext *pContext, const cell_t *params)
{
	auto value = static_cast<double>(sp_ctof(params[1]));
	
	return Double::CreateHandle(pContext, &value);
}

cell_t native_DoubleFromInt(IPluginContext *pContext, const cell_t *params)
{
	auto value = static_cast<double>(params[1]);

	return Double::CreateHandle(pContext, &value);
}

cell_t native_DoubleIsNaN(IPluginContext *pContext, const cell_t *params)
{
	auto handle = static_cast<Handle_t>(params[1]);

	pdouble_t value;

	auto err = Double::ReadHandle(pContext, handle, &value);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading double handle (err: %d)", err);
	}

	return std::isnan(*value) || std::isinf(*value);
}

cell_t native_DoubleToString(IPluginContext *pContext, const cell_t *params)
{
	auto handle = static_cast<Handle_t>(params[1]);

	pdouble_t value;
	auto err = Double::ReadHandle(pContext, handle, &value);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading double handle (err: %d)", err);
	}

	char* str;
	pContext->LocalToString(params[2], &str);

	auto maxlen = static_cast<size_t>(params[3]);

	char format[16];
	snprintf(format, 16, "%%.%if", params[4]);

	snprintf(str, maxlen, format, *value);

	return static_cast<cell_t>(handle);
}

cell_t native_DoubleToInt(IPluginContext *pContext, const cell_t *params)
{
	auto handle = static_cast<Handle_t>(params[1]);

	pdouble_t value;
	auto err = Double::ReadHandle(pContext, handle, &value);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading double handle (err: %d)", err);
	}

	return static_cast<int>(*value);
}

cell_t native_DoubleToFloat(IPluginContext *pContext, const cell_t *params)
{
	auto handle = static_cast<Handle_t>(params[1]);

	pdouble_t value;
	auto err = Double::ReadHandle(pContext, handle, &value);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading double handle (err: %d)", err);
	}

	return sp_ftoc(static_cast<float>(*value));
}

cell_t native_DoubleGreaterThan(IPluginContext *pContext, const cell_t *params)
{
	auto handleLeft = static_cast<Handle_t>(params[1]);
	auto handleRight = static_cast<Handle_t>(params[2]);

	pdouble_t valueLeft, valueRight;

	auto errLeft = Double::ReadHandle(pContext, handleLeft, &valueLeft);
	auto errRight = Double::ReadHandle(pContext, handleRight, &valueRight);

	if (errLeft != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading left double handle (err: %d)", errLeft);
	}

	if (errLeft != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading right double handle (err: %d)", errRight);
	}

	return *valueLeft > *valueRight;
}

cell_t native_DoubleLessThan(IPluginContext *pContext, const cell_t *params)
{
	auto handleLeft = static_cast<Handle_t>(params[1]);
	auto handleRight = static_cast<Handle_t>(params[2]);

	pdouble_t valueLeft, valueRight;

	auto errLeft = Double::ReadHandle(pContext, handleLeft, &valueLeft);
	auto errRight = Double::ReadHandle(pContext, handleRight, &valueRight);

	if (errLeft != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading left double handle (err: %d)", errLeft);
	}

	if (errLeft != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading right double handle (err: %d)", errRight);
	}

	return *valueLeft < *valueRight;
}

cell_t native_DoubleEqualTo(IPluginContext *pContext, const cell_t *params)
{
	auto handleLeft = static_cast<Handle_t>(params[1]);
	auto handleRight = static_cast<Handle_t>(params[2]);

	pdouble_t valueLeft, valueRight;

	auto errLeft = Double::ReadHandle(pContext, handleLeft, &valueLeft);
	auto errRight = Double::ReadHandle(pContext, handleRight, &valueRight);

	if (errLeft != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading left double handle (err: %d)", errLeft);
	}

	if (errLeft != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading right double handle (err: %d)", errRight);
	}

	return *valueLeft == *valueRight;
}

cell_t native_DoubleClone(IPluginContext *pContext, const cell_t *params)
{
	auto handle = static_cast<Handle_t>(params[1]);

	pdouble_t value;
	auto err = Double::ReadHandle(pContext, handle, &value);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading double handle (err: %d)", err);
	}

	return Double::CreateHandle(pContext, value);
}

cell_t native_DoubleAbsoluteRef(IPluginContext *pContext, const cell_t *params)
{
	auto handle = static_cast<Handle_t>(params[1]);

	pdouble_t value;
	auto err = Double::ReadHandle(pContext, handle, &value);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading double handle (err: %d)", err);
	}

	*value = std::abs(*value);

	return static_cast<cell_t>(handle);
}

cell_t native_DoubleAbsolute(IPluginContext *pContext, const cell_t *params)
{
	auto handle = static_cast<Handle_t>(params[1]);

	pdouble_t value;
	auto err = Double::ReadHandle(pContext, handle, &value);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading double handle (err: %d)", err);
	}

	auto retValue = std::abs(*value);

	return Double::CreateHandle(pContext, &retValue);
}

cell_t native_DoubleModuloRef(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto secondHandle = static_cast<Handle_t>(params[2]);

	pdouble_t secondValue;
	err = Double::ReadHandle(pContext, secondHandle, &secondValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading second double handle (err: %d)", err);
	}

	*refValue = std::fmod(*refValue, *secondValue);

	return static_cast<cell_t>(refHandle);
}

cell_t native_DoubleModulo(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto secondHandle = static_cast<Handle_t>(params[2]);

	pdouble_t secondValue;
	err = Double::ReadHandle(pContext, secondHandle, &secondValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading second double handle (err: %d)", err);
	}

	auto retValue = std::fmod(*refValue, *secondValue);

	return Double::CreateHandle(pContext, &retValue);
}

cell_t native_DoubleAddRef(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto secondHandle = static_cast<Handle_t>(params[2]);

	pdouble_t secondValue;
	err = Double::ReadHandle(pContext, secondHandle, &secondValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading second double handle (err: %d)", err);
	}

	*refValue = *refValue + *secondValue;

	return static_cast<cell_t>(refHandle);
}

cell_t native_DoubleAdd(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto secondHandle = static_cast<Handle_t>(params[2]);

	pdouble_t secondValue;
	err = Double::ReadHandle(pContext, secondHandle, &secondValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading second double handle (err: %d)", err);
	}

	auto retValue = *refValue + *secondValue;

	return Double::CreateHandle(pContext, &retValue);
}

cell_t native_DoubleSubtractRef(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto secondHandle = static_cast<Handle_t>(params[2]);

	pdouble_t secondValue;
	err = Double::ReadHandle(pContext, secondHandle, &secondValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading second double handle (err: %d)", err);
	}

	*refValue = *refValue - *secondValue;

	return static_cast<cell_t>(refHandle);
}

cell_t native_DoubleSubtract(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto secondHandle = static_cast<Handle_t>(params[2]);

	pdouble_t secondValue;
	err = Double::ReadHandle(pContext, secondHandle, &secondValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading second double handle (err: %d)", err);
	}

	auto retValue = (*refValue - *secondValue);

	return Double::CreateHandle(pContext, &retValue);
}

cell_t native_DoubleMultiplyRef(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto secondHandle = static_cast<Handle_t>(params[2]);

	pdouble_t secondValue;
	err = Double::ReadHandle(pContext, secondHandle, &secondValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading second double handle (err: %d)", err);
	}

	*refValue = *refValue **secondValue;

	return static_cast<cell_t>(refHandle);
}

cell_t native_DoubleMultiply(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto secondHandle = static_cast<Handle_t>(params[2]);

	pdouble_t secondValue;
	err = Double::ReadHandle(pContext, secondHandle, &secondValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading second double handle (err: %d)", err);
	}

	auto retValue = (*refValue * *secondValue);

	return Double::CreateHandle(pContext, &retValue);
}

cell_t native_DoubleDivideRef(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto secondHandle = static_cast<Handle_t>(params[2]);

	pdouble_t secondValue;
	err = Double::ReadHandle(pContext, secondHandle, &secondValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading second double handle (err: %d)", err);
	}

	*refValue = *refValue / *secondValue;

	return static_cast<cell_t>(refHandle);
}

cell_t native_DoubleDivide(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto secondHandle = static_cast<Handle_t>(params[2]);

	pdouble_t secondValue;
	err = Double::ReadHandle(pContext, secondHandle, &secondValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading second double handle (err: %d)", err);
	}

	auto retValue = (*refValue / *secondValue);

	return Double::CreateHandle(pContext, &retValue);
}

cell_t native_DoublePowRef(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto secondHandle = static_cast<Handle_t>(params[2]);

	pdouble_t secondValue;
	err = Double::ReadHandle(pContext, secondHandle, &secondValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading second double handle (err: %d)", err);
	}

	*refValue = std::pow(*refValue, *secondValue);

	return static_cast<cell_t>(refHandle);
}

cell_t native_DoublePow(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto secondHandle = static_cast<Handle_t>(params[2]);

	pdouble_t secondValue;
	err = Double::ReadHandle(pContext, secondHandle, &secondValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading second double handle (err: %d)", err);
	}

	auto retValue = std::pow(*refValue, *secondValue);

	return Double::CreateHandle(pContext, &retValue);
}

cell_t native_DoubleSquareRootRef(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	*refValue = std::sqrt(*refValue);

	return static_cast<cell_t>(refHandle);
}

cell_t native_DoubleSquareRoot(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto retValue = std::sqrt(*refValue);

	return Double::CreateHandle(pContext, &retValue);
}

cell_t native_DoubleAtanRef(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	*refValue = std::atan(*refValue);

	return static_cast<cell_t>(refHandle);
}

cell_t native_DoubleAtan(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto retValue = std::atan(*refValue);

	return Double::CreateHandle(pContext, &retValue);
}

cell_t native_DoubleAtan2Ref(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto secondHandle = static_cast<Handle_t>(params[2]);

	pdouble_t secondValue;
	err = Double::ReadHandle(pContext, secondHandle, &secondValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading second double handle (err: %d)", err);
	}

	*refValue = std::atan2(*refValue, *secondValue);

	return static_cast<cell_t>(refHandle);
}

cell_t native_DoubleAtan2(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto secondHandle = static_cast<Handle_t>(params[2]);

	pdouble_t secondValue;
	err = Double::ReadHandle(pContext, secondHandle, &secondValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading second double handle (err: %d)", err);
	}

	auto retValue = std::atan2(*refValue, *secondValue);

	return Double::CreateHandle(pContext, &retValue);
}

cell_t native_DoubleSineRef(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	*refValue = std::sin(*refValue);

	return static_cast<cell_t>(refHandle);
}

cell_t native_DoubleSine(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto retValue = std::sin(*refValue);

	return Double::CreateHandle(pContext, &retValue);
}

cell_t native_DoubleArcSineRef(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	*refValue = std::asin(*refValue);

	return static_cast<cell_t>(refHandle);
}

cell_t native_DoubleArcSine(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto retValue = std::asin(*refValue);

	return Double::CreateHandle(pContext, &retValue);
}

cell_t native_DoubleTangentRef(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	*refValue = std::tan(*refValue);

	return static_cast<cell_t>(refHandle);
}

cell_t native_DoubleTangent(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto retValue = std::tan(*refValue);

	return Double::CreateHandle(pContext, &retValue);
}

cell_t native_DoubleCosineRef(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	*refValue = std::cos(*refValue);

	return static_cast<cell_t>(refHandle);
}

cell_t native_DoubleCosine(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto retValue = std::cos(*refValue);

	return Double::CreateHandle(pContext, &retValue);
}

cell_t native_DoubleArcCosineRef(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	*refValue = std::acos(*refValue);

	return static_cast<cell_t>(refHandle);
}

cell_t native_DoubleArcCosine(IPluginContext *pContext, const cell_t *params)
{
	auto refHandle = static_cast<Handle_t>(params[1]);

	pdouble_t refValue;
	auto err = Double::ReadHandle(pContext, refHandle, &refValue);

	if (err != HandleError_None)
	{
		return pContext->ThrowNativeError("Error with reading ref. double handle (err: %d)", err);
	}

	auto retValue = std::acos(*refValue);

	return Double::CreateHandle(pContext, &retValue);
}

// native bool Double_IsNaN(any double[2]);
cell_t native_Double_IsNaN(IPluginContext *pContext, const cell_t *params)
{
	double value = Double::ReadArray(pContext, params[1]);
	Double::ToArray(pContext, params[2], value);

	return (std::isnan(value) || std::isinf(value));
}

// native void Double_FromString(char[] value, any double[2]);
cell_t native_Double_FromString(IPluginContext *pContext, const cell_t *params)
{
	char *str;
	pContext->LocalToString(params[1], &str);

	double value = std::atof(str);

	Double::ToArray(pContext, params[2], value);

	return 0;
}

// native void Double_FromFloat(float value, any double[2]);
cell_t native_Double_FromFloat(IPluginContext *pContext, const cell_t *params)
{
	double value = static_cast<double>(sp_ctof(params[1]));
	Double::ToArray(pContext, params[2], value);

	return 0;
}

// native void Double_FromInt(int value, any double[2]);
cell_t native_Double_FromInt(IPluginContext *pContext, const cell_t *params)
{
	double value = static_cast<double>(params[1]);
	Double::ToArray(pContext, params[2], value);

	return 0;
}

// native void Double_ToString(any double[2], char[] buffer, int maxlen, int precision = 18);
cell_t native_Double_ToString(IPluginContext *pContext, const cell_t *params)
{
	double value = Double::ReadArray(pContext, params[1]);

	char *str;
	pContext->LocalToString(params[2], &str);

	size_t maxlen = static_cast<size_t>(params[3]);
	
	char format[16];
	snprintf(format, 16, "%%.%if", params[4]);
	snprintf(str, maxlen, format, value);

	return 0;
}

// native int Double_ToInt(any double[2]);
cell_t native_Double_ToInt(IPluginContext *pContext, const cell_t *params)
{
	double value = Double::ReadArray(pContext, params[1]);

	return static_cast<int>(value);
}

// native float Double_ToFloat(any double[2]);
cell_t native_Double_ToFloat(IPluginContext *pContext, const cell_t *params)
{
	double value = Double::ReadArray(pContext, params[1]);

	return sp_ftoc(static_cast<float>(value));
}

// native bool Double_GreaterThan(any left[2], any right[2]);
cell_t native_Double_GreaterThan(IPluginContext *pContext, const cell_t *params)
{
	double left = Double::ReadArray(pContext, params[1]);
	double right = Double::ReadArray(pContext, params[2]);

	return left > right;
}

// native bool Double_LessThan(any left[2], any right[2]);
cell_t native_Double_LessThan(IPluginContext *pContext, const cell_t *params)
{
	double left = Double::ReadArray(pContext, params[1]);
	double right = Double::ReadArray(pContext, params[2]);

	return left < right;
}

// native bool Double_EqualTo(any left[2], any right[2]);
cell_t native_Double_EqualTo(IPluginContext *pContext, const cell_t *params)
{
	double left = Double::ReadArray(pContext, params[1]);
	double right = Double::ReadArray(pContext, params[2]);

	return left == right;
}

// native void Double_Absolute(any input[2], any output[2]);
cell_t native_Double_Absolute(IPluginContext *pContext, const cell_t *params)
{
	double value = Double::ReadArray(pContext, params[1]);
	Double::ToArray(pContext, params[2], std::abs(value));

	return 0;
}

// native void Double_Modulo(any input[2], any denominator[2], any output[2]);
cell_t native_Double_Modulo(IPluginContext *pContext, const cell_t *params)
{
	double input = Double::ReadArray(pContext, params[1]);
	double denominator = Double::ReadArray(pContext, params[2]);
	Double::ToArray(pContext, params[3], std::fmod(input, denominator));

	return 0;
}

// native void Double_Add(any left[2], any right[2], any output[2]);
cell_t native_Double_Add(IPluginContext *pContext, const cell_t *params)
{
	double left = Double::ReadArray(pContext, params[1]);
	double right = Double::ReadArray(pContext, params[2]);
	Double::ToArray(pContext, params[3], left + right);

	return 0;
}

// native void Double_Subtract(any left[2], any right[2], any output[2]);
cell_t native_Double_Subtract(IPluginContext *pContext, const cell_t *params)
{
	double left = Double::ReadArray(pContext, params[1]);
	double right = Double::ReadArray(pContext, params[2]);
	Double::ToArray(pContext, params[3], left - right);

	return 0;
}

// native void Double_Multiply(any left[2], any right[2], any output[2]);
cell_t native_Double_Multiply(IPluginContext *pContext, const cell_t *params)
{
	double left = Double::ReadArray(pContext, params[1]);
	double right = Double::ReadArray(pContext, params[2]);
	Double::ToArray(pContext, params[3], left * right);

	return 0;
}

// native void Double_Divide(any left[2], any right[2], any output[2]);
cell_t native_Double_Divide(IPluginContext *pContext, const cell_t *params)
{
	double left = Double::ReadArray(pContext, params[1]);
	double right = Double::ReadArray(pContext, params[2]);
	Double::ToArray(pContext, params[3], left / right);

	return 0;
}

// native void Double_Pow(any left[2], any right[2], any output[2]);
cell_t native_Double_Pow(IPluginContext *pContext, const cell_t *params)
{
	double left = Double::ReadArray(pContext, params[1]);
	double right = Double::ReadArray(pContext, params[2]);
	Double::ToArray(pContext, params[3], std::pow(left, right));

	return 0;
}

// native void Double_SquareRoot(any input[2], any output[2]);
cell_t native_Double_SquareRoot(IPluginContext *pContext, const cell_t *params)
{
	double value = Double::ReadArray(pContext, params[1]);
	Double::ToArray(pContext, params[2], std::sqrt(value));
	
	return 0;
}

// native void Double_Atan(any input[2], any output[2]);
cell_t native_Double_Atan(IPluginContext *pContext, const cell_t *params)
{
	double value = Double::ReadArray(pContext, params[1]);
	Double::ToArray(pContext, params[2], std::atan(value));

	return 0;
}

// native void Double_Atan2(any left[2], any right[2], any output[2]);
cell_t native_Double_Atan2(IPluginContext *pContext, const cell_t *params)
{
	double left = Double::ReadArray(pContext, params[1]);
	double right = Double::ReadArray(pContext, params[2]);
	Double::ToArray(pContext, params[2], std::atan2(left, right));

	return 0;
}

// native void Double_Sine(any angle[2], any output[2]);
cell_t native_Double_Sine(IPluginContext *pContext, const cell_t *params)
{
	double value = Double::ReadArray(pContext, params[1]);
	Double::ToArray(pContext, params[2], std::sin(value));

	return 0;
}

// native void Double_ArcSine(any angle[2], any output[2]);
cell_t native_Double_ArcSine(IPluginContext *pContext, const cell_t *params)
{
	double value = Double::ReadArray(pContext, params[1]);
	Double::ToArray(pContext, params[2], std::asin(value));
	return 0;
}

// native void Double_Tangent(any angle[2], any output[2]);
cell_t native_Double_Tangent(IPluginContext *pContext, const cell_t *params)
{
	double value = Double::ReadArray(pContext, params[1]);
	Double::ToArray(pContext, params[2], std::tan(value));
	return 0;
}

// native void Double_Cosine(any angle[2], any output[2]);
cell_t native_Double_Cosine(IPluginContext *pContext, const cell_t *params)
{
	double value = Double::ReadArray(pContext, params[1]);
	Double::ToArray(pContext, params[2], std::cos(value));
	return 0;
}

// native void Double_ArcCosine(any angle[2], any output[2]);
cell_t native_Double_ArcCosine(IPluginContext *pContext, const cell_t *params)
{
	double value = Double::ReadArray(pContext, params[1]);
	Double::ToArray(pContext, params[2], std::acos(value));
	return 0;
}


SMEXT_LINK(&g_Double);
