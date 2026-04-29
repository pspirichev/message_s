cmake_minimum_required(VERSION 3.31)
project(message_s)

set(CMAKE_CXX_STANDARD 20)

#openssl init
find_package(OpenSSL REQUIRED)

#main config
add_executable(message_s main.cpp
        cipher/generate_ssl_cert.cpp
        cipher/cipher.h
        common/global_variables.h
        common/common_types.h
        cipher/get_ssl_cert_fingerprint.cpp
        utils/utils.h
        cipher/save_cert_key_to_disk.cpp
        utils/puke.cpp
        cipher/load_cert_key_from_disk.cpp
)

#tests
add_executable(message_s_test tests/main_tests.cpp
        cipher/generate_ssl_cert.cpp
        cipher/cipher.h
        common/global_variables.h
        common/common_types.h
        cipher/get_ssl_cert_fingerprint.cpp
        utils/utils.h
        cipher/save_cert_key_to_disk.cpp
        utils/puke.cpp
        cipher/load_cert_key_from_disk.cpp
)

target_link_libraries(message_s PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(message_s_test PRIVATE OpenSSL::SSL OpenSSL::Crypto)