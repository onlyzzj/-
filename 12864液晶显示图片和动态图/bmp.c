#include "bmp.h"



uchar code table[]={
0x00,0x00,0x00,0x7F,0xF0,0x00,0x00,0x00,0x00,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0xF0,0x00,0x00,0x00,0x00,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0xF0,0x00,0x00,0x00,0x00,0x7F,0xFF,0xF0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0xE0,0x00,0x00,0x00,0x00,0x7F,0xFF,0xF0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0xE0,0x00,0x00,0x00,0x00,0x7F,0xFF,0xF0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0xE0,0x00,0x00,0x00,0x00,0x4F,0xFF,0xF0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x3F,0xE0,0x00,0x00,0x00,0x00,0x07,0xFF,0xF0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x3F,0xE0,0x00,0x00,0x00,0x00,0x07,0xFF,0xF0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x3F,0xE0,0x00,0x00,0x00,0x00,0x07,0xFF,0xF0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x3F,0xE0,0x00,0x00,0x00,0x00,0x07,0xFF,0xF0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xF0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xF0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1F,0x80,0x00,0x00,0x00,0x00,0x07,0xFF,0xF0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1F,0x80,0x00,0x00,0x00,0x00,0x03,0xFF,0xF8,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x0F,0xC0,0x00,0x00,0x00,0x03,0x84,0xFF,0xF8,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,0x1F,0xFC,0xFF,0x7C,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x0F,0x10,0x00,0x00,0x07,0xFF,0xFE,0xFF,0xFC,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x0F,0x3C,0x00,0x00,0x1F,0xFF,0xFF,0x7F,0xD8,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x17,0x7F,0xF8,0x00,0x3F,0xFF,0xFF,0x7F,0x98,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x17,0x7F,0xFF,0x00,0xFF,0xC0,0xFF,0x7F,0x98,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1F,0x7F,0xFF,0xE0,0x7F,0x97,0xFF,0x3F,0x80,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1F,0x7C,0x7F,0xE0,0x7F,0xFF,0xFE,0x3F,0xE4,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1B,0x79,0xFF,0xE0,0x7F,0xFF,0xFC,0x7F,0xE4,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x13,0x7F,0xFF,0xF0,0x7F,0x7F,0xF9,0xFF,0xE4,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x13,0x7F,0xFF,0xF0,0x7F,0x7F,0xF9,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x13,0x3E,0xFF,0xE0,0x73,0xCD,0x80,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x13,0x1F,0xFF,0xE0,0x7F,0x00,0x80,0xFF,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0F,0xF7,0xE0,0x3C,0x02,0x00,0xFF,0xC0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0x02,0xE0,0x38,0x00,0x00,0x7F,0x80,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x0C,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x04,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x01,0xFF,0xC0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x01,0xFF,0xC0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x00,0x03,0xFF,0x80,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x16,0x00,0x03,0xFB,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x13,0x80,0x03,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x03,0xF0,0x03,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x01,0x00,0x03,0xF0,0x03,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x07,0xC0,0x1F,0xBE,0x07,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x38,0x0F,0xF0,0x7F,0xFE,0x07,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x38,0x1E,0xFF,0xFF,0xFF,0xBF,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3E,0x3F,0xFF,0xFE,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3F,0xFD,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x1F,0xFF,0xF1,0x0C,0x7F,0xDE,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x1F,0xFF,0xC0,0x01,0x7F,0xDC,0xFF,0x80,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x1F,0xFF,0x80,0x07,0xFF,0x9C,0xFF,0x80,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x1F,0xFF,0x00,0x3F,0xFF,0x9C,0xFF,0xC0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0F,0x3F,0xFF,0xFF,0xFF,0x98,0xFF,0xC0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0F,0x3F,0xFF,0xFF,0xF1,0x39,0xFF,0xC0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0F,0xBF,0xFF,0xFF,0xF3,0x79,0xFF,0xC0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xEF,0xFF,0x3F,0xF3,0xBB,0xFF,0x88,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xEF,0xF0,0x0F,0xF3,0xFF,0xFF,0x8E,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0xFF,0xFE,0x3F,0xFF,0xFF,0xFF,0x06,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xFD,0xFF,0xFF,0xFF,0xFF,0xFE,0x07,0x80,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x7E,0xFF,0xFF,0xFF,0xFF,0xFC,0x0F,0xC0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xF8,0x0F,0xE0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xC7,0x7F,0xFF,0xF0,0x1F,0xF0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x0F,0xC6,0x06,0x1F,0xFF,0xC0,0x1F,0xF8,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x07,0x86,0x02,0x3F,0xFF,0x80,0x3F,0xFC,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x3F,0xFF,0x00,0x7F,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x01,0x89,0xE0,0x7F,0xFC,0x00,0x7F,0xFF,0xC0,0x00,0x00
};




uchar code table1[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x9B,0xD0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x46,0x7F,0xF4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x7F,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x7F,0xEF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x7F,0x2C,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x7F,0x03,0x0F,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x70,0x80,0x03,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x7C,0x00,0x01,0xFE,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x71,0xC0,0x00,0x3E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x7C,0x00,0x00,0x0F,0xD0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x3F,0x80,0x00,0x03,0xC8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x3E,0x00,0x00,0x00,0xF9,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x1F,0x80,0x00,0x00,0x1F,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x2F,0xE0,0x00,0x00,0x0F,0xCC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x0F,0x80,0x00,0x00,0x03,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x07,0xE0,0x00,0x00,0x40,0x3F,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x02,0xF0,0x00,0x00,0x30,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x70,0x00,0x00,0x3E,0x07,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0xFC,0x00,0x00,0x3F,0x83,0xE8,0x00,0x01,0x02,0x80,0x00,0x00,0x00,0x00,0x18,
0x00,0x3E,0x00,0x00,0x3F,0xE1,0xF0,0x00,0x05,0xFF,0xC0,0x00,0x00,0x00,0x00,0x18,
0x00,0x1F,0x00,0x00,0xFF,0xF8,0x64,0x00,0x2F,0xFF,0xE0,0x00,0x00,0x00,0x00,0x18,
0x00,0x0F,0x00,0x00,0x3F,0xFC,0x3E,0x00,0x7F,0x03,0xE0,0x00,0x00,0x00,0x00,0x18,
0x00,0x0F,0x80,0x00,0x0F,0xFF,0x1F,0x01,0xFC,0x1F,0xF8,0x00,0x00,0x00,0x00,0x18,
0x00,0x01,0xC0,0x00,0x1F,0xFE,0x8F,0x99,0xF0,0x1F,0xE0,0x00,0x00,0x00,0x00,0x18,
0x00,0x0B,0xC0,0x00,0x07,0xFF,0xE3,0xFB,0xC0,0x7F,0xF0,0x00,0x00,0x00,0x00,0x18,
0x00,0x03,0xF0,0x00,0x03,0xFF,0xF0,0xFF,0x00,0x7F,0xD8,0x00,0x00,0x00,0x00,0x18,
0x00,0x01,0xF8,0x00,0x00,0xFF,0xFE,0x38,0x00,0xFF,0x10,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x78,0x00,0x00,0xFF,0xFF,0x80,0x03,0xDE,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x7E,0x00,0x00,0xFF,0xFF,0xC0,0x0F,0xFC,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x3F,0x80,0x00,0x7F,0xFF,0xE0,0x3F,0xF0,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x0F,0x80,0x00,0x1F,0xFF,0xFF,0x3F,0xE0,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x03,0xF0,0x00,0x1F,0xFF,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x05,0xF8,0x00,0x0F,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x9F,0x00,0x07,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x1F,0xC0,0x07,0xFF,0xDF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x33,0xFE,0x0F,0xFF,0xDF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x0B,0xFF,0xFF,0xFF,0xBF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x01,0xDF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x00,0xBE,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x00,0x1F,0xFD,0x7F,0xFF,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x00,0x0F,0xFB,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x00,0x05,0xFF,0xEF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x00,0x00,0x1F,0xFD,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x00,0x01,0x7F,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x00,0x01,0xFD,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x00,0x01,0xF9,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x00,0x13,0xF3,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x00,0x3E,0xE7,0xFC,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x00,0x7F,0xDF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x00,0xFF,0xCF,0xEE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x01,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x00,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x01,0xFF,0xF2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x03,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x0F,0xFE,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x03,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x07,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,
0x7F,0xFF,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};



uchar code table2[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x2E,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1F,0xF3,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x3F,0xFF,0xD0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x3F,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1F,0xFC,0x7C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x3F,0x78,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1F,0x18,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1F,0x88,0x3D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1E,0xE0,0x1F,0xA0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xF0,0x1F,0xC8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x02,0xFC,0x03,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xFE,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x7F,0x00,0x0D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0F,0x80,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0F,0xE0,0x02,0x00,0x00,0xFF,0xA0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0xE0,0x03,0x80,0x03,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xE0,0x01,0xE0,0xA3,0xC0,0x64,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xF8,0x01,0xF3,0xFF,0x03,0x34,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x78,0x00,0x77,0xFC,0x03,0xDE,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xF8,0x00,0x7F,0x20,0x0F,0xFC,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x18,0x00,0x1F,0xFE,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0xE0,0x10,0x00,0x00,0x3F,0xFE,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xE0,0x3C,0x00,0x03,0xFF,0x0E,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0xDE,0x11,0x00,0x3F,0xFC,0xB4,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0xFE,0x19,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0xFE,0x1F,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0xFE,0x1E,0xFF,0xFF,0xC8,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFF,0x1F,0xFF,0xFF,0x90,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0xFF,0xBF,0xFF,0xFE,0x40,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xFC,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFB,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xFB,0xDF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0xFF,0x9F,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0xFD,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0xFB,0xFF,0xFF,0xF4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0xC3,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0F,0x8F,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0F,0x1F,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x1E,0x1F,0xFF,0xFE,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3E,0x07,0xFF,0xF9,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x1C,0x07,0xFF,0x84,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3C,0x0F,0xF8,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3C,0x1F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x1C,0x1F,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3E,0x3F,0xF4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3C,0x7B,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x39,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x39,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3F,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x7F,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x7F,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0xFF,0xA0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x02,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x03,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x03,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};




uchar code table3[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x02,0xD0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x01,0xF1,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x2F,0xFD,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x1F,0x9F,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x5D,0x8E,0x7E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xFC,0x84,0x3F,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xFC,0x00,0x1F,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0xE0,0x00,0x07,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0xE0,0x00,0x03,0x8F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x03,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0x80,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x0F,0x4E,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x0E,0x4F,0x80,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x0F,0x7F,0xC0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0F,0x80,0xE0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x0F,0x0E,0xC8,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0C,0x07,0xE0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x08,0x0F,0xF8,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x1F,0xF8,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,0x0F,0xF0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x0E,0x08,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3E,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x1E,0x00,0x00,0x07,0x80,0x7E,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3E,0x00,0x00,0x03,0x82,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x1E,0x00,0x00,0x03,0xE3,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x1E,0x00,0x00,0x0F,0xF1,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x1E,0x00,0x00,0x1F,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x1E,0x00,0x01,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x1E,0x00,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0E,0x00,0x0F,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x1F,0x00,0x1F,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0x00,0x1F,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0F,0x80,0x7F,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x07,0xE0,0x7F,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0xF9,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x05,0xF1,0xFF,0xFF,0xF4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xE1,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0xE1,0xFF,0xFC,0xA0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x05,0xC0,0x7F,0xFE,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x17,0x80,0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3F,0x00,0x5F,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x1C,0x00,0xF8,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x38,0x00,0xE4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x78,0x01,0xC8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xF0,0x03,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x70,0x07,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xF0,0x0F,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0xF0,0x1F,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x03,0xC0,0x3E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0x80,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x03,0x80,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0x13,0xF4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0xBF,0xD0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0xFD,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x02,0xBC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x04,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};




uchar code table4[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0xE8,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x28,0xE0,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xBF,0xF8,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xB1,0xFF,0xF8,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x3F,0xFB,0xFD,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x59,0xFE,0x0F,0x3E,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xF0,0x30,0xFF,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0xFF,0x80,0x00,0x0F,0x80,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x7F,0xFF,0xF8,0x00,0x00,0x0F,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x7F,0xFF,0x80,0x00,0x00,0x3F,0x80,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0D,0xFF,0xFC,0x18,0x00,0x00,0x3F,0x80,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xBF,0xC0,0x07,0xFC,0x00,0x03,0xFF,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x1F,0xFF,0xF8,0x00,0x00,0xFE,0x80,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF9,0xFF,0xFF,0xF0,0x00,0x07,0xFC,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xE7,0xFF,0xFF,0xE0,0x00,0x3F,0xFE,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xCF,0xFF,0xFD,0x80,0x00,0x03,0xF4,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x0B,0xBF,0xFF,0xFC,0x00,0x00,0x3F,0xC0,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x7F,0xFF,0xF8,0x00,0x05,0xFF,0x20,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x9E,0xFF,0xFF,0xF0,0x00,0x00,0x7C,0x40,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x01,0xF9,0xFF,0xFF,0xC0,0x00,0x03,0xFE,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x09,0xF1,0xFF,0xFF,0xC0,0x00,0x07,0xC4,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x1F,0xC3,0xFF,0xFC,0x00,0x00,0x7F,0xC0,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x5F,0x03,0xFF,0xF0,0x00,0x00,0x7F,0x80,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0xFC,0x07,0xFF,0xF8,0x00,0x01,0xFB,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x06,0xF0,0x1F,0xFF,0xF0,0x00,0x03,0xF8,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x07,0xE0,0x3F,0xFF,0xF0,0x00,0x17,0xF4,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x0F,0x80,0x7F,0xFF,0xF0,0x00,0x3F,0xA0,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x5F,0x00,0xFF,0xFF,0xF0,0x00,0xFF,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x7C,0x01,0xFF,0xFF,0xE9,0x3F,0xF2,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0xF8,0x1F,0xFF,0xFF,0xFD,0xFF,0x80,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x38,0xFF,0xFF,0xFF,0xFF,0xF1,0x40,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x01,0xE8,0x3F,0xFF,0xFF,0xBF,0xD4,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x03,0xE0,0x1F,0xFF,0xFF,0xFE,0x80,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x01,0xE0,0x07,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x03,0xC0,0x1F,0xFF,0xFF,0xBC,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x07,0xC0,0x39,0xFF,0xFD,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x1F,0x80,0x79,0x7F,0xC1,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x0F,0x00,0xF8,0x1C,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x1F,0x01,0xF0,0x2E,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x3E,0x03,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x01,0xBC,0x07,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x3E,0x0F,0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x01,0xF6,0x3F,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x03,0xFD,0xFE,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x07,0xFB,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x03,0xFF,0xF4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x07,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x07,0xFF,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x03,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x05,0xD8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04
};



uchar code table5[]={
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xBF,0x40,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xE0,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xC0,0xF0,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x82,0xF8,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5E,0x0F,0xFC,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xDC,0x0E,0xF8,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0xBF,0xF0,0x09,0xFC,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xC0,0x03,0xFF,0xA0,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x03,0xF0,0x00,0x0F,0xFF,0xF8,0x00,0x00,0x19,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x0F,0xC0,0x00,0x1F,0xFF,0xF0,0x00,0x00,0xDF,0xE2,
0x10,0x00,0x00,0x00,0x00,0x00,0x2F,0x80,0x00,0x1F,0xFF,0xFF,0xEF,0x56,0xFF,0xC2,
0x10,0x00,0x00,0x00,0x00,0x01,0x7C,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFB,0xE2,
0x10,0x00,0x00,0x00,0x00,0x03,0xF8,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xE7,0xF2,
0x10,0x00,0x00,0x00,0x00,0x13,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFE,
0x10,0x00,0x00,0x00,0x00,0x3F,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFE,
0x10,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x03,0xC6,
0x10,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0xF7,0xA0,0x20,0x00,0x00,0x00,0x00,0x0E,
0x10,0x00,0x00,0x00,0x02,0xF0,0x00,0x03,0xFF,0xFE,0x20,0x00,0x00,0x00,0x00,0x3E,
0x10,0x00,0x00,0x00,0x07,0xC0,0x00,0x1F,0xFF,0xFE,0x80,0x00,0x00,0x00,0x03,0xFE,
0x10,0x00,0x00,0x00,0x1F,0x80,0x00,0x7F,0xFF,0xFC,0x71,0x00,0x00,0x00,0x00,0x0E,
0x10,0x00,0x00,0x00,0x5E,0x02,0x31,0xFF,0xFF,0xE8,0x30,0x00,0x00,0x00,0x00,0x1E,
0x10,0x00,0x00,0x00,0x3C,0x3F,0xFF,0xFF,0xFF,0x96,0x03,0x00,0x00,0x00,0x01,0xFE,
0x10,0x00,0x00,0x00,0xF8,0x0F,0xFF,0xFF,0xE3,0xFE,0x11,0x80,0x00,0x00,0x0F,0xFE,
0x10,0x00,0x00,0x00,0x78,0x01,0x3F,0xFF,0xE1,0xFF,0x00,0x40,0x00,0x00,0x00,0x7E,
0x10,0x00,0x00,0x00,0xF0,0x00,0x43,0xFB,0xF0,0x3F,0xC0,0x40,0x00,0x00,0x03,0xFA,
0x10,0x00,0x00,0x03,0xF0,0x07,0xCC,0x00,0xFF,0x8F,0x01,0x20,0x00,0x00,0xFF,0xD2,
0x10,0x00,0x00,0x03,0xE0,0x3F,0xFF,0x0D,0xFF,0xFE,0x00,0x90,0x00,0x00,0x04,0x52,
0x10,0x00,0x00,0x03,0xE0,0x7F,0xFF,0x01,0xFF,0x58,0x00,0x00,0x00,0x07,0xFE,0x02,
0x10,0x00,0x00,0x07,0xC0,0xE6,0xFE,0x01,0xFE,0x0C,0x00,0x04,0x00,0x03,0xFC,0x02,
0x10,0x00,0x00,0x0F,0x83,0xE0,0x4F,0xF7,0xE0,0x20,0x00,0x01,0x4B,0xFF,0xFA,0x02,
0x10,0x00,0x00,0x17,0x07,0xC8,0x81,0xFF,0xE3,0xF2,0x01,0xFF,0xFF,0xFF,0xD0,0x02,
0x10,0x00,0x00,0x07,0x0F,0x80,0x00,0x7F,0xFF,0xFF,0xF1,0xFF,0xFF,0xFF,0x80,0x02,
0x10,0x00,0x00,0x2E,0x3F,0x00,0x03,0x81,0xFF,0xFF,0xFF,0xFF,0xF3,0xE7,0x40,0x02,
0x10,0x00,0x01,0xF8,0x7B,0x80,0x00,0x01,0x7F,0x77,0xFF,0xFF,0xD8,0x80,0x00,0x02,
0x10,0x00,0x00,0xF1,0xF8,0x00,0x00,0x00,0x01,0x12,0x80,0x02,0x10,0x00,0x00,0x02,
0x10,0x00,0x03,0xEB,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x01,0xE7,0xE8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x03,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x03,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x01,0x7A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x02,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02
};