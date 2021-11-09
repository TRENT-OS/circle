/*
 * Copyright (C) 2021, HENSOLDT Cyber GmbH
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

//
// circleos.h
//
// External functions used by the circle library
//
// This header defines functions that have to be implemented by a module using
// the circle library. The filename is analog to the one of the USPi library.
//

#ifndef _uspios_h
#define _uspios_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <camkes/io.h>

//
// Memory allocation
//
#define DMA_PAGE_SIZE	4096
#define DMA_ALIGNEMENT 	4096

void* dma_alloc (unsigned nSize, unsigned alignement);
void dma_free (void* pBlock, unsigned alignement);
uintptr_t dma_getPhysicalAddr (void* ptr);

//
// Timer
//
void MsDelay (unsigned nMilliSeconds);
void usDelay (unsigned nMicroSeconds);
void nsDelay (unsigned nNanoSeconds);

#ifndef AARCH64
typedef unsigned TKernelTimerHandle;
#else
typedef unsigned long TKernelTimerHandle;
#endif

typedef void TKernelTimerHandler (
	TKernelTimerHandle hTimer,
	void* pParam,
    void* pContext);

// returns the timer handle (hTimer)
unsigned StartKernelTimer (
	unsigned nHzDelay,	// in Hz units (see "system configuration" above)
    TKernelTimerHandler* pHandler,
	void* pParam,
	void* pContext);	// handed over to the timer handler
void CancelKernelTimer (unsigned hTimer);

//
// Interrupt handling
//
typedef void TInterruptHandler (void* pParam);

void ConnectInterrupt (
	unsigned nIRQ,
	TInterruptHandler* pHandler,
	void* pParam);

void DisconnectInterrupt (unsigned nIRQ);

//
// Mailbox
//
int SetPowerStateOn (unsigned nDeviceId);

int GetMACAddress (unsigned char Buffer[6]);

int GetCMDLine (unsigned char Buffer[2048]);

unsigned GetClockTicks (void);

//
// Logging
//

// Severity (change this before building if you want different values)
// Renamed so it does not clash with other (system) error codes
#define CIRCLE_LOG_ERROR		1
#define CIRCLE_LOG_WARNING		2
#define CIRCLE_LOG_NOTICE		3
#define CIRCLE_LOG_DEBUG		4
#define CIRCLE_LOG_PANIC        5

void LogWrite (
	const char* pSource,		// short name of module
	unsigned	Severity,		// see above
    const char* pMessage, ...);	// uses printf format options

#ifdef __cplusplus
}
#endif

#endif