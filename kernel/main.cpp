#include <cstdint>
#include <cstddef>
#include <cstdio>

#include "frame_buffer_config.hpp"
#include "graphics.hpp"
#include "font.hpp"
#include "console.hpp"

// displacement new
// new instance without OS memory management
void* operator new(size_t size, void* buf) {
  return buf;
}

// Link error without delete
void operator delete(void* obj) noexcept {
}
// displacement new

char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;

char console_buf[sizeof(Console)];
Console* console;

// printk: printing messages inside the kernel (Linux)
// ...: Variable argument
int printk(const char* format, ...) {
  va_list ap;
  int result;
  char s[1024];

  va_start(ap, format);
  result = vsprintf(s, format, ap);
  va_end(ap);

  console->PutString(s);
  return result;
}

// Reference type available in C++ only
// Using pointers to call functions with reference type parameters from C
// This is defined in the "System V AMD64 ABI" instead of the standard C++ specification
extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config) {
  switch (frame_buffer_config.pixel_format) {
    case kPixelRGBResv8BitPerColor:
      pixel_writer = new(pixel_writer_buf)
        RGBResv8BitPerColorPixelWriter{frame_buffer_config};
      break;
    case kPixelBGRResv8BitPerColor:
      pixel_writer = new(pixel_writer_buf)
        BGRResv8BitPerColorPixelWriter{frame_buffer_config};
      break;
  }

  for (int x = 0; x < frame_buffer_config.horizontal_resolution; ++x) {
    for (int y = 0; y < frame_buffer_config.vertical_resolution; y++) {
      pixel_writer->Write(x, y, {255, 255, 255});
    }
  }
  for (int x = 0; x < 200; ++x) {
    for (int y = 0; y < 100; y++) {
      pixel_writer->Write(x, y, {0, 255, 0});
    }
  }

  // new console
  console = new(console_buf) Console{*pixel_writer, {0, 0, 0}, {255, 255, 255}};

  // use printk
  for (int i = 0; i < 27; ++i) {
    printk("printk: %d\n", i);
  }

  // // Write asciifont
  // // Using reference instead of pointer to prevent nullptr
  // int i = 0;
  // for (char c = '!'; c <= '~'; ++c, ++i) {
  //   WriteAscii(*pixel_writer, 8 * i, 50, c, {0, 0, 0});
  // }
  // WriteString(*pixel_writer, 0, 66, "Hello, world!", {0, 0, 255});

  // // sprintf from newlib/cstdio
  // char buf[128];
  // sprintf(buf, "1 + 2 = %d", 1 + 2);
  // WriteString(*pixel_writer, 0, 82, buf, {0, 0, 0});

  while (1) __asm__("hlt");
}
