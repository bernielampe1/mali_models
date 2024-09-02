#ifndef __MALI_KBASE_MODEL_DUMMY_H__
#define __MALI_KBASE_MODEL_DUMMY_H__

#include<mali_kbase.h>

#define KBASE_DUMMY_MODEL_MAX_MEMSYS_BLOCKS 32
#define KBASE_DUMMY_MODEL_MAX_SHADER_CORES 1

void gpu_model_set_dummy_prfcnt_base_cpu(void *dump_va);
int kbase_gpu_device_create(struct kbase_device *kbdev);
void kbase_gpu_device_destroy(struct kbase_device *kbdex);
int gpu_device_create(struct kbase_device *kbdev);
void gpu_device_destroy(struct kbase_device *kbdex);
void gpu_model_set_dummy_prfcnt_sample(unsigned int *data, unsigned int size);

#endif
