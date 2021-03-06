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

#pragma once

#include "runtime/os_interface/windows/gdi_interface.h"
#include "unit_tests/fixtures/gmm_environment_fixture.h"
#include "unit_tests/mocks/mock_wddm20.h"
#include "unit_tests/os_interface/windows/mock_gdi_interface.h"
#include "unit_tests/os_interface/windows/gdi_dll_fixture.h"
#include "mock_gmm_memory.h"
#include "test.h"

namespace OCLRT {
struct WddmFixture : public GmmEnvironmentFixture {
    void SetUp() override {
        GmmEnvironmentFixture::SetUp();
        wddm.reset(static_cast<WddmMock *>(Wddm::createWddm(WddmInterfaceVersion::Wddm20)));
        gdi = new MockGdi();
        wddm->gdi.reset(gdi);
    }

    void TearDown() override {
        GmmEnvironmentFixture::TearDown();
    };

    std::unique_ptr<WddmMock> wddm;
    MockGdi *gdi = nullptr;
};

struct WddmFixtureWithMockGdiDll : public GmmEnvironmentFixture, public GdiDllFixture {
    void SetUp() override {
        GmmEnvironmentFixture::SetUp();
        GdiDllFixture::SetUp();
        wddm.reset(static_cast<WddmMock *>(Wddm::createWddm(WddmInterfaceVersion::Wddm20)));
    }

    void TearDown() override {
        GdiDllFixture::TearDown();
        GmmEnvironmentFixture::TearDown();
    }

    std::unique_ptr<WddmMock> wddm;
};

struct WddmInstrumentationGmmFixture : public GmmEnvironmentFixture {
    void SetUp() override {
        GmmEnvironmentFixture::SetUp();
        wddm.reset(static_cast<WddmMock *>(Wddm::createWddm(WddmInterfaceVersion::Wddm20)));
        gmmMem = new ::testing::NiceMock<GmockGmmMemory>();
        wddm->gmmMemory.reset(gmmMem);
    }
    void TearDown() override {
        GmmEnvironmentFixture::TearDown();
    }

    std::unique_ptr<WddmMock> wddm;
    GmockGmmMemory *gmmMem = nullptr;
};

using WddmTest = Test<WddmFixture>;
using WddmTestWithMockGdiDll = Test<WddmFixtureWithMockGdiDll>;
using WddmInstrumentationTest = Test<WddmInstrumentationGmmFixture>;
using WddmTestSingle = ::testing::Test;
} // namespace OCLRT
