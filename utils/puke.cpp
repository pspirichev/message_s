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

#include <chrono>

#include "utils.h"
#include <iostream>

namespace message_s {
    void puke(const std::string& what_to_puke, const std::source_location location) {
        auto now = std::chrono::system_clock::now();
        std::cerr <<
            std::format("{:%Y-%m-%d %H:%M:%S}: ", now) <<
                location.function_name() <<
                    " at " <<
                        location.file_name() <<
                            std::endl <<
                            what_to_puke <<
                                std::endl;
    }
}
