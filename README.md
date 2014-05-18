
Mining Incorporated
===================

This is a continunation of my unfinished game, [Mining Incorporated](https://github.com/treeman/LD29), for Ludum Dare 29 with the theme "Beneath the Surface".

Todo
====

Next steps:

4. Refactor world.  
    * Pathfinding in level/dimension, possibly other things.
    * Rename commands to events
    * Move task done/skip to events
    * Move build calculations to gui
    * Task handling
5. Refactor Worker.--
    * Report back to world via events.
    * Proper non-laggy movement
5. Refactor Tile.  
    Readd objects, ability to change ground.
5. Move ground definitions to object factory
5. Move floor definitions to Locator
6. Remove rooms the way they are now.
7. Refactor objects.
8. Add materials (look of the ground).
9. Specify all data things from lua.  
    * Planning objects (currently in world, move?)
    * Sprites (set colors/alpha channels. load from tileset with indexes)
    * Buildable materials, with costs and what ground it is.
    * Colors and positions of gui elements.
    * What buttons in ButtonPanel and in what order.  
        Should be able to specify actions. Need to expose functions C++ -> lua.
10. Correct task handling for workers.
11. Multilevel pathfinding.
12. AreaSelection needs iterators over positions  
    Annoying iterators.
13. log.hxx

* remove typedef shared ptrs
* unit tests
    for fmt at least
* Refactor RoomType into OreType or similar
* Multiple levels
* Use lua for constants and definitions
    Would be cool to be able to change some things via console (colors etc?)
* Create a console where we can set settings and cheat etc.
* General refactoring
* Prettier worker sprites
* Simulation and interaction of objects
* Logging  
    * Cannot `<< endl` to it, but maybe that's ok?
* Move global state to Locator
    * Butler
* Make independent of screen size!
* Remove constants.hxx. Move to lua settings file instead.
* Scrollable history
* Suggestions for console
* Console should function
* Develop guiobjects and collections
    Need to be able to style everything in collection
* Cool pixelated graphics.
* Extend fmt to allow precision and long types, possibly.
* Smarter level generation
    Better algorithm
    Use levels and specify vein size for each ores etc..

* Consider Command pattern with actors to handle input
* Flyweight pattern for tile handling?
* Tiles as data, load from lua
* Prototypes in lua ("mixins" from tables)
* State for worker handling
* Type Object for ground, rooms, ores
    Tile *rock->create_tile(...)

Refactor
========

* Tile, cut up into components
* World, cut up into components
* Levels, not as a simple array of array of shared pointers to tiles
* Ores. How to handle?

Ideas
=====

Inspiration taken from Evil Genius, Theme Hospital, Rollercoaster Tycoon, Prison Architect, LEGO Rock Raiders among others.

* Base building like Evil Genius and Prison Architect.
* Hire workers and train them to be specialists.
* Protect the operations from spies, thieves and saboteurs.  
    ???
* Considerations for base building:
    * Visits from buyers must be clear from dead bodies and similar.
    * Different areas have different safety levels.
    * Ores can be found thoughout the level.
    * Protect sensitive buildings/areas from spies and saboteurs.
        Can blow up power/water/air.
        Mining equipment.
        Steal ores, riches, technologies. etc.
    * Workers need air and water cleaning/generator facilities.
        Draw pipes and the like. Cannot short-circuit! Need to plan ahead.
    * Need transport systems.
        Railways, subways, cars, walkways and elevators.
* Art Style
    Everything ordinary in Black/White
    Ores and things produced by ores are the only things with color.

Ground
------

* Unmined rock terrain

Rooms
-----

* Baracks/Sleeping quarters.  
    Workers go here to rest and recover. Build more to increase worker cap.
* Kitchen.  
    Hire chefs for higher quality food. Better food -> benefits.
* Canteen/Mess hall.  
    Increase stats for workers.
* Spa. With sauna and massage etc. Luxury. Higher social minions need these.
* Infirmary.
* Power plant/utilities.
* Archives/library.
* Armoury.
* Office.  
    Unlock tech tree things.
* Laboratory and/or Tech development.  
    Different kinds perhaps? Research and improve things.
* Meeting room. Where the big deals go down.
* Training room.
    Different kinds perhaps?
* Strongroom. To keep the riches! Possibly ingots or diamond?
* Freezer/Morgue?
* Control room?
* Tech development.
* Kennels.
* Storage.
* Deliveries.
* Garbage.
* Cleaning cupboard.
* Common room.
* Corridor

Some considerations:

* "Heat zones". Some rooms all can see, baracks for example. Morgue and strongroom not so much.
* Big vs small rooms. Should build as small as possible, but no smaller.
* Loot or high status items. Crowded vs hidden.

Workers
-------

* Exhaustion level
* Hunger
* Happiness level
* Hygien
* Sleep/Exhaustion
* Motivation

* Worker minions  
    The Basic minion class. Train all other minion from this one.
    Build all the things.
    Move items etc.
    Mine/Drive cars/Drills?
    Repair things?
* Scientists
    Perform research.

    * Technitians? Repair things
    * Scientists. Research.
    * Biochemist?
    * Quantum phycicist?
* Chefs
* Office dudes
* Military minions  
    Protect the operations from evil!
    Probably in different classes?
* Spy  
    Send to other companies and steal trade secrets.
* Social minions
    Cater to selling and escorting visitors. Can be used to convert enemies?

Ores/Minerals/Things to collect
-------------------------------

To gain ores:

1. Locate, either exact or approximate.
2. Mine.
3. Extract from mined rock.
4. Enhance. Create diamond jewelry for example or smelt gold into ingots.

Can sell the mined material (cheap).
Can sell raw material, after the resources have been split. For example sell ugly diamond chunks or sell Argenite.
Can sell the enhancement. Golden ingots, diamond jewelry or similar (expensive).

* Coal - common
* Iron - common
* Copper - common
* Gold - rare
* Argenite (Silver) - rare
* Diamond - very rare
* Titanium - rare
* Platinum - very rare
* Chrom (Chromite) - common
* - (Aluminium) - common
* - (Uranium) - very rare
* Natural gas - fairly common
* Etherium - and other rare made up things?
* Bitcoin (Minecoin) - Need servers to mine it!
* Aluminium
* Uranium
* Etherium

1. Locate (?) - maybe have a hover over effect on level (estimated X ores...)
2. Mine
3. Refine      ore -> ingot
4. Enhance (?) diamonds -> jewelry

Things
------

* When you cave deeper, monsters and things will come alive and hurt you.
* FOV
* Prospecting to locate ores (?)

