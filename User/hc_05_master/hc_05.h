/*
 * hc_05.h
 *
 *  Created on: Oct 27, 2023
 *      Author: vypa0
 */

#ifndef HC_05_MASTER_HC_05_H_
#define HC_05_MASTER_HC_05_H_

#include "board.h"


#define DEFAUL_HC_05_BAUD 38400UL
#define HC_05_TIMEOUT 1000


void hc_05_init(void);
HC_05_STATUS_T hc_05_master_process(void);


#endif /* HC_05_MASTER_HC_05_H_ */
