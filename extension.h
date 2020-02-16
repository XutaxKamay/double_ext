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

#ifndef _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_
#define _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_

/**
 * @file extension.h
 * @brief Double extension code header.
 */

#include "IHandleSys.h"
#include "smsdk_ext.h"

using pdouble_t = double*;

/**
 * @brief Double implementation of the SDK Extension.
 * Note: Uncomment one of the pre-defined virtual functions in order to use it.
 */
class Double : public SDKExtension, public IHandleTypeDispatch
{
public:
    // IHandleTypeDispatch::OnHandleDestroy
    virtual void OnHandleDestroy(HandleType_t type, void *object);

public:
	/**
	 * @brief This is called after the initial loading sequence has been processed.
	 *
	 * @param error		Error message buffer.
	 * @param maxlen	Size of error message buffer.
	 * @param late		Whether or not the module was loaded after map load.
	 * @return			True to succeed loading, false to fail.
	 */
	virtual bool SDK_OnLoad(char *error, size_t maxlen, bool late);
	
	/**
	 * @brief This is called right before the extension is unloaded.
	 */
	//virtual void SDK_OnUnload();

	/**
	 * @brief This is called once all known extensions have been loaded.
	 * Note: It is is a good idea to add natives here, if any are provided.
	 */
	//virtual void SDK_OnAllLoaded();

	/**
	 * @brief Called when the pause state is changed.
	 */
	//virtual void SDK_OnPauseChange(bool paused);

	/**
	 * @brief this is called when Core wants to know if your extension is working.
	 *
	 * @param error		Error message buffer.
	 * @param maxlen	Size of error message buffer.
	 * @return			True if working, false otherwise.
	 */
	//virtual bool QueryRunning(char *error, size_t maxlen);
public:
#if defined SMEXT_CONF_METAMOD
	/**
	 * @brief Called when Metamod is attached, before the extension version is called.
	 *
	 * @param error			Error buffer.
	 * @param maxlen		Maximum size of error buffer.
	 * @param late			Whether or not Metamod considers this a late load.
	 * @return				True to succeed, false to fail.
	 */
	//virtual bool SDK_OnMetamodLoad(ISmmAPI *ismm, char *error, size_t maxlen, bool late);

	/**
	 * @brief Called when Metamod is detaching, after the extension version is called.
	 * NOTE: By default this is blocked unless sent from SourceMod.
	 *
	 * @param error			Error buffer.
	 * @param maxlen		Maximum size of error buffer.
	 * @return				True to succeed, false to fail.
	 */
	//virtual bool SDK_OnMetamodUnload(char *error, size_t maxlen);

	/**
	 * @brief Called when Metamod's pause state is changing.
	 * NOTE: By default this is blocked unless sent from SourceMod.
	 *
	 * @param paused		Pause state being set.
	 * @param error			Error buffer.
	 * @param maxlen		Maximum size of error buffer.
	 * @return				True to succeed, false to fail.
	 */
	//virtual bool SDK_OnMetamodPauseChange(bool paused, char *error, size_t maxlen);
#endif

public:
    static cell_t CreateHandle(IPluginContext* const pContext, pdouble_t value = nullptr);
    static HandleError ReadHandle(IPluginContext* const pContext, const Handle_t& handle, pdouble_t* value);
}extern g_Double;

/**
 * Double natives
 */

cell_t native_DoubleConstructor(IPluginContext *pContext, const cell_t *);
cell_t native_DoubleFromString(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleFromFloat(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleFromInt(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleIsNaN(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleToString(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleToInt(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleToFloat(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleGreaterThan(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleLessThan(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleEqualTo(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleClone(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleAbsoluteRef(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleAbsolute(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleModuloRef(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleModulo(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleAddRef(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleAdd(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleSubstractRef(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleSubstract(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleMultiplyRef(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleMultiply(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleDivideRef(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleDivide(IPluginContext *pContext, const cell_t *params);
cell_t native_DoublePowRef(IPluginContext *pContext, const cell_t *params);
cell_t native_DoublePow(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleSquareRootRef(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleSquareRoot(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleAtanRef(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleAtan(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleAtan2Ref(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleAtan2(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleSineRef(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleSine(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleArcSineRef(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleArcSine(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleTangentRef(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleTangent(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleCosineRef(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleCosine(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleArcCosineRef(IPluginContext *pContext, const cell_t *params);
cell_t native_DoubleArcCosine(IPluginContext *pContext, const cell_t *params);

extern HandleType_t g_DoubleType;

#endif // _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_
