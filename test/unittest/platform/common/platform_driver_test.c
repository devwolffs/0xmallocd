/*
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd.
 *
 * HDF is dual licensed: you can use it either under the terms of
 * the GPL, or the BSD license, at your option.
 * See the LICENSE file in the root of this repository for complete details.
 */

#include "i2c_test.h"
#include "device_resource_if.h"
#include "hdf_base.h"
#include "hdf_device_desc.h"
#include "hdf_log.h"

static void DoAllPlatformTest(void)
{
#ifdef PLATFORM_TEST_ON_INIT
#ifdef LOSCFG_DRIVERS_HDF_PLATFORM_I2C
    HDF_LOGE("DoAllPlatformTest: do i2c test ...");
    I2cTestExecuteAll();
#endif
#endif
}

static int32_t PlatformTestBind(struct HdfDeviceObject *device)
{
    struct IDeviceIoService service;

    if (device == NULL) {
        HDF_LOGE("%s: device is null!", __func__);
        return HDF_ERR_IO;
    }

    device->service = &service;
    DoAllPlatformTest();
    HDF_LOGE("PlatformTestBind: done!");
    return HDF_SUCCESS;
}

static int32_t PlatformTestInit(struct HdfDeviceObject *device)
{
    (void)device;
    return HDF_SUCCESS;
}

static void PlatformTestRelease(struct HdfDeviceObject *device)
{
    if (device != NULL) {
        device->service = NULL;
    }
    return;
}

struct HdfDriverEntry g_platformTestEntry = {
    .moduleVersion = 1,
    .Bind = PlatformTestBind,
    .Init = PlatformTestInit,
    .Release = PlatformTestRelease,
    .moduleName = "PLATFORM_TEST_DRIVER",
};
HDF_INIT(g_platformTestEntry);
