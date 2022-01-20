#ifndef RAYTRACE_INCLUDE_FILEFORMAT_FILEFORMAT_H_
#define RAYTRACE_INCLUDE_FILEFORMAT_FILEFORMAT_H_
#include <string>
#include "../Canvas.h"
namespace raytrace {
namespace file_format {
class FileFormat {
 public:
  FileFormat(const Canvas &canvas) : m_canvas_(canvas) {}
  virtual void Output(const std::string &filename) = 0;
  virtual ~FileFormat() {}
 protected:
  const Canvas &GetCanvas() const { return m_canvas_; }
 private:
  const Canvas &m_canvas_;
};
}
}
#endif //RAYTRACE_INCLUDE_FILEFORMAT_FILEFORMAT_H_
