add_library(MathFunctions SHARED mysqrt.cxx)

install (TARGETS MathFunctions DESTINATION lib)
install (FILES mysqrt.h DESTINATION include)

