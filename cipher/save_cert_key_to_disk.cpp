// Copyright (c) 2026 wlm1861.
//
// This program or pice of code is free software or its part: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, version 3 of the License.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>.

//
// Created by user0 on 27.04.2026.
//

#include <string>
#include <openssl/types.h>
#include <iostream>
#include <memory>
#include <openssl/asn1.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/x509.h>

#include "cipher.h"
#include "../common/global_variables.h"

namespace message_s {

    std::string get_cert_common_name(const X509* cert) {
        const X509_NAME* name = X509_get_subject_name(cert);

        const int loc = X509_NAME_get_index_by_NID(name, NID_commonName, -1);
        if (loc < 1) return "";

        const ASN1_STRING* data = X509_NAME_ENTRY_get_data(X509_NAME_get_entry(name, loc));

        unsigned char* utf8 = nullptr;
        if (ASN1_STRING_to_UTF8(&utf8, data) < 0) return "";

        auto common_name = std::string(reinterpret_cast<char*>(utf8));

        OPENSSL_free(utf8);
        return common_name;
    }

    unsigned int save_cert_to_disk(const X509* cert, std::string folder_name) {
        if (!cert) {
            return 1;
        } if (folder_name.empty()) {
            return 2;
        } if (folder_name.back() == '/') {
            folder_name.pop_back();
        }

        std::string static full_filename = folder_name + "/" + get_cert_common_name(cert) + ".pem";

        BIO* bio = BIO_new_file(full_filename.c_str(), "w");

        if (!bio) {
            std::cerr << "BIO_new_file() failed: " << full_filename << std::endl;
            return 3;
        }

        if (PEM_write_bio_X509(bio, cert) != 1) return 4;

        BIO_free(bio);

        return 0;
    };

    unsigned int save_kay_to_disk(const EVP_PKEY* key, std::string folder_name) {

        return 0;
    };

    unsigned int save_cert_key_pair_to_disk(const X509* cert, const EVP_PKEY* key, std::string file_name) {

        return 0;
    };
}
