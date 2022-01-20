#ifndef RAYTRACE_INCLUDE_FILEFORMAT_PFM_H_
#define RAYTRACE_INCLUDE_FILEFORMAT_PFM_H_
#include "FileFormat.h"
#include <fstream>
#include <sstream>
namespace raytrace {
namespace file_format {
class PFM : public FileFormat {
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
    headerStream << "PF\n";
    headerStream << canvas.Width() << ' ' << canvas.Height() << '\n';
    headerStream << "-1.0\n";
    os << headerStream.str();
  }
  void OutputBody(std::ostream &os) const {
    const Canvas &canvas = GetCanvas();
    const size_t width = canvas.Width(), height = canvas.Height();
    for (size_t y = 0; y < width; y++) {
      for (size_t x = 0; x < width; x++) {
        Color color = canvas.Pixel(x, height - y - 1);
        float r = static_cast<float>(color.R()),
              g = static_cast<float>(color.G()),
              b = static_cast<float>(color.B());
        os << r << g << b;
      }
    }
  }
 private:
};
}
}
#endif //RAYTRACE_INCLUDE_FILEFORMAT_PFM_H_
