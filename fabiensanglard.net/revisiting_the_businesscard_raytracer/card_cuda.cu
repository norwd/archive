#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sysinfoapi.h>
// #include "cpu_bitmap.h"

#define DIM 512
#define BPP 3

struct v {
  float x, y, z;
 __device__  v operator+(v r) { return v(x + r.x, y + r.y, z + r.z); }
 __device__  v operator*(float r) { return v(x * r, y * r, z * r); }
 __device__  float operator%(v r) { return x * r.x + y * r.y + z * r.z; }
 __device__  v() {}
 __device__  v operator^(v r) {
    return v(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.x);
  }
  __device__ v(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
  }
  __device__ v operator!() { return *this * (1 / sqrt(*this % *this)); }
};

__device__ int G[] = {247570, 280596, 280600, 249748, 18578, 18577, 231184, 16, 16};

__device__ int g_seed=1;
__device__ float R() {
  g_seed = (214013*g_seed+2531011);
      return ((g_seed>>16)&0x7FFF) / (float)66635;
}

//The intersection test for line [o,v].
// Return 2 if a hit was found (and also return distance t and bouncing ray n).
// Return 0 if no hit was found but ray goes upward
// Return 1 if no hit was found but ray goes downward
__device__ int TraceRay(v origin, v destination, float &t, v &normal) {
  t = 1e9;
  int m = 0;
  float p = -origin.z / destination.z;
  if (.01 < p) {
      t = p;
      normal = v(0, 0, 1);
      m = 1;
  }

  for (int k = 19; k--;)
    for (int j = 9; j--;)
      if (G[j] & 1 << k) {
        v p = origin + v(-k, 0, -j - 4);
        float b = p % destination;
        float c = p % p - 1;
        float q = b * b - c;

          //Does the ray hit the sphere ?
        if (q > 0) {
          float s = -b - sqrt(q);
            //It does, compute the distance camera-sphere
          if (s < t && s > .01) {
              t = s;
              normal = !(p + destination * t);
              m = 2;
          }
        }
      }
  return m;
}

__device__ v Sample(v origin, v destination, int r) {
  float t;
  v normal;
  if (r > 4) {
    return v();
  }
  int match = TraceRay(origin, destination, t, normal);
  if (!match) {
      //No sphere found and the ray goes upward: Generate a sky color
      return v(.7, .6, 1) * pow(1 - destination.z, 4);
  }

  //A sphere was maybe hit.
  v intersection = origin + destination * t;
  v light_dir = !(v(9 + R(), 9 + R(), 16) + intersection * -1);
  v half_vec = destination + normal * (normal % destination * -2);

  //Calculated the lambertian factor
  float lamb_f = light_dir % normal;

  //Calculate illumination factor (lambertian coefficient > 0 or in shadow)?
  if (lamb_f < 0 || TraceRay(intersection, light_dir, t, normal)) {
      lamb_f = 0;
  }

  float color = pow(light_dir % half_vec * (lamb_f > 0), 99);

  if (match & 1) {
    //No sphere was hit and the ray was going downward: Generate a floor color
    intersection = intersection * .2;
    return ((int)(ceil(intersection.x) + ceil(intersection.y)) & 1 ?
                  v(3, 1, 1) :
                  v(3, 3, 3)) * (lamb_f * .2 + .1);
  }

  //m == 2 A sphere was hit. Cast an ray bouncing from the sphere surface.
  //Attenuate color by 50% since it is bouncing (* .5)
  return v(color, color, color) + Sample(intersection, half_vec, r+1) * .5;
}


__global__ void GetColor(unsigned char *img) {
  int x = blockIdx.x;
  int y = threadIdx.x;
v cam_dir = !v(-6, -16, 0);
v cam_up = !(v(0, 0, 1) ^ cam_dir) * .002;
v cam_right = !(cam_dir ^ cam_up) * .002;
v eye_offset = (cam_up + cam_right) * -256 + cam_dir;
  v color(13, 13, 13);
      for (int r = 64; r--;) {
        v delta = cam_up * (R() - .5) * 99 + cam_right * (R() - .5) * 99;
        color = Sample(v(17, 16, 8) + delta,
                !(delta * -1 + (cam_up * (R() + x) + cam_right * (y + R()) + eye_offset) * 16), 0) * 3.5 + color;
      }
      img[DIM * y * BPP + x * BPP + 0] = color.x;
      img[DIM * y * BPP + x * BPP + 1] = color.y;
      img[DIM * y * BPP + x * BPP + 2] = color.z;
}


#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true)
{
   if (code != cudaSuccess) 
   {
      fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
      if (abort) exit(code);
   }
}

int main() {
  // printf("Starting\n");
  DWORD start_time = GetTickCount();

  // CPUBitmap bitmap( DIM, DIM );
  char* bitmap = new char[DIM * DIM * BPP];
  unsigned char *dev_bitmap;

  // cudaMalloc( (void**)&dev_bitmap, bitmap.image_size() );
  cudaMalloc( (void**)&dev_bitmap, (DIM * DIM * BPP) );
  // gpuErrchk( cudaPeekAtLastError() );

  GetColor<<<DIM,DIM>>>(dev_bitmap); 
  // gpuErrchk( cudaDeviceSynchronize() );

  // cudaMemcpy( bitmap.get_ptr(), dev_bitmap, bitmap.image_size(), cudaMemcpyDeviceToHost );
  cudaMemcpy( bitmap, dev_bitmap, (DIM * DIM * BPP), cudaMemcpyDeviceToHost );
  // gpuErrchk( cudaPeekAtLastError() );
 
  DWORD elapsed_ms = GetTickCount() - start_time;
  fprintf(stderr, "Time: %dms\n", elapsed_ms);

  printf("P6 512 512 255 ");
  char* c = bitmap;
  for (int y = DIM; y--;) {
    for (int x = DIM; x--;) {
      c = &bitmap[y * DIM * BPP  + x * BPP];
      printf("%c%c%c", c[0], c[1], c[2]);
      c += BPP;
    }
  }

  delete bitmap;
  return EXIT_SUCCESS;
}
