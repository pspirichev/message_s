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
#include "../utils/utils.h"

namespace message_s {
    bool get_ssl_cert_pubkey_hash_common(const X509* cert, unsigned int& md_len, unsigned char* md) {
        if (!cert) {
            puke("No certificate provided");
            return "";
        }

        X509_PUBKEY* pubkey = X509_get_X509_PUBKEY(cert);
        if (!pubkey) {
            puke("No pubkey in provided certificate found");
            return "";
        }

        unsigned char* der = nullptr;
        int der_len = i2d_X509_PUBKEY(pubkey, &der);
        if (der_len < 0 || !der) {
            puke("Can not get DER binary representation of public key");
            return "";
        }

        if (EVP_Digest(der, der_len, md, &md_len, EVP_sha256(), nullptr)) {
            return true;
        }

        puke("Digestion failed");
        return false;
    }

    std::string get_ssl_cert_pubkey_fingerprint(const X509* cert) {
        unsigned char md[EVP_MAX_MD_SIZE];
        unsigned int md_len;

       if (get_ssl_cert_pubkey_hash_common(cert, md_len, md)) {
            std::stringstream ss;
            for (unsigned int i = 0; i < md_len; i++) {
                ss << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << static_cast<int>(md[i]);
                if (i < md_len - 1) ss << ":";
            }
            return ss.str();
        }

        return "";
    }

    std::vector<uint8_t> get_ssl_cert_pubkey_fingerprint_bin(const X509* cert) {
        unsigned char md[EVP_MAX_MD_SIZE];
        unsigned int md_len;

        if (get_ssl_cert_pubkey_hash_common(cert, md_len, md)) {
            return std::vector<uint8_t>(md, md + md_len);
        }

        return {};
    }
} // message_s