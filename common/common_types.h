// Copyright (c) 2026 wlm1861.
//
// This program or pice of code is free software or its part: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, version 3 of the License.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef MESSAGE_S_COMMON_TYPES_H
#define MESSAGE_S_COMMON_TYPES_H
#include <memory>
#include <openssl/types.h>
#include <openssl/x509.h>

namespace message_s {
    //For X509 self-signed certificate generation
    using X509_ptr = std::unique_ptr<X509, decltype(&X509_free)>;
    using EVP_PKEY_ptr = std::unique_ptr<EVP_PKEY, decltype(&EVP_PKEY_free)>;
    struct CertKeySafePair {
        X509_ptr cert;
        EVP_PKEY_ptr pkey;
    };

}

#endif //MESSAGE_S_COMMON_TYPES_H
