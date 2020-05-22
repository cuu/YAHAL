
extern "C" {
  void  __yahal_bad_function_call(void) {
      // Loop forever
      while(true) ;
  }
}

namespace std {
  extern void __throw_bad_function_call(void) __attribute__((weak, alias("__yahal_bad_function_call"), unused));
}

