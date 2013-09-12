/* bricklib
 * Copyright (C) 2010 Olaf Lüke <olaf@tinkerforge.com>
 *
 * spi_stack_master.h: SPI stack master functionality
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef SPI_MASTER_H
#define SPI_MASTER_H

#include <stdint.h>

#include "bricklib/com/com_common.h"

bool spi_stack_master_transceive(void);

void spi_master_state_machine(void);
void spi_master_reset_state_machine(void);
void spi_stack_master_init(void);
void spi_stack_master_insert_position(void* data, const uint8_t position);

void spi_stack_master_state_machine_loop(void *arg);
void spi_stack_master_message_loop(void *parameters);

void spi_stack_master_message_loop_return(const char *data, const uint16_t length);

#endif
