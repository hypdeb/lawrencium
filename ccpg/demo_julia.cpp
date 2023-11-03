#include "julia.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

#pragma pack(push, 1)
struct BITMAPFILEHEADER {
  uint16_t type{0x4D42}; // Magic identifier: 0x4d42='BM'
  uint32_t size;         // File size in bytes
  uint16_t reserved1{0}; // Not used
  uint16_t reserved2{0}; // Not used
  uint32_t offset{54};   // Offset to image data, bytes
};

struct BITMAPINFOHEADER {
  uint32_t size{40};             // Info Header size in bytes
  int32_t width;                 // Width of the image
  int32_t height;                // Height of image
  uint16_t planes{1};            // Number of color planes
  uint16_t bit_count{32};        // Bits per pixel (32 bits for BGRA)
  uint32_t compression{0};       // Compression type (no compression)
  uint32_t image_size;           // Image size in bytes
  int32_t x_pixels_per_meter{0}; // Pixels per meter X
  int32_t y_pixels_per_meter{0}; // Pixels per meter Y
  uint32_t colors_used{0};       // Number of colors
  uint32_t colors_important{0};  // Important colors
};
#pragma pack(pop)

bool saveBitmapToFile(const std::vector<unsigned char> &pixelData,
                      int width,
                      int height,
                      const std::string &filename) {
  BITMAPFILEHEADER fileHeader;
  BITMAPINFOHEADER infoHeader;

  int imageSize = width * height * 4; // 4 bytes per pixel

  fileHeader.size = 54 + imageSize; // File header + info header + pixel data
  infoHeader.width = width;
  infoHeader.height = height;
  infoHeader.image_size = imageSize;

  std::ofstream file(filename, std::ios::binary);
  if (!file) {
    std::cerr << "Error: Could not open the file for writing." << std::endl;
    return false;
  }

  // Write the file header
  file.write(reinterpret_cast<const char *>(&fileHeader), sizeof(fileHeader));

  // Write the info header
  file.write(reinterpret_cast<const char *>(&infoHeader), sizeof(infoHeader));

  // Write the pixel data (no padding needed for 32-bit)
  file.write(reinterpret_cast<const char *>(pixelData.data()),
             pixelData.size());

  if (!file.good()) {
    std::cerr << "Error: Write operation failed." << std::endl;
    file.close();
    return false;
  }

  file.close();
  return true;
}

int main() {
  const int width = 4096 * 2;
  const auto bitmap = lawrencium::ccpg::julia::DrawOnGpu(width);
  const auto checkSum = std::reduce(bitmap.cbegin(), bitmap.cend());
  std::cout << bitmap[10000] << '\n';

  const std::string filename = "julia.bmp";

  if (saveBitmapToFile(bitmap, width, width, filename)) {
    std::cout << "Bitmap image saved successfully." << std::endl;
  } else {
    std::cerr << "Failed to save bitmap image." << std::endl;
  }

  return 0;
}