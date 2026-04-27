// Copyright (c) 2026 wlm1861.
//
// This program or pice of code is free software or its part: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, version 3 of the License.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "cipher.h"
#include <openssl/x509.h>
#include "../common/global_variables.h"

namespace message_s {

    EVP_PKEY* generate_pkey() {
        EVP_PKEY* pkey = EVP_RSA_gen(2048);
        if (!pkey) {
            return nullptr;
        }
        return pkey;
    }

    unsigned int generate_ssl_cert(const unsigned int ttl_sec, const unsigned char *common_name, X509 **cert,
                                   EVP_PKEY **pkey) {
        *cert = X509_new();
        if (!*cert) {
            EVP_PKEY_free(*pkey);
            X509_free(*cert);
            return 1;
        }
        X509_set_version(*cert, 2);

        ASN1_INTEGER* serial_number = X509_get_serialNumber(*cert);
        BIGNUM* bn_serial_number = BN_new();
        if (BN_rand(bn_serial_number, 160, BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ANY)) {
            BN_to_ASN1_INTEGER(bn_serial_number, serial_number);
        } else {
            ASN1_INTEGER_set(serial_number, 1);
        }
        BN_free(bn_serial_number);

        X509_gmtime_adj(X509_get_notBefore(*cert), 0);
        X509_gmtime_adj(X509_get_notAfter(*cert), ttl_sec);

        *pkey = generate_pkey();
        if (!*pkey) {
            X509_free(*cert);
            EVP_PKEY_free(*pkey);
            return 2;
        }
        X509_set_pubkey(*cert, *pkey);

        X509_NAME* name = X509_get_subject_name(*cert);
        X509_NAME_add_entry_by_txt(name, "C", MBSTRING_ASC, CERTIFICATE_FIELD_COUNTRY, -1, -1, 0);
        X509_NAME_add_entry_by_txt(name, "O", MBSTRING_ASC, CERTIFICATE_COMPANY_NAME, -1, -1, 0);
        X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, common_name, -1, -1, 0);

        X509_set_issuer_name(*cert, name);

        if (!X509_sign(*cert, *pkey, EVP_sha256())) {
            EVP_PKEY_free(*pkey);
            X509_free(*cert);
            return 3;
        }

        return 0;
    }
} // message_s