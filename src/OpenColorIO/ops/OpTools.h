// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the OpenColorIO Project.


#ifndef INCLUDED_OCIO_OPTOOLS_H
#define INCLUDED_OCIO_OPTOOLS_H

#include <OpenColorIO/OpenColorIO.h>

#include "Op.h"
#include "PrivateTypes.h"


namespace OCIO_NAMESPACE
{

void EvalTransform(const float * in, float * out,
                   long numPixels,
                   OpRcPtrVec & ops);

// Allow us to temporarily manipulate the inversion quality without
// cloning the object.
template <class LutType>
class LutStyleGuard
{
public:
    LutStyleGuard() = delete;
    LutStyleGuard(const LutStyleGuard &) = delete;
    LutStyleGuard & operator=(const LutStyleGuard &) = delete;
    LutStyleGuard & operator=(LutStyleGuard &&) = delete;

    LutStyleGuard(const LutType & lut)
        : m_prevQuality(lut.getInversionQuality())
        , m_lut(const_cast<LutType &>(lut))
    {
        m_lut.setInversionQuality(LUT_INVERSION_EXACT);
    }

    ~LutStyleGuard()
    {
        if (m_prevQuality != LUT_INVERSION_EXACT)
        {
            m_lut.setInversionQuality(m_prevQuality);
        }
    }

private:
    LutInversionQuality m_prevQuality;
    LutType &           m_lut;
};


} // namespace OCIO_NAMESPACE

#endif
