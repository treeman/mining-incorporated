
Mining Incorporated
===================

This is a continunation of my unfinished game, [Mining Incorporated](https://github.com/treeman/LD29), for Ludum Dare 29 with the theme "Beneath the Surface".

Todo
====

* Preview building and items, see Prison Architect
* Refactor RoomType into OreType or similar
* Multiple levels
* Use lua for constants and settings
    Settings is different than constants. Settings can be changed in terminal and are typically flags.
    Should split into several files.
    Need to expose the values in c++ in a nice way.
    Global access is probably nicer here??
* Create a console where we can set settings and cheat etc.
* Cleanup readme
* General refactoring
* Prettier worker sprites
* Simulation and interaction of objects
* A way to abort application
* Logging
* Visal debugging
* Remove global state
* Make independent of screen size!
* Remove constants.hxx. Move to lua settings file instead.
* Waterfalling input handling!
* Scrollable history
* Suggestions for console
* Console should function
* General gui for buttons and buttonlist.  
    Should be able to replace a buttonlist "management" with a button for example.

Ideas
=====

Rooms
-----

* Baracks
* Canteen/Mass hall
* Office
* Laboratory/Research
* Storage
* Deliveries
* Corridor

Workers
-------

If time

* Exhaustion level - maybe
* Hunger - maybe
* Happiness level - nope
* Hygien - nope

* Worker minions - yes!
* Scientists - nope

Ores/Minerals/Things to collect

* Coal
* Iron
* Copepr
* Gold
* Silver
* Diamond
* Titanium
* Platinum
* Chrom

Ideas2
=====

Inspiration taken from Evil Genius, Theme Hospital, Rollercoaster Tycoon, Prison Architect, LEGO Rock Raiders among others.

* Base building like Evil Genius and Prison Architect.
* Hire workers and train them to be specialists.
* Protect the operations from spies, thieves and saboteurs.
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
* Minions/Workers
    Should have different traits:
    * Sleep/Exhaustion
    * Bladder/Bowels
    * Hygiene
    * Motivation

    Comes in different flavours:
    * Worker minions
        The Basic minion class. rain all other minion from this one.
        Build all the things.
        Move items etc.
        Mine/Drive cars/Drills?
        Repair things?
    * Military minions
        Protect the operations from evil!
        Probably in different classes?
        * Spy
            Send to other companies and steal trade secrets.
    * Social minions
        Cater to selling and escorting visitors. Can be used to convert enemies?
    * Science minions
        Perform research.

        * Technitians? Repair things
        * Scientists. Research.
        * Biochemist?
        * Quantum phycicist?
* Rooms
    * Baracks/Sleeping quarters. Workers go here to rest and recover.
    * Kitchen.
    * Canteen/Mess hall.
    * Spa. With sauna and massage etc. Luxury. Higher social minions need these.
    * Infirmary.
    * Power plant/utilities.
    * Archives/library.
    * Armoury.
    * Office.
    * Meeting room. Where the big deals go down.
    * Laboratory and/or Tech development.
        Different kinds perhaps?
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

    Some considerations:

    * "Heat zones". Some rooms all can see, baracks for example. Morgue and strongroom not so much.
    * Big vs small rooms. Should build as small as possible, but no smaller.
    * Loot or high status items. Crowded vs hidden.

* Ores/Minerals/Things
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

    To gain ores:

    1. Locate, either exact or approximate.
    2. Mine.
    3. Extract from mined rock.
    4. Enhance. Create diamond jewelry for example or smelt gold into ingots.

    Can sell the mined material (cheap).
    Can sell raw material, after the resources have been split. For example sell ugly diamond chunks or sell Argenite.
    Can sell the enhancement. Golden ingots, diamond jewelry or similar (expensive).

* Art Style
    Everything ordinary in Black/White
    Ores and things produced by ores are the only things with color.

* Aluminium
* Uranium
* Etherium

1. Locate (?) - maybe have a hover over effect on level (estimated X ores...)
2. Mine
3. Refine      ore -> ingot
4. Enhance (?) diamonds -> jewelry

