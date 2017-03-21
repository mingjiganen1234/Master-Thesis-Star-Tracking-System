// ==============================================================
// File generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2014.4
// Copyright (C) 2014 Xilinx Inc. All rights reserved.
// 
// ==============================================================

#ifndef XCCLABEL_H
#define XCCLABEL_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xcclabel_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Crtls_BaseAddress;
} XCclabel_Config;
#endif

typedef struct {
    u32 Crtls_BaseAddress;
    u32 IsReady;
} XCclabel;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XCclabel_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XCclabel_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XCclabel_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XCclabel_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XCclabel_Initialize(XCclabel *InstancePtr, u16 DeviceId);
XCclabel_Config* XCclabel_LookupConfig(u16 DeviceId);
int XCclabel_CfgInitialize(XCclabel *InstancePtr, XCclabel_Config *ConfigPtr);
#else
int XCclabel_Initialize(XCclabel *InstancePtr, const char* InstanceName);
int XCclabel_Release(XCclabel *InstancePtr);
#endif

void XCclabel_Start(XCclabel *InstancePtr);
u32 XCclabel_IsDone(XCclabel *InstancePtr);
u32 XCclabel_IsIdle(XCclabel *InstancePtr);
u32 XCclabel_IsReady(XCclabel *InstancePtr);
void XCclabel_EnableAutoRestart(XCclabel *InstancePtr);
void XCclabel_DisableAutoRestart(XCclabel *InstancePtr);
u32 XCclabel_Get_return(XCclabel *InstancePtr);

void XCclabel_Set_imgHeight(XCclabel *InstancePtr, u32 Data);
u32 XCclabel_Get_imgHeight(XCclabel *InstancePtr);
void XCclabel_Set_imgWidth(XCclabel *InstancePtr, u32 Data);
u32 XCclabel_Get_imgWidth(XCclabel *InstancePtr);

void XCclabel_InterruptGlobalEnable(XCclabel *InstancePtr);
void XCclabel_InterruptGlobalDisable(XCclabel *InstancePtr);
void XCclabel_InterruptEnable(XCclabel *InstancePtr, u32 Mask);
void XCclabel_InterruptDisable(XCclabel *InstancePtr, u32 Mask);
void XCclabel_InterruptClear(XCclabel *InstancePtr, u32 Mask);
u32 XCclabel_InterruptGetEnabled(XCclabel *InstancePtr);
u32 XCclabel_InterruptGetStatus(XCclabel *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif