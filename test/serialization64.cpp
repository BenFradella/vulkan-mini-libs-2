/*
    Copyright (C) 2020 George Cave - gcave@stablecoder.ca

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless CHECKd by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <catch.hpp>
#include <vk_value_serialization.hpp>

#ifdef VK_KHR_synchronization2

namespace {
std::string cDummyStr = "AAABBBCCC";
}

TEST_CASE("Serialize64: Serializing one of the few 64-bit flag types, VkAccessFlagBits2KHR") {
  std::string retVal = cDummyStr;

  SECTION("Failure case where a bad type is given") {
    CHECK(vk_serialize("VkGarbagio", VK_ACCESS_2_INDEX_READ_BIT_KHR, &retVal) ==
          STEC_VK_SERIALIZATION_RESULT_ERROR_TYPE_NOT_FOUND);
    CHECK(retVal == cDummyStr);
  }

  SECTION("Failure case where a garbage non-existant bit is given") {
    CHECK(vk_serialize("VkAccessFlagBits2KHR", VK_ACCESS_2_INDEX_READ_BIT_KHR | 0xFFFFFFFF,
                       &retVal) == STEC_VK_SERIALIZATION_RESULT_ERROR_VALUE_NOT_FOUND);
    CHECK(retVal == cDummyStr);
  }

  SECTION("Successfully returns an when the bitflag has a zero-value enum") {
    CHECK(vk_serialize("VkAccessFlagBits2KHR", 0, &retVal) == STEC_VK_SERIALIZATION_RESULT_SUCCESS);
    CHECK(retVal == "NONE");
  }

  SECTION("Regular success cases") {
    SECTION("FlagBits") {
      CHECK(vk_serialize("VkAccessFlagBits2KHR", VK_ACCESS_2_INDEX_READ_BIT_KHR, &retVal) ==
            STEC_VK_SERIALIZATION_RESULT_SUCCESS);
      CHECK(retVal == "INDEX_READ");

      CHECK(vk_serialize("VkAccessFlagBits2KHR",
                         VK_ACCESS_2_INDEX_READ_BIT_KHR |
                             VK_ACCESS_2_ACCELERATION_STRUCTURE_WRITE_BIT_NV,
                         &retVal) == STEC_VK_SERIALIZATION_RESULT_SUCCESS);
      CHECK(retVal == "ACCELERATION_STRUCTURE_WRITE_BIT_KHR | INDEX_READ");
    }
    SECTION("Flags") {
      CHECK(vk_serialize("VkAccessFlags2KHR", VK_ACCESS_2_INDEX_READ_BIT_KHR, &retVal) ==
            STEC_VK_SERIALIZATION_RESULT_SUCCESS);
      CHECK(retVal == "INDEX_READ");

      CHECK(vk_serialize("VkAccessFlags2KHR",
                         VK_ACCESS_2_INDEX_READ_BIT_KHR |
                             VK_ACCESS_2_ACCELERATION_STRUCTURE_WRITE_BIT_NV,
                         &retVal) == STEC_VK_SERIALIZATION_RESULT_SUCCESS);
      CHECK(retVal == "ACCELERATION_STRUCTURE_WRITE_BIT_KHR | INDEX_READ");
    }
  }
}

#endif // VK_KHR_synchronization2