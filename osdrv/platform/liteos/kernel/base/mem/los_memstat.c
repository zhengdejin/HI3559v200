/*----------------------------------------------------------------------------
 * Copyright (c) <2013-2015>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/

#include "los_memstat.inc"
#include "los_task.ph"

LITE_OS_SEC_BSS_MINOR TSK_MEM_USED_INFO * g_TskMemUsedInfo;
__attribute__((section(".sysmemused")))TSK_MEM_USED_INFO g_TskMemUsedInfo_0;


LITE_OS_SEC_TEXT_MINOR VOID osTaskMemUsedInc(UINT32 uwUsedSize, UINT32 uwTaskID)
{
    if (uwTaskID >= g_uwTskMaxNum)
    {
        return;
    }

    g_TskMemUsedInfo[uwTaskID].uwMemUsed += uwUsedSize;
}

LITE_OS_SEC_TEXT_MINOR VOID osTaskMemUsedDec(UINT32 uwUsedSize, UINT32 uwTaskID)
{
    if (uwTaskID >= g_uwTskMaxNum)
    {
        return;
    }
    if (g_TskMemUsedInfo[uwTaskID].uwMemUsed < uwUsedSize)
    {
        PRINT_WARN("mem used of current task '%s':0x%x, decrease size:0x%x\n",
            g_stLosTask.pstRunTask->pcTaskName, g_TskMemUsedInfo[uwTaskID].uwMemUsed, uwUsedSize);
        return;
    }
    g_TskMemUsedInfo[uwTaskID].uwMemUsed -= uwUsedSize;
}

LITE_OS_SEC_TEXT_MINOR UINT32 osTaskMemUsage(UINT32 uwTaskID)
{
    if (uwTaskID >= g_uwTskMaxNum)
    {
        return LOS_NOK;
    }

    return g_TskMemUsedInfo[uwTaskID].uwMemUsed;
}

LITE_OS_SEC_TEXT_MINOR VOID osTaskMemClear(UINT32 uwTaskID)
{
    if (uwTaskID >= g_uwTskMaxNum)
    {
        return;
    }
    if (g_TskMemUsedInfo[uwTaskID].uwMemUsed != 0)
    {
        PRINT_WARN("mem used of task '%s' is:0x%x, not zero when task being deleted\n",
            g_stLosTask.pstRunTask->pcTaskName, g_TskMemUsedInfo[uwTaskID].uwMemUsed);
    }
    g_TskMemUsedInfo[uwTaskID].uwMemUsed = 0;
    return;
}

#ifdef LOS_MEM_SLAB
LITE_OS_SEC_BSS_MINOR TSK_SLAB_USED_INFO * g_TskSlabUsedInfo;
__attribute__((section(".sysslabused")))TSK_SLAB_USED_INFO g_TskSlabUsedInfo_0;

LITE_OS_SEC_TEXT_MINOR VOID osTaskSlabUsedInc(UINT32 uwUsedSize, UINT32 uwTaskID)
{
    if (uwTaskID >= g_uwTskMaxNum)
    {
        return;
    }

    g_TskSlabUsedInfo[uwTaskID].uwSlabUsed += uwUsedSize;
}

LITE_OS_SEC_TEXT_MINOR VOID osTaskSlabUsedDec(UINT32 uwUsedSize, UINT32 uwTaskID)
{
    if (uwTaskID >= g_uwTskMaxNum)
    {
        return;
    }

    g_TskSlabUsedInfo[uwTaskID].uwSlabUsed -= uwUsedSize;
}

LITE_OS_SEC_TEXT_MINOR UINT32 osTaskSlabUsage(UINT32 uwTaskID)
{
    if (uwTaskID >= g_uwTskMaxNum)
    {
        return LOS_NOK;
    }

    return g_TskSlabUsedInfo[uwTaskID].uwSlabUsed;
}
#endif
