#ifndef INTERPOLATE_H
#define INTERPOLATE_H

#include <stdint.h>

enum InterpolateType {LINEAR,SMOOTH};

/**
 * Interpolate numbers
 * 
 * You can use any type that allows addition, signed subtraction, and multiplication with floats
 * 
 * The Color class that comes with this library can be used as a template for creating your own 
 * interpolateable classes
 * 
 * any number (int, float, signed int, etc.) can be used without issues
 * 
 */
template<typename T>
class Interpolate {

private:

    T begin_;
    T end_;

    InterpolateType type_;

    float delta_;
    uint32_t time_;

    bool done_;

    //smooth interpolation
    float smooth() {
        return delta_ * delta_ * (3 - (2 * delta_));
    }

    //linear interpolation
    float linear() {
        return delta_;
    }

public:

    /**
     * Create a new Interpolate class with a default value
     * 
     * @param interp Interpolation type (default: LINEAR)
     * 
     * @see InterpolateType
     */
    Interpolate(InterpolateType interp=LINEAR) : Interpolate(T(), interp) {}
    /**
     * Create a new Interpolate class with a custom value
     * 
     * @param initial initial value
     * @param interp Interpolation Type (default: LINEAR)
     * 
     * @see Interpolate Type
     */
    Interpolate(T initial, InterpolateType interp=LINEAR) {
        begin_ = initial;
        end_ = initial;
        
        setInterpolation(interp);
        delta_ = 1;
        done_ = true;
    }

    /**
     * Change the Interpolation used
     * 
     * @note it is generally not a good idea to change interpolation
     * while in the middle of a change
     * 
     * @param type Interpolation
     * 
     */
    void setInterpolation(InterpolateType type) {
        type_ = type;
    }

    /**
     * Get the current value
     * 
     * @return current value
     */
    T getValue() {
        if(delta_ == 1) {
            return end_;
        } else if(delta_ == 0) {
            return begin_;
        }

        float delta;

        if(type_ == SMOOTH) {
            delta = smooth();
        } else {
            delta = linear();
        }

        return static_cast<T>((end_ - begin_) * delta + begin_);

    }

    /**
     * Start interpolating to a new value
     * 
     * It doesn't matter if currently in an interpolation, it 
     * will then start from the current value, then interpolate 
     * to the final value
     * 
     * @param value final value
     * @param t time (could be any unit, but step() needs to use the same units)
     * @param t If 0 the change will be immidiate without any interpolation
     */
    void setValue(T value, uint32_t t) {
        begin_ = getValue();

        end_ = value;
        time_ = t;

        if(t == 0) {
            begin_ = value;
            delta_ = 1;
            return;
        }

        delta_ = 0;
        done_ = false;
    }

    /**
     * progress through the interpolation t amount of time
     * 
     * @param t time (could be any unit, but setValue() needs to use the same units)
     */
    void step(uint32_t t) {
        if(t > time_ || delta_ >= 1 || time_ == 0) {
            delta_ = 1;
            return;
        }

        float delta = static_cast<float>(t) / time_;

        if(delta + delta_ > 1) {
            delta_ = 1;
        } else {
            delta_ += delta;
        }
    }

    /**
     * Check if the current interpolation has finished
     * 
     * @return true if done
     */
    bool isDone() {
        return delta_ >= 1;
    }

    /**
     * Check if the current interpolation has just finished since 
     * the last time this has been called
     * 
     * @return true if just finished
     */
    bool justFinished() {
        if(isDone() && !done_) {
            done_ = true;
            return true;
        } else {
            return false;
        }
    }

    /**
     * Get the delta value for the interpolation
     * 
     * @note the returned interpolation is always linear
     * 
     * return delta (0.0 to 1.0)
     */
    float getDelta() {
        return delta_;
    }

    /**
     * Get the time left in the interpolation
     * 
     * @note returns 0 if done_
     * 
     * @return time
     */
    uint32_t getTimeLeft() {
        return static_cast<uint32_t>((1 - delta_) * time_);
    }

    /**
     * Get the interpolation type
     * 
     * @return interpolation type
     */
    InterpolateType getInterpolation() {
        return type_;
    }

};

#endif