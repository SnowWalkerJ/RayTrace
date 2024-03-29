#ifndef RAYTRACE_INCLUDE_IMPL_FAKE_THREAD_POOL_H_
#define RAYTRACE_INCLUDE_IMPL_FAKE_THREAD_POOL_H_

class thread_pool {
 public:
  thread_pool(unsigned int count=0) {

  }
  template <typename T1, typename T2, typename F>
  void parallelize_loop(T1 start, T2 end, F func) {
    func(start, end);
  }
};

#endif //RAYTRACE_INCLUDE_IMPL_FAKE_THREAD_POOL_H_
