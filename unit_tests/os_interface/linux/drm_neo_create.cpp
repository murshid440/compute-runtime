/*
 * Copyright (c) 2017 - 2018, Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "runtime/os_interface/linux/drm_neo.h"
#include "drm/i915_drm.h"
#include "runtime/helpers/options.h"
#include "test.h"
#include "unit_tests/os_interface/linux/drm_mock.h"

#include <vector>

namespace OCLRT {

static std::vector<Drm *> drmMockStack;

class DrmMockDefault : public DrmMock {
  public:
    DrmMockDefault() : DrmMock() {
        StoredRetVal = 0;
        StoredRetValForDeviceID = 0;
        StoredRetValForEUVal = 0;
        StoredRetValForSSVal = 0;
        StoredRetValForDeviceRevID = 0;
        StoredRetValForPooledEU = 0;
        StoredRetValForMinEUinPool = 0;
        setGtType(GTTYPE_GT1);
    }
};

struct static_init : public DrmMockDefault {
    static_init() : DrmMockDefault() {
        drmMockStack.push_back(this);
    }
};

static static_init s;

void pushDrmMock(Drm *mock) {
    drmMockStack.push_back(mock);
}

void popDrmMock() {
    drmMockStack.pop_back();
}

Drm::~Drm() {
    fd = -1;
}

Drm *Drm::get(int32_t deviceOrdinal) {
    // We silently skip deviceOrdinal
    EXPECT_EQ(deviceOrdinal, 0);
    return drmMockStack[drmMockStack.size() - 1];
}

Drm *Drm::create(int32_t deviceOrdinal) {
    // We silently skip deviceOrdinal
    EXPECT_EQ(deviceOrdinal, 0);

    return drmMockStack[drmMockStack.size() - 1];
}

void Drm::closeDevice(int32_t deviceOrdinal) {
    drmMockStack[drmMockStack.size() - 1]->fd = -1;
}
} // namespace OCLRT
