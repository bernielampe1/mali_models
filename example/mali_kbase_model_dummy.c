#ifndef KBASE_MODEL_DUMMY_H_
#define KBASE_MODEL_DUMMY_H_

#include<mali_kbase.h>

#include<gpu/mali_kbase_gpu_regmap.h>
#include<gpu/mali_kbase_gpu_id.h>


#define REGISTER_SPACE_SIZE_DTS 0x5000
static u32 dummy_regs[REGISTER_SPACE_SIZE_DTS];

void clear_gpu(void) {
    int i = 0;
    while(i < REGISTER_SPACE_SIZE_DTS) {
        dummy_regs[i++] = 0;
    }
}

// Register mapping comes from mali_midg_regmap.h and mali_midg_regmap_jm.h
int kbase_gpu_device_create(struct kbase_device *kbdev) {
    clear_gpu();

    // gpu id is used to find hw issues and workaround functions
    // look as mali_kbase_hw.c: kbase_hw_get_issues_for_new_id() for hardcoded arch/product/verions
    dummy_regs[GPU_CONTROL_REG(GPU_ID)] = GPU_ID2_MAKE(6, 0, 0, 0, 0, 1, 0);

    dummy_regs[GPU_CONTROL_REG(L2_FEATURES)] =
        (0x07 << 24) |  // lg2 ext bus width
        (0x13 << 16) |  // lg2 cache size
        (0x02 << 8) |   // lg2 associativity
        (0x06);         // lg2 line size

    dummy_regs[GPU_CONTROL_REG(TILER_FEATURES)] =
        (0x8 << 8) |    // Maximum no active hierarchy levels
        0x09;           // lg2 bin size

    /* Coherent core group, but incoherent supergroup. 1 L2 slice. */
    dummy_regs[GPU_CONTROL_REG(MEM_FEATURES)] = 0x1;

    dummy_regs[GPU_CONTROL_REG(MMU_FEATURES)] = 0x2830;
    dummy_regs[GPU_CONTROL_REG(AS_PRESENT)] = 0xff;
    dummy_regs[GPU_CONTROL_REG(JS_PRESENT)] = 0x7;
    dummy_regs[GPU_CONTROL_REG(JS0_FEATURES)] = 0x20e;
    dummy_regs[GPU_CONTROL_REG(JS1_FEATURES)] = 0x1fe;
    dummy_regs[GPU_CONTROL_REG(JS2_FEATURES)] = 0x7e;

    dummy_regs[GPU_CONTROL_REG(TEXTURE_FEATURES_0)] = 0x00fe001e;
    dummy_regs[GPU_CONTROL_REG(TEXTURE_FEATURES_1)] = 0xffff;
    dummy_regs[GPU_CONTROL_REG(TEXTURE_FEATURES_2)] = 0x9f81ffff;

    dummy_regs[GPU_CONTROL_REG(THREAD_MAX_THREADS)] = 0x100;
    dummy_regs[GPU_CONTROL_REG(THREAD_MAX_WORKGROUP_SIZE)] = 0x100;
    dummy_regs[GPU_CONTROL_REG(THREAD_MAX_BARRIER_SIZE)] = 0x100;
    dummy_regs[GPU_CONTROL_REG(THREAD_FEATURES)] = 0x0a040400;

    dummy_regs[GPU_CONTROL_REG(SHADER_PRESENT_LO)] = 0xf;
    dummy_regs[GPU_CONTROL_REG(TILER_PRESENT_LO)] = 0x1;
    dummy_regs[GPU_CONTROL_REG(L2_PRESENT_LO)] = 0x1;

    return 0;
}

int gpu_device_create(struct kbase_device *kbdev) {
    return kbase_gpu_device_create(kbdev);
}

void kbase_gpu_device_destroy(struct kbase_device *kbdex) {
    clear_gpu();
    return;
}

void gpu_device_destroy(struct kbase_device *kbdex) {
    clear_gpu();
    return;
}

unsigned int kbase_reg_read(struct kbase_device *kbdev, u32 offset)
{
    if (offset == GPU_CONTROL_REG(GPU_IRQ_STATUS)) {
        return dummy_regs[offset] & dummy_regs[GPU_CONTROL_REG(GPU_IRQ_MASK)];
    }
    else if (offset == JOB_CONTROL_REG(JOB_IRQ_STATUS)) {
        return dummy_regs[offset] & dummy_regs[JOB_CONTROL_REG(JOB_IRQ_MASK)];
    }
    else if (offset == MMU_REG(MMU_IRQ_STATUS)) {
        return dummy_regs[offset] & dummy_regs[MMU_REG(MMU_IRQ_MASK)];
    }

    return dummy_regs[offset];
}

void kbase_reg_write(struct kbase_device *kbdev, u32 offset, u32 value) {
    dummy_regs[offset] = value;

    // just mark all jobs done successfully all the time
    dummy_regs[JOB_SLOT_REG(0, JS_STATUS)] = 0;
    dummy_regs[JOB_SLOT_REG(1, JS_STATUS)] = 0;
    dummy_regs[JOB_SLOT_REG(2, JS_STATUS)] = 0;
    dummy_regs[JOB_SLOT_REG(3, JS_STATUS)] = 0;
    dummy_regs[JOB_SLOT_REG(4, JS_STATUS)] = 0;
    dummy_regs[JOB_SLOT_REG(5, JS_STATUS)] = 0;
    dummy_regs[JOB_SLOT_REG(6, JS_STATUS)] = 0;
    dummy_regs[JOB_SLOT_REG(7, JS_STATUS)] = 0;
    dummy_regs[JOB_SLOT_REG(8, JS_STATUS)] = 0;
    dummy_regs[JOB_SLOT_REG(9, JS_STATUS)] = 0;
    dummy_regs[JOB_SLOT_REG(10, JS_STATUS)] = 0;
    dummy_regs[JOB_SLOT_REG(11, JS_STATUS)] = 0;
    dummy_regs[JOB_SLOT_REG(12, JS_STATUS)] = 0;
    dummy_regs[JOB_SLOT_REG(13, JS_STATUS)] = 0;
    dummy_regs[JOB_SLOT_REG(14, JS_STATUS)] = 0;
    dummy_regs[JOB_SLOT_REG(15, JS_STATUS)] = 0;
}

bool kbase_is_gpu_removed(struct kbase_device *kbdev)
{
    return 0;
}

void gpu_model_set_dummy_prfcnt_sample(unsigned int *data, unsigned int size)
{
    return;
}

void gpu_model_set_dummy_prfcnt_base_cpu(void *p)
{
    return;
} 

void kbase_synchronize_irqs(struct kbase_device *kbdev)
{
    return;
}

int kbase_install_interrupts(struct kbase_device *kbdev)
{
    return 0;
}

void kbase_release_interrupts(struct kbase_device *kbdev)
{
    return;
}

#endif /* KBASE_MODEL_DUMMY_H_ */
