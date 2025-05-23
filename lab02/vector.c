/* Include the system headers we need */
#include <stdlib.h>
#include <stdio.h>

/* Include our header */
#include "vector.h"

/* Define what our struct is */
struct vector_t {
    size_t size;
    int *data;
};

/* Utility function to handle allocation failures. In this
   case we print a message and exit. */
static void allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}

/* Bad example of how to create a new vector */
vector_t *bad_vector_new() {
    /* Create the vector and a pointer to it */
    vector_t *retval, v;
    retval = &v;

    /* Initialize attributes */
    retval->size = 1;
    retval->data = malloc(sizeof(int));
    if (retval->data == NULL) {
        allocation_failed();
    }

    retval->data[0] = 0;
    return retval;

    /*
     *retvalv 是一个局部变量，它在 bad_vector_new() 函数栈上分配。
     *retval = &v; 是把 v 的地址赋给 retval。最后你 return retval;，也就是返回了 一个指向函数局部变量的指针。
     *然而，一旦这个函数执行完毕，v 所在的内存会被释放（或覆盖），此时 retval 指向的内容就不再有效。
   */
}

/* Another suboptimal way of creating a vector */
vector_t also_bad_vector_new()
{
    /* Create the vector */
    vector_t v;

    /* Initialize attributes */
    v.size = 1;
    v.data = malloc(sizeof(int));
    if (v.data == NULL) {
        allocation_failed();
    }
    v.data[0] = 0;
    return v;
    /*
     *效率低下
     */
}

/* 创建一个大小（长度）为 1 的新向量
并将其单个分量设置为零……
正确的方法 */
vector_t *vector_new() {
    /* 声明此函数将返回什么 */
    vector_t *retval;

    /* 首先，我们需要在堆上为结构体分配内存 */
    retval = malloc(sizeof(*retval));

    /* 检查我们的返回值以确保我们获得了内存 */
    if (retval == NULL) {
        allocation_failed();
    }

    /* 现在我们需要初始化数据。
    由于 retval->data 应该能够动态增长，
    你需要做什么？ */
    retval->size =  1;
    retval->data = malloc(sizeof(int) * retval -> size);

    /* 检查向量的数据属性，以确保我们有内存 */
    if (retval->data == NULL) {
        free(retval);				//为什么这行是必要的?  会导致内存泄露
        allocation_failed();
    }

    /* 通过将单个组件设置为零来完成初始化 */
    retval->data[0] = 0;

    /* 返回值 */
    return retval;
}

/* 返回向量指定位置/分量“loc”处的值 */
int vector_get(vector_t *v, size_t loc) {

    /* 如果我们传递了一个向量的空指针，则发出警告并退出。 */
    if(v == NULL) {
        fprintf(stderr, "vector_get: passed a NULL vector.\n");
        abort();
    }

    /* 如果请求的位置高于我们分配的位置，则返回 0。
     * 否则，返回传递的位置中的内容。
     */
    if (loc < v->size) {
        return v->data[loc];
    } else {
        return 0;
    }
}

/* 释放为传递的向量分配的内存。
请记住，您需要释放所有已分配的内存。 */
void vector_delete(vector_t *v) {
    free(v->data);
    free(v);
}

/* 在向量中设置一个值。如果额外内存分配失败，则调用allocation_failed()。 */
void vector_set(vector_t *v, size_t loc, int value) {
    /* 如果位置大于我们分配的大小，该怎么办？请记住，未设置的位置应该包含 0 值。
     */

    if (loc >= v->size) {
        v->data = (int*)realloc(v->data, sizeof(int)*(loc+1));
        if (v->data == NULL) {
            allocation_failed();
        }
        for (size_t i = v->size; i < loc + 1; i++){
            v->data[i] = 0;
        }
        v->size = loc + 1;
    }
    v->data[loc] = value;

}