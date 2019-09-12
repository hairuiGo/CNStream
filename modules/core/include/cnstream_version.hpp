/*************************************************************************
 * Copyright (C) [2019] by Cambricon, Inc. All rights reserved
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *************************************************************************/

#ifndef CNSTREAM_VERSION_HPP_
#define CNSTREAM_VERSION_HPP_

namespace cnstream {

/*************************************************************************
 * @brief get cnstream version string
 * @return version string formatted as "v%major.%minor.%patch"
 *         e.g. "v3.5.1"
 ************************************************************************/
const char* VersionString();

/*************************************************************************
 * @brief get cnstream major version
 * @return major version, [0, MAXINT]
 ************************************************************************/
const int MajorVersion();
/*************************************************************************
 * @brief get cnstream minor version
 * @return minor version, [0, MAXINT]
 ************************************************************************/
const int MinorVersion();
/*************************************************************************
 * @brief get cnstream patch version
 * @return patch version, [0, MAXINT]
 ************************************************************************/
const int PatchVersion();

}  // namespace cnstream

#endif  // CNSTREAM_VERSION_HPP_
