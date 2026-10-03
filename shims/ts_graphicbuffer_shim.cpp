// SPDX-License-Identifier: Apache-2.0

#include <new>
#include <ui/GraphicBuffer.h>

static_assert(sizeof(android::GraphicBuffer) >= 0x100);

extern "C" __attribute__((visibility("default")))
void* miui_ts_operator_new(std::size_t size) {
    // The stock TS plugin allocates 0x100 bytes for GraphicBuffer.
    if (size == 0x100) {
        size = sizeof(android::GraphicBuffer);
    }
    return ::operator new(size);
}
