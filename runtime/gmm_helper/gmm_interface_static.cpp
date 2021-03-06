/*
 * Copyright (c) 2018, Intel Corporation
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

#include "runtime/gmm_helper/gmm_helper.h"

namespace OCLRT {
GMM_STATUS GMM_STDCALL myPfnCreateSingletonContext(const PLATFORM platform, const void *pSkuTable, const void *pWaTable, const void *pGtSysInfo) {
    return GmmInitGlobalContext(platform, reinterpret_cast<const SKU_FEATURE_TABLE *>(pSkuTable), reinterpret_cast<const WA_TABLE *>(pWaTable), reinterpret_cast<const GT_SYSTEM_INFO *>(pGtSysInfo), GMM_CLIENT::GMM_OCL_VISTA);
}
decltype(GmmHelper::initGlobalContextFunc) GmmHelper::initGlobalContextFunc = nullptr;
decltype(GmmHelper::destroyGlobalContextFunc) GmmHelper::destroyGlobalContextFunc = nullptr;
decltype(GmmHelper::createClientContextFunc) GmmHelper::createClientContextFunc = nullptr;
decltype(GmmHelper::deleteClientContextFunc) GmmHelper::deleteClientContextFunc = nullptr;

void GmmHelper::loadLib() {
    GmmHelper::initGlobalContextFunc = myPfnCreateSingletonContext;
    GmmHelper::destroyGlobalContextFunc = GmmDestroyGlobalContext;
    GmmHelper::createClientContextFunc = GmmCreateClientContext;
    GmmHelper::deleteClientContextFunc = GmmDeleteClientContext;
    isLoaded = true;
}
} // namespace OCLRT
