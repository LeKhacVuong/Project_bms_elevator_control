/*
 * modbus_server.h
 *
 *  Created on: Nov 8, 2023
 *      Author: vypa0
 */

#ifndef MODBUS_RTU_SERVER_MODBUS_SERVER_H_
#define MODBUS_RTU_SERVER_MODBUS_SERVER_H_

#include "stm32l1xx_hal.h"
#include "main.h"
#include "../../User/modbus_rtu_server/nanomodbus.h"


#define COILS_ADDR_MAX       15
#define HOLD_REGS_ADDR_MAX   10
#define INPUT_REGS_ADDR_MAX  10
#define RTU_SERVER_ADDRESS   5


extern nmbs_bitfield server_coils;
extern uint16_t server_holding_registers[];
extern uint16_t server_input_registers[];


int32_t read_serial(uint8_t* buf, uint16_t count, int32_t byte_timeout_ms, void* arg);
int32_t write_serial(const uint8_t* buf, uint16_t count, int32_t byte_timeout_ms, void* arg);
void onError(void);
nmbs_error handle_read_coils(uint16_t address, uint16_t quantity, nmbs_bitfield coils_out, uint8_t unit_id, void *arg);
nmbs_error handle_write_multiple_coils(uint16_t address, uint16_t quantity, const nmbs_bitfield coils, uint8_t unit_id, void *arg);
nmbs_error handler_read_holding_registers(uint16_t address, uint16_t quantity, uint16_t* registers_out, uint8_t unit_id, void *arg);
nmbs_error handle_write_multiple_registers(uint16_t address, uint16_t quantity, const uint16_t* registers, uint8_t unit_id, void *arg);
nmbs_error handle_write_single_registers(uint16_t address, uint16_t value, uint8_t unit_id, void *arg);
nmbs_error handler_read_input_registers(uint16_t address, uint16_t quantity, uint16_t* registers_out, uint8_t unit_id, void *arg);






#endif /* MODBUS_RTU_SERVER_MODBUS_SERVER_H_ */
