/*

The MIT License (MIT)

Copyright (c) 2023 Quantulum Ltd, Phil Greenland <phil@quantulum.co.uk>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include "board.h"
#include "config.h"
#include "device.h"
#include "gpio.h"
#include "usbd_gs_can.h"

#define LEDPWR_GPIO_Port		 GPIOA
#define LEDPWR_Pin				 GPIO_PIN_9
#define LEDPWR_Mode				 GPIO_MODE_OUTPUT_PP
#define LEDPWR_Active_High		 1

#define LEDCANPWR_GPIO_Port		 GPIOA
#define LEDCANPWR_Pin			 GPIO_PIN_10
#define LEDCANPWR_Mode			 GPIO_MODE_OUTPUT_PP
#define LEDCANPWR_Active_High	 1

#define LEDCANEN0_GPIO_Port		 GPIOB
#define LEDCANEN0_Pin			 GPIO_PIN_4
#define LEDCANEN0_Mode			 GPIO_MODE_OUTPUT_PP
#define LEDCANEN0_Active_High	 1

#define LEDCANEN1_GPIO_Port		 GPIOB
#define LEDCANEN1_Pin			 GPIO_PIN_7
#define LEDCANEN1_Mode			 GPIO_MODE_OUTPUT_PP
#define LEDCANEN1_Active_High	 1

#define LEDRX0_GPIO_Port		 GPIOA
#define LEDRX0_Pin				 GPIO_PIN_15
#define LEDRX0_Mode				 GPIO_MODE_OUTPUT_PP
#define LEDRX0_Active_High		 1

#define LEDTX0_GPIO_Port		 GPIOB
#define LEDTX0_Pin				 GPIO_PIN_3
#define LEDTX0_Mode				 GPIO_MODE_OUTPUT_PP
#define LEDTX0_Active_High		 1

#define LEDRX1_GPIO_Port		 GPIOB
#define LEDRX1_Pin				 GPIO_PIN_6
#define LEDRX1_Mode				 GPIO_MODE_OUTPUT_PP
#define LEDRX1_Active_High		 1

#define LEDTX1_GPIO_Port		 GPIOB
#define LEDTX1_Pin				 GPIO_PIN_5
#define LEDTX1_Mode				 GPIO_MODE_OUTPUT_PP
#define LEDTX1_Active_High		 1

#define CANEN0_GPIO_Port		 GPIOA
#define CANEN0_Pin				 GPIO_PIN_0
#define CANEN0_Mode				 GPIO_MODE_OUTPUT_PP
#define CANEN0_Active_High		 0

#define CANEN1_GPIO_Port		 GPIOA
#define CANEN1_Pin				 GPIO_PIN_1
#define CANEN1_Mode				 GPIO_MODE_OUTPUT_PP
#define CANEN1_Active_High		 0

#define CAN_PWR_GPIO_Port		 GPIOC
#define CAN_PWR_Pin				 GPIO_PIN_6
#define CAN_PWR_Mode			 GPIO_MODE_OUTPUT_PP
#define CAN_PWR_Active_High		 0

#define CAN_PWR_FLT_GPIO_Port	 GPIOA
#define CAN_PWR_FLT_Pin			 GPIO_PIN_8
#define CAN_PWR_FLT_Mode		 GPIO_MODE_INPUT

static void quantulumltd_usbtocanfd_v1_setup(USBD_GS_CAN_HandleTypeDef *hcan)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	UNUSED(hcan);

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	/* LEDS */
	HAL_GPIO_WritePin(LEDPWR_GPIO_Port, LEDPWR_Pin, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = LEDPWR_Pin;
	GPIO_InitStruct.Mode = LEDPWR_Mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LEDPWR_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(LEDCANPWR_GPIO_Port, LEDCANPWR_Pin, GPIO_INIT_STATE(LEDCANPWR_Active_High));
	GPIO_InitStruct.Pin = LEDCANPWR_Pin;
	GPIO_InitStruct.Mode = LEDCANPWR_Mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LEDCANPWR_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(LEDCANEN0_GPIO_Port, LEDCANEN0_Pin, GPIO_INIT_STATE(LEDCANEN0_Active_High));
	GPIO_InitStruct.Pin = LEDCANEN0_Pin;
	GPIO_InitStruct.Mode = LEDCANEN0_Mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LEDCANEN0_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(LEDCANEN1_GPIO_Port, LEDCANEN1_Pin, GPIO_INIT_STATE(LEDCANEN1_Active_High));
	GPIO_InitStruct.Pin = LEDCANEN1_Pin;
	GPIO_InitStruct.Mode = LEDCANEN1_Mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LEDCANEN1_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(LEDRX0_GPIO_Port, LEDRX0_Pin, GPIO_INIT_STATE(LEDRX0_Active_High));
	GPIO_InitStruct.Pin = LEDRX0_Pin;
	GPIO_InitStruct.Mode = LEDRX0_Mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LEDRX0_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(LEDTX0_GPIO_Port, LEDTX0_Pin, GPIO_INIT_STATE(LEDTX0_Active_High));
	GPIO_InitStruct.Pin = LEDTX0_Pin;
	GPIO_InitStruct.Mode = LEDTX0_Mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LEDTX0_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(LEDRX1_GPIO_Port, LEDRX1_Pin, GPIO_INIT_STATE(LEDRX1_Active_High));
	GPIO_InitStruct.Pin = LEDRX1_Pin;
	GPIO_InitStruct.Mode = LEDRX1_Mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LEDRX1_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(LEDTX1_GPIO_Port, LEDTX1_Pin, GPIO_INIT_STATE(LEDTX1_Active_High));
	GPIO_InitStruct.Pin = LEDTX1_Pin;
	GPIO_InitStruct.Mode = LEDTX1_Mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LEDTX1_GPIO_Port, &GPIO_InitStruct);

	/* Transceiver enables */
	HAL_GPIO_WritePin(CANEN0_GPIO_Port, CANEN0_Pin, GPIO_INIT_STATE(CANEN0_Active_High));
	GPIO_InitStruct.Pin = CANEN0_Pin;
	GPIO_InitStruct.Mode = CANEN0_Mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CANEN0_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(CANEN1_GPIO_Port, CANEN1_Pin, GPIO_INIT_STATE(CANEN1_Active_High));
	GPIO_InitStruct.Pin = CANEN1_Pin;
	GPIO_InitStruct.Mode = CANEN1_Mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CANEN1_GPIO_Port, &GPIO_InitStruct);

	/* External power enable */
	HAL_GPIO_WritePin(CAN_PWR_GPIO_Port, CAN_PWR_Pin, GPIO_INIT_STATE(CAN_PWR_Active_High));
	GPIO_InitStruct.Pin = CAN_PWR_Pin;
	GPIO_InitStruct.Mode = CAN_PWR_Mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CAN_PWR_GPIO_Port, &GPIO_InitStruct);

	/* External power fault indication */
	GPIO_InitStruct.Pin = CAN_PWR_FLT_Pin;
	GPIO_InitStruct.Mode = CAN_PWR_FLT_Mode;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CAN_PWR_FLT_GPIO_Port, &GPIO_InitStruct);

	/* FDCAN */
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {
		.PeriphClockSelection = RCC_PERIPHCLK_FDCAN,
		.FdcanClockSelection = RCC_FDCANCLKSOURCE_PLL,
	};

	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
	__HAL_RCC_FDCAN_CLK_ENABLE();

	/* FDCAN1_RX, FDCAN1_TX */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF3_FDCAN1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* FDCAN2_RX, FDCAN2_TX */
	GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF3_FDCAN2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

static void quantulumltd_usbtocanfd_v1_phy_power_set(can_data_t *channel, bool enable)
{
	switch (channel->nr)
	{
		case 0:
			HAL_GPIO_WritePin(LEDCANEN0_GPIO_Port, LEDCANEN0_Pin, enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
			HAL_GPIO_WritePin(CANEN0_GPIO_Port, CANEN0_Pin, enable ? GPIO_PIN_RESET : GPIO_PIN_SET);
			break;
		case 1:
			HAL_GPIO_WritePin(LEDCANEN1_GPIO_Port, LEDCANEN1_Pin, enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
			HAL_GPIO_WritePin(CANEN1_GPIO_Port, CANEN1_Pin, enable ? GPIO_PIN_RESET : GPIO_PIN_SET);
			break;
		default:
			break;
	}
}

static bool can_pwr_enabled;

static void
quantulumltd_usbtocanfd_v1_termination_set(can_data_t *channel,
							  enum gs_can_termination_state enable)
{
	static uint32_t term_status = 0;

	if (enable)
	{
		term_status |= ((uint32_t)1U << channel->nr);
	}
	else
	{
		term_status &= ~((uint32_t)1U << channel->nr);
	}

	/* Enable external supply if termination is enabled on both channels (a hack I know) */
	can_pwr_enabled = (0x3 == term_status);
	HAL_GPIO_WritePin(LEDCANPWR_GPIO_Port, LEDCANPWR_Pin, can_pwr_enabled ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(CAN_PWR_GPIO_Port, CAN_PWR_Pin, can_pwr_enabled ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

static void quantulumltd_usbtocanfd_v1_mainloop_callback(void)
{
	static uint32_t last_time;
	static bool fault_toggle;
	uint32_t curr_time = HAL_GetTick();

	/* Every 100ms */
	if ((curr_time - last_time) >= 100)
	{
		/* Check current fault status */
		bool can_pwr_fault_status = (HAL_GPIO_ReadPin(CAN_PWR_FLT_GPIO_Port, CAN_PWR_FLT_Pin) == GPIO_PIN_RESET);

		/* Toggle led state on each tick in the event of a fault */
		if (can_pwr_fault_status)
		{
			fault_toggle = !fault_toggle;
		}
		else
		{
			fault_toggle = false;
		}

		/* Update CAN external power status LED */
		HAL_GPIO_WritePin(LEDCANPWR_GPIO_Port, LEDCANPWR_Pin, can_pwr_enabled && !fault_toggle ? GPIO_PIN_SET : GPIO_PIN_RESET);

		/* Reset timer */
		last_time = curr_time;
	}
}

const struct BoardConfig config = {
	.setup = quantulumltd_usbtocanfd_v1_setup,
	.phy_power_set = quantulumltd_usbtocanfd_v1_phy_power_set,
	.termination_set = quantulumltd_usbtocanfd_v1_termination_set,
	.mainloop_callback = quantulumltd_usbtocanfd_v1_mainloop_callback,
	.channels[0] = {
		.interface = FDCAN1,
		.leds = {
			[LED_RX] = {
				.port = LEDRX0_GPIO_Port,
				.pin = LEDRX0_Pin,
				.active_high = LEDRX0_Active_High,
			},
			[LED_TX] = {
				.port = LEDTX0_GPIO_Port,
				.pin = LEDTX0_Pin,
				.active_high = LEDTX0_Active_High,
			},
		},
	},
	.channels[1] = {
		.interface = FDCAN2,
		.leds = {
			[LED_RX] = {
				.port = LEDRX1_GPIO_Port,
				.pin = LEDRX1_Pin,
				.active_high = LEDRX1_Active_High,
			},
			[LED_TX] = {
				.port = LEDTX1_GPIO_Port,
				.pin = LEDTX1_Pin,
				.active_high = LEDTX1_Active_High,
			},
		},
	},
};
