#ifndef _BASE_MODEL_LINUX_H_
#define _BASE_MODEL_LINUX_H_

int kbase_gpu_device_create(struct kbase_device *kbdev);
void kbase_gpu_device_destroy(struct kbase_device *kbdex);
int gpu_device_create(struct kbase_device *kbdev);
void gpu_device_destroy(struct kbase_device *kbdex);

#endif
