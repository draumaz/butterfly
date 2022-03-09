# Butterfly
A text-based TBBS with fantasy creatures, projectile weaponry, poisonous elixirs, and more.

```
Butterfly v0.16 | KILLS: 0   | DEATHS: 0   | SPARES: 0

PLAYR: Aradi  | HP: 26 | STR: 14

ENEMY: Goblin | HP: 2  | STR: 7

[FIGHT]
[ITEMS] <
[SPARE]
[EXIT ]

[1x POTION]
[0x SPEAR ] <
[1x POISON]
[BACK     ]
```

# Controls

```W, I, UP``` - up

```S, K, DOWN``` - down

```ENTER``` - select

```CTRL-Q, CTRL-C, Q``` - close game

# Download

## Grab a binary!
  You can find these <a href="https://github.com/draumaz/butterfly/releases/latest">here</a>.

## Build from source! (it won't take long, I promise)

- ```git clone https://github.com/draumaz/butterfly```

- ```cd butterfly```

- ```make```

- ```./butterfly-debug```

### Notes for non-Linux compilation

Butterfly requires slightly different build parameters on non-Linux platforms. To compile on them, apply patches/non_linux.patch to the Makefile.

- ```cd butterfly```

- ```patch Makefile < patches/non_linux.patch```

- ```make```

- ```./butterfly-debug```

#### If you encounter anything in your builds that feel like bugs, report them and I'll fix it as soon as possible!

# Acknowledgements

catboy6969 - ARMv8 experimentation, quality assurance, battle design assistance, game naming, bugtest

