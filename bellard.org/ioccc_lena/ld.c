/* image decoder */
#ifndef TINY
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define for_loop(i, n) for(int i=0;i<n;i++)
#endif

#include "img.h"

#define IMG_SIZE_MAX_LOG2 20

#define DCT_BITS 10
#define DCT_ONE  1024
#define DCT_SIZE_LOG2_MAX 5
#define DCT_SIZE_MAX 32 /* (1 << DCT_SIZE_LOG2_MAX) */
#define DCT_SIZE_MAX4 128 /* 4 * DCT_SIZE_MAX */
#define DCT_SIZE_MAX_SQ2 2048 /* 2 * DCT_SIZE_MAX^2 */

#define FREQ_MAX 63
#define SYM_COUNT 1968

//#define DUMP_GET_BIT

int img_data[3][1<<IMG_SIZE_MAX_LOG2], buf1[DCT_SIZE_MAX_SQ2], a_ctx[ACTX_COUNT2], a_low, a_range = 1, stride, sym_count, y_scale, c_scale, dct_coef[DCT_SIZE_MAX4];

get_bit(c)
{
    int v, *p = a_ctx + c * 2, b = *p + 1, s = b + p[1] + 1;
    if (a_range < sym_count) {
        a_range *= sym_count;
        a_low *= sym_count;
        if (sym_count >> 9) {
            if (v = *inp) {
                /* char conversion */
                a_low += v - 1 - (v > 10) - (v > 13) - (v > 34) - (v > 92) << 4;
                /* space conversion */
                v = *++inp;
                inp++;
                a_low += v < 33 ?
                    (v ^ 8) * 2 % 5 :
                    (v ^ 6) % 3 * 4 + (*inp++ ^ 8) * 2 % 5 + 4;
            }
        } else {
            v = getchar();
            a_low += v < 0 ? 0 : v;
        }
    }
    /* 0 < range0 < a_range */
    v = a_range * b / s;
#ifdef DUMP_GET_BIT
    {
        static int count;
        printf("%d: c=%d range=%d b=%d range0=%d low=%d\n", count++, c, a_range, a_low >= v, v, a_low);
    }
#endif
    if (b = a_low >= v) {
        a_low -= v;
        a_range -= v;
    } else
        a_range = v;
    p[b]++;
    if (s > FREQ_MAX) {
        *p /= 2;
        p[1] /= 2;
    }
    return b;
}

/* positive number, Golomb encoding */
get_ue(c)
{
    int i = 0, v = 1;
    while (!get_bit(c + i))
        i++;
    while (i--)
        v += v + get_bit(ACTX_VDATA);
    return v - 1;
}

idct(dst, dst_stride, src, src_stride, stride2, n, rshift)
int *dst, *src;
{
    for_loop(l, n)
        for_loop(i, n) {
            int sum = 1 << rshift - 1;
            for_loop(j, n)
                sum += src[j * src_stride + l * stride2] * dct_coef[(2 * i + 1) * j * DCT_SIZE_MAX / n % DCT_SIZE_MAX4];
            dst[i * dst_stride + l * stride2] = sum >> rshift;
        }
}

decode_rec(x, y, w_log2)
{
    int dc, b, *out, w = 1 << w_log2, n = w * w, c_idx1, pred_idx, swap, x1, delta, frac;
    
    //    printf("decode_rec: x=%d y=%d w=%d\n", x, y, 1 << w_log2);
    if (w_log2 > DCT_SIZE_LOG2_MAX ||
        w_log2 > 2 && get_bit(w_log2 - 3)) {
        w /= 2;
        for_loop(i, 4)
            decode_rec(x + i % 2 * w, y + i / 2 * w, w_log2 - 1);
    } else {
        pred_idx = get_ue(ACTX_IPRED);
        for_loop(c_idx, 3) {
            out = img_data[c_idx] + y * stride + x;
            c_idx1 = c_idx > 0;
            
            /* decode coefs */
            for_loop(i, n)
                buf1[i] = 0;
            for_loop(i, n) {
                if (get_bit(ACTX_EOB2 + w_log2 * 2 + c_idx1))
                    break;
                i += get_ue(ACTX_LEN + c_idx1 * ACTX_UE_LEN);
                b = 1 - 2 * get_bit(ACTX_SIGN);
                buf1[i] = b *
                    (get_ue(ACTX_LEVEL + (c_idx1 + (i < n / 8) * 2) * ACTX_UE_LEN) + 1) * (c_idx ? c_scale : y_scale);
            }
            
            /* DC prediction */
            if (!pred_idx) {
                dc = 0;
                for_loop(i, w) {
                    dc += y ? out[- stride + i] : 0;
                    dc += x ? out[i * stride - 1] : 0;
                }
                *buf1 += x && y ? dc / 2 : dc;
            }

            /* horizontal */
            idct(buf1 + n, 1, buf1, 1, w, w, DCT_BITS);
            /* vertical */
            idct(out, stride, buf1 + n, w, 1, w, DCT_BITS + w_log2);

            if (pred_idx) {
                /* directional prediction */
                swap = pred_idx < 17;
                delta = swap ? 9 - pred_idx : pred_idx - 25;
                for_loop(i, w)
                for_loop(j, w) {
                    for_loop(k, 2) {
                        x1 = i * delta + delta;
                        frac = x1 & 7;
                        x1 = (x1 >> 3) + j + k;
                        if (b = x1 < 0)
                            x1 = (x1 * 8 + delta / 2) / delta - 2;
                        x1 = x1 < w ? x1 : w - 1;
                        buf1[k] = b ^ swap ?
                            out[x1 * stride - 1] : out[-stride + x1];
                    }
                    out[swap ? j * stride + i : i * stride + j] +=
                        *buf1 * (8 - frac) + buf1[1] * frac + 4 >> 3;
                }
            }
        }
    }
}

put_val(v)
{
    putchar(v < 0 ? 0 : v > 255 ? 255 : v);
}

main(t)
{
    int y, cg, co, w_log2, h;

    sym_count = t > 1 ? 256 : SYM_COUNT;
#if 0
    /* alternate (but longer) all integer version */
    {
        int a, b, c;
        a = 0;
        b = 74509276;
        for_loop(i, 128) {
            dct_coef[i + 96 & 127] = (a >> 19) + 1 >> 1;
            c = b;
            b = (2144896910LL * b >> 30) - a;
            a = c;
        }
        *dct_coef = 1024;
    }
#else
    for_loop(i, DCT_SIZE_MAX4)
        dct_coef[i] = lrint(cos(asin(1) / DCT_SIZE_MAX * i) * sqrt(2 - !i) * DCT_ONE);
#endif
    w_log2 = get_ue(ACTX_LEN);
    stride = 1 << w_log2;
    h = stride - get_ue(ACTX_LEN);
    y_scale = get_ue(ACTX_LEN);
    c_scale = get_ue(ACTX_LEN);

    decode_rec(0, 0, w_log2);

    /* output */
    printf("P6 %d %d 255 ", stride, h);
    for_loop(i, h * stride) {
        y = img_data[0][i];
        cg = img_data[1][i];
        co = img_data[2][i];
        t = y - cg;
        put_val(t + co);
        put_val(y + cg);
        put_val(t - co);
    }
    return 0;
}
