/*
 * Copyright (c) 2015-2017, Ari Suutari <ari@stonepile.fi>.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote
 *     products derived from this software without specific prior written
 *     permission. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT,  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <picoos.h>

#include "py/nlr.h"
#include "py/objtuple.h"
#include "py/objstr.h"
#include "py/runtime.h"
#include "py/stream.h"
#include "py/builtin.h"

/*
 * posTask methods.
 */
STATIC mp_obj_t task_sleep(mp_obj_t self, mp_obj_t arg) {

    int ticks = mp_obj_get_int(arg);
    posTaskSleep(ticks);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_2(task_sleep_fun_obj, task_sleep);
STATIC MP_DEFINE_CONST_CLASSMETHOD_OBJ(task_sleep_obj, (mp_obj_t)&task_sleep_fun_obj);

STATIC const mp_map_elem_t task_locals_dict_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR_sleep), (mp_obj_t)&task_sleep_obj },
};

STATIC MP_DEFINE_CONST_DICT(task_locals_dict, task_locals_dict_table);

STATIC const mp_obj_type_t task_type = {
    { &mp_type_type },
    .name = MP_QSTR_Task,
    .locals_dict = (mp_obj_t)&task_locals_dict,
};

/*
 * Provide helper for Pico]OS MS(n) macro for converting milliseconds to ticks.
 */
STATIC mp_obj_t mod_pos_MS(mp_obj_t arg) {

    int ms = mp_obj_get_int(arg);
    return MP_OBJ_NEW_SMALL_INT(MS(ms));
}

STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_pos_MS_obj, mod_pos_MS);

/*
 * "pos" module contains Pico]OS pico layer functions.
 */
STATIC const mp_map_elem_t mp_module_pos_globals_table[] = {

    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_pos) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_Task), (mp_obj_t)&task_type },
    { MP_OBJ_NEW_QSTR(MP_QSTR_MS), (mp_obj_t)&mod_pos_MS_obj },
};

STATIC MP_DEFINE_CONST_DICT(mp_module_pos_globals, mp_module_pos_globals_table);

const mp_obj_module_t mp_module_pos = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_pos_globals,
};

