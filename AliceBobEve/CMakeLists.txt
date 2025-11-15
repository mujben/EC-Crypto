add_executable(ECDH ECDH_sim.cpp)
target_link_libraries(ECDH krypto_lib)
target_link_libraries(ECDH sodium)

add_executable(ECDSA ECDSA_sim.cpp)
target_link_libraries(ECDSA krypto_lib)
target_link_libraries(ECDSA sodium)

