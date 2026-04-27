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
#include <openssl/ssl.h>
#include <openssl/x509.h>

#include "cipher.h"
#include "../utils/utils.h"

namespace message_s {

    std::string get_cert_common_name(const X509* cert) {
        const X509_NAME* name = X509_get_subject_name(cert);

        const int loc = X509_NAME_get_index_by_NID(name, NID_commonName, -1);
        if (loc < 1) {
            puke("Did not found common name in provided certificate");
            return "";
        }

        const ASN1_STRING* data = X509_NAME_ENTRY_get_data(X509_NAME_get_entry(name, loc));

        unsigned char* utf8 = nullptr;
        if (ASN1_STRING_to_UTF8(&utf8, data) < 0) {
            puke("Can not convert provided data to UTF8");
            return "";
        }

        auto common_name = std::string(reinterpret_cast<char*>(utf8));

        OPENSSL_free(utf8);
        return common_name;
    }

    unsigned int save_cert_to_disk(const X509* cert, std::string folder_name) {
        if (!cert) {
            puke("No certificate provided");
            return 1;
        } if (folder_name.empty()) {
            puke("Empty folder name provided");
            return 2;
        } if (folder_name.back() == '/') {
            folder_name.pop_back();
        }

        std::string static full_filename = folder_name + "/" + get_cert_common_name(cert) + ".pem";

        BIO* bio = BIO_new_file(full_filename.c_str(), "w");

        if (!bio) {
            puke("BIO_new_file() failed: " + full_filename);
            return 3;
        }

        if (PEM_write_bio_X509(bio, cert) != 1) {
            puke("Writing PEM file error");
            return 4;
        }

        BIO_free(bio);

        return 0;
    };

    unsigned int save_kay_to_disk(const EVP_PKEY* key, std::string folder_name) {
        if (!key) {
            puke ("No key provided");
            return 1;
        } if (folder_name.empty()) {
            puke("Empty folder name provided");
            return 2;
        } if (folder_name.back() == '/') {
            folder_name.pop_back();
        }

        std::string static public_key_filename = folder_name + "/public.pem";
        std::string static private_key_filename = folder_name + "/private.pem";

        BIO* private_bio = BIO_new_file(private_key_filename.c_str(), "w");
        BIO* public_bio = BIO_new_file(public_key_filename.c_str(), "w");

        if (!public_bio || !private_bio) {
            puke("BIO_new_file() failed: " + public_key_filename + " " + private_key_filename);
            BIO_free(private_bio);
            BIO_free(public_bio);
            return 3;
        }

        if (PEM_write_bio_PrivateKey(private_bio, key, nullptr, nullptr, 0, nullptr, nullptr) != 1
            || PEM_write_bio_PUBKEY(public_bio, key) != 1 ) {
            puke("Key write failed: " + public_key_filename + " " + private_key_filename);
            BIO_free(private_bio);
            BIO_free(public_bio);
            return 4;
        }

        BIO_free(private_bio);
        BIO_free(public_bio);

        return 0;
    };

    unsigned int save_cert_key_pair_to_disk(const X509* cert, const EVP_PKEY* key, const std::string& folder_name, unsigned int* cert_res, unsigned int* key_res) {
        *cert_res = save_cert_to_disk(cert, folder_name);
        *key_res = save_kay_to_disk(key, folder_name);
        if (*cert_res != 0 && *key_res != 0) {
            return 1;
        }
        return 0;
    };
}
