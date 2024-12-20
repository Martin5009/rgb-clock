/**
 * Credit for these font bitmaps goes to Jared Sanson.
 * https://jared.geek.nz/2014/01/custom-fonts-for-microcontrollers/
*/

#include "fonts.h"

const unsigned char sevenlinedigital_font[96][4] = {
	{0x00,0x00,0x00,0x00}, //  
	{0x36,0x00,0x00,0x00}, // !
	{0x06,0x00,0x00,0x06}, // "
	{0x36,0x49,0x49,0x36}, // #
	{0x06,0x49,0x49,0x30}, // $
	{0x36,0x49,0x49,0x36}, // %
	{0x36,0x49,0x49,0x36}, // &
	{0x06,0x00,0x00,0x00}, // '
	{0x36,0x41,0x41,0x00}, // (
	{0x41,0x41,0x36,0x00}, // )
	{0x06,0x09,0x09,0x06}, // *
	{0x36,0x08,0x08,0x00}, // +
	{0x30,0x00,0x00,0x00}, // ,
	{0x08,0x08,0x00,0x00}, // -
	{0x30,0x00,0x00,0x00}, // .
	{0x30,0x08,0x08,0x06}, // /
	{0x36,0x41,0x41,0x36}, // 0
	{0x36,0x00,0x00,0x00}, // 1
	{0x30,0x49,0x49,0x06}, // 2
	{0x49,0x49,0x36,0x00}, // 3
	{0x06,0x08,0x08,0x36}, // 4
	{0x06,0x49,0x49,0x30}, // 5
	{0x36,0x49,0x49,0x30}, // 6
	{0x01,0x01,0x36,0x00}, // 7
	{0x36,0x49,0x49,0x36}, // 8
	{0x06,0x49,0x49,0x36}, // 9
	{0x36,0x00,0x00,0x00}, // :
	{0x36,0x00,0x00,0x00}, // ;
	{0x36,0x41,0x41,0x00}, // <
	{0x48,0x48,0x00,0x00}, // =
	{0x41,0x41,0x36,0x00}, // >
	{0x30,0x09,0x09,0x06}, // ?
	{0x36,0x49,0x49,0x36}, // @
	{0x36,0x09,0x09,0x36}, // A
	{0x36,0x49,0x49,0x36}, // B
	{0x36,0x41,0x41,0x00}, // C
	{0x30,0x48,0x48,0x36}, // D
	{0x36,0x49,0x49,0x00}, // E
	{0x36,0x09,0x09,0x00}, // F
	{0x36,0x49,0x49,0x30}, // G
	{0x36,0x08,0x08,0x36}, // H
	{0x36,0x00,0x00,0x00}, // I
	{0x40,0x40,0x36,0x00}, // J
	{0x36,0x08,0x08,0x36}, // K
	{0x36,0x40,0x40,0x00}, // L
	{0x36,0x01,0x01,0x36}, // M
	{0x36,0x01,0x01,0x36}, // N
	{0x36,0x41,0x41,0x36}, // O
	{0x36,0x09,0x09,0x06}, // P
	{0x06,0x09,0x09,0x36}, // Q
	{0x36,0x01,0x01,0x00}, // R
	{0x06,0x49,0x49,0x30}, // S
	{0x36,0x48,0x48,0x00}, // T
	{0x36,0x40,0x40,0x36}, // U
	{0x36,0x40,0x40,0x36}, // V
	{0x36,0x40,0x40,0x36}, // W
	{0x36,0x08,0x08,0x36}, // X
	{0x06,0x08,0x08,0x36}, // Y
	{0x30,0x49,0x49,0x06}, // Z
	{0x36,0x41,0x41,0x00}, // [
	{0x06,0x08,0x08,0x30}, // "\"
	{0x41,0x41,0x36,0x00}, // ]
	{0x06,0x01,0x01,0x06}, // ^
	{0x40,0x40,0x00,0x00}, // _
	{0x06,0x00,0x00,0x00}, // `
	{0x30,0x49,0x49,0x36}, // a
	{0x36,0x48,0x48,0x30}, // b
	{0x36,0x41,0x41,0x00}, // c
	{0x30,0x48,0x48,0x36}, // d
	{0x36,0x49,0x49,0x00}, // e
	{0x36,0x09,0x09,0x00}, // f
	{0x06,0x49,0x49,0x36}, // g
	{0x36,0x08,0x08,0x30}, // h
	{0x36,0x00,0x00,0x00}, // i
	{0x40,0x40,0x36,0x00}, // j
	{0x36,0x08,0x08,0x36}, // k
	{0x36,0x00,0x00,0x00}, // l
	{0x36,0x01,0x01,0x36}, // m
	{0x36,0x01,0x01,0x36}, // n
	{0x36,0x41,0x41,0x36}, // o
	{0x36,0x09,0x09,0x06}, // p
	{0x06,0x09,0x09,0x36}, // q
	{0x36,0x01,0x01,0x00}, // r
	{0x06,0x49,0x49,0x30}, // s
	{0x36,0x48,0x48,0x00}, // t
	{0x36,0x40,0x40,0x36}, // u
	{0x36,0x40,0x40,0x36}, // v
	{0x36,0x40,0x40,0x36}, // w
	{0x36,0x08,0x08,0x36}, // x
	{0x06,0x48,0x48,0x36}, // y
	{0x30,0x49,0x49,0x06}, // z
	{0x36,0x41,0x41,0x00}, // {
	{0x36,0x00,0x00,0x00}, // |
	{0x41,0x41,0x36,0x00}, // }
	{0x30,0x08,0x08,0x06}, // ~
	{0x00,0x00,0x00,0x00}
};

const unsigned char aztech_font[96][6] = {
	{0x00,0x00,0x00,0x00,0x00,0x00}, //  
	{0x00,0x2e,0x00,0x00,0x00,0x00}, // !
	{0x00,0x02,0x00,0x02,0x00,0x00}, // "
	{0x00,0x0a,0x1e,0x0a,0x1e,0x00}, // #
	{0x00,0x0e,0x2a,0x6b,0x2a,0x3a}, // $
	{0x00,0x06,0x06,0x26,0x18,0x06}, // %
	{0x38,0x3e,0x2a,0x2a,0x28,0x38}, // &
	{0x18,0x02,0x00,0x00,0x00,0x00}, // '
	{0x00,0x3e,0x22,0x00,0x00,0x00}, // (
	{0x00,0x22,0x3e,0x00,0x00,0x00}, // )
	{0x00,0x0e,0x0e,0x0e,0x04,0x00}, // *
	{0x00,0x08,0x1c,0x08,0x00,0x00}, // +
	{0x00,0x20,0x00,0x00,0x00,0x00}, // ,
	{0x00,0x08,0x08,0x08,0x00,0x00}, // -
	{0x00,0x20,0x00,0x00,0x00,0x00}, // .
	{0x00,0x20,0x18,0x06,0x00,0x00}, // /
	{0x00,0x3e,0x22,0x2a,0x22,0x3e}, // 0
	{0x02,0x3e,0x00,0x00,0x00,0x00}, // 1
	{0x00,0x38,0x28,0x2a,0x2a,0x2e}, // 2
	{0x00,0x22,0x2a,0x2e,0x38,0x00}, // 3
	{0x00,0x0e,0x08,0x08,0x3e,0x08}, // 4
	{0x00,0x2e,0x2a,0x2a,0x28,0x38}, // 5
	{0x00,0x3e,0x2a,0x2a,0x28,0x38}, // 6
	{0x00,0x06,0x02,0x02,0x0a,0x3e}, // 7
	{0x00,0x38,0x2e,0x2a,0x2e,0x38}, // 8
	{0x00,0x0e,0x0a,0x2a,0x2a,0x3e}, // 9
	{0x00,0x28,0x00,0x00,0x00,0x00}, // :
	{0x00,0x28,0x00,0x00,0x00,0x00}, // ;
	{0x00,0x08,0x14,0x22,0x00,0x00}, // <
	{0x00,0x14,0x14,0x14,0x14,0x00}, // =
	{0x00,0x22,0x14,0x08,0x00,0x00}, // >
	{0x00,0x06,0x02,0x2a,0x0a,0x06}, // ?
	{0x00,0x3e,0x02,0x3a,0x2a,0x0a}, // @
	{0x22,0x3e,0x02,0x0a,0x0a,0x3e}, // A
	{0x00,0x3e,0x22,0x2a,0x2e,0x38}, // B
	{0x00,0x3e,0x22,0x22,0x20,0x30}, // C
	{0x00,0x3e,0x22,0x22,0x22,0x3c}, // D
	{0x00,0x3e,0x2a,0x22,0x20,0x30}, // E
	{0x00,0x3e,0x0a,0x0a,0x06,0x02}, // F
	{0x00,0x3e,0x22,0x2a,0x28,0x38}, // G
	{0x00,0x3e,0x08,0x08,0x08,0x3e}, // H
	{0x00,0x22,0x3e,0x22,0x00,0x00}, // I
	{0x00,0x30,0x20,0x20,0x22,0x3e}, // J
	{0x00,0x3e,0x08,0x08,0x0e,0x38}, // K
	{0x00,0x3e,0x20,0x20,0x20,0x30}, // L
	{0x00,0x3e,0x02,0x3e,0x20,0x3e}, // M
	{0x3e,0x3e,0x02,0x3e,0x20,0x3e}, // N
	{0x00,0x3e,0x22,0x22,0x22,0x3e}, // O
	{0x00,0x3e,0x02,0x0a,0x0a,0x0e}, // P
	{0x00,0x3e,0x22,0x22,0x22,0x3e}, // Q
	{0x00,0x3e,0x02,0x0a,0x0e,0x38}, // R
	{0x00,0x0e,0x0a,0x2a,0x2a,0x3a}, // S
	{0x00,0x06,0x02,0x3e,0x02,0x06}, // T
	{0x00,0x3e,0x20,0x20,0x20,0x3e}, // U
	{0x00,0x3e,0x20,0x20,0x3e,0x00}, // V
	{0x00,0x3e,0x20,0x3e,0x02,0x3e}, // W
	{0x3e,0x3a,0x0e,0x08,0x0e,0x3a}, // X
	{0x00,0x0e,0x08,0x08,0x28,0x3e}, // Y
	{0x00,0x3a,0x2a,0x2a,0x0a,0x0e}, // Z
	{0x00,0x3e,0x22,0x00,0x00,0x00}, // [
	{0x00,0x02,0x0c,0x30,0x00,0x00}, // "\"
	{0x22,0x3e,0x00,0x00,0x00,0x00}, // ]
	{0x00,0x01,0x00,0x01,0x00,0x00}, // ^
	{0x00,0x20,0x20,0x20,0x00,0x00}, // _
	{0x00,0x01,0x00,0x00,0x00,0x00}, // `
	{0x00,0x38,0x28,0x28,0x08,0x38}, // a
	{0x00,0x3e,0x20,0x28,0x28,0x38}, // b
	{0x00,0x38,0x28,0x28,0x20,0x30}, // c
	{0x00,0x38,0x28,0x28,0x20,0x3e}, // d
	{0x00,0xf8,0x88,0x28,0x28,0x38}, // e
	{0x00,0xf8,0x28,0x28,0x18,0x08}, // f
	{0x00,0x38,0x28,0xa8,0x88,0xf8}, // g
	{0x00,0x3c,0x08,0x08,0x08,0x38}, // h
	{0x00,0x3a,0x00,0x00,0x00,0x00}, // i
	{0x80,0xfa,0x00,0x00,0x00,0x00}, // j
	{0x00,0x3e,0x08,0x08,0x38,0x2c}, // k
	{0x00,0x3e,0x20,0x00,0x00,0x00}, // l
	{0x00,0x38,0x08,0x38,0x20,0x38}, // m
	{0x38,0x38,0x08,0x38,0x20,0x38}, // n
	{0x00,0x38,0x28,0x28,0x28,0x38}, // o
	{0x00,0xf8,0x08,0x28,0x28,0x38}, // p
	{0x00,0x38,0x28,0x28,0x08,0xf8}, // q
	{0x00,0x38,0x08,0x08,0x18,0x08}, // r
	{0x00,0x38,0x28,0xa8,0xa8,0xe8}, // s
	{0x00,0x3e,0x28,0x28,0x20,0x30}, // t
	{0x00,0x38,0x20,0x20,0x20,0x38}, // u
	{0x00,0x38,0x20,0x38,0x00,0x00}, // v
	{0x00,0x38,0x20,0x38,0x08,0x38}, // w
	{0x38,0x28,0x38,0x10,0x38,0x28}, // x
	{0x00,0x38,0x20,0xa0,0xa0,0xf8}, // y
	{0x00,0xe8,0xa8,0xa8,0x28,0x38}, // z
	{0x08,0x3e,0x22,0x00,0x00,0x00}, // {
	{0x00,0x3f,0x00,0x00,0x00,0x00}, // |
	{0x22,0x3e,0x08,0x00,0x00,0x00}, // }
	{0x00,0x00,0x00,0x00,0x00,0x00}, // ~
	{0x00,0x00,0x00,0x00,0x00,0x00}
};

const unsigned char blokus_font[96][6] = {
	{0x00,0x00,0x00,0x00,0x00,0x00}, //  
	{0x00,0x00,0x5e,0x00,0x00,0x00}, // !
	{0x00,0x0e,0x00,0x0e,0x00,0x00}, // "
	{0xd0,0x70,0xdc,0x70,0x58,0x00}, // #
	{0x26,0x4a,0xff,0x52,0x22,0x00}, // $
	{0x00,0x46,0x2a,0x1a,0x0e,0x04}, // %
	{0x7e,0x76,0x42,0x45,0x6b,0x51}, // &
	{0x00,0x00,0x0e,0x02,0x00,0x00}, // '
	{0x00,0x7e,0x81,0x00,0x00,0x00}, // (
	{0x00,0x81,0x7e,0x00,0x00,0x00}, // )
	{0x00,0x1c,0x00,0x00,0x00,0x00}, // *
	{0x00,0x20,0x7c,0x20,0x00,0x00}, // +
	{0x00,0x00,0x80,0x60,0x00,0x00}, // ,
	{0x00,0x10,0x10,0x10,0x00,0x00}, // -
	{0x00,0x40,0x00,0x00,0x00,0x00}, // .
	{0x00,0xfe,0x00,0x00,0x00,0x00}, // /
	{0x00,0x30,0x48,0x48,0x30,0x00}, // 0
	{0x10,0x48,0x78,0x40,0x00,0x00}, // 1
	{0x00,0x42,0x62,0x52,0x4a,0x46}, // 2
	{0x00,0x88,0x28,0x38,0xc0,0x00}, // 3
	{0x00,0x20,0x50,0x48,0x48,0xe0}, // 4
	{0xf0,0x28,0x28,0xc8,0x48,0x00}, // 5
	{0x00,0x38,0x4c,0x46,0x26,0x1a}, // 6
	{0x08,0x88,0x48,0x28,0x18,0x08}, // 7
	{0x14,0x2a,0x46,0x2a,0x14,0x00}, // 8
	{0x00,0x30,0x48,0x48,0xa8,0x78}, // 9
	{0x00,0x00,0x48,0x00,0x00,0x00}, // :
	{0x00,0x00,0x80,0x68,0x00,0x00}, // ;
	{0x08,0x14,0x22,0x41,0x00,0x00}, // <
	{0x00,0x30,0x30,0x30,0x30,0x00}, // =
	{0x41,0x22,0x14,0x08,0x00,0x00}, // >
	{0x00,0x02,0x52,0x0a,0x06,0x00}, // ?
	{0x00,0x38,0x44,0x42,0xa2,0xbc}, // @
	{0x20,0x40,0x62,0x14,0x12,0x14}, // A
	{0x62,0x7e,0x4a,0x4a,0x34,0x00}, // B
	{0x1c,0x22,0x42,0x42,0x42,0x24}, // C
	{0x42,0x7e,0x42,0x42,0x24,0x18}, // D
	{0x42,0x7e,0x4a,0x4a,0x42,0x00}, // E
	{0x00,0x42,0x7e,0x0a,0x02,0x00}, // F
	{0x1c,0x22,0x42,0x52,0xe4,0x00}, // G
	{0x00,0x42,0x7e,0x08,0x7e,0x42}, // H
	{0x00,0x42,0x7e,0x42,0x00,0x00}, // I
	{0x02,0x82,0x7e,0x02,0x00,0x00}, // J
	{0x00,0x42,0x7e,0x08,0x08,0x16}, // K
	{0x00,0x42,0x7e,0x40,0x60,0x00}, // L
	{0x00,0x7e,0x44,0x08,0x10,0x08}, // M
	{0x00,0x7e,0x42,0x04,0x08,0x08}, // N
	{0x7e,0x24,0x42,0x42,0x24,0x18}, // O
	{0x02,0x7e,0x52,0x12,0x0c,0x00}, // P
	{0x18,0x24,0x42,0x42,0xa4,0x18}, // Q
	{0x42,0x7e,0x46,0x0e,0x16,0x20}, // R
	{0xf3,0xc6,0x46,0x4a,0x37,0x00}, // S
	{0x02,0x02,0x7e,0x02,0x02,0x00}, // T
	{0x00,0x02,0x3e,0x40,0x3e,0x02}, // U
	{0x02,0x1e,0x20,0x40,0x20,0x12}, // V
	{0x02,0x0e,0x20,0x40,0x22,0x1e}, // W
	{0x42,0x66,0x1a,0x1e,0x66,0x42}, // X
	{0x02,0x0a,0x50,0x60,0x50,0x0a}, // Y
	{0x02,0x42,0x62,0x4a,0x42,0x20}, // Z
	{0x00,0x00,0xfe,0x82,0x00,0x00}, // [
	{0x00,0xfe,0x00,0x00,0x00,0x00}, // "\"
	{0x00,0x82,0xfe,0x00,0x00,0x00}, // ]
	{0x00,0x1c,0x06,0x18,0x00,0x00}, // ^
	{0x80,0x80,0x80,0x80,0x80,0x00}, // _
	{0x00,0x00,0x02,0x00,0x00,0x00}, // `
	{0x28,0x58,0x58,0x78,0x40,0x00}, // a
	{0x40,0x3f,0x48,0x48,0x38,0x00}, // b
	{0x30,0x48,0x48,0x30,0x00,0x00}, // c
	{0x38,0x48,0x48,0x3f,0x40,0x00}, // d
	{0x30,0x68,0x68,0x30,0x00,0x00}, // e
	{0x48,0x7f,0x09,0x02,0x00,0x00}, // f
	{0x98,0x68,0x68,0x58,0x84,0x00}, // g
	{0x40,0x7f,0x08,0x48,0x78,0x40}, // h
	{0x00,0x78,0x40,0x00,0x00,0x00}, // i
	{0x08,0xfa,0x08,0x00,0x00,0x00}, // j
	{0x40,0x7f,0x08,0x14,0x28,0x48}, // k
	{0x7e,0x40,0x00,0x00,0x00,0x00}, // l
	{0x48,0x78,0x48,0x78,0x48,0x78}, // m
	{0x48,0x78,0x08,0x48,0x78,0x40}, // n
	{0x30,0x48,0x48,0x30,0x00,0x00}, // o
	{0x08,0xf0,0x48,0x48,0x30,0x00}, // p
	{0x30,0x48,0x48,0xf0,0x08,0x00}, // q
	{0x40,0x78,0x00,0x08,0x00,0x00}, // r
	{0x30,0x68,0x68,0x10,0x00,0x00}, // s
	{0x08,0x3e,0x48,0x48,0x20,0x00}, // t
	{0x08,0x78,0x38,0x48,0x00,0x00}, // u
	{0x18,0x40,0x20,0x18,0x08,0x00}, // v
	{0x38,0x40,0x38,0x40,0x38,0x40}, // w
	{0x48,0x28,0x10,0x28,0x48,0x00}, // x
	{0x08,0x38,0x48,0xf8,0x00,0x00}, // y
	{0x48,0x68,0x58,0x48,0x00,0x00}, // z
	{0x00,0x00,0x10,0x6c,0x82,0x00}, // {
	{0x00,0x00,0x7e,0x00,0x00,0x00}, // |
	{0x00,0x00,0x82,0x6c,0x10,0x00}, // }
	{0x00,0x20,0x10,0x20,0x10,0x00}, // ~
	{0x00,0x00,0x00,0x00,0x00,0x00}
};

const unsigned char bubblesstandard_font[96][7] = {
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //  
	{0xbf,0x00,0x00,0x00,0x00,0x00,0x00}, // !
	{0x03,0x00,0x03,0x00,0x00,0x00,0x00}, // "
	{0x24,0x7e,0x24,0x24,0x7e,0x24,0x00}, // #
	{0x44,0x4a,0xd3,0x22,0x00,0x00,0x00}, // $
	{0x82,0x60,0x18,0x06,0x21,0x00,0x00}, // %
	{0x60,0x90,0x8e,0xb9,0x46,0xb0,0x00}, // &
	{0x03,0x00,0x00,0x00,0x00,0x00,0x00}, // '
	{0x7e,0x81,0x81,0x00,0x00,0x00,0x00}, // (
	{0x81,0x81,0x7e,0x00,0x00,0x00,0x00}, // )
	{0x02,0x0e,0x05,0x0e,0x02,0x00,0x00}, // *
	{0x10,0x38,0x10,0x00,0x00,0x00,0x00}, // +
	{0x80,0x00,0x00,0x00,0x00,0x00,0x00}, // ,
	{0x10,0x10,0x10,0x00,0x00,0x00,0x00}, // -
	{0x80,0x00,0x00,0x00,0x00,0x00,0x00}, // .
	{0x80,0x60,0x18,0x06,0x01,0x00,0x00}, // /
	{0x7e,0x81,0x81,0x7e,0x00,0x00,0x00}, // 0
	{0x88,0x86,0x7f,0x40,0x00,0x00,0x00}, // 1
	{0x82,0xc5,0xb1,0x8e,0x40,0x00,0x00}, // 2
	{0x66,0x81,0x89,0x76,0x00,0x00,0x00}, // 3
	{0x10,0x18,0x16,0xff,0x08,0x00,0x00}, // 4
	{0x4e,0x8a,0x8a,0x91,0x61,0x00,0x00}, // 5
	{0x20,0x78,0x96,0x91,0x60,0x00,0x00}, // 6
	{0x02,0x02,0xc1,0x39,0x07,0x00,0x00}, // 7
	{0x76,0x89,0x89,0x76,0x00,0x00,0x00}, // 8
	{0x06,0x09,0x09,0xfe,0x00,0x00,0x00}, // 9
	{0x81,0x00,0x00,0x00,0x00,0x00,0x00}, // :
	{0x81,0x00,0x00,0x00,0x00,0x00,0x00}, // ;
	{0x10,0x28,0x00,0x00,0x00,0x00,0x00}, // <
	{0x28,0x28,0x28,0x00,0x00,0x00,0x00}, // =
	{0x28,0x10,0x00,0x00,0x00,0x00,0x00}, // >
	{0x06,0x01,0xb1,0x0e,0x00,0x00,0x00}, // ?
	{0x3c,0x42,0x99,0xa5,0xbd,0xa2,0x1c}, // @
	{0x50,0x30,0x1c,0x23,0x5c,0xe0,0x00}, // A
	{0x82,0x7f,0x49,0x36,0x00,0x00,0x00}, // B
	{0x3c,0x42,0x81,0x89,0x86,0x60,0x00}, // C
	{0x42,0xff,0xa1,0xa1,0x82,0x7c,0x00}, // D
	{0x76,0x89,0x81,0x8a,0x70,0x00,0x00}, // E
	{0x90,0x70,0x1e,0x0a,0x0a,0x01,0x01}, // F
	{0x3c,0x42,0x81,0xb1,0xaa,0x48,0x30}, // G
	{0x45,0x3e,0x08,0x1c,0x6a,0x80,0x00}, // H
	{0x84,0x82,0xff,0x41,0x40,0x00,0x00}, // I
	{0x60,0x90,0x81,0x7f,0x02,0x00,0x00}, // J
	{0x7e,0x08,0x16,0x61,0x80,0x00,0x00}, // K
	{0x02,0xff,0x80,0x40,0x40,0x20,0x00}, // L
	{0x01,0x7e,0x01,0x06,0x18,0x06,0x01}, // M
	{0x80,0x7f,0x02,0x0c,0x30,0x40,0x3e}, // N
	{0x3c,0x42,0x8d,0x83,0x42,0x3c,0x00}, // O
	{0x8a,0x7f,0x11,0x11,0x0e,0x00,0x00}, // P
	{0x3c,0x42,0x81,0xa3,0xa3,0x45,0xb8}, // Q
	{0x92,0x7f,0x09,0x09,0x36,0x40,0x00}, // R
	{0x60,0x8e,0x91,0xa1,0x46,0x00,0x00}, // S
	{0x02,0x02,0x7f,0x81,0x01,0x00,0x00}, // T
	{0x3e,0x41,0x80,0x80,0x80,0x42,0x3c}, // U
	{0x01,0x06,0x38,0xc0,0x30,0x0e,0x01}, // V
	{0x01,0x0e,0x30,0x40,0x20,0x18,0x60}, // W
	{0x82,0x80,0x41,0x32,0x0c,0x38,0x44}, // X
	{0x01,0x0e,0xf0,0x0c,0x03,0x00,0x00}, // Y
	{0x04,0xc2,0xb2,0x8d,0x43,0x40,0x20}, // Z
	{0xff,0x81,0x00,0x00,0x00,0x00,0x00}, // [
	{0x80,0x60,0x18,0x06,0x01,0x00,0x00}, // "\"
	{0x81,0xff,0x00,0x00,0x00,0x00,0x00}, // ]
	{0x08,0x06,0x01,0x0e,0x10,0x00,0x00}, // ^
	{0x80,0x80,0x80,0x00,0x00,0x00,0x00}, // _
	{0x03,0x04,0x00,0x00,0x00,0x00,0x00}, // `
	{0x64,0x92,0x92,0x92,0xfc,0x90,0x00}, // a
	{0x50,0xfe,0x89,0x88,0x70,0x00,0x00}, // b
	{0x78,0x84,0x82,0x82,0x84,0x60,0x00}, // c
	{0x70,0x88,0x88,0xfe,0x51,0x00,0x00}, // d
	{0x7c,0x92,0x92,0x8a,0x64,0x10,0x00}, // e
	{0x90,0x7e,0x09,0x01,0x00,0x00,0x00}, // f
	{0x00,0x78,0x84,0x84,0xfe,0x44,0x00}, // g
	{0x01,0x7e,0x08,0x08,0x70,0x80,0x00}, // h
	{0x04,0x7d,0x80,0x00,0x00,0x00,0x00}, // i
	{0x00,0xfd,0x04,0x00,0x00,0x00,0x00}, // j
	{0x81,0x7e,0x08,0x34,0x40,0x00,0x00}, // k
	{0x01,0x7e,0x80,0x00,0x00,0x00,0x00}, // l
	{0x3e,0x04,0x04,0x18,0x04,0x04,0x78}, // m
	{0x7e,0x04,0x04,0x78,0x80,0x00,0x00}, // n
	{0x7c,0x82,0x86,0x84,0x78,0x00,0x00}, // o
	{0x48,0xfe,0x84,0x84,0x78,0x00,0x00}, // p
	{0x78,0x84,0x84,0xfe,0x48,0x00,0x00}, // q
	{0x82,0x7c,0x02,0x02,0x04,0x00,0x00}, // r
	{0x60,0x8c,0x92,0x62,0x04,0x00,0x00}, // s
	{0x08,0x7f,0x84,0x90,0x60,0x00,0x00}, // t
	{0x02,0x7c,0x80,0x80,0x80,0x78,0x80}, // u
	{0x02,0x0c,0x70,0x80,0x78,0x04,0x00}, // v
	{0x02,0x0c,0x70,0x80,0x60,0x18,0x60}, // w
	{0x86,0x64,0x18,0x66,0x80,0x00,0x00}, // x
	{0x02,0x7c,0x80,0x80,0xf8,0x00,0x00}, // y
	{0x08,0x84,0xc4,0xb2,0x8e,0x40,0x00}, // z
	{0xee,0x01,0x00,0x00,0x00,0x00,0x00}, // {
	{0xff,0x00,0x00,0x00,0x00,0x00,0x00}, // |
	{0x01,0xee,0x10,0x00,0x00,0x00,0x00}, // }
	{0x10,0x08,0x08,0x10,0x10,0x08,0x00}, // ~
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};

const unsigned char font[96][5] = {
	{0x00,0x00,0x00,0x00,0x00}, //  
	{0x00,0x00,0xbe,0x00,0x00}, // !
	{0x00,0x07,0x00,0x07,0x00}, // "
	{0x48,0xfc,0x48,0xfc,0x48}, // #
	{0x48,0x54,0xfe,0x54,0x24}, // $
	{0x88,0x54,0x28,0x50,0xa8}, // %
	{0x6c,0x92,0x92,0xac,0x40}, // &
	{0xa0,0x00,0x07,0x00,0x00}, // '
	{0x00,0x7c,0x82,0x01,0x00}, // (
	{0x00,0x01,0x82,0x7c,0x00}, // )
	{0x28,0x10,0x7c,0x10,0x28}, // *
	{0x10,0x10,0x7c,0x10,0x10}, // +
	{0x00,0x00,0x80,0x00,0x00}, // ,
	{0x10,0x10,0x10,0x10,0x10}, // -
	{0x00,0x00,0x80,0x00,0x00}, // .
	{0x00,0xc0,0x30,0x0c,0x03}, // /
	{0x7c,0x82,0x92,0x82,0x7c}, // 0
	{0x00,0x84,0xfe,0x80,0x00}, // 1
	{0xc4,0xa2,0x92,0x92,0x8c}, // 2
	{0x44,0x82,0x92,0x92,0x6c}, // 3
	{0x30,0x28,0x24,0xfe,0x20}, // 4
	{0x5e,0x92,0x92,0x92,0x62}, // 5
	{0x78,0x94,0x92,0x92,0x60}, // 6
	{0x02,0x82,0x62,0x1a,0x06}, // 7
	{0x6c,0x92,0x92,0x92,0x6c}, // 8
	{0x0c,0x92,0x92,0x52,0x3c}, // 9
	{0x00,0x00,0x48,0x00,0x00}, // :
	{0x00,0x80,0x48,0x00,0x00}, // ;
	{0x10,0x10,0x28,0x28,0x44}, // <
	{0x28,0x28,0x28,0x28,0x28}, // =
	{0x44,0x28,0x28,0x10,0x10}, // >
	{0x04,0x02,0xa2,0x12,0x0c}, // ?
	{0x7c,0x82,0xba,0xba,0xa2}, // @
	{0xfc,0x38,0x26,0x38,0xc0}, // A
	{0xfe,0x92,0x92,0x92,0x6c}, // B
	{0x7c,0x82,0x82,0x82,0x44}, // C
	{0xfe,0x82,0x82,0x44,0x38}, // D
	{0xfe,0x92,0x92,0x92,0x82}, // E
	{0xfe,0x12,0x12,0x12,0x02}, // F
	{0x7c,0x82,0x82,0x92,0xf4}, // G
	{0xfe,0x10,0x10,0x10,0xfe}, // H
	{0x00,0x82,0xfe,0x82,0x00}, // I
	{0x80,0x80,0x82,0x82,0x7e}, // J
	{0xfe,0x10,0x28,0x44,0x82}, // K
	{0xfe,0x80,0x80,0x80,0x80}, // L
	{0xfe,0x18,0x60,0x18,0xfe}, // M
	{0xfe,0x06,0x38,0xc0,0xfe}, // N
	{0x7c,0x82,0x82,0x82,0x7c}, // O
	{0xfe,0x12,0x12,0x12,0x0c}, // P
	{0x7c,0x82,0x82,0xc2,0xfc}, // Q
	{0xfe,0x12,0x12,0x12,0xec}, // R
	{0x4c,0x92,0x92,0x92,0x64}, // S
	{0x02,0x02,0xfe,0x02,0x02}, // T
	{0x7e,0x80,0x80,0x80,0x7e}, // U
	{0x0e,0x30,0xc0,0x30,0x0e}, // V
	{0x1e,0xe0,0x1c,0xe0,0x1e}, // W
	{0xc6,0x28,0x10,0x28,0xc6}, // X
	{0x0e,0x10,0xf0,0x10,0x0e}, // Y
	{0xc2,0xa2,0x92,0x8a,0x86}, // Z
	{0x00,0xff,0x01,0x01,0x00}, // [
	{0x03,0x0c,0x30,0xc0,0x00}, // "\"
	{0x00,0x01,0x01,0xff,0x00}, // ]
	{0x08,0x04,0x02,0x04,0x08}, // ^
	{0x00,0x00,0x00,0x00,0x00}, // _
	{0x00,0x00,0x02,0x04,0x00}, // `
	{0x40,0xa8,0xa8,0xa8,0xf0}, // a
	{0xff,0x88,0x88,0x88,0x70}, // b
	{0x70,0x88,0x88,0x88,0x88}, // c
	{0x70,0x88,0x88,0x88,0xff}, // d
	{0x70,0xa8,0xa8,0xa8,0xb0}, // e
	{0x08,0xfe,0x09,0x09,0x01}, // f
	{0x70,0x88,0x88,0x88,0xf0}, // g
	{0xff,0x08,0x08,0x08,0xf0}, // h
	{0x00,0x08,0xfa,0x00,0x00}, // i
	{0x00,0x00,0x08,0xfa,0x00}, // j
	{0x00,0xff,0x20,0x50,0x88}, // k
	{0x00,0x01,0xff,0x00,0x00}, // l
	{0xf8,0x08,0xf0,0x08,0xf0}, // m
	{0xf8,0x08,0x08,0x08,0xf0}, // n
	{0x70,0x88,0x88,0x88,0x70}, // o
	{0xf8,0x88,0x88,0x88,0x70}, // p
	{0x70,0x88,0x88,0x88,0xf8}, // q
	{0xf8,0x10,0x08,0x08,0x10}, // r
	{0x90,0xa8,0xa8,0xa8,0x48}, // s
	{0x00,0x7e,0x88,0x88,0x80}, // t
	{0x78,0x80,0x80,0x80,0xf8}, // u
	{0x18,0x60,0x80,0x60,0x18}, // v
	{0x38,0xc0,0x30,0xc0,0x38}, // w
	{0x88,0x50,0x20,0x50,0x88}, // x
	{0x78,0x80,0x80,0x80,0xf8}, // y
	{0x88,0xc8,0xa8,0x98,0x88}, // z
	{0x00,0x10,0xee,0x01,0x00}, // {
	{0x00,0x00,0xff,0x00,0x00}, // |
	{0x00,0x01,0xee,0x10,0x00}, // }
	{0x20,0x10,0x10,0x20,0x20}, // ~
	{0x00,0x00,0x00,0x00,0x00}
};

const unsigned char formplex12_font[96][8] = {
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //  
	{0x00,0x2f,0x2f,0x00,0x00,0x00,0x00,0x00}, // !
	{0x03,0x03,0x00,0x03,0x03,0x00,0x00,0x00}, // "
	{0x14,0x3e,0x3e,0x14,0x3e,0x3e,0x14,0x00}, // #
	{0x24,0x2e,0x2a,0x7f,0x7f,0x3a,0x3a,0x00}, // $
	{0x26,0x36,0x18,0x0c,0x36,0x32,0x00,0x00}, // %
	{0x1a,0x3f,0x25,0x25,0x3f,0x1a,0x28,0x28}, // &
	{0x00,0x03,0x03,0x00,0x00,0x00,0x00,0x00}, // '
	{0x00,0x3e,0x7f,0x41,0x41,0x41,0x00,0x00}, // (
	{0x00,0x41,0x41,0x41,0x7f,0x3e,0x00,0x00}, // )
	{0x08,0x2a,0x3e,0x1c,0x3e,0x2a,0x08,0x00}, // *
	{0x08,0x08,0x3e,0x3e,0x08,0x08,0x00,0x00}, // +
	{0x00,0x70,0x70,0x00,0x00,0x00,0x00,0x00}, // ,
	{0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00}, // -
	{0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00}, // .
	{0x20,0x30,0x18,0x0c,0x06,0x02,0x00,0x00}, // /
	{0x1c,0x3e,0x32,0x2a,0x2a,0x3e,0x3e,0x00}, // 0
	{0x00,0x24,0x3e,0x3e,0x20,0x00,0x00,0x00}, // 1
	{0x3a,0x3a,0x2a,0x2a,0x2a,0x2e,0x24,0x00}, // 2
	{0x2a,0x2a,0x2a,0x2a,0x2a,0x3e,0x14,0x00}, // 3
	{0x06,0x0e,0x08,0x08,0x08,0x3e,0x3e,0x00}, // 4
	{0x2e,0x2e,0x2a,0x2a,0x2a,0x3a,0x12,0x00}, // 5
	{0x1c,0x3e,0x2a,0x2a,0x2a,0x3a,0x10,0x00}, // 6
	{0x02,0x02,0x02,0x02,0x02,0x3e,0x3c,0x00}, // 7
	{0x14,0x3e,0x2a,0x2a,0x2a,0x3e,0x14,0x00}, // 8
	{0x04,0x0e,0x0a,0x0a,0x0a,0x7e,0x7c,0x00}, // 9
	{0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00}, // :
	{0x00,0x16,0x36,0x20,0x00,0x00,0x00,0x00}, // ;
	{0x00,0x08,0x1c,0x36,0x22,0x22,0x00,0x00}, // <
	{0x14,0x14,0x14,0x14,0x14,0x00,0x00,0x00}, // =
	{0x00,0x22,0x22,0x36,0x1c,0x08,0x00,0x00}, // >
	{0x00,0x01,0x2d,0x2f,0x06,0x00,0x00,0x00}, // ?
	{0x1e,0x3f,0x21,0x2d,0x2d,0x29,0x06,0x06}, // @
	{0x3c,0x3e,0x02,0x0a,0x0a,0x3e,0x3c,0x00}, // A
	{0x3e,0x3e,0x22,0x2a,0x2a,0x3e,0x14,0x00}, // B
	{0x1c,0x3e,0x22,0x22,0x22,0x22,0x22,0x00}, // C
	{0x3e,0x3e,0x02,0x22,0x22,0x3e,0x1c,0x00}, // D
	{0x1c,0x3e,0x22,0x2a,0x2a,0x2a,0x22,0x00}, // E
	{0x3c,0x3e,0x02,0x0a,0x0a,0x0a,0x02,0x00}, // F
	{0x1c,0x3e,0x22,0x22,0x22,0x3a,0x18,0x00}, // G
	{0x3e,0x3e,0x00,0x08,0x08,0x3e,0x3e,0x00}, // H
	{0x3e,0x3e,0x00,0x00,0x00,0x00,0x00,0x00}, // I
	{0x20,0x20,0x20,0x20,0x30,0x3e,0x1e,0x00}, // J
	{0x3e,0x3e,0x00,0x08,0x08,0x3e,0x36,0x00}, // K
	{0x1e,0x3e,0x30,0x20,0x20,0x20,0x20,0x00}, // L
	{0x3e,0x3e,0x02,0x3a,0x02,0x3e,0x3c,0x00}, // M
	{0x3c,0x3e,0x02,0x02,0x02,0x3e,0x3c,0x00}, // N
	{0x1c,0x3e,0x22,0x22,0x22,0x3e,0x1c,0x00}, // O
	{0x3c,0x3e,0x02,0x0a,0x0a,0x0e,0x04,0x00}, // P
	{0x1c,0x3e,0x22,0x22,0x32,0x3e,0x3c,0x00}, // Q
	{0x3c,0x3e,0x02,0x0a,0x0a,0x3e,0x34,0x00}, // R
	{0x24,0x2e,0x2a,0x2a,0x2a,0x3a,0x12,0x00}, // S
	{0x02,0x02,0x3e,0x3e,0x02,0x02,0x00,0x00}, // T
	{0x1e,0x3e,0x20,0x20,0x20,0x3e,0x1e,0x00}, // U
	{0x0e,0x1e,0x30,0x20,0x30,0x1e,0x0e,0x00}, // V
	{0x1e,0x3e,0x20,0x2e,0x20,0x3e,0x3e,0x00}, // W
	{0x36,0x3e,0x08,0x08,0x3e,0x36,0x00,0x00}, // X
	{0x06,0x0e,0x38,0x38,0x0e,0x06,0x00,0x00}, // Y
	{0x32,0x32,0x3a,0x2a,0x2e,0x26,0x26,0x00}, // Z
	{0x00,0x7f,0x7f,0x41,0x41,0x41,0x00,0x00}, // [
	{0x02,0x06,0x0c,0x18,0x30,0x20,0x00,0x00}, // "\"
	{0x00,0x41,0x41,0x41,0x7f,0x7f,0x00,0x00}, // ]
	{0x01,0x01,0x00,0x01,0x01,0x00,0x00,0x00}, // ^
	{0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00}, // _
	{0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00}, // `
	{0x3c,0x3e,0x02,0x0a,0x0a,0x3e,0x3c,0x00}, // a
	{0x3e,0x3e,0x22,0x2a,0x2a,0x3e,0x14,0x00}, // b
	{0x1c,0x3e,0x22,0x22,0x22,0x22,0x22,0x00}, // c
	{0x3e,0x3e,0x02,0x22,0x22,0x3e,0x1c,0x00}, // d
	{0x1c,0x3e,0x22,0x2a,0x2a,0x2a,0x22,0x00}, // e
	{0x3c,0x3e,0x02,0x0a,0x0a,0x0a,0x02,0x00}, // f
	{0x1c,0x3e,0x22,0x22,0x22,0x3a,0x18,0x00}, // g
	{0x3e,0x3e,0x00,0x08,0x08,0x3e,0x3e,0x00}, // h
	{0x3e,0x3e,0x00,0x00,0x00,0x00,0x00,0x00}, // i
	{0x20,0x20,0x20,0x20,0x30,0x3e,0x1e,0x00}, // j
	{0x3e,0x3e,0x00,0x08,0x08,0x3e,0x36,0x00}, // k
	{0x1e,0x3e,0x30,0x20,0x20,0x20,0x20,0x00}, // l
	{0x3e,0x3e,0x02,0x3a,0x02,0x3e,0x3c,0x00}, // m
	{0x3c,0x3e,0x02,0x02,0x02,0x3e,0x3c,0x00}, // n
	{0x1c,0x3e,0x22,0x22,0x22,0x3e,0x1c,0x00}, // o
	{0x3c,0x3e,0x02,0x0a,0x0a,0x0e,0x04,0x00}, // p
	{0x1c,0x3e,0x22,0x22,0x32,0x3e,0x3c,0x00}, // q
	{0x3c,0x3e,0x02,0x0a,0x0a,0x3e,0x34,0x00}, // r
	{0x24,0x2e,0x2a,0x2a,0x2a,0x3a,0x12,0x00}, // s
	{0x02,0x02,0x3e,0x3e,0x02,0x02,0x00,0x00}, // t
	{0x1e,0x3e,0x20,0x20,0x20,0x3e,0x1e,0x00}, // u
	{0x0e,0x1e,0x30,0x20,0x30,0x1e,0x0e,0x00}, // v
	{0x1e,0x3e,0x20,0x2e,0x20,0x3e,0x3e,0x00}, // w
	{0x36,0x3e,0x08,0x08,0x3e,0x36,0x00,0x00}, // x
	{0x06,0x0e,0x38,0x38,0x0e,0x06,0x00,0x00}, // y
	{0x32,0x32,0x3a,0x2a,0x2e,0x26,0x26,0x00}, // z
	{0x00,0x08,0x7f,0x77,0x41,0x41,0x00,0x00}, // {
	{0x7f,0x7f,0x00,0x00,0x00,0x00,0x00,0x00}, // |
	{0x00,0x41,0x41,0x77,0x7f,0x08,0x00,0x00}, // }
	{0x00,0x04,0x06,0x02,0x04,0x06,0x02,0x00}, // ~
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};

const unsigned char minimum_font[96][6] = {
	{0x00,0x00,0x00,0x00,0x00,0x00}, //  
	{0x2e,0x00,0x00,0x00,0x00,0x00}, // !
	{0x06,0x00,0x06,0x00,0x00,0x00}, // "
	{0x14,0x3e,0x14,0x3e,0x14,0x00}, // #
	{0x04,0x2a,0x3e,0x2a,0x10,0x00}, // $
	{0x22,0x10,0x08,0x04,0x22,0x00}, // %
	{0x14,0x2a,0x2a,0x2c,0x10,0x28}, // &
	{0x06,0x00,0x00,0x00,0x00,0x00}, // '
	{0x1c,0x22,0x00,0x00,0x00,0x00}, // (
	{0x22,0x1c,0x00,0x00,0x00,0x00}, // )
	{0x14,0x08,0x14,0x00,0x00,0x00}, // *
	{0x08,0x1c,0x08,0x00,0x00,0x00}, // +
	{0x60,0x00,0x00,0x00,0x00,0x00}, // ,
	{0x08,0x08,0x08,0x00,0x00,0x00}, // -
	{0x20,0x00,0x00,0x00,0x00,0x00}, // .
	{0x30,0x0c,0x02,0x00,0x00,0x00}, // /
	{0x1c,0x22,0x22,0x22,0x1e,0x00}, // 0
	{0x02,0x3e,0x00,0x00,0x00,0x00}, // 1
	{0x32,0x2a,0x2a,0x24,0x00,0x00}, // 2
	{0x2a,0x2a,0x2a,0x16,0x00,0x00}, // 3
	{0x0e,0x10,0x10,0x3e,0x10,0x00}, // 4
	{0x2e,0x2a,0x2a,0x12,0x00,0x00}, // 5
	{0x3c,0x2a,0x2a,0x2a,0x12,0x00}, // 6
	{0x06,0x02,0x22,0x12,0x0e,0x00}, // 7
	{0x14,0x2a,0x2a,0x2a,0x16,0x00}, // 8
	{0x04,0x2a,0x2a,0x2a,0x1e,0x00}, // 9
	{0x24,0x00,0x00,0x00,0x00,0x00}, // :
	{0x64,0x00,0x00,0x00,0x00,0x00}, // ;
	{0x08,0x14,0x22,0x00,0x00,0x00}, // <
	{0x14,0x14,0x14,0x00,0x00,0x00}, // =
	{0x22,0x14,0x08,0x00,0x00,0x00}, // >
	{0x02,0x2a,0x0a,0x04,0x00,0x00}, // ?
	{0x3c,0x02,0x1a,0x2a,0x22,0x1e}, // @
	{0x3c,0x12,0x12,0x12,0x3e,0x00}, // A
	{0x3c,0x2a,0x2a,0x2e,0x10,0x00}, // B
	{0x1c,0x22,0x22,0x22,0x00,0x00}, // C
	{0x3c,0x22,0x22,0x22,0x1c,0x00}, // D
	{0x3c,0x2a,0x2a,0x2a,0x00,0x00}, // E
	{0x3c,0x12,0x12,0x12,0x00,0x00}, // F
	{0x3c,0x22,0x22,0x2a,0x1a,0x00}, // G
	{0x3e,0x08,0x08,0x3e,0x00,0x00}, // H
	{0x22,0x3e,0x22,0x00,0x00,0x00}, // I
	{0x30,0x22,0x22,0x1e,0x00,0x00}, // J
	{0x3e,0x08,0x0c,0x32,0x00,0x00}, // K
	{0x3e,0x20,0x20,0x20,0x00,0x00}, // L
	{0x3c,0x02,0x02,0x3c,0x02,0x02}, // M
	{0x3c,0x02,0x02,0x02,0x3e,0x00}, // N
	{0x1c,0x22,0x22,0x22,0x1e,0x00}, // O
	{0x3c,0x12,0x12,0x12,0x0e,0x00}, // P
	{0x1c,0x22,0x22,0x62,0x1e,0x00}, // Q
	{0x3c,0x12,0x12,0x32,0x0e,0x00}, // R
	{0x24,0x2a,0x2a,0x12,0x00,0x00}, // S
	{0x02,0x02,0x3e,0x02,0x02,0x00}, // T
	{0x1e,0x20,0x20,0x20,0x1e,0x00}, // U
	{0x0e,0x10,0x20,0x10,0x0e,0x00}, // V
	{0x3e,0x20,0x20,0x1e,0x20,0x20}, // W
	{0x36,0x08,0x08,0x36,0x00,0x00}, // X
	{0x26,0x28,0x28,0x1e,0x00,0x00}, // Y
	{0x32,0x2a,0x2a,0x26,0x00,0x00}, // Z
	{0x3e,0x22,0x00,0x00,0x00,0x00}, // [
	{0x02,0x0c,0x30,0x00,0x00,0x00}, // "\"
	{0x22,0x3e,0x00,0x00,0x00,0x00}, // ]
	{0x04,0x02,0x04,0x00,0x00,0x00}, // ^
	{0x20,0x20,0x20,0x00,0x00,0x00}, // _
	{0x02,0x04,0x00,0x00,0x00,0x00}, // `
	{0x3c,0x12,0x12,0x12,0x3e,0x00}, // a
	{0x3c,0x2a,0x2a,0x2e,0x10,0x00}, // b
	{0x1c,0x22,0x22,0x22,0x00,0x00}, // c
	{0x3c,0x22,0x22,0x22,0x1c,0x00}, // d
	{0x3c,0x2a,0x2a,0x2a,0x00,0x00}, // e
	{0x3c,0x12,0x12,0x12,0x00,0x00}, // f
	{0x3c,0x22,0x22,0x2a,0x1a,0x00}, // g
	{0x3e,0x08,0x08,0x3e,0x00,0x00}, // h
	{0x22,0x3e,0x22,0x00,0x00,0x00}, // i
	{0x30,0x22,0x22,0x1e,0x00,0x00}, // j
	{0x3e,0x08,0x0c,0x32,0x00,0x00}, // k
	{0x3e,0x20,0x20,0x20,0x00,0x00}, // l
	{0x3c,0x02,0x02,0x3c,0x02,0x02}, // m
	{0x3c,0x02,0x02,0x02,0x3e,0x00}, // n
	{0x1c,0x22,0x22,0x22,0x1e,0x00}, // o
	{0x3c,0x12,0x12,0x12,0x0e,0x00}, // p
	{0x1c,0x22,0x22,0x62,0x1e,0x00}, // q
	{0x3c,0x12,0x12,0x32,0x0e,0x00}, // r
	{0x24,0x2a,0x2a,0x12,0x00,0x00}, // s
	{0x02,0x02,0x3e,0x02,0x02,0x00}, // t
	{0x1e,0x20,0x20,0x20,0x1e,0x00}, // u
	{0x0e,0x10,0x20,0x10,0x0e,0x00}, // v
	{0x3e,0x20,0x20,0x1e,0x20,0x20}, // w
	{0x36,0x08,0x08,0x36,0x00,0x00}, // x
	{0x26,0x28,0x28,0x1e,0x00,0x00}, // y
	{0x32,0x2a,0x2a,0x26,0x00,0x00}, // z
	{0x08,0x3e,0x22,0x00,0x00,0x00}, // {
	{0x3e,0x00,0x00,0x00,0x00,0x00}, // |
	{0x22,0x3e,0x08,0x00,0x00,0x00}, // }
	{0x04,0x02,0x02,0x00,0x00,0x00}, // ~
	{0x00,0x00,0x00,0x00,0x00,0x00}
};

const unsigned char raumsond_font[96][5] = {
	{0x00,0x00,0x00,0x00,0x00}, //  
	{0x5c,0x00,0x00,0x00,0x00}, // !
	{0x0c,0x00,0x0c,0x00,0x00}, // "
	{0x28,0x7c,0x28,0x7c,0x28}, // #
	{0x5c,0x54,0xfe,0x54,0x74}, // $
	{0x44,0x20,0x10,0x08,0x44}, // %
	{0x70,0x5c,0x54,0x7c,0x50}, // &
	{0x0c,0x00,0x00,0x00,0x00}, // '
	{0x7c,0x44,0x00,0x00,0x00}, // (
	{0x44,0x7c,0x00,0x00,0x00}, // )
	{0x28,0x10,0x7c,0x10,0x28}, // *
	{0x10,0x10,0x7c,0x10,0x10}, // +
	{0xc0,0x00,0x00,0x00,0x00}, // ,
	{0x10,0x10,0x10,0x10,0x00}, // -
	{0x40,0x00,0x00,0x00,0x00}, // .
	{0x60,0x1c,0x00,0x00,0x00}, // /
	{0x7c,0x44,0x44,0x44,0x7c}, // 0
	{0x04,0x7c,0x00,0x00,0x00}, // 1
	{0x70,0x54,0x54,0x5c,0x40}, // 2
	{0x54,0x54,0x54,0x5c,0x70}, // 3
	{0x1c,0x10,0x10,0x10,0x7c}, // 4
	{0x5c,0x54,0x54,0x74,0x04}, // 5
	{0x1c,0x74,0x54,0x54,0x74}, // 6
	{0x04,0x04,0x04,0x7c,0x00}, // 7
	{0x7c,0x54,0x54,0x54,0x7c}, // 8
	{0x5c,0x54,0x54,0x74,0x1c}, // 9
	{0x50,0x00,0x00,0x00,0x00}, // :
	{0xd0,0x00,0x00,0x00,0x00}, // ;
	{0x10,0x28,0x44,0x00,0x00}, // <
	{0x28,0x28,0x28,0x28,0x00}, // =
	{0x6c,0x10,0x00,0x00,0x00}, // >
	{0x0c,0x04,0x54,0x14,0x1c}, // ?
	{0xfe,0x82,0x92,0xaa,0xba}, // @
	{0x7e,0x54,0x54,0x5c,0x70}, // A
	{0x7c,0x48,0x48,0x48,0x78}, // B
	{0x7c,0x44,0x44,0x44,0x40}, // C
	{0x78,0x48,0x48,0x48,0x7c}, // D
	{0x70,0x5c,0x54,0x54,0x5c}, // E
	{0x70,0x1c,0x14,0x14,0x14}, // F
	{0x1c,0x54,0x54,0x74,0x1c}, // G
	{0x7c,0x10,0x10,0x10,0x78}, // H
	{0x7c,0x00,0x00,0x00,0x00}, // I
	{0x60,0x40,0x40,0x7c,0x00}, // J
	{0x7c,0x10,0x10,0x70,0x1c}, // K
	{0x7c,0x40,0x40,0x40,0x00}, // L
	{0x7c,0x04,0x7c,0x08,0x78}, // M
	{0x7c,0x04,0x04,0x04,0x7c}, // N
	{0x1c,0x54,0x54,0x54,0x1c}, // O
	{0x1c,0x74,0x14,0x14,0x1c}, // P
	{0x3c,0x24,0x24,0x64,0x3c}, // Q
	{0x7c,0x14,0x14,0x74,0x1c}, // R
	{0x40,0x5c,0x54,0x54,0x70}, // S
	{0x78,0x4c,0x48,0x48,0x48}, // T
	{0x1c,0x50,0x50,0x50,0x1c}, // U
	{0x04,0x7c,0x40,0x7c,0x04}, // V
	{0x7c,0x40,0x7c,0x20,0x3c}, // W
	{0x44,0x7c,0x10,0x7c,0x44}, // X
	{0x1c,0x50,0x50,0x70,0x1c}, // Y
	{0x70,0x54,0x54,0x5c,0x40}, // Z
	{0x7c,0x44,0x00,0x00,0x00}, // [
	{0x0c,0x70,0x00,0x00,0x00}, // "\"
	{0x44,0x7c,0x00,0x00,0x00}, // ]
	{0x08,0x04,0x08,0x00,0x00}, // ^
	{0x40,0x40,0x40,0x40,0x00}, // _
	{0x0c,0x00,0x00,0x00,0x00}, // `
	{0x74,0x54,0x54,0x74,0x1c}, // a
	{0x7c,0x48,0x48,0x48,0x78}, // b
	{0x7c,0x44,0x44,0x44,0x40}, // c
	{0x78,0x48,0x48,0x48,0x7c}, // d
	{0x1c,0x74,0x54,0x54,0x5c}, // e
	{0x1c,0x74,0x14,0x14,0x14}, // f
	{0x5c,0x54,0x54,0x5c,0x70}, // g
	{0x7c,0x10,0x10,0x10,0x78}, // h
	{0x74,0x00,0x00,0x00,0x00}, // i
	{0x60,0x40,0x40,0x7c,0x00}, // j
	{0x7c,0x10,0x10,0x70,0x1c}, // k
	{0x7c,0x40,0x40,0x40,0x00}, // l
	{0x78,0x08,0x7c,0x04,0x7c}, // m
	{0x7c,0x04,0x04,0x04,0x7c}, // n
	{0x1c,0x54,0x54,0x54,0x1c}, // o
	{0x1c,0x74,0x14,0x14,0x1c}, // p
	{0x3c,0x24,0x24,0x64,0x3c}, // q
	{0x7c,0x04,0x04,0x04,0x00}, // r
	{0x40,0x5c,0x54,0x54,0x70}, // s
	{0x78,0x4c,0x48,0x48,0x48}, // t
	{0x1c,0x50,0x50,0x50,0x1c}, // u
	{0x04,0x7c,0x40,0x7c,0x04}, // v
	{0x3c,0x20,0x7c,0x40,0x7c}, // w
	{0x44,0x7c,0x10,0x7c,0x44}, // x
	{0x1c,0x10,0x10,0x10,0x7c}, // y
	{0x70,0x54,0x54,0x5c,0x40}, // z
	{0x10,0x6c,0x44,0x00,0x00}, // {
	{0x7c,0x00,0x00,0x00,0x00}, // |
	{0x44,0x6c,0x10,0x00,0x00}, // }
	{0x08,0x04,0x08,0x04,0x00}, // ~
	{0x00,0x00,0x00,0x00,0x00}
};