// kernel.c - Notepad OS Lite Kernel
// Version: 1.0.0 "TeXHo"

#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((unsigned short*)0xB8000)

#define COLOR_BLACK      0x0
#define COLOR_LIGHT_GREY 0x7
#define COLOR_WHITE      0xF
#define COLOR_CYAN       0xB
#define COLOR_YELLOW     0xE

static unsigned int cursor_row = 0;
static unsigned int cursor_col = 0;
static unsigned char current_color = (COLOR_BLACK << 4) | COLOR_LIGHT_GREY;

static void vga_putchar(char c) {
    if (c == '\n') { cursor_row++; cursor_col = 0; return; }
    if (c == '\r') { cursor_col = 0; return; }

    unsigned int index = cursor_row * VGA_WIDTH + cursor_col;
    VGA_MEMORY[index] = (current_color << 8) | (unsigned char)c;

    cursor_col++;
    if (cursor_col >= VGA_WIDTH) { cursor_col = 0; cursor_row++; }
}

static void vga_print(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) vga_putchar(str[i]);
}

static void vga_clear(void) {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        VGA_MEMORY[i] = (current_color << 8) | ' ';
    }
    cursor_row = 0; cursor_col = 0;
}

static void vga_set_color(unsigned char fg, unsigned char bg) {
    current_color = (bg << 4) | fg;
}

void kernel_main(unsigned int magic, unsigned int* mbi) {
    (void)magic; (void)mbi;

    vga_clear();

    vga_set_color(COLOR_CYAN, COLOR_BLACK);
    vga_print("========================================\n");
    vga_set_color(COLOR_WHITE, COLOR_BLACK);
    vga_print("        Notepad OS Lite 1.0.0\n");
    vga_print("           Codename: TeXHo\n");
    vga_set_color(COLOR_CYAN, COLOR_BLACK);
    vga_print("========================================\n");
    vga_print("\n");

    vga_set_color(COLOR_LIGHT_GREY, COLOR_BLACK);
    vga_print("Kernel loaded successfully.\n");
    vga_print("This is a real 32-bit OS kernel written in C.\n");
    vga_print("\n");

    vga_set_color(COLOR_YELLOW, COLOR_BLACK);
    vga_print("Status:\n");
    vga_set_color(COLOR_LIGHT_GREY, COLOR_BLACK);
    vga_print("  [+] Multiboot loaded\n");
    vga_print("  [+] Protected mode (32-bit)\n");
    vga_print("  [+] VGA text output\n");
    vga_print("\n");

    vga_print("Next steps (roadmap):\n");
    vga_print("  [ ] GDT / IDT\n");
    vga_print("  [ ] Keyboard driver\n");
    vga_print("  [ ] Memory management\n");
    vga_print("  [ ] Shell\n");
    vga_print("\n");
    vga_print("System halted. Press reset to reboot.\n");

    while (1) __asm__ volatile ("hlt");
}
