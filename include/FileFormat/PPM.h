#ifndef RAYTRACE_INCLUDE_FILEFORMAT_PPM_H_
#define RAYTRACE_INCLUDE_FILEFORMAT_PPM_H_
#include "FileFormat.h"
#include <fstream>
#include <sstream>
namespace raytrace {
namespace file_format {
class PPM : public FileFormat {
 public:
  using FileFormat::FileFormat;
  virtual void Output(const std::string &filename) override {
    std::ofstream os(filename, std::ios::out | std::ios::binary);
    OutputHeader(os);
    OutputBody(os);
    os.flush();
    os.close();
  }
 protected:
  void OutputHeader(std::ostream &os) const {
    std::ostringstream headerStream;
    const Canvas &canvas = GetCanvas();
    headerStream << "P6\n";
    headerStream << canvas.Width() << ' ' << canvas.Height() << '\n';
    headerStream << "255\n";
    os << headerStream.str();
  }
  void OutputBody(std::ostream &os) const {
    const Canvas &canvas = GetCanvas();
    const size_t width = canvas.Width(), height = canvas.Height();
    for (size_t y = 0; y < width; y++) {
      for (size_t x = 0; x < width; x++) {
        Color color = canvas.Pixel(width - x - 1, height - y - 1).Truncate();
        unsigned char r = static_cast<unsigned char>(color.R() * 255),
                      g = static_cast<unsigned char>(color.G() * 255),
                      b = static_cast<unsigned char>(color.B() * 255);
        os << r << g << b;
      }
    }
  }
 private:
};
}
}
#endif //RAYTRACE_INCLUDE_FILEFORMAT_PPM_H_
