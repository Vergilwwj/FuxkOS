/*****************************************************************************
 *   Copyright(C)2009-2022 by VSF Team                                       *
 *                                                                           *
 *  Licensed under the Apache License, Version 2.0 (the "License");          *
 *  you may not use this file except in compliance with the License.         *
 *  You may obtain a copy of the License at                                  *
 *                                                                           *
 *     http://www.apache.org/licenses/LICENSE-2.0                            *
 *                                                                           *
 *  Unless required by applicable law or agreed to in writing, software      *
 *  distributed under the License is distributed on an "AS IS" BASIS,        *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 *  See the License for the specific language governing permissions and      *
 *  limitations under the License.                                           *
 *                                                                           *
 ****************************************************************************/

#ifndef __WIN_GENERIC_H__
#define __WIN_GENERIC_H__

/*============================ INCLUDES ======================================*/
#include "hal/vsf_hal_cfg.h"
#include "utilities/vsf_utilities.h"

#undef PUBLIC_CONST
#if     defined(__VSF_ARCH_WIN_IMPLEMENT)
#   define __VSF_CLASS_IMPLEMENT__
#   define PUBLIC_CONST
#else
#   define PUBLIC_CONST                 const
#endif

#include "utilities/ooc_class.h"

#ifdef __cplusplus
extern "C" {
#endif

/*============================ MACROS ========================================*/

#ifndef __LITTLE_ENDIAN
#   define __LITTLE_ENDIAN              1
#endif
#ifndef __BYTE_ORDER
#   define __BYTE_ORDER                 __LITTLE_ENDIAN
#endif

#ifndef VSF_ARCH_PRI_NUM
#   define VSF_ARCH_PRI_NUM             64
#endif

#ifndef VSF_SYSTIMER_CFG_IMPL_MODE
#   define VSF_SYSTIMER_CFG_IMPL_MODE   VSF_SYSTIMER_IMPL_REQUEST_RESPONSE
#endif

// software interrupt provided by arch
#ifndef VSF_ARCH_SWI_NUM
#   define VSF_ARCH_SWI_NUM             32
#endif

#define VSF_ARCH_STACK_PAGE_SIZE        4096
#define VSF_ARCH_STACK_GUARDIAN_SIZE    4096

#ifndef FAR
#   define FAR
#endif
#ifndef NEAR
#   define NEAR
#endif

/*============================ MACROFIED FUNCTIONS ===========================*/

// for trace
#ifndef VSF_ARCH_TRACE_FUNC
#   define VSF_ARCH_TRACE_FUNC              printf
#endif

#ifndef vsf_arch_trace
#   if VSF_ARCH_PRI_NUM == 1 && VSF_ARCH_SWI_NUM == 0
#       define vsf_arch_trace(__header, __color, ...)
#   else
#       define vsf_arch_trace(__header, __color, ...)                           \
        do {                                                                    \
            vsf_arch_irq_thread_t *__irq_thread =                               \
                        __vsf_arch_get_cur_irq_thread();                        \
            __vsf_arch_trace_lock();                                            \
                VSF_ARCH_TRACE_FUNC("%s[%s]: ", (__color), (__header));         \
                if (__irq_thread != NULL) {                                     \
                    VSF_ARCH_TRACE_FUNC("%s(%d) %lld ",                         \
                        __irq_thread->name, (int)__irq_thread->thread_id,       \
                        __vsf_systimer_get());                                  \
                } else {                                                        \
                }                                                               \
                VSF_ARCH_TRACE_FUNC(__VA_ARGS__);                               \
            __vsf_arch_trace_unlock();                                          \
        } while (0)
#   endif
#endif

#define __VSF_ARCH_PRI(__N, __UNUSED)                                           \
            VSF_ARCH_PRIO_##__N = (__N),                                        \
            vsf_arch_prio_##__N = (__N),

#define vsf_arch_wakeup()

/*============================ TYPES =========================================*/

// avoid to use windows.h, fix if any conflicts
typedef void *                      HANDLE;
typedef unsigned long               DWORD;
typedef unsigned int                UINT;
typedef unsigned char               BYTE;
typedef char *                      LPSTR;
#ifdef __CPU_X64__
typedef unsigned long long          ULONG_PTR, *PULONG_PTR;
#else
typedef unsigned long               ULONG_PTR, *PULONG_PTR;
#endif
typedef ULONG_PTR                   DWORD_PTR, *PDWORD_PTR;

#ifndef VSF_ARCH_SYSTIMER_TICK_T
#   define VSF_ARCH_SYSTIMER_TICK_T uint64_t
#endif
typedef VSF_ARCH_SYSTIMER_TICK_T    vsf_systimer_tick_t;

typedef enum vsf_arch_prio_t {
    VSF_ARCH_PRIO_INVALID = -1,
    vsf_arch_prio_invalid = -1,
    VSF_MREPEAT(VSF_ARCH_PRI_NUM, __VSF_ARCH_PRI, __UNUSED)
    vsf_arch_prio_highest = VSF_ARCH_PRI_NUM - 1,
} vsf_arch_prio_t;

typedef void (*vsf_arch_irq_entry_t)(void*);

vsf_class(vsf_arch_irq_request_t) {
    private_member(
        HANDLE event;
        bool is_inited;
    )
};

typedef volatile bool vsf_gint_state_t;

/*============================ INCLUDES ======================================*/

#if VSF_ARCH_PRI_NUM == 1 && VSF_ARCH_SWI_NUM == 0
#   include "hal/arch/common/arch_without_thread_suspend/vsf_arch_without_thread_suspend_template.h"
#endif

/*============================ TYPES =========================================*/

#if VSF_ARCH_PRI_NUM == 1 && VSF_ARCH_SWI_NUM == 0
vsf_class(vsf_arch_irq_thread_t) {
    private_member(
        implement(vsf_arch_irq_thread_common_t)
        HANDLE thread;
        DWORD thread_id;
    )
};
#else
typedef enum vsf_arch_irq_state_t {
    VSF_ARCH_IRQ_STATE_IDLE,
    VSF_ARCH_IRQ_STATE_ACTIVE,
    VSF_ARCH_IRQ_STATE_FOREGROUND,
    VSF_ARCH_IRQ_STATE_BACKGROUND,
} vsf_arch_irq_state_t;

vsf_class(vsf_arch_irq_thread_t) {
    public_member(
        const char name[32];

        PUBLIC_CONST vsf_dlist_node_t irq_node;
        PUBLIC_CONST vsf_dlist_node_t rdy_node;
        PUBLIC_CONST HANDLE thread;
        PUBLIC_CONST DWORD thread_id;
        PUBLIC_CONST vsf_arch_prio_t priority;
        PUBLIC_CONST vsf_arch_irq_thread_t *prev;     // call stack
        PUBLIC_CONST vsf_arch_irq_state_t state;
        PUBLIC_CONST vsf_arch_irq_request_t *reply;
    )
};
#endif
#undef PUBLIC_CONST

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

extern void __vsf_arch_irq_sleep(uint_fast32_t ms);

extern void __vsf_arch_irq_request_init(vsf_arch_irq_request_t *request);
extern void __vsf_arch_irq_request_fini(vsf_arch_irq_request_t *request);
extern void __vsf_arch_irq_request_pend(vsf_arch_irq_request_t *request);
extern void __vsf_arch_irq_request_send(vsf_arch_irq_request_t *request);

extern void __vsf_arch_irq_init(vsf_arch_irq_thread_t *irq_thread, char *name,
    vsf_arch_irq_entry_t entry, vsf_arch_prio_t priority);
extern void __vsf_arch_irq_fini(vsf_arch_irq_thread_t *irq_thread);
extern void __vsf_arch_irq_set_background(vsf_arch_irq_thread_t *irq_thread);
extern void __vsf_arch_irq_start(vsf_arch_irq_thread_t *irq_thread);
extern void __vsf_arch_irq_end(vsf_arch_irq_thread_t *irq_thread, bool is_terminate);

// for trace only
extern vsf_systimer_tick_t __vsf_systimer_get(void);

static ALWAYS_INLINE void vsf_arch_set_stack(uintptr_t stack)
{
#if     defined(__CPU_X86__)
    __asm__("movl %0, %%esp" : : "r"(stack));
#elif   defined(__CPU_X64__)
    __asm__("movq %0, %%rsp" : : "r"(stack));
#endif
}

static ALWAYS_INLINE uintptr_t vsf_arch_get_stack(void)
{
    uintptr_t stack;
#if     defined(__CPU_X86__)
    __asm__("movl %%esp, %0" : "=r"(stack) :);
#elif   defined(__CPU_X64__)
    __asm__("movq %%esp, %0" : "=r"(stack) :);
#endif
    return stack;
}

#ifdef __cplusplus
}
#endif

#endif
/* EOF */
