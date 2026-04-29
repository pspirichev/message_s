// Copyright (C) 2026 wlm1891
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <openssl/bio.h>
#include <openssl/pem.h>

#include "cipher.h"
#include "../utils/utils.h"

namespace message_s {
    unsigned int load_cert_from_disk(X509** cert, const std::string& certificate_file_name) {
        if (certificate_file_name.empty()) {
            puke("File name not set");
            return 1;
        }

        BIO* bio = BIO_new_file(certificate_file_name.c_str(), "r");
        if (!bio) {
            puke("Can not open bio");
            return 2;
        }

        X509* internal_cert = PEM_read_bio_X509(bio, nullptr, nullptr, nullptr);
        BIO_free(bio);
        if (!internal_cert) {
            puke("Can not read certificate from disk");
            return 3;
        }

        *cert = internal_cert;
        return 0;
    }

    unsigned int load_key_from_disk(EVP_PKEY** key, const std::string& private_key_file_name) {
        if (private_key_file_name.empty()) {
            puke("File name is empty");
            return 1;
        }

        BIO* bio_private = BIO_new_file(private_key_file_name.c_str(), "r");
        if (!bio_private) {
            puke("Can not open bio");
            return 2;
        }

        EVP_PKEY* internal_key = nullptr;
        internal_key = PEM_read_bio_PrivateKey(bio_private, nullptr, nullptr, nullptr);
        if (!internal_key) {
            puke("Can not read private key from disk");
            return 3;
        }

        BIO_free(bio_private);
        *key = internal_key;
        return 0;
    }

    unsigned int load_cert_key_pair_from_disk(X509** cert, EVP_PKEY** key, const std::string& certificate_file_name, const std::string& private_key_file_name) {
        const unsigned int c = load_cert_from_disk(cert, certificate_file_name);
        const unsigned int k = load_key_from_disk(key, private_key_file_name);

        if (c != 0) return c;
        if (k != 0) return k;
        return 0;
    }
}
