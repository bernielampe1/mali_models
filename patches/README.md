These are patches for bifrost modules which can be download from https://developer.arm.com/downloads/-/mali-drivers/bifrost-kernel.

For example:

```console
$ wget https://developer.arm.com/-/media/Files/downloads/mali-drivers/kernel/mali-bifrost-gpu/BX304L01B-SW-99002-r29p0-01eac0.tar > /dev/null 2>&1
$ tar xvf BX304L01B-SW-99002-r29p0-01eac0.tar
$ cd driver
$ patch -p2 < ../v_r29.patch
patching file product/kernel/drivers/gpu/arm/midgard/Kbuild
patching file product/kernel/drivers/gpu/arm/midgard/Makefile
patching file product/kernel/drivers/gpu/arm/midgard/backend/gpu/Kbuild
patching file product/kernel/drivers/gpu/arm/midgard/backend/gpu/mali_kbase_model_dummy.c
patching file product/kernel/drivers/gpu/arm/midgard/backend/gpu/mali_kbase_model_dummy.h
patching file product/kernel/drivers/gpu/arm/midgard/backend/gpu/mali_kbase_pm_backend.c
patching file product/kernel/drivers/gpu/arm/midgard/backend/gpu/mali_kbase_pm_driver.c
patching file product/kernel/drivers/gpu/arm/midgard/mali_kbase_model_linux.h
patching file product/kernel/drivers/gpu/arm/midgard/platform/devicetree/mali_kbase_config_devicetree.c
```
