# Algorithm Module Documentation

This module provides implementations of three common algorithms used in embedded systems: Mean Filter, Sliding Window Filter, and Curve Fitting.

## Algorithms

### 1. Mean Filter
Computes the arithmetic mean of a given array of integers.

**Functions:**
- `int mean(int* data, int size)`: Computes the mean of the array `data` of size `size`.

### 2. Sliding Window Filter
Applies a sliding window filter to smooth out a sequence of data points.

**Functions:**
- `void sliding_window_filter(int* input, int* output, int size, int window_size)`: Applies a sliding window filter to the `input` array and stores the result in the `output` array.

### 3. Curve Fitting
Fits a linear curve to a set of data points using the least squares method.

**Functions:**
- `void linear_curve_fit(float* x, float* y, int size, float* slope, float* intercept)`: Fits a linear curve to the points `(x[i], y[i])` and returns the `slope` and `intercept` of the fitted line.

## Usage

Include `algorithm_module.h` in your project to use these algorithms.

## Unit Testing

Run the unit tests by building the `tests` target. Each algorithm has a corresponding test file in the `tests` directory.
