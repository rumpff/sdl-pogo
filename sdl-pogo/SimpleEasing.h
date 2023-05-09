#pragma once

#include <cmath>
#include <SDL_stdinc.h>

static class Easing
{
public:
    static float easeInBack(float time, float start, float change, float duration)
    {
        float s = 1.70158f; // feel free to modify this value

        time /= duration;
        return change * (time)*time * ((s + 1) * time - s) + start;
    }
    static float easeInBounce(float time, float start, float change, float duration)
    {
        return change - easeOutBounce(duration - time, 0, change, duration) + start;
    }
    static float easeInCirc(float time, float start, float change, float duration)
    {
        time /= duration;
        return change * (1 - sqrtf(1 - time * time)) + start;
    }
    static float easeInCubic(float time, float start, float change, float duration)
    {
        return change * powf(time / duration, 3) + start;
    }
    static float easeInElastic(float time, float start, float change, float duration)
    {
        float s = 1.70158f;
        float p = 0;
        float a = change;

        if (time == 0 || a == 0)
        {
            return start;
        }

        time /= duration;

        if (time == 1)
        {
            return start + change;
        }

        if (p == 0)
        {
            p = duration * 0.3f;
        }

        if (a < fabsf(change))
        {
            a = change;
            s = p * 0.25f;
        }
        else
        {
            s = p / (2 * M_PI) * asinf(change / a);
        }

        return -(a * powf(2, 10 * (--time)) * sinf((time * duration - s) * (2 * M_PI) / p)) + start;

    }
    static float easeInExpo(float time, float start, float change, float duration)
    {
        return change * powf(2, 10 * (time / duration - 1)) + start;
    }
    static float easeInQuad(float time, float start, float change, float duration)
    {
        time /= duration;
        return change * time * time + start;
    }
    static float easeInQuart(float time, float start, float change, float duration)
    {
        return change * powf(time / duration, 4) + start;
    }
    static float easeInQuint(float time, float start, float change, float duration)
    {
        return change * powf(time / duration, 5) + start;
    }
    static float easeInSine(float time, float start, float change, float duration)
    {
        return change * (1 - cosf(time / duration * (M_PI / 2))) + start;
    }
    static float easeInOutBack(float time, float start, float change, float duration)
    {
        float s = 1.70158f;

        time /= duration;
        time *= 2;

        if ((time) < 1)
        {
            s *= (1.525f);
            return change * 0.5f * (time * time * ((s + 1) * time - s)) + start;
        }

        time -= 2;
        s *= 1.525f;
        return change * 0.5f * ((time)*time * ((s + 1) * time + s) + 2) + start;
    }
    static float easeInOutBounce(float time, float start, float change, float duration)
    {
        if (time < duration * 0.5f)
        {
            return (easeInBounce(time * 2, 0, change, duration) * 0.5f + start);
        }

        return (easeOutBounce(time * 2 - duration, 0, change, duration) * 0.5f + change * 0.5f + start);
    }
    static float easeInOutCirc(float time, float start, float change, float duration)
    {
        time /= duration * 0.5f;

        if (time < 1)
        {
            return change * 0.5f * (1 - sqrtf(1 - time * time)) + start;
        }

        time -= 2;
        return change * 0.5f * (sqrtf(1 - time * time) + 1) + start;
    }
    static float easeInOutCubic(float time, float start, float change, float duration)
    {
        time /= duration * 0.5f;

        if (time < 1)
        {
            return (change * 0.5f) * powf(time, 3) + start;
        }

        return (change * 0.5f) * (powf(time - 2, 3) + 2) + start;
    }
    static float easeInOutElastic(float time, float start, float change, float duration)
    {
        float s = 1.70158f;
        float p = 0;
        float a = change;
        if (time == 0 || a == 0)
        {
            return start;
        }
        time /= (duration * 0.5f);
        if (time == 2)
        {
            return start + change;
        }
        if (p < 0.5f)
        {
            p = duration * (0.3f * 1.5f);
        }
        if (a < fabsf(change))
        {
            a = change;
            s = p * 0.25f;
        }
        else
        {
            s = p / (2 * M_PI) * asinf(change / a);
        }
        if (time < 1)
        {
            return -0.5f * (a * powf(2, 10 * (--time)) * sinf((time * duration - s) * (2 * M_PI) / p)) + start;
        }
        return a * powf(2, -10 * (--time)) * sinf((time * duration - s) * (2 * M_PI) / p) * 0.5f + change + start;
    }
    static float easeInOutExpo(float time, float start, float change, float duration)
    {
        time /= duration * 0.5f;

        if (time < 1)
        {
            return change * 0.5f * powf(2, 10 * (time - 1)) + start;
        }

        time -= 1;
        return change * 0.5f * (-powf(2, -10 * time) + 2) + start;

    }
    static float easeInOutQuad(float time, float start, float change, float duration)
    {
        time /= (duration * 0.5f);

        if (time < 1)
        {
            return (change * 0.5f) * (time * time) + start;
        }

        return (-change * 0.5f) * (--time * (time - 2) - 1) + start;
    }
    static float easeInOutQuart(float time, float start, float change, float duration)
    {
        time /= duration * 0.5f;

        if (time < 1)
        {
            return change * 0.5f * powf(time, 4) + start;
        }

        return -change * 0.5f * (powf(time - 2, 4) - 2) + start;

    }
    static float easeInOutQuint(float time, float start, float change, float duration)
    {
        time /= duration * 0.5f;

        if (time < 1)
        {
            return change * 0.5f * powf(time, 5) + start;
        }

        return change * 0.5f * (powf(time - 2, 5) + 2) + start;

    }
    static float easeInOutSine(float time, float start, float change, float duration)
    {
        return change * 0.5f * (1 - cosf(M_PI * time / duration)) + start;
    }
    static float easeLiniear(float time, float start, float change, float duration)
    {
        return change * time / duration + start;
    }
    static float easeOutBack(float time, float start, float change, float duration)
    {
        float s = 1.70158f;

        time = (time / duration) - 1;
        return change * ((time)*time * ((s + 1) * time + s) + 1) + start;

    }
    static float easeOutBounce(float time, float start, float change, float duration)
    {
        time /= duration;

        if (time < (1 / 2.75f))
        {
            return change * (7.5625f * time * time) + start;
        }
        else
            if (time < (2 / 2.75f))
            {
                time -= (1.5f / 2.75f);
                return change * (7.5625f * time * time + 0.75f) + start;
            }
            else
                if (time < (2.5f / 2.75f))
                {
                    time -= (2.25f / 2.75f);
                    return change * (7.5625f * time * time + 0.9375f) + start;
                }
                else
                {
                    time -= (2.625f / 2.75f);
                    return change * (7.5625f * time * time + 0.984375f) + start;
                }

    }
    static float easeOutCirc(float time, float start, float change, float duration)
    {
        time = time / duration - 1;
        return change * sqrtf(1 - time * time) + start;
    }
    static float easeOutCubic(float time, float start, float change, float duration)
    {
        return change * (powf(time / duration - 1, 3) + 1) + start;
    }
    static float easeOutElastic(float time, float start, float change, float duration)
    {
        float s = 1.70158f;
        float p = 0;
        float time2 = time;
        float start2 = start;
        float change2 = change;
        float duration2 = duration;

        if (time2 == 0 || change2 == 0)
        {
            return start2;
        }
        time2 /= duration2;
        if (time2 == 1)
        {
            return start2 + change;
        }
        if (p < 0.5f)
        {
            p = duration2 * 0.3f;
        }
        if (change2 < fabsf(change))
        {
            change2 = change;
            s = p * 0.25f;
        }
        else
        {
            s = p / (2 * M_PI) * asinf(change / change2);
        }
        return change2 * powf(2, -10 * time2) * sinf((time2 * duration2 - s) * (2 * M_PI) / p) + change + start2;
    }
    static float easeOutExpo(float time, float start, float change, float duration)
    {
        return change * (-powf(2, -10 * time / duration) + 1) + start;
    }
    static float easeOutQuad(float time, float start, float change, float duration)
    {
        time /= duration;
        return -change * time * (time - 2) + start;
    }
    static float easeOutQuart(float time, float start, float change, float duration)
    {
        return -change * (powf(time / duration - 1, 4) - 1) + start;
    }
    static float easeOutQuint(float time, float start, float change, float duration)
    {
        return change * (powf(time / duration - 1, 5) + 1) + start;
    }
    static float easeOutSine(float time, float start, float change, float duration)
    {
        return change * sinf(time / duration * (M_PI / 2)) + start;
    }
};