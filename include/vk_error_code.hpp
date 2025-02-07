/*
    Copyright (C) 2021 George Cave - gcave@stablecoder.ca

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
    This file was auto-generated by the Vulkan Mini Libs 2 utility:
    https://github.com/stablecoder/vulkan-mini-libs-2.git
    or
    https://git.stabletec.com/utilities/vulkan-mini-libs-2.git

    Check for an updated version anytime, or state concerns/bugs.
*/

#ifndef VK_ERROR_CODE_HPP
#define VK_ERROR_CODE_HPP

#include <vk_result_to_string.h>
#include <vulkan/vulkan.h>

#include <system_error>

/*  USAGE
    To use, include this header where the declarations for the boolean checks are required.

    On *ONE* compilation unit, include the definition of `#define VK_ERROR_CODE_CONFIG_MAIN`
    so that the definitions are compiled somewhere following the one definition rule.
*/

namespace std {
template <>
struct is_error_code_enum<VkResult> : true_type {};
} // namespace std

std::error_code make_error_code(VkResult);

#ifdef VK_ERROR_CODE_CONFIG_MAIN

namespace {

struct VulkanErrCategory : std::error_category {
  const char *name() const noexcept override;
  std::string message(int ev) const override;
};

const char *VulkanErrCategory::name() const noexcept { return "VkResult"; }

std::string VulkanErrCategory::message(int ev) const {
  return vkResultToString(static_cast<VkResult>(ev));
}

const VulkanErrCategory vulkanErrCategory{};

} // namespace

std::error_code make_error_code(VkResult e) { return {static_cast<int>(e), vulkanErrCategory}; }

#endif // VK_ERROR_CODE_CONFIG_MAIN
#endif // VK_ERROR_CODE_HPP
