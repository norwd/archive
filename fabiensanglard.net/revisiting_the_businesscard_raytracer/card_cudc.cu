#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sysinfoapi.h>

#define DIM 512
#define BPP 3

#define INSTRINSIC 1
#if defined(INSTRINSIC)
#define POW __powf
#define CEIL ceilf
#define RSQRT(x) (rsqrtf(x))
#define SQRT(x) (sqrtf(x))
#define DIVIDE(x,y) __fdividef((x),(y))
#else
#define POW pow
#define CEIL ceil
#define RSQRT(x) (1/sqrt(x))
#define SQRT(x) (sqrt((x)))
#define DIVIDE(x,y) ((x)/(y))
#endif

struct v {
  float x, y, z;
 __device__  v operator+(v r) { return v(x + r.x, y + r.y, z + r.z); }
 __device__  v operator*(float r) { return v(x * r, y * r, z * r); }
 __device__  float operator%(v r) {return x * r.x + y * r.y + z * r.z;}
 __device__  v() {}
 __device__  v operator^(v r) {
    return v(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.x);
  }
  __device__ v(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
  }
  __device__ v operator!() { return *this * RSQRT(*this % *this); }
};

__device__ int G[] = {247570, 280596, 280600, 249748, 18578, 18577, 231184, 16, 16};

__shared__ int g_seed;
__device__ float R() {
  g_seed = (214013*g_seed+2531011);
      return DIVIDE((g_seed >> 16)&0x7FFF,66635.0f);
}

//The intersection test for line [o,v].
// Return 2 if a hit was found (and also return distance t and bouncing ray n).
// Return 0 if no hit was found but ray goes upward
// Return 1 if no hit was found but ray goes downward
__device__ int TraceRay(v origin, v destination, float &t, v &normal) {
  t = 1e9;
  int m = 0;
  float p = DIVIDE(-origin.z, destination.z);
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
          float s = -b - SQRT(q);
            //It does, compute the distance camera-sphere
          if (s < t && s > 0.01f) {
              t = s;
              normal = !(p + destination * t);
              m = 2;
          }
        }
      }
  return m;
}

__device__ v Sample(v origin, v destination) {
  float attenuation = 1.0f;
  v pixel_color(0,0,0);
  for (int r=0 ; r < 4 ; r++, attenuation /= 2) {
    float t;
    v normal;

    int match = TraceRay(origin, destination, t, normal);
    if (!match) {
        //No sphere found and the ray goes upward: Generate a sky color
        return  pixel_color + v(0.7f, 0.6f, 1.0f) * POW(1 - destination.z, 4) * attenuation;
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


    if (match & 1) {
      //No sphere was hit and the ray was going downward: Generate a floor color
      intersection = intersection * .2f;
      v c = ((int)(CEIL(intersection.x) + CEIL(intersection.y)) & 1 ?
                  v(3, 1, 1) :
                  v(3, 3, 3)) * (lamb_f * .2f + .1f);
      return pixel_color + c * attenuation;
    }

    float color = POW(light_dir % half_vec * (lamb_f > 0), 99);
    pixel_color = pixel_color + v(color, color, color) * attenuation;
    //m == 2 A sphere was hit. Cast an ray bouncing from the sphere surface.
    //Attenuate color by 50% since it is bouncing (* .5)
    origin = intersection;
    destination = half_vec;
  }
  return pixel_color;
}


__global__ void GetColor(unsigned char *img) {
  int x = blockIdx.x;
  int y = threadIdx.x;
v cam_dir = !v(-6, -16, 0);
v cam_up = !(v(0, 0, 1) ^ cam_dir) * .002f;
v cam_right = !(cam_dir ^ cam_up) * .002f;
v eye_offset = (cam_up + cam_right) * -256 + cam_dir;
  v color(13, 13, 13);
      for (int r = 64; r--;) {
        v delta = cam_up * (R() - .5) * 99.0f + cam_right * (R() - 0.5f) * 99.0f;
        color = Sample(v(17, 16, 8) + delta,
                !(delta * -1 + (cam_up * (R() + x) + cam_right * (y + R()) + eye_offset) * 16.0f)) * 3.5f + color;
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
  DWORD start_time = GetTickCount();

  // CPUBitmap bitmap( DIM, DIM );
  char* bitmap = new char[DIM * DIM * BPP];
  unsigned char *dev_bitmap;

  // cudaMalloc( (void**)&dev_bitmap, bitmap.image_size() );
  cudaMalloc( (void**)&dev_bitmap, (DIM * DIM * BPP) );
  gpuErrchk( cudaPeekAtLastError() );

  GetColor<<<DIM,DIM>>>(dev_bitmap); 
  gpuErrchk( cudaDeviceSynchronize() );

  // cudaMemcpy( bitmap.get_ptr(), dev_bitmap, bitmap.image_size(), cudaMemcpyDeviceToHost );
  cudaMemcpy( bitmap, dev_bitmap, (DIM * DIM * BPP), cudaMemcpyDeviceToHost );
  gpuErrchk( cudaPeekAtLastError() );
 
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
