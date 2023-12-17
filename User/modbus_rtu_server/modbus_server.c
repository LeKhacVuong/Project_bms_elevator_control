/*
 * modbus_server.c
 *
 * author: le khac vuong
 *
 */

#include "../../User/modbus_rtu_server/modbus_server.h"


nmbs_bitfield server_coils = {0};
uint16_t server_holding_registers[HOLD_REGS_ADDR_MAX] = {0,1,2,3,4,5,6,7,8,9};
uint16_t server_input_registers[INPUT_REGS_ADDR_MAX] = {01,11,21,31,41,51,61,71,81,91};



int32_t read_serial(uint8_t* buf, uint16_t count, int32_t byte_timeout_ms, void* arg) {
	uint32_t timeout = g_sys_time + byte_timeout_ms;
	while(g_sys_time < timeout){
		uint32_t gap_ = 0;
		if(front_index > rear_index){
			gap_ = front_index - rear_index;
		}
		if(front_index < rear_index){
			gap_ = 1024 + front_index - rear_index;
		}
		if(gap_ >= count){
			for(int i = 0; i < count; i++){
				*(buf + i) = ring_buffer[rear_index];
				rear_index++;
				if(rear_index >= 1024){
					rear_index = 0;
				}
			}
			return count;
		}
	}
	return -1;
}


int32_t write_serial(const uint8_t* buf, uint16_t count, int32_t byte_timeout_ms, void* arg) {
	HAL_UART_Transmit(&huart2, buf, count, byte_timeout_ms);
  return count;
}


void onError(void) {

	return;
}


nmbs_error handle_read_coils(uint16_t address, uint16_t quantity, nmbs_bitfield coils_out, uint8_t unit_id, void *arg) {
  if (address + quantity > COILS_ADDR_MAX + 1)
    return NMBS_EXCEPTION_ILLEGAL_DATA_ADDRESS;

  // Read our coils values into coils_out
  for (int i = 0; i < quantity; i++) {
    bool value = nmbs_bitfield_read(server_coils, address + i);
    nmbs_bitfield_write(coils_out, i, value);
  }

  return NMBS_ERROR_NONE;
}


nmbs_error handle_write_multiple_coils(uint16_t address, uint16_t quantity, const nmbs_bitfield coils, uint8_t unit_id, void *arg) {
  if (address + quantity > COILS_ADDR_MAX + 1)
    return NMBS_EXCEPTION_ILLEGAL_DATA_ADDRESS;

  // Write coils values to our server_coils
  for (int i = 0; i < quantity; i++) {
    nmbs_bitfield_write(server_coils, address + i, nmbs_bitfield_read(coils, i));
  }

  return NMBS_ERROR_NONE;
}


nmbs_error handler_read_holding_registers(uint16_t address, uint16_t quantity, uint16_t* registers_out, uint8_t unit_id, void *arg) {
  if (address + quantity > HOLD_REGS_ADDR_MAX + 1)
    return NMBS_EXCEPTION_ILLEGAL_DATA_ADDRESS;

  // Read our registers values into registers_out
  for (int i = 0; i < quantity; i++)
    registers_out[i] = server_holding_registers[address + i];

  return NMBS_ERROR_NONE;
}


nmbs_error handle_write_multiple_registers(uint16_t address, uint16_t quantity, const uint16_t* registers, uint8_t unit_id, void *arg) {
  if (address + quantity > HOLD_REGS_ADDR_MAX + 1)
    return NMBS_EXCEPTION_ILLEGAL_DATA_ADDRESS;

  // Write registers values to our server_holding_registers
  for (int i = 0; i < quantity; i++)
	  server_holding_registers[address + i] = registers[i];

  return NMBS_ERROR_NONE;
}

nmbs_error handle_write_single_registers(uint16_t address, uint16_t value, uint8_t unit_id, void *arg) {
  if (address > HOLD_REGS_ADDR_MAX + 1)
    return NMBS_EXCEPTION_ILLEGAL_DATA_ADDRESS;

  // Write register value to our server_holding_register

	  server_holding_registers[address] = value;

  return NMBS_ERROR_NONE;
}


nmbs_error handler_read_input_registers(uint16_t address, uint16_t quantity, uint16_t* registers_out, uint8_t unit_id, void *arg) {
  if (address + quantity > INPUT_REGS_ADDR_MAX + 1)
    return NMBS_EXCEPTION_ILLEGAL_DATA_ADDRESS;

  // Read our registers values into registers_out
  for (int i = 0; i < quantity; i++)
    registers_out[i] = server_input_registers[address + i];

  return NMBS_ERROR_NONE;
}








