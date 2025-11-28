// SPDX-License-Identifier: MIT
// Adapted from hifiasm (MIT-licensed). Original authors: Haoyu Cheng, Heng Li, et al.
// See LICENSE in the project root for the full license text.

#ifndef KTHREAD_H
#define KTHREAD_H

#ifdef __cplusplus
extern "C" {
#endif

void kt_for(int n_threads, void (*func)(void*,long,int), void *data, long n);
void kt_pipeline(int n_threads, void *(*func)(void*, int, void*), void *shared_data, int n_steps);

#ifdef __cplusplus
}
#endif

#endif
