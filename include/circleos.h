//
// circleos.h
//
// External functions used by the circle library
//
// USPi - An USB driver for Raspberry Pi written in C
// Copyright (C) 2014-2018  R. Stange <rsta2@o2online.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef _uspios_h
#define _uspios_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <camkes/io.h>

//
// System configuration
//
// (Change this before you build the USPi library!)
//

//
// Memory allocation
//
#define DMA_PAGE_SIZE	4096
#define DMA_ALIGNEMENT 	4096

int dma_manager();
void dma_man_cache_op(void *addr, size_t size, dma_cache_op_t op);
void *dma_alloc (unsigned nSize, unsigned alignement);
void dma_free (void *pBlock, unsigned alignement);
uintptr_t dma_getPhysicalAddr(void *ptr);

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

typedef void TKernelTimerHandler (TKernelTimerHandle hTimer, void *pParam, void *pContext);

// returns the timer handle (hTimer)
unsigned StartKernelTimer (unsigned	        nHzDelay,	// in HZ units (see "system configuration" above)
			   TKernelTimerHandler *pHandler,
			   void *pParam, void *pContext);	// handed over to the timer handler

void CancelKernelTimer (unsigned hTimer);

//
// Interrupt handling
//
typedef void TInterruptHandler (void *pParam);

void ConnectInterrupt (unsigned nIRQ, TInterruptHandler *pHandler, void *pParam);
void DisconnectInterrupt (unsigned nIRQ);

//
// Mailbox
//
int SetPowerStateOn (unsigned nDeviceId);	// "set power state" to "on", wait until completed

int GetMACAddress (unsigned char Buffer[6]);

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

void LogWrite (const char *pSource,		// short name of module
	       unsigned	   Severity,		// see above
	       const char *pMessage, ...);	// uses printf format options

#ifdef __cplusplus
}
#endif

#endif