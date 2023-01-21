/*
 modbus_registers.h - Modbus Registers Structure
 Copyright (C) 2020 Germain Masse

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

 ModBus Configuration for AstralPool Chlorinator
*/

#ifndef SRC_MODBUS_REGISTERS_H_
#define SRC_MODBUS_REGISTERS_H_

#include "Arduino.h"

typedef enum {
    MODBUS_TYPE_HOLDING = 0x00,         /*!< Modbus Holding register. */
    MODBUS_TYPE_INPUT = 0x01           /*!< Modbus Input register. */
//    MODBUS_TYPE_COIL,                   /*!< Modbus Coils. */
//    MODBUS_TYPE_DISCRETE,               /*!< Modbus Discrete bits. */
//    MODBUS_TYPE_COUNT,
//    MODBUS_TYPE_UNKNOWN = 0xFF
} modbus_entity_t;

typedef enum {
//    REGISTER_TYPE_U8 = 0x00,                   /*!< Unsigned 8 */
    REGISTER_TYPE_U16 = 0x01,                  /*!< Unsigned 16 */
//    REGISTER_TYPE_U32 = 0x02,                  /*!< Unsigned 32 */
//    REGISTER_TYPE_FLOAT = 0x03,                /*!< Float type */
//    REGISTER_TYPE_ASCII = 0x04,                  /*!< ASCII type */
    REGISTER_TYPE_DIEMATIC_ONE_DECIMAL = 0x05,
    REGISTER_TYPE_BITFIELD = 0x06,
    REGISTER_TYPE_DEBUG = 0x07
} register_type_t;

typedef union {
    const char* bitfield[16];
} optional_param_t;

typedef struct {
    uint16_t            id;
    modbus_entity_t     modbus_entity;      /*!< Type of modbus parameter */
    register_type_t     type;               /*!< Float, U8, U16, U32, ASCII, etc. */
    const char*         name;
    optional_param_t    optional_param;
} modbus_register_t;

const modbus_register_t registers[] = {
    { 0x00, MODBUS_TYPE_HOLDING, REGISTER_TYPE_DEBUG, "id_address"}, //by default 1
    { 0x01, MODBUS_TYPE_HOLDING, REGISTER_TYPE_DEBUG, "communication_setup"}, //by default 9600 8E1
    { 0x02, MODBUS_TYPE_HOLDING, REGISTER_TYPE_DEBUG, "id_manufacturer_high"}, // 0 for astral pool 
    { 0x03, MODBUS_TYPE_HOLDING, REGISTER_TYPE_DEBUG, "id_manufacturer_low"}, // 178 for astral pool 
    { 0x04, MODBUS_TYPE_HOLDING, REGISTER_TYPE_DEBUG, "id_product_code_high"}, //0-Electrolysis 1-Electrolysis with PH control 2-Electrolysis with PH and ORP control
    { 0x05, MODBUS_TYPE_HOLDING, REGISTER_TYPE_DEBUG, "id_product_code_low"}, //Electrolysis chlorine production in (g/h)
    { 0x06, MODBUS_TYPE_HOLDING, REGISTER_TYPE_DEBUG, "id_verify"}, //verification code
    { 0x07, MODBUS_TYPE_HOLDING, REGISTER_TYPE_DEBUG, "hardware_version"}, 
    { 0x08, MODBUS_TYPE_HOLDING, REGISTER_TYPE_DEBUG, "software_version"},
    { 0x00, MODBUS_TYPE_INPUT, REGISTER_TYPE_BITFIELD, "status", { .bitfield = {
            "alarm", // 0-normal 1-some alarm active
            "direct-cell-polarity", //1-direct 0-reverse
            "electrolysis-orp-stop", // external electrolysis halted by ORP/PPM Controller
            "cover-input-on",
            "ph-output", 
            "electrolysis-on"
    } } },
    { 0x01, MODBUS_TYPE_INPUT, REGISTER_TYPE_BITFIELD, "alarms", { .bitfield = {
            "flow-alarm", 
            "low-salt", 
            "high-salt", 
            "check-cell",
            "low-ph", 
            "high-ph",
            "unused", 
            "pump-stop-ph",
            "low-mv-orp",
            "high-mv-orp"
    } } },
    { 0x03, MODBUS_TYPE_INPUT, REGISTER_TYPE_U16, "calibration-response"}, //0-reset value  1-calibration ok   2-E2 calibretion error 3-E3 calibretion error 
    { 0x05, MODBUS_TYPE_INPUT, REGISTER_TYPE_U16, "chlorine-production"}, // in (g/h)
    { 0x06, MODBUS_TYPE_INPUT, REGISTER_TYPE_U16, "chlorine-percentage-production"}, 
    { 0x07, MODBUS_TYPE_INPUT, REGISTER_TYPE_U16, "chlorine-setpoint-actual"}, 
    { 0x08, MODBUS_TYPE_INPUT, REGISTER_TYPE_U16, "salt-test-result"}, //10-reset  255-test in progress 0-low salt 3-normal 6-high salt
    { 0x0A, MODBUS_TYPE_INPUT, REGISTER_TYPE_U16, "ph-measure"}, 
    { 0x0B, MODBUS_TYPE_INPUT, REGISTER_TYPE_U16, "ph-dossage-time"}, 
    { 0x0F, MODBUS_TYPE_INPUT, REGISTER_TYPE_U16, "orp-measure"}, 
    { 0x10, MODBUS_TYPE_INPUT, REGISTER_TYPE_U16, "ppm-measure"}, 
    { 0x11, MODBUS_TYPE_INPUT, REGISTER_TYPE_U16, "ppm-probe-current"}
};

#endif  // SRC_MODBUS_REGISTERS_H_
