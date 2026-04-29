// Copyright (c) 2026 wlm1861.
//
// This program or pice of code is free software or its part: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, version 3 of the License.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <iostream>
#include <openssl/evp.h>
#include <openssl/ssl.h>
#include "../cipher/cipher.h"
#include <openssl/types.h>

int test_1() {
    std::cout << OpenSSL_version(OPENSSL_VERSION) << std::endl;
    return 0;
}

int test_2() {
    X509* cert = nullptr;
    EVP_PKEY* pkey = nullptr;
    message_s::generate_ssl_cert(message_s::TTL_SEC_YEAR, (unsigned char*) "localhost", &cert, &pkey);
    PEM_write_X509(stdout, cert);
    BIO *out = BIO_new_fp(stdout, BIO_NOCLOSE);
    EVP_PKEY_print_public(out, pkey, 0, nullptr);
    EVP_PKEY_print_private(out, pkey, 0, nullptr);
    BIO_free(out);
    X509_free(cert);
    EVP_PKEY_free(pkey);
    return 0;
}

int test_3() {
    X509* cert = nullptr;
    EVP_PKEY* pkey = nullptr;
    message_s::generate_ssl_cert(message_s::TTL_SEC_YEAR, (unsigned char*) "localhost", &cert, &pkey);
    std::string const hash1 = message_s::get_ssl_cert_pubkey_fingerprint(cert);
    std::string const hash2 = message_s::get_ssl_cert_pubkey_fingerprint(cert);
    std::string const hash3 = message_s::get_ssl_cert_pubkey_fingerprint(cert);
    std::vector<uint8_t> const hash4 = message_s::get_ssl_cert_pubkey_fingerprint_bin(cert);
    std::cout << hash1 << std::endl << hash2 << std::endl << hash3 << std::endl;
    for (unsigned char i : hash4) {
        std::cout << i;
    }
    std::cout << std::endl;
    X509_free(cert);
    EVP_PKEY_free(pkey);
    return 0;
}

int test_4() {
    X509* cert = nullptr;
    EVP_PKEY* pkey = nullptr;
    message_s::generate_ssl_cert(message_s::TTL_SEC_YEAR, (unsigned char*) "127.0.0.1", &cert, &pkey);

    PEM_write_X509(stdout, cert);

    BIO *out = BIO_new_fp(stdout, BIO_NOCLOSE);
    EVP_PKEY_print_public(out, pkey, 0, nullptr);
    EVP_PKEY_print_private(out, pkey, 0, nullptr);

    std::cout << message_s::save_cert_to_disk(cert, "/home/user0/dev/message_s/") << std::endl;
    std::cout << message_s::save_kay_to_disk(pkey, "/home/user0/dev/message_s/") << std::endl;

    X509_free(cert);
    EVP_PKEY_free(pkey);
    BIO_free(out);
    return 0;
}

int test_5() {
    X509* cert = nullptr;
    EVP_PKEY* pkey = nullptr;
    message_s::load_cert_key_pair_from_disk(&cert, &pkey, "/home/user0/dev/message_s/127.0.0.1.pem", "/home/user0/dev/message_s/private.pem");

    PEM_write_X509(stdout, cert);

    BIO *out = BIO_new_fp(stdout, BIO_NOCLOSE);
    EVP_PKEY_print_public(out, pkey, 0, nullptr);
    EVP_PKEY_print_private(out, pkey, 0, nullptr);

    BIO_free(out);
    X509_free(cert);
    EVP_PKEY_free(pkey);
    return 0;
}

int main() {
    test_4();
    std::cout << std::endl << std::endl;
    test_5();
    return 0;
}