/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

/**
 * \file
 *
 * \par Purpose
 *
 * This module provides several definitions and methods for using an USART
 * peripheral.
 *
 * \par Usage
 *
 * -# Enable the USART peripheral clock in the PMC.
 * -# Enable the required USART PIOs (see pio.h).
 * -# Configure the UART by calling usart_configure.
 * -# Enable the transmitter and/or the receiver of the USART using
 *    usart_set_transmitter_enabled and usart_set_receiver_enabled.
 * -# Send data through the USART using the usart_write methods.
 * -# Receive data from the USART using the usart_read functions; the availability of data can be polled
 *    with usart_is_data_available.
 * -# Disable the transmitter and/or the receiver of the USART with
 *    usart_set_transmitter_enabled and usart_set_receiver_enabled.
 */

#ifndef _USART_
#define _USART_

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "chip.h"

#include <stdbool.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Macros
 *----------------------------------------------------------------------------*/

/* Returns 1 if the TXRDY bit (ready to transmit data) is set in the given status register value.*/
#define USART_STATUS_TXRDY(status) ((status & US_CSR_TXRDY) == US_CSR_TXRDY)

/* Returns 1 if the RXRDY bit (ready to receive data) is set in the given status register value.*/
#define USART_STATUS_RXRDY(status) ((status & US_CSR_RXRDY) == US_CSR_RXRDY)

/* Returns 1 if the TXEMPTY bit (end of transmit) is set in the given status register value.*/
#define USART_STATUS_TXEMPTY(status) ((status & US_CSR_TXEMPTY) == US_CSR_TXEMPTY)

/*------------------------------------------------------------------------------*/
/*         Exported functions                                                   */
/*------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

extern void usart_reset_status(Usart *usart);
extern void usart_configure(Usart *usart, uint32_t mode, uint32_t baudrate);
extern uint32_t usart_get_status(Usart * usart);
extern void usart_enable_it(Usart *usart, uint32_t mode);
extern void usart_disable_it(Usart *usart, uint32_t mode);
extern uint32_t usart_get_it_mask(Usart *usart);
extern void usart_set_transmitter_enabled(Usart *usart, uint8_t enabled);
extern void usart_set_receiver_enabled(Usart *usart, uint8_t enabled);
extern void usart_set_rts_enabled(Usart *usart, uint8_t enabled);
extern uint32_t usart_get_masked_status(Usart *usart);

extern void usart_reset_tx(Usart *usart);
extern void usart_set_tx_timeguard(Usart *usart, uint32_t timeguard);
extern void usart_reset_rx(Usart *usart);
extern void usart_set_rx_timeout(Usart *usart, uint32_t timeout);
extern void usart_start_tx_break(Usart *usart);
extern void usart_stop_tx_break(Usart *usart);
extern void usart_start_rx_timeout(Usart *usart);
extern void usart_reset_iterations(Usart *usart);
extern void usart_reset_nack(Usart *usart);
extern void usart_restart_rx_timeout(Usart *usart);

extern void usart_write(Usart *usart, uint16_t data, volatile uint32_t timeout);
extern uint16_t usart_read(Usart *usart, volatile uint32_t timeout);

extern bool usart_is_rx_ready(Usart *usart);
extern bool usart_is_tx_ready(Usart *usart);
extern void usart_put_char(Usart *usart, uint8_t c);
extern uint8_t usart_get_char(Usart *usart);

extern void usart_set_irda_filter(Usart *usart, uint8_t filter);

extern void usart_set_sync_slave_baudrate(Usart *usart);
extern uint32_t usart_set_spi_master_baudrate(Usart *usart, uint32_t baudrate);
extern void usart_set_spi_slave_baudrate(Usart *usart);
extern uint32_t usart_init_hw_handshaking(Usart *usart);
extern uint32_t usart_set_async_baudrate(Usart *usart, uint32_t baudrate);

#ifdef CONFIG_HAVE_USART_FIFO
extern void usart_fifo_configure(Usart *usart, uint8_t tx_thres,
			  uint8_t rx_down_thres, uint8_t rx_up_thres,
			  uint32_t ready_modes);
extern void usart_fifo_disable(Usart *usart);
extern void usart_fifo_enable_it(Usart *usart, uint32_t interrupt_mask);
extern void usart_fifo_disable_it(Usart *usart, uint32_t interrupt_mask);
extern uint32_t usart_fifo_get_interrupts(Usart *usart);
extern uint32_t usart_fifo_rx_size(Usart *usart);
extern uint32_t usart_fifo_tx_size(Usart *usart);
extern uint32_t usart_read_stream(Usart *usart, void *stream, uint32_t len);
extern uint32_t usart_write_stream(Usart *usart, const void *stream, uint32_t len);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _USART_ */
