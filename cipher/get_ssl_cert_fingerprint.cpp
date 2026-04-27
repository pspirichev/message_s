// Copyright (c) 2026 wlm1861.
//
// This program or pice of code is free software or its part: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, version 3 of the License.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <iomanip>
#include <ios>
#include <openssl/evp.h>
#include <openssl/x509.h>

#include "cipher.h"

namespace message_s {
    std::string get_ssl_cert_fingerprint(const X509* cert) {
        if (!cert) {
            return "";
        }

        unsigned char md[EVP_MAX_MD_SIZE];
        unsigned int n;

        if (X509_digest(cert, EVP_sha256(), md, &n)) {
            std::stringstream ss;
            for (unsigned int i = 0; i < n; i++) {
                ss << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << static_cast<int>(md[i]);
                if (i < n - 1) ss << ":";
            }
            return ss.str();
        }
        return "";
    }

    std::vector<uint8_t> get_ssl_cert_fingerprint_bin(const X509* cert) {
        if (!cert) return {};

        unsigned char md[EVP_MAX_MD_SIZE];
        unsigned int n;

        if (X509_digest(cert, EVP_sha256(), md, &n)) {
            return std::vector<uint8_t>(md, md + n);
        }

        return {};
    }
} // message_s