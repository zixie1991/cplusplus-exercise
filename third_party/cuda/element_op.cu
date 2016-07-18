#include <stdio.h>
#include <stdlib.h>

#include <cuda.h>
#include <cuda_runtime.h>
#include <driver_types.h>

#include <iostream>
#include <string>

#include "timer.h"

using namespace std;
using namespace timer;

class ElementOp {
  public:
    virtual ~ElementOp() {}
    virtual void Calc(int n, const float* x, const float* y, float* z) {}
};

class ElementContext {
  public:
    ElementContext(ElementOp* op):
      op_(op)
    {
    }

    void Calc(int n, const float* x, const float* y, float* z) {
      op_->Calc(n, x, y, z);
    }

  private:
    ElementOp* op_;
};

__global__ void AddKernelPerThread(const float* x, const float* y, float* z) {
  int idx = threadIdx.x;
  z[idx] = x[idx] + y[idx];
}

__global__ void AddKernelPerBlock(const float* x, const float* y, float* z) {
  int idx = blockIdx.x;
  z[idx] = x[idx] + y[idx];
}

class ElementAddOpWithThread: public ElementOp {
  public:
    ~ElementAddOpWithThread() {}

    void Calc(int n, const float* x, const float* y, float* z) {
      // allocate GPU buffers
      float* cuda_x = NULL;
      float* cuda_y = NULL;
      float* cuda_z = NULL;
      cudaMalloc((void**)&cuda_x, sizeof(float) * n);
      cudaMalloc((void**)&cuda_y, sizeof(float) * n);
      cudaMalloc((void**)&cuda_z, sizeof(float) * n);

      // copy host memory to GPU buffers
      cudaMemcpy(cuda_x, x, sizeof(float) * n, cudaMemcpyHostToDevice);
      cudaMemcpy(cuda_y, y, sizeof(float) * n, cudaMemcpyHostToDevice);

      AddKernelPerThread<<<1, n>>>(cuda_x, cuda_y, cuda_z);

      // cudaThreadSynchronize waits for the kernel to finish, and returns  
      // any errors encountered during the launch.  
      cudaThreadSynchronize();

      // copy GPU buffers to host memory
      cudaMemcpy(z, cuda_z, sizeof(float) * n, cudaMemcpyDeviceToHost);

      cudaFree(cuda_x);
      cudaFree(cuda_y);
      cudaFree(cuda_z);
    }
};


class ElementAddOpWithBlock: public ElementOp {
  public:
    ~ElementAddOpWithBlock() {}

    void Calc(int n, const float* x, const float* y, float* z) {
      // allocate GPU buffers
      float* cuda_x = NULL;
      float* cuda_y = NULL;
      float* cuda_z = NULL;
      cudaMalloc((void**)&cuda_x, sizeof(float) * n);
      cudaMalloc((void**)&cuda_y, sizeof(float) * n);
      cudaMalloc((void**)&cuda_z, sizeof(float) * n);

      // copy host memory to GPU buffers
      cudaMemcpy(cuda_x, x, sizeof(float) * n, cudaMemcpyHostToDevice);
      cudaMemcpy(cuda_y, y, sizeof(float) * n, cudaMemcpyHostToDevice);

      AddKernelPerBlock<<<n, 1>>>(cuda_x, cuda_y, cuda_z);

      cudaStreamSynchronize(0);
      // cudaThreadSynchronize waits for the kernel to finish, and returns  
      // any errors encountered during the launch.  
      cudaThreadSynchronize();

      // copy GPU buffers to host memory
      cudaMemcpy(z, cuda_z, sizeof(float) * n, cudaMemcpyDeviceToHost);

      cudaFree(cuda_x);
      cudaFree(cuda_y);
      cudaFree(cuda_z);
    }
};

class ElementAddOpWithStream: public ElementOp {
  public:
    ~ElementAddOpWithStream() {}

    void Calc(int n, const float* x, const float* y, float* z) {
      // allocate GPU buffers
      float* cuda_x = NULL;
      float* cuda_y = NULL;
      float* cuda_z = NULL;
      cudaMalloc((void**)&cuda_x, sizeof(float) * n);
      cudaMalloc((void**)&cuda_y, sizeof(float) * n);
      cudaMalloc((void**)&cuda_z, sizeof(float) * n);

      // copy host memory to GPU buffers
      cudaMemcpy(cuda_x, x, sizeof(float) * n, cudaMemcpyHostToDevice);
      cudaMemcpy(cuda_y, y, sizeof(float) * n, cudaMemcpyHostToDevice);

      // stream
      const int num_streams = 5;
      cudaStream_t stream[num_streams];
      for (int i = 0; i < num_streams; i++) {
        cudaStreamCreate(&stream[i]);
      }

      for (int i = 0; i < num_streams; i++) {
        AddKernelPerBlock<<<1, 1, 0, stream[i]>>>(x + i, y + i, z + i);
      }

      cudaDeviceSynchronize();
      // cudaThreadSynchronize waits for the kernel to finish, and returns  
      // any errors encountered during the launch.  
      cudaThreadSynchronize();

      // copy GPU buffers to host memory
      cudaMemcpy(z, cuda_z, sizeof(float) * n, cudaMemcpyDeviceToHost);

      cudaFree(cuda_x);
      cudaFree(cuda_y);
      cudaFree(cuda_z);
    }
};

void Print(const float* a, int n) {
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

class GPUAutoTimer {
  public:
    GPUAutoTimer(string str=""):
      str_(str)
    {
      cudaEventCreate(&start_); // 创建事件
      cudaEventCreate(&stop_);
      cudaEventRecord(start_, 0); // 记录开始
    }

    ~GPUAutoTimer() {
      cudaEventRecord(stop_, 0); // 记录结束
      cudaEventSynchronize(stop_); // 事件同步，等待结束事件之前的设备操作均已完成
      float elapsed_time;
      cudaEventElapsedTime(&elapsed_time, start_, stop_); // 计算两个事件之间的时长(单位:ms)
      fprintf(stderr, "%s use %.3fms\n", str_.c_str(), elapsed_time);
      cudaEventDestroy(start_);
      cudaEventDestroy(stop_);
    }

  private:
    string str_;
    cudaEvent_t start_; // 事件对象
    cudaEvent_t stop_;
};

int main() {
  const int n = 1024;
  float a[n];
  float b[n];
  float c[n];

  for (int i = 0; i < n; i++) {
    a[i] = random() % 10;
    b[i] = random() % 10;
  }
  
  int count;
  cudaGetDeviceCount(&count);
  cudaSetDevice(0);

  {
  GPUAutoTimer gpu_auto_timer("GPU");
  AutoTimer auto_timer("CPU");
  ElementAddOpWithThread elt_op_add_with_thread;
  ElementContext elt_context1(&elt_op_add_with_thread);
  elt_context1.Calc(n, a, b, c);
  }

  {
  GPUAutoTimer gpu_auto_timer("GPU");
  AutoTimer auto_timer("CPU");
  ElementAddOpWithBlock elt_op_add_with_block;
  ElementContext elt_context2(&elt_op_add_with_block);
  elt_context2.Calc(n, a, b, c);
  }

  {
  GPUAutoTimer gpu_auto_timer("GPU");
  AutoTimer auto_timer("CPU");
  ElementAddOpWithStream elt_op_add_with_stream;
  ElementContext elt_context3(&elt_op_add_with_stream);
  elt_context3.Calc(n, a, b, c);
  }

  // cudaThreadExit must be called before exiting in order for profiling and  
  // tracing tools such as Nsight and Visual Profiler to show complete traces.  
  cudaThreadExit();

  return 0;
}
