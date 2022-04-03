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

DeltaDove - ARMv8 experimentation, quality assurance, battle design assistance, game naming, bugtest

# Licensing

- Butterfly is dual-licensed under both the GPL-v3.0 and MIT licenses.
- The facets of this game covered by the MIT license can be found at <a href="https://github.com/draumaz/butterfly/blob/main/lic/MIT.txt">lic/MIT.txt</a>. 
- All other parts are licensed under GPL-v3.0.
