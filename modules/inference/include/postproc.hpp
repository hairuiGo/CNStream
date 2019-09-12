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

#ifndef POSTPROC_H_
#define POSTPROC_H_

#include <string>
#include <utility>
#include <vector>

#include "cnbase/reflex_object.h"
#include "cninfer/model_loader.h"

#include "cnstream_frame.hpp"

namespace cnstream {

using CNFrameInfoPtr = std::shared_ptr<CNFrameInfo>;

class Postproc {
 public:
  virtual ~Postproc() {}
  static Postproc* Create(const std::string& proc_name);

  void set_threshold(const float threshold);

  /******************************************************************************
   * @brief Execute postproc on neural network outputs
   * @param
   *   net_outputs: neural network outputs
   *   model: model information(you can get input shape and output shape from model)
   *   package: smart pointer of struct to store processed result
   * @return return 0 if succeed
   ******************************************************************************/
  virtual int Execute(const std::vector<float*>& net_outputs,
      const std::shared_ptr<libstream::ModelLoader>& model,
      const CNFrameInfoPtr& package) = 0;

 protected:
  float threshold_ = 0;
};  // class Postproc

class PostprocSsd : public Postproc, virtual public libstream::ReflexObjectEx<Postproc> {
 public:
  int Execute(const std::vector<float*>& net_outputs,
      const std::shared_ptr<libstream::ModelLoader>& model,
      const CNFrameInfoPtr& package) override;

  DECLARE_REFLEX_OBJECT_EX(PostprocSsd, Postproc)
};  // class PostprocSsd

}  // namespace cnstream

#endif  // ifndef POSTPROC_H_
