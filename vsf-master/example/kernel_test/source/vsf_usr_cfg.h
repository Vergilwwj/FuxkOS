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


//! \note Top Level Application Configuration 

#ifndef __TOP_APP_CFG_H__
#define __TOP_APP_CFG_H__

/*============================ INCLUDES ======================================*/
/*============================ MACROS ========================================*/

//#define VSF_ASSERT(...)         if (!(__VA_ARGS__)) {vsf_interrupt_safe() {while(1);}};
#define VSF_ASSERT(...)

#define VSF_SYSTIMER_FREQ               25000000ul

#define VSF_HEAP_SIZE                   2048

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

//http://www.keil.com/support/man/docs/uv4/uv4_ut_configwizard.htm

//! \name kernel resource configuration
//! @{

//  <h> Kernel Resource Configuration

//      <h> Kernal event-driven system configuration
//          <o>Maximum event pool size
//          <i>Simon, please add description here...
//#define VSF_OS_CFG_EVTQ_POOL_SIZE                     16

//          <o>The number of preemptive priorities <1-4>
//          <i>Simon, please add description here...
//#define VSF_OS_CFG_PRIORITY_NUM                         1
//      </h>

//#define VSF_OS_CFG_ADD_EVTQ_TO_IDLE                     ENABLED

//      <o>The default eda stack frame pool size <1-65535>
//      <i>The default eda stack frame pool is shared among all eda tasks. 
//#define VSF_OS_CFG_DEFAULT_TASK_FRAME_POOL_SIZE       16
//  </h>

//! @}

//! \name kernel feature configuration
//! @{
//  <h> Kernel Feature Configuration
//      <h> Main Function
//          <o>Main Stack Size              <128-65536:8>
//          <i>When main function is configured as a thread, this option controls the size of the stack.
#define VSF_OS_CFG_MAIN_STACK_SIZE              2048

//          <c1>Run main as a thread
//          <i>This feature will run main function as a thread. RTOS thread support must be enabled. 
#define VSF_OS_CFG_MAIN_MODE                    VSF_OS_CFG_MAIN_MODE_THREAD
//          </c>
//      </h>
//  </h>
//! @}

#define VSF_USE_TRACE                               DISABLED
#define VSF_KERNEL_CFG_EDA_SUPPORT_SIMPLE_FSM       ENABLED
//#define VSF_KERNEL_CFG_EDA_SUPPORT_TASK             DISABLED
//#define VSF_POOL_LOCK()             
//#define VSF_POOL_UNLOCK()
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/


#endif
/* EOF */
