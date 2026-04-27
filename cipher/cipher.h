// Copyright (c) 2026 wlm1861.
//
// This program or pice of code is free software or its part: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, version 3 of the License.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Plic License along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef MESSAGE_S_GENERATE_SSL_CERT_H
#define MESSAGE_S_GENERATE_SSL_CERT_H
#include <string>
#include <vector>
#include <openssl/types.h>

namespace message_s {
        constexpr unsigned int TTL_SEC_YEAR = 31536000L;

        /// @brief Generate SSL certificate for designated common name and keypair
        /// @param ttl_sec Certificate Time To Live in seconds, can use TTL_SEC_YEAR for 1 year lifecycle
        /// @param common_name Common name for certificate based on external IP or DNS name
        /// @param cert Pointer to pointer for returning X509 certificate object, remember to manage memory
        /// @param pkey Pointer to pointer for returning EVP_PKEY keys envelope object, remember to manage memory
        /// @return 0 - success, 1 - can't create X509 object, 2 - can't create EvP_PKEY object, 3 - can't sign certificate
        unsigned int generate_ssl_cert(unsigned int ttl_sec, const unsigned char* common_name, X509** cert, EVP_PKEY** pkey);

        /**
         * @brief Get SHA256 hash of certificate in string human-readable format
         * @param cert Certificate for getting hash of
         * @return String of human-readable representation of certificate
         */
        std::string get_ssl_cert_fingerprint(const X509* cert);

        /**
         * @brief et SHA256 hash of certificate in binary format
         * @param cert Certificate for getting hash of
         * @return Binary vector digest of the DER representation of their entire data of 'cert' param
         */
        std::vector<uint8_t> get_ssl_cert_fingerprint_bin(const X509* cert);

        /**
         * @brief
         * @param cert
         * @param folder_name
         * @return
         */
        unsigned int save_cert_to_disk(const X509* cert, std::string folder_name);

        /**
         * @brief
         * @param key
         * @param folder_name
         * @return
         */
        unsigned int save_kay_to_disk(const EVP_PKEY* key, std::string folder_name);

        /**
         * @brief
         * @param cert
         * @param key
         * @param file_name
         * @return
         */
        unsigned int save_cert_key_pair_to_disk(const X509* cert, const EVP_PKEY* key, std::string file_name);
} // message_s

#endif //MESSAGE_S_GENERATE_SSL_CERT_H
