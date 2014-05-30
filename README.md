
Mining Incorporated
===================

This is a continunation of my unfinished game, [Mining Incorporated](https://github.com/treeman/LD29), for Ludum Dare 29 with the theme "Beneath the Surface".

Todo
====

Next steps
----------

3. Buildable/Non-buildable objects
5. Properly mine ores and move to storage room
8. Refactor world.  
    * World could be split into Components  
        1. Coordinate mappings
        2. Event handling
        3. Task handling
        4. Worker handling (map to tasks etc)
        5. Resource handling (can be inside resources)
8. Refactor Tile.  
    Readd objects.
8. Remove rooms the way they are now.
8. Refactor objects.
8. Remove constants.hxx
8. Specify all data things from lua.  
    * Planning objects (currently in world, move?)
    * Sprites (set colors/alpha channels. load from tileset with indexes)
    * Buildable materials, with costs and what ground it is.
    * Colors and positions of gui elements.
    * What buttons in ButtonPanel and in what order.  
        Should be able to specify actions. Need to expose functions C++ -> lua.
    * First floor
    * Selection preview color
8. Fog of War
10. Multilevel pathfinding.
10. Rework base object. Not used??
10. Worker stats
11. Load first floor via lua
12. Save games
13. After mining, build support on edges
14. Build actions  
    * Ability to remove pending builds
    * Remove pending when building on same spot

Random
------

* Rooms  
    * Prettier name of room
    * Preview size of room
    * Sometimes marking double rooms
    * Name is not repositioned
    * Split rooms
* Don't lookup from settings at every frame,
    keep a pointer thing to fetch values.
* Lazy state change (after drawing)
* unit tests
    for fmt at least
* Use lua for constants and definitions
    Would be cool to be able to change some things via console (colors etc?)
* Create a console where we can set settings and cheat etc.
* Prettier worker sprites
* Simulation and interaction of objects
* Make independent of screen size!
* Remove constants.hxx. Move to lua settings file instead.
* Scrollable history
* Suggestions for console
* Console should function
* Develop guiobjects and collections
    Need to be able to style everything in collection
* Extend fmt to allow precision and long types, possibly.
* Smarter level generation
    Better algorithm
    Use levels and specify vein size for each ores etc..
* Prettier buttons

Considerations
--------------

* Consider Command pattern with actors to handle input
* Flyweight pattern for tile handling?
* Tiles as data, load from lua
* Prototypes in lua ("mixins" from tables)
* State for worker handling
* Type Object for ground, rooms, ores
    Tile *rock->create_tile(...)

Refactor
--------

* Tile, cut up into components
* World, cut up into components
* Sprite handling via lua + sprite collection
* Constants from lua

Larger changes
--------------

* Specify object behaviour from lua  
    Quite a large undertaking? Need to expose an interface to lua.
* Cool pixelated graphics.
* Chunking levels?
* Move around camera

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

* Mining rock should be expensive and you should go minus
* Water pockets may flood your floors
* Only robots can work in lower floors
* Level up workers + items
* Locator on floors above are able to see down through the rocks, but not through empty space
* Things shall cost both money + minerals
* Need to add wood etc on sides of mines to keep them from falling in
* Journalists will visit
* Cover up accidents?
* Newspaper with articles writing about the corporation
* Bribe journalists?
* Genetically manipulated workers

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

