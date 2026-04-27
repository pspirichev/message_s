// Copyright (c) $today.year wlm1861.
//
// This program or pice of code is free software or its part: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, version 3 of the License.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef MESSAGE_S_GLOBAL_VARIABLES_H
#define MESSAGE_S_GLOBAL_VARIABLES_H

namespace message_s {
    //For X509 self-signed certificate generation
    inline unsigned char CERTIFICATE_FIELD_COUNTRY[] = "RU";
    inline unsigned char CERTIFICATE_COMPANY_NAME[] = "ISNAt";
    inline unsigned char COMMON_DIRECTORY_LINUX[] = "~/.config/message_s/";
}

#endif //MESSAGE_S_GLOBAL_VARIABLES_H
