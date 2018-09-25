/*
* This file is part of the PX series horticulture appliance codebase (https://github.com/atsteen/PrimeBox).
* Copyright (c) 2017-2018 Sound Venture Group LLC.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define TARGET_PLAT_WIN32  //define when running on a Win32 host
//#define TARGET_PLAT_AVR  //define when running on a AVR host

// Platform configuration directives
#define ENABLE_MEMORY_PROFILING
#define ENABLE_VERBOSE_LOGGING
#define BATCH_TASK_PROCESSING_LIMIT 3
#define DISPLAY_SLEEP_TIMEOUT_SEC 30
#define DEFAULT_VIEW_TIMEOUT_SEC 40
#define MAX_POWER_RELAY_STATE_REFRESH_INTERVAL_SEC 2
#define MAX_VIEWSTATE_REFRESH_INTERVAL_SEC 60
#define CONTROLLER_STATUS_OUTPUT_INTERVAL_SEC 10
#define DEFAULT_EXHAUST_FAN_DUTY_CYCLE_DURATION 20 // in minutes
#define DEFAULT_EXHAUST_FAN_DUTY_CYCLE_DURATION_MAX 999 // in minutes
#define DEFAULT_EXHAUST_FAN_DUTY_CYCLE_DAY 30 // int equiv of cycle percentage, x = x% where 1 <= x <= 100
#define DEFAULT_EXHAUST_FAN_DUTY_CYCLE_NIGHT 10 // int equiv of cycle percentage, x = x% where 1 <= x <= 100
#define DEFAULT_EXHAUST_FAN_DUTY_CYCLE_STATE true
#define DEFAULT_CIRCULATION_FAN_DUTY_CYCLE_DURATION 20 // in minutes
#define DEFAULT_CIRCULATION_FAN_DUTY_CYCLE_DURATION_MAX 999 // in minutes
#define DEFAULT_CIRCULATION_FAN_DUTY_CYCLE_DAY 50 // int equiv of cycle percentage, x = x% where 1 <= x <= 100
#define DEFAULT_CIRCULATION_FAN_DUTY_CYCLE_NIGHT 10 // int equiv of cycle percentage, x = x% where 1 <= x <= 100
#define DEFAULT_CIRCULATION_FAN_DUTY_CYCLE_STATE true

#define EVENT_LOG_CACHE_SIZE 3
#define SCHEDULED_TASK_DETAIL_COUNT 24
#define OBSERVER_LIMIT 4
#define T_QUEUE_SIZE 24
#define T_LIST_MAXSIZE 64
#define T_STACK_MAX_SIZE 24
#define TASK_ITEM_POOL_SIZE 10
#define SELECTABLE_ELEMENT_COUNT 3
#define MAX_TASK_RETRY_ATTEMPTS 3
#define MINUTES_IN_DAY 1440
#define DISPLAY_ROW_LENGTH 20

// Buzzer tone definitions
#define NOTE_7K 7000
#define NOTE_BROWN 80
#define NOTE_B0  31
#define NOTE_CS1 35
#define NOTE_AS4 466
#define NOTE_GS4 415
#define NOTE_F5  698
#define NOTE_B4  494
#define NOTE_F4  349
#define NOTE_D4  294
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_D6  1175

// ComponentModule Settings
// ------------------------

// HD44780 LCD Display (parallel interface)
// common init order: LiquidCrystal(rs, enable, d4, d5, d6, d7)
#define Rs_pin A7
#define En_pin A6
#define D4_pin A5
#define D5_pin A4
#define D6_pin A3
#define D7_pin A2
#define BACKLIGHT_PIN 8

// PCF8574T LCD Display (I2C interface)
#define PCF8574T_I2C_ADDR 0x27 
#define PCF8574T_BACKLIGHT_PIN 3
#define PCF8574T_En_pin 2
#define PCF8574T_Rw_pin 1
#define PCF8574T_Rs_pin 0
#define PCF8574T_D4_pin 4
#define PCF8574T_D5_pin 5
#define PCF8574T_D6_pin 6
#define PCF8574T_D7_pin 7
#define PCF8574T_LED_OFF 1
#define PCF8574T_LED_ON  0

// Define buzzer pin
#define BUZZER_PIN 9

//PowerRelay Configuration
#define POWER_RELAY_COUNT 4
#define POWER_RELAY_PIN_1 4
#define POWER_RELAY_PIN_2 5
#define POWER_RELAY_PIN_3 6
#define POWER_RELAY_PIN_4 7

//Encoder configuration (AVR imp only)
#define ENCODER_D1 2
#define ENCODER_D2 3
#define ENCODER_SW 19
#define ENCODER_SW_MIN_DEBOUNCE_DELAY_MS 25 // only required in PCB V1.32