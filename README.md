Some toy maze-ing
=================

The purpose is to see how a maze can be generated and solved, what kind of variations are there. The final goal is to see how an unaware solver can go through.


# Requirements

- C++11 compiler
- SDL2

(Your include path might vary.)


# Run

```bash
c++ \
  -I/Library/Frameworks/SDL2.framework/Headers 
  -F/Library/Frameworks \
  -framework SDL2 \
  -std=c++11 \
  -stdlib=libc++ \
  main.cpp -o main && ./main <WIDTH> <HEIGHT>
```


# Appetizer

```
║╔═╔╗╔═╗ ╔══╗╔═╔═════════════╗═╗
║╚╗║╠╣║║ ╠══║║╔╝╔╦══════════╗╚═╝
╚═╬╝║╠╝╚╗║╔═╣╠╣╔╝╚═╔═║╔══╦╗║╚═══
═╗║═╝╚═╗║╔╝║║║╚╩═╗║║║║║═╗║╚╬╦══╗
╔╣╚╗  ╔╝║║╔╝║╠═╗╔╩╝║╚╣╠═╝╚═║║╔╗║
║╚═╝ ╔╝╔╝║╚╗╚╝║║║╔═╝╔╝║╔═════║║║
╚══╦╗╚╗╚═╬╗╚═╗║╚═╝╔═╩═╝╚═╗╔╗╔╣║║
║╔╗║║║╚╗╔╝╠╗ ║╠══╗╠╗╔╗╔══╩╝╚╝╚╝║
╚╝║║║║║║║╔╝╚╦╝╚═╔╝║╚╝║║ ╔╗║╔═══╝
╔═╝║╠╩╝║║╚╗╔╝ ╔═╩═╩═╗╔╝╔╝╠╩╝╔╗═╗
╠══║╠╦╗╚═╗║╚══╬════╗╚╝║║╔╩╦═╝║╔╝
║╔╗║║║╠══╠══╗║╚═══╗╚══╩╝║║╚═══╝║
║║║║║║╚═╗╚╗ ╚╝ ╔══╚═╗╔╗ ╔╝╔════╝
╚╝╚╝╚═╗╔╝║╚══╦╗╠╦══╗║║╚═╩═╩═════
      ║╚═╝╔╗╔╝╚╣║╔╗║╚╣╔╗╔═══╦══╗
      ╚═══╝║╚══╚═╝╚══╚╝╚╝   ╚══║
```