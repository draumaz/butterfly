```
______ _   _ _____ _____ _________________ _   __   __ |
| ___ | | | |_   _|_   _|  ___| ___ |  ___| |  \ \ / / |
| |_/ | | | | | |   | | | |__ | |_/ | |_  | |   \ V /  |
| ___ | | | | | |   | | |  __||    /|  _| | |    \ /   |
| |_/ | |_| | | |   | | | |___| |\ \| |   | |____| |   |
\____/ \___/  \_/   \_/ \____/\_| \_\_|   \_____/\_/   |
-------------------------------------------------------|
```


A text-based TBBS, written by draumaz.

![Screenie](https://github.com/draumaz/butterfly/raw/main/media/btf-main.svg "Game screen")
![Weapon](https://github.com/draumaz/butterfly/raw/main/media/btf-item.svg "Item screen")

# Controls

```W, I, UP``` - move up

```S, K, DOWN``` - move down

```ENTER``` - confirm

```CTRL-Q, CTRL-C, Q``` - close game

# Download

## Grab a binary!
  You can find these <a href="https://github.com/draumaz/butterfly/releases/latest">here</a>.

## Build from source! (it won't take long, I promise)

```git clone https://github.com/draumaz/butterfly; cd butterfly```

```make```

```./butterfly-debug```

### Notes for non-GNU C compilers

- Clang handles Butterfly slightly differently than GCC. To successfuly compile using clang, apply patches/build_clang.patch to the root of the cloned repo.

```
cd butterfly
patch -ruN < patches/build_clang.patch
```

#### If you encounter anything in your builds that feel like bugs, report them and I'll fix it as soon as possible!

# Thanks!

catboy6969 - playtest, game design, armv8 testing

Bryce Cano - character design, inspiration

<a href="https://carbon.now.sh/">Carbon</a> - screenshots
