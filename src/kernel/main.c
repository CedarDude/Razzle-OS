#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*

			RAZZLE OPERATING SYSTEM MAIN KERNEL
						LICENSE GPL 
				COPYRIGHT JAD 2025-2026 (c)

*/

// hardware color !
/* using:
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

is pretty garbage
so we gona switch to smt else*/

enum colorv {
	// all vga text mode color
	vga-black = 0,
	vga-blue = 1,
	vga-green = 2,
	vga-cyan = 3,
	vga-red = 4,
	vga-magenta = 5,
	vga-brown = 6,
	vga-light-grey = 7,
	vga-grey = 8,
	vga-light-blue = 9,
	vga-light-green = 10,
	vga-light-cyan = 11,
	vga-light-red = 12,
	vga-light-magenta = 13,
	vga-light-brown = 14,
	vga-white = 15,
}

// background and text stuff
static inline uint_t vgaentry_col(enum colorv fg, enum colorv bg)
{
	return fg | bg << 4;
}
// vga entry
static inline uinit16_t ventry(unsigned char uc, unint8_t color)
{
	return (uint16_t) uc | (uint16_t) color <<8;
}


size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

// as it says
// we define vga
#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000 

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = (vga-white, vga-black);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vgaentry_col(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = ventry(c, color);
}

void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

void kernel_main(void) 
{
	/* Initialize the terminal !
	*/
	terminal_initialize();

	terminal_writestring("Hello Everyone!\n");
}