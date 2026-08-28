# Requirements

  * g++ v5.4 or newer (compilation was performed with g++ 9.3)
  * Boost 1.58.0 or newer
    * The `boost/multiprecision/float128.hpp` header must be available
  * Make

## Installed Boost Packages

For development the following boost packages were installed.

```
libboost-date-time1.58.0/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed]
libboost-filesystem1.58.0/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed]
libboost-iostreams1.58.0/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed]
libboost-python1.58.0/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed,automatic]
libboost-regex1.58.0/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed,automatic]
libboost-system1.58.0/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed]
libboost-test-dev/xenial,now 1.58.0.1ubuntu1 amd64 [installed]
libboost-test1.58-dev/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed,automatic]
libboost-test1.58.0/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed,automatic]
libboost1.58-dev/xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 amd64 [installed,automatic]
libboost1.58-doc/xenial-updates,xenial-updates,now 1.58.0+dfsg-5ubuntu3.1 all [installed]
```

This listing was obtained by running `apt list --installed | grep boost`.


# Compilation

The code can be compiled with the provided makefile using the standard `make`
command.

If compiling the code manually, or integrating into a larger program, include
the following flags:

```
FLAGS=-std=c++17 -fsanitize=address -fuse-ld=gold -Wall -MMD \
      -fext-numeric-literals -lquadmath #-O3
```

Note that flag `-fuse-ld=gold` is only required on certain Ubuntu systems due
to a know bug with g++ 5.x.


# Sample Execution & Output

If run without command line arguments, using

```
./precisionEstimate
```

the following usage message will be displayed.

```
Usage: ./precisionEstimate numExecs
```

If run using

```
./precisionEstimate 100000000
```

output *simliar* to

```
   0 secs | 1.19209e-07
   1 secs | 2.22045e-16
  17 secs | 1.92593e-34
```

will  be displayed. Note that the precision estimates will vary by
architecture/system.


---

# Merge Requests

This section documents contributions made by students via merge requests.


## Replace naïve float128 abs implementation with something closer to Rust implementation 

**Author**: Alex Launi
**Date**: 2020-05-21

#### Goal

Remove bottleneck caused by conditional negation implementation of float128 abs.

#### Results

Note: these were run on a 2019 MacBook Pro using a 2.4 GHz 8-Core Intel Core i9.

| Version    | Time (1x10^9)   |
| ---        | --------------: |
| Orig (-O0) | 326s            |
| Mine (-O0) | __179s__        |
| Orig (-O3) | 92s             |
| Mine (-O3) | __60s__         |

#### Possible Improvement

Rust uses MPFR on the backend. I dug into the MPFR source, and this is close to
the implementation used. The primary difference is the use of a `MPFR_SET_SIGN`
macro. Boost has a copysign(const T& x, const T& y) which copies the sign from
y to x. Something like

```C++
inline
float128 abs(float 128 x)
{
    const float128 p = 1.0Q;
    return copysign(x, p);
}
```

should work, but I was unable to get any use of copysign to compile. I settled
on the approach used in this merge request. I think the results speak well.
