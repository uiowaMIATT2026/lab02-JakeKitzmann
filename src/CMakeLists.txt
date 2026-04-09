set(Register_SOURCE Register.cxx)


add_executable(Register_${MYHAWKID} ${Register_SOURCE})
target_link_libraries(Register_${MYHAWKID} ${ITK_LIBRARIES})