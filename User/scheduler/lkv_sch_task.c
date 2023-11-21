/*
 * lkv_task.c
 *
 *  Created on: Jul 14, 2023
 *      Author: Admin
 */




#include <stdint.h>
#include "lkv_sch_task.h"

#define _impl(p)    ((lkv_scheduler_t*)(p))


#define lkv_SCH_TASK_REPEAT_FOREVER      0xFFFF


lkv_sch_t* lkv_sch_create(){
    lkv_scheduler_t* sch = malloc (sizeof(lkv_scheduler_t));
    if(!sch){
        return NULL;
    }
    for(int index = 0; index < lkv_SCH_TASK_MAX_SUPPORT; ++index){
        sch->m_tasks->m_count = 0;
        sch->m_tasks->m_task.m_arg = NULL;
        sch->m_tasks[index].m_task.m_fn = NULL;
        sch->m_tasks[index].m_task.m_interval = 0;
        sch->m_tasks[index].m_task.m_repeat_count = 0;
    }

    return (lkv_sch_t*)sch;
}



int32_t lkv_sch_free(lkv_sch_t* _this){
    if(!_this){
        return -1;
    }
    for (int index = 0; index < lkv_SCH_TASK_MAX_SUPPORT; ++index) {
        _impl(_this)->m_tasks[index].m_task.m_arg = NULL;
        _impl(_this)->m_tasks[index].m_task.m_fn = NULL;
        _impl(_this)->m_tasks[index].m_task.m_interval = 0;
        _impl(_this)->m_tasks[index].m_task.m_repeat_count = 0;
    }
    return 0;
}

int32_t lkv_sch_start_task(lkv_sch_t* _this, const lkv_sch_task_t* _task){
    if(!_this){
        return -1;
    }
    for (int index = 0; index < lkv_SCH_TASK_MAX_SUPPORT; ++index) {
        if(!_impl(_this)->m_tasks[index].m_task.m_fn){
            _impl(_this)->m_tasks[index].m_task.m_arg = _task->m_arg;
            _impl(_this)->m_tasks[index].m_task.m_fn = _task->m_fn;
            _impl(_this)->m_tasks[index].m_task.m_interval = _task->m_interval;
            _impl(_this)->m_tasks[index].m_task.m_repeat_count = _task->m_repeat_count;
            _impl(_this)->m_tasks[index].m_count = 0;
            elapsed_timer_resetz(&_impl(_this)->m_tasks[index].m_timeout, _task->m_interval);
            for (index = index + 1; index < lkv_SCH_TASK_MAX_SUPPORT; index++)
                if (_impl(_this)->m_tasks[index].m_task.m_fn == _task->m_fn)
                    _impl(_this)->m_tasks[index].m_task.m_fn = NULL;
            return index;
        }
    }
    return -1;
}

int32_t lkv_sch_cancel_task(lkv_sch_t* _this,  int32_t _task_id){
    if(!_this || _task_id >= lkv_SCH_TASK_MAX_SUPPORT){
        return -1;
    }
    _impl(_this)->m_tasks[_task_id].m_task.m_arg = NULL;
    _impl(_this)->m_tasks[_task_id].m_task.m_fn = NULL;
    _impl(_this)->m_tasks[_task_id].m_task.m_interval = 0;
    _impl(_this)->m_tasks[_task_id].m_task.m_repeat_count = 0;
    _impl(_this)->m_tasks[_task_id].m_count = 0;
    return 0;
}

int32_t lkv_sch_process(lkv_sch_t* _this){
    lkv_sch_task_fn_t callback_fn = NULL;

    if(!_this){
        return -1;
    }
    for (int index = 0; index < lkv_SCH_TASK_MAX_SUPPORT; ++index) {
        if (!elapsed_timer_get_remain(&_impl(_this)->m_tasks[index].m_timeout) && _impl(_this)->m_tasks[index].m_task.m_fn) {
            callback_fn = _impl(_this)->m_tasks[index].m_task.m_fn;
            callback_fn(_impl(_this)->m_tasks[index].m_task.m_arg);

            if ((_impl(_this)->m_tasks[index].m_count < _impl(_this)->m_tasks[index].m_task.m_repeat_count - 1)
                || (_impl(_this)->m_tasks[index].m_task.m_repeat_count == lkv_SCH_TASK_REPEAT_FOREVER)) {
                _impl(_this)->m_tasks[index].m_count++;
                elapsed_timer_reset(&_impl(_this)->m_tasks[index].m_timeout);
            }else{
                _impl(_this)->m_tasks[index].m_task.m_fn = NULL;
                _impl(_this)->m_tasks[index].m_task.m_arg = NULL;
            }
        }
    }
    return 0;
}
