// kernel.c - минимальное ядро Notepad OS
// Выводит текст напрямую в VGA-память (0xB8000)

#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((unsigned short*)0xB8000)

// Цвета VGA: старший байт = фон<<4 | текст
#define COLOR_BLACK        0x0
#define COLOR_LIGHT_GREY   0x7
#define COLOR_WHITE        0xF

static unsigned int cursor_row = 0;
static unsigned int cursor_col = 0;
static unsigned char current_color = (COLOR_BLACK << 4) | COLOR_LIGHT_GREY;

// Записать символ в VGA-память
static void vga_putchar(char c) {
    if (c == '\n') {
        cursor_row++;
        cursor_col = 0;
        return;
    }
    if (c == '\r') {
        cursor_col = 0;
        return;
    }

    unsigned int index = cursor_row * VGA_WIDTH + cursor_col;
    VGA_MEMORY[index] = (current_color << 8) | (unsigned char)c;

    cursor_col++;
    if (cursor_col >= VGA_WIDTH) {
        cursor_col = 0;
        cursor_row++;
    }
}

// Вывести строку
static void vga_print(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        vga_putchar(str[i]);
    }
}

// Очистить экран
static void vga_clear(void) {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        VGA_MEMORY[i] = (current_color << 8) | ' ';
    }
    cursor_row = 0;
    cursor_col = 0;
}

// Точка входа ядра (вызывается из boot.asm)
void kernel_main(unsigned int magic, unsigned int* mbi) {
    (void)magic;
    (void)mbi;

    vga_clear();

    // Цвет заголовка
    current_color = (COLOR_BLACK << 4) | COLOR_WHITE;
    vga_print("========================================\n");
    vga_print("        Notepad OS Lite 1.0.0\n");
    vga_print("           Codename: TeXHo\n");
    vga_print("========================================\n");
    vga_print("\n");

    current_color = (COLOR_BLACK << 4) | COLOR_LIGHT_GREY;
    vga_print("Kernel loaded successfully.\n");
    vga_print("This is a real OS kernel written in C.\n");
    vga_print("\n");
    vga_print("Next steps:\n");
    vga_print("  - GDT/IDT setup\n");
    vga_print("  - Keyboard driver\n");
    vga_print("  - Memory management\n");
    vga_print("  - ...and eventually applications\n");
    vga_print("\n");
    vga_print("System halted. Press reset to reboot.\n");

    // Бесконечный цикл — ядро не завершается
    while (1) {
        __asm__ volatile ("hlt");
    }
}
