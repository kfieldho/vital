/*ckwg +29
 * Copyright 2014-2015 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither name of Kitware, Inc. nor the names of any contributors may be used
 *    to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file
 * \brief Header defining abstract \link vital::algo::optimize_cameras camera
 *        optimization \endlink algorithm
 */

#ifndef VITAL_ALGO_OPTIMIZE_CAMERAS_H_
#define VITAL_ALGO_OPTIMIZE_CAMERAS_H_

#include <vital/vital_config.h>

#include <vital/algo/algorithm.h>
#include <vital/types/camera_map.h>
#include <vital/types/landmark_map.h>
#include <vital/types/track_set.h>


namespace kwiver {
namespace vital {
namespace algo {


/// Abstract algorithm definition base for optimizing cameras
class VITAL_EXPORT optimize_cameras
  : public kwiver::vital::algorithm_def<optimize_cameras>
{
public:
  /// Return the name of this algorithm definition
  static std::string static_type_name() { return "optimize_cameras"; }

  /// Optimize camera parameters given sets of landmarks and tracks
  /**
   * We only optimize cameras that have associating tracks and landmarks in
   * the given maps.
   *
   * \throws invalid_value When one or more of the given pointer is Null.
   *
   * \param[in,out] cameras   Cameras to optimize.
   * \param[in]     tracks    The tracks to use as constraints.
   * \param[in]     landmarks The landmarks the cameras are viewing.
   */
  virtual void
  optimize(kwiver::vital::camera_map_sptr & cameras,
           kwiver::vital::track_set_sptr tracks,
           kwiver::vital::landmark_map_sptr landmarks) const = 0;

};


/// Type definition for shared pointer to an optimize cameras algorithm
typedef boost::shared_ptr<optimize_cameras> optimize_cameras_sptr;


} } } // end namespace


#endif // VITAL_ALGO_OPTIMIZE_CAMERAS_H_
