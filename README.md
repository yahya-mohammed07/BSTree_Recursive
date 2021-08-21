# Binary-search tree V2.0.1

==============

## Introduction

- Binary-search tree data-structure written in c++ modern with `smart-raw pointers and iterators`

## Requirement

- c++17 or later

  - Tested on:
    - g++-9 -std=c++1z
    - g++10 -std=c++1z
    - g++-11 -std=c++1z
    - clang++-11 -std=c++1z
    - clang++-10 -std=c++1z

### Everything inside `bst.hpp`

![image](https://user-images.githubusercontent.com/62993724/130318791-18abc0c2-0e1c-46eb-90d0-57de1792f549.png)

- including: min() and size()

## Usage

- simply download this library then copy `lib` folder to your working directory then include it like this: `#include "lib/bst.hpp"`!

- if you're on ubuntu you can do this:

  - open terminal then do `sudo apt install nautilus-admin` then when it's done do `nautilus -q`
  - open `usr/include` folder as administrator
  - add `lib` folder into `usr/include`, you may rename library into `bst` after you're done!, this is how you include it without copying it every time into your directory!

  - ```cpp
    #include <lib/bst.hpp>
    #include <iostream>

    auto main()
        -> int
    {
      bst_<int> nums {1, 2, 3, 5};
      nums.print(1);
    }
    ```
