// g2o - General Graph Optimization
// Copyright (C) 2011 R. Kuemmerle, G. Grisetti, W. Burgard
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
// IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
// TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef G2O_VERTEX_SE2_OFFSET_PARAMETERS_H_
#define G2O_VERTEX_SE2_OFFSET_PARAMETERS_H_


#include "se2.h"
#include "g2o_types_slam2d_api.h"
#include "g2o/core/cache.h"


namespace g2o {

  class VertexSE2;

  /**
   * \brief offset for an SE2
   */
  class G2O_TYPES_SLAM2D_API ParameterSE2Offset: public Parameter
  {
    public:
      EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
      ParameterSE2Offset();

      virtual bool read(std::istream& is);
      virtual bool write(std::ostream& os) const;

      /**
       * update the offset to a new value.
       * re-calculates the different representations, e.g., the rotation matrix
       */
      void setOffset(const SE2& offset_ = SE2());

      const SE2& offset() const { return _offset;}

      //! rotation of the offset as 2x2 rotation matrix
      const Isometry2& offsetMatrix() const { return _offsetMatrix;}

      //! rotation of the inverse offset as 2x2 rotation matrix
      const Isometry2& inverseOffsetMatrix() const { return _inverseOffsetMatrix;}

    protected:
      SE2 _offset;
      Isometry2 _offsetMatrix;
      Isometry2 _inverseOffsetMatrix;
  };

  /**
   * \brief caching the offset related to a vertex
   */
  class G2O_TYPES_SLAM2D_API CacheSE2Offset: public Cache {
    public:
      EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
      using ParameterType = ParameterSE2Offset;

      CacheSE2Offset();
      virtual void updateImpl();

      std::shared_ptr<ParameterSE2Offset> offsetParam() const {
        return std::static_pointer_cast<ParameterSE2Offset>(_parameters[0]);
      }

      const SE2& w2n() const {return _se2_w2n;}
      const SE2& n2w() const {return _se2_n2w;}

      const Isometry2& w2nMatrix() const { return _w2n;}
      const Isometry2& n2wMatrix() const { return _n2w;}
      const Isometry2& w2lMatrix() const { return _w2l;}

      const Matrix2 RpInverseRInverseMatrix() const { return _RpInverse_RInverse; }
      const Matrix2 RpInverseRInversePrimeMatrix() const { return _RpInverse_RInversePrime; }

    protected:
      SE2 _se2_w2n;
      SE2 _se2_n2w;

      Isometry2 _w2n; ///< world to sensor transform
      Isometry2 _w2l; ///< world to local
      Isometry2 _n2w; ///< sensor to world
      Matrix2 _RpInverse_RInverse;
      Matrix2 _RpInverse_RInversePrime;

  };

}

#endif
