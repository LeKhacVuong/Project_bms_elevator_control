/*
 * task.h
 *
 *  Created on: Jul 14, 2023
 *      Author: Admin
 */

#ifndef CORES_TASK_lkv_sch_task_H_
#define CORES_TASK_lkv_sch_task_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "lkv_elapsed_timer.h"

#define lkv_SCH_TASK_MAX_SUPPORT		32
#define TIMER_REPEAT_FOREVER        0xffff

typedef void lkv_sch_t;

typedef void (*lkv_sch_task_fn_t)(void *arg);
typedef void (*lkv_service_task_fn_t)(void*);

typedef struct {
    int32_t m_repeat_count;
    int32_t m_interval;
    lkv_service_task_fn_t m_fn;
    void* m_arg;
}lkv_sch_task_t;

typedef struct{
    struct {
        elapsed_timer_t m_timeout;
        int32_t m_count;
        lkv_sch_task_t m_task;
    }m_tasks[lkv_SCH_TASK_MAX_SUPPORT];
}lkv_scheduler_t;

lkv_sch_t* lkv_sch_create();
lkv_sch_t* lkv_sch_create_default();

int32_t lkv_sch_free(lkv_sch_t* _this);

int32_t lkv_sch_start_task(lkv_sch_t* _this, const lkv_sch_task_t* _task);
int32_t lkv_sch_cancel_task(lkv_sch_t* _this, int32_t _task_id);

int32_t lkv_sch_process(lkv_sch_t* _this);




/*
 * lkv_scheduler_t service;
 * void Dosomething_function(datatype _arg);
 *
 * VD: lkv_sch_task_t Dosomething;
 *
 *	Dosomething.m_repeat_count = TIMER_REPEAT_FOREVER or (uint32_t) put time repeat here;
 *	Dosomething.m_interval = (unint32_t) pu time delay here;	/
 *	Dosomething.m_fn = (lkv_service_task_fn_t) Dosomething_function;
 *	Dosomething.m_arg = put argument of Dosomething_function here;
 *
 *  lkv_sch_start_task(&service, &Dosomething);
 *
 *  int main(void){
 *
 *    while(1){
 *       lkv_sch_process(&service);
 *    }
 *  }
 *
 * */












#endif /* CORES_TASK_lkv_sch_task_H_ */
