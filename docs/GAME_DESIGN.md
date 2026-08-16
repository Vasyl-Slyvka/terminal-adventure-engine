# Elden Ring TUKE Edition — Design Document

> This is an unofficial, fan-made, non-commercial educational design. See the repository [NOTICE](../NOTICE.md) for intellectual-property information.

Elden Ring TUKE Edition is a text adventure design for Problem Set #5: Adventure.
The game is a fan-made, educational TUKE-themed interpretation inspired by Elden Ring.
The player controls the Tarnished and tries to become the TUKE Lord by collecting Great Runes, reaching the Heart of the Erdtree, and choosing one rune at the Erdtree Forge.

Important theme:
Not every ending gives true freedom. In most endings, the Tarnished becomes a consort, servant, vessel, or instrument of some greater power.

1. Game Title
-------------
Elden Ring TUKE Edition

2. Hero
-------
The hero is the Tarnished.

Final goal:
The Tarnished must collect Great Runes, reach the Heart of the Erdtree, choose one rune at the Erdtree Forge, and become the TUKE Lord.

3. Intro Idea
-------------
At the beginning of the game, the player receives a short lore intro:

The Lands Between are broken. The Elden Ring has been shattered, the demigods hold fragments of its power, and the Erdtree waits for a new lord.

You are the Tarnished. You awaken in the Stranded Graveyard with nothing but a forgotten calling. To become the TUKE Lord, you must gather Great Runes, survive the cursed paths of the Lands Between, reach the Heart of the Erdtree, and choose the fate of the world.

In the starting location, there is also VETERANS NOTES. This item explains the rules of the game.

4. Latin Quote Used After Endings
---------------------------------
After every ending, this quote is printed:

Num fatum hominum lege arcana regitur?
An manus ignota super mundum pendet?
Homo tamen suae voluntatis dominus non semper est.

Meaning:
Is the fate of men ruled by a hidden law?
Does an unknown hand hang over the world?
Yet man is not always the master of his own will.

5. Room List
------------
There are 17 rooms:

1. STRANDED GRAVEYARD
2. STORMVEIL CASTLE
3. ACADEMY OF RAYA LUCARIA
4. RADAHN ARENA
5. NOKSTELLA ETERNAL CITY
6. VOLCANO MANOR
7. LEYNDELL ROYAL CAPITAL
8. DEEPROOT DEPTHS
9. MOUNTAINTOPS OF THE GIANTS
10. CRUMBLING FARUM AZULA
11. PLACIDUSAX ARENA
12. MOHGWYN PALACE
13. CONSECRATED SNOWFIELD
14. HALIGTREE
15. FRENZIED FLAME PROSCRIPTION
16. LEYNDELL ASHEN CAPITAL
17. HEART OF THE ERDTREE

6. Room Connections
-------------------
The map uses only north / south / east / west.

1. STRANDED GRAVEYARD
   north -> STORMVEIL CASTLE

2. STORMVEIL CASTLE
   south -> STRANDED GRAVEYARD
   north -> ACADEMY OF RAYA LUCARIA
   east  -> RADAHN ARENA

3. ACADEMY OF RAYA LUCARIA
   south -> STORMVEIL CASTLE
   west  -> NOKSTELLA ETERNAL CITY
   north -> LEYNDELL ROYAL CAPITAL

4. RADAHN ARENA
   west -> STORMVEIL CASTLE

5. NOKSTELLA ETERNAL CITY
   east  -> ACADEMY OF RAYA LUCARIA
   south -> VOLCANO MANOR

6. VOLCANO MANOR
   north -> NOKSTELLA ETERNAL CITY

7. LEYNDELL ROYAL CAPITAL
   south -> ACADEMY OF RAYA LUCARIA
   east  -> DEEPROOT DEPTHS
   north -> MOUNTAINTOPS OF THE GIANTS
   west  -> FRENZIED FLAME PROSCRIPTION

8. DEEPROOT DEPTHS
   west -> LEYNDELL ROYAL CAPITAL

9. MOUNTAINTOPS OF THE GIANTS
   south -> LEYNDELL ROYAL CAPITAL
   east  -> CRUMBLING FARUM AZULA
   north -> CONSECRATED SNOWFIELD

10. CRUMBLING FARUM AZULA
    west -> MOUNTAINTOPS OF THE GIANTS
    east -> PLACIDUSAX ARENA

11. PLACIDUSAX ARENA
    west  -> CRUMBLING FARUM AZULA
    south -> MOHGWYN PALACE

12. MOHGWYN PALACE
    north -> PLACIDUSAX ARENA

13. CONSECRATED SNOWFIELD
    south -> MOUNTAINTOPS OF THE GIANTS
    north -> HALIGTREE

14. HALIGTREE
    south -> CONSECRATED SNOWFIELD
    north -> LEYNDELL ASHEN CAPITAL

15. FRENZIED FLAME PROSCRIPTION
    east -> LEYNDELL ROYAL CAPITAL

16. LEYNDELL ASHEN CAPITAL
    south -> HALIGTREE
    north -> HEART OF THE ERDTREE

17. HEART OF THE ERDTREE
    south -> LEYNDELL ASHEN CAPITAL

7. Special Movement Rules
-------------------------
7.1 Sword rule
The player must take TARNISHED SWORD from STRANDED GRAVEYARD. Without TARNISHED SWORD, the player cannot normally leave the first location.
Exception: If the player has RUNE OF THREE FINGERS, movement restrictions are ignored.

7.2 Leyndell rule
To enter LEYNDELL ROYAL CAPITAL, the player must have MEDALLION.
Exception: If the player has RUNE OF THREE FINGERS, the lock is ignored.

7.3 Haligtree rule
To enter HALIGTREE, the player must have INVERTED MEDALLION.
Exception: If the player has RUNE OF THREE FINGERS, the lock is ignored.

7.4 Farum Azula rule
To enter CRUMBLING FARUM AZULA, the player must have FLAME OF THE GIANTS.
Exception: If the player has RUNE OF THREE FINGERS, the lock is ignored.

7.5 Ashen Capital rule
To enter LEYNDELL ASHEN CAPITAL, the player must have RUNE OF DEATH.
Exception: If the player has RUNE OF THREE FINGERS, the lock is ignored.

7.6 Frenzied Flame Proscription rule
To enter FRENZIED FLAME PROSCRIPTION from LEYNDELL ROYAL CAPITAL, the inventory must be empty. This means the player must drop all items before entering.

Inside this room, the player may take RUNE OF THREE FINGERS.
After taking it:
- it cannot be dropped;
- most locked paths are opened;
- the player is forced into the Frenzied Flame ending unless cleansed.

8. Main Runes
-------------
1. RUNE OF GODRICK
   Location: STORMVEIL CASTLE
   Ending type: Standard TUKE Lord ending

2. RUNE OF RENNALA
   Location: ACADEMY OF RAYA LUCARIA
   Ending type: Standard TUKE Lord ending

3. RUNE OF RADAHN
   Location: RADAHN ARENA
   Ending type: Standard TUKE Lord ending

4. RUNE OF RYKARD
   Location: VOLCANO MANOR
   Ending type: World Serpent ending

5. RUNE OF RANNI
   Location: NOKSTELLA ETERNAL CITY
   Ending type: Age of Stars

6. RUNE OF MOHG
   Location: MOHGWYN PALACE
   Ending type: Bloody Dynasty

7. RUNE OF FIA
   Location: DEEPROOT DEPTHS
   Ending type: Age of Those Who Live in Death

8. RUNE OF MORGOTT
   Location: LEYNDELL ROYAL CAPITAL
   Ending type: Standard TUKE Lord ending

9. RUNE OF THREE FINGERS
   Location: FRENZIED FLAME PROSCRIPTION
   Ending type: Frenzied Flame / Chaos

10. RUNE OF GOLDMASK
    Location: LEYNDELL ASHEN CAPITAL
    Ending type: Perfect Golden Order

11. RUNE OF DEATH
    Location: CRUMBLING FARUM AZULA
    Function: key to LEYNDELL ASHEN CAPITAL

12. RUNE OF DUNG EATER
    Location: LEYNDELL ASHEN CAPITAL
    Ending type: Cursed world

13. RUNE OF MALENIA
    Location: HALIGTREE
    Ending type: Miquella / eternal deception ending

9. Key Items
------------
TARNISHED SWORD
Location: STRANDED GRAVEYARD
Function: required for normal movement after the starting location
Properties: MOVABLE | USABLE | EXAMINABLE

MEDALLION
Location: ACADEMY OF RAYA LUCARIA
Function: key to LEYNDELL ROYAL CAPITAL
Properties: MOVABLE | USABLE | EXAMINABLE

INVERTED MEDALLION
Location: CONSECRATED SNOWFIELD
Function: key to HALIGTREE
Properties: MOVABLE | USABLE | EXAMINABLE

FLAME OF THE GIANTS
Location: MOUNTAINTOPS OF THE GIANTS
Function: key to CRUMBLING FARUM AZULA
Properties: MOVABLE | USABLE | EXAMINABLE

MIQUELLAS NEEDLE
Location: HALIGTREE
Function: can cleanse the Frenzied Flame only in PLACIDUSAX ARENA
Properties: MOVABLE | USABLE | EXAMINABLE

MIQUELLAS CLEANSING
Location: created after using MIQUELLAS NEEDLE in PLACIDUSAX ARENA
Function: prevents forced Frenzied Flame ending
Properties: MOVABLE | EXAMINABLE

10. Stationary Important Objects
--------------------------------
PLACIDUSAX RING
Location: PLACIDUSAX ARENA
Function: place/use MIQUELLAS NEEDLE here to receive MIQUELLAS CLEANSING
Properties: EXAMINABLE

ERDTREE FORGE
Location: HEART OF THE ERDTREE
Function: final place where the chosen rune is used
Properties: EXAMINABLE

11. Lore Items by Location
--------------------------
Each location should have at least one lore item. The descriptions below are written as in-game lore drafts and are paraphrased from Elden Ring wiki lore material.

1. STRANDED GRAVEYARD
   - MAIDENS CORPSE
     Stationary.
     Lore description: The corpse shows the broken link between a Tarnished and the Finger Maiden who should have guided him. Finger Maidens serve the Two Fingers, offer direction to the Tarnished, and transform gathered runes into strength. Here, the Tarnished begins without that sacred support, already separated from the normal path of grace.
   - VETERANS NOTES
     Stationary or movable.
     Lore description: Old notes left by a previous Tarnished. They explain the rules of this adventure: take the sword, collect Great Runes, learn which paths require keys, beware the Three Fingers, and use one chosen rune at the Erdtree Forge to claim an ending.

2. STORMVEIL CASTLE
   - GODWYNS CORPSE
     Stationary.
     Lore description: A corpse-like relic recalling Godwyn the Golden, the demigod whose soul was killed during the Night of the Black Knives. His soulless body became the Prince of Death, spreading Deathroot through the roots beneath the world and giving rise to Those Who Live in Death.

3. ACADEMY OF RAYA LUCARIA
   - ACADEMY NOTES
     Examinable lore item.
     Lore description: Notes about the old astrologers and the birth of glintstone study. The astrologers came before the sorcerers, read fate in the stars, and their legacy survived in the Carian royal line and the scholars of Raya Lucaria. The Academy is therefore not only a school of magic, but a monument to a time when fate was written in the night sky.

4. RADAHN ARENA
   - DEATHROOT
     Examinable lore item.
     Lore description: A blackened root tied to the spread of death after Godwyns burial. Deathroot marks the corruption of the great roots and the return of ancient death-rites. It recalls Tibia Mariners, Those Who Live in Death, Malikeths failure to guard Destined Death, and Fias attempt to give the dead a place within the order of the world.

5. NOKSTELLA ETERNAL CITY
   - RANNIS CORPSE
     Stationary.
     Lore description: The remains symbolize Rannis rejection of her Empyrean flesh. During the Night of the Black Knives, Ranni used a stolen fragment of Destined Death to kill her own body while another demigod died in soul. This act freed her spirit from the control of the Greater Will and opened the road toward the Age of Stars.

6. VOLCANO MANOR
   - TANITHS MASK
     Examinable lore item.
     Lore description: The mask recalls Taniths loyalty to Rykard and Volcano Manors rebellion against the Erdtree. Rykard embraced blasphemy and the God-Devouring Serpent, while Tanith remained devoted to him even after his monstrous transformation. The Manor is therefore a house of recusants who chose rebellion over obedience.

7. LEYNDELL ROYAL CAPITAL
   - MARIKA STATUE
     Stationary.
     Lore description: A statue that carries the forbidden revelation: Radagon is Marika. This secret shakes the foundation of Golden Order theology, because the Order was built around Marika as the one true god, while Radagons identity exposes a contradiction at the heart of that law.

8. DEEPROOT DEPTHS
   - CRUCIBLE ROOT
     Stationary.
     Lore description: A root from the old Crucible, the primordial form of the Erdtree. The Crucible Knights served Godfrey and drew power from a more ancient, chaotic vitality that could manifest horns, tails, wings, and other beast-like forms. What later ages called impure was once sacred life itself.

9. MOUNTAINTOPS OF THE GIANTS
   - GIANTS EYE
     Examinable lore item.
     Lore description: The eye remembers the war against the Fire Giants. Godfrey led Marikas golden armies in that ancient conflict, defeating the giants and confining the Flame of Ruin. The victory helped establish the age of the Erdtree, but it also left the mountaintops as a graveyard of a conquered people.

10. CRUMBLING FARUM AZULA
   - WOLF AND CHILD STATUE
     Stationary.
     Lore description: A statue about Empyreans and their shadows. Empyreans are beings capable of becoming gods of a new age, and some are given shadowbound beasts as protectors and restraints. The wolf beside the child suggests both loyalty and imprisonment: a companion created to guard, but also to enforce the will of the Fingers.

11. PLACIDUSAX ARENA
   - PLACIDUSAX CLAW
     Examinable lore item.
     Lore description: A relic of Dragonlord Placidusax, the lord who waited in the storm beyond time. Placidusax was said to have been Elden Lord before the age of the Erdtree, ruling beside a god that eventually fled. The claw represents a forgotten order older than Marika, still waiting for a vanished divinity to return.

12. MOHGWYN PALACE
   - MIQUELLAS COCOON
     Stationary.
     Lore description: The cocoon recalls Mohgs theft of Miquella from the Haligtree. Miquella created the Haligtree as an alternative to the Erdtree and as a refuge connected to his hope of healing Malenias rot. Mohg tried to raise Miquella into the center of a new Bloody Dynasty, turning devotion into captivity.

13. CONSECRATED SNOWFIELD
   - BLACK KNIFE ARMOR
     Examinable lore item.
     Lore description: Armor of the assassins from the Night of the Black Knives. The Black Knife assassins were women, said to be Numen with close ties to Marika, and they carried blades empowered by stolen Destined Death. Their act shattered the divine family and changed the history of the Lands Between forever.

14. HALIGTREE
   - MALENIAS FLOWER
     Stationary.
     Lore description: The flower represents Malenia, Blade of Miquella and Goddess of Rot. Malenia was born afflicted by Scarlet Rot and remained bound to her brother Miquella, whose Haligtree was tied to the hope of healing or surpassing the limits of the Golden Order. The flower is beautiful, but it blooms from decay.

15. FRENZIED FLAME PROSCRIPTION
   - THREE FINGERS STATUE
     Stationary.
     Lore description: A statue devoted to the Three Fingers, vassals of the Frenzied Flame. Their doctrine rejects division, order, and suffering by burning everything back into one chaotic origin. Shabriri and the Flame do not offer freedom in a gentle sense - they offer the end of all difference, all law, and all selves.

16. LEYNDELL ASHEN CAPITAL
   - GODFREYS CROWN
     Examinable lore item.
     Lore description: A crown recalling Godfrey, First Elden Lord and lord of the battlefield. He led Marikas armies in the war against the Giants and became the first consort of the Golden Order. Yet after his victories were complete, grace left him and he became the first Tarnished - a king turned exile.
   - GOLDMASKS CORPSE
     Stationary.
     Lore description: Before you lies the silent corpse of Goldmask. His finger still points toward the broken Erdtree, as if even death could not interrupt his calculation. In pariete cinereo verba antiqua manent: Ordo non nascitur ex voluntate deorum, sed ex lege pura, frigida et incorrupta. Ubi passio tacet, ibi veritas regnat. Goldmask did not seek mercy, glory, or chaos. He sought a perfect order - law without divine fickleness, without passion, without contradiction.

17. HEART OF THE ERDTREE
   - MARIKAS BODY
     Stationary.
     Lore description: The broken body of Marika stands at the end of the path. Marika was the vessel of the Elden Ring and the center of the Golden Order, yet she shattered the Ring and was punished within the Erdtree. Her body is both throne and prison, origin and ruin, proof that even a god can become a tool of a greater design.

12. Veterans Notes Content
--------------------------
VETERANS NOTES should explain:

- Take the Tarnished Sword before leaving the Stranded Graveyard.
- Collect Great Runes from demigods.
- You need at least three runes to claim the ending.
- Some paths require special key items.
- To enter the Frenzied Flame Proscription, your inventory must be empty.
- The Rune of Three Fingers cannot be dropped.
- Miquellas Needle can cleanse the Frenzied Flame only in Placidusax Arena.
- In the Heart of the Erdtree, use one rune at the Erdtree Forge to choose your ending.

13. Final Room Rules
--------------------
Final room:
HEART OF THE ERDTREE

Stationary objects:
- ERDTREE FORGE
- MARIKAS BODY

To enter the final room normally:
- the player should have at least three runes;
- the player should have reached LEYNDELL ASHEN CAPITAL.

If the player has RUNE OF THREE FINGERS and does not have MIQUELLAS CLEANSING:
- the Frenzied Flame ending starts automatically.

If the player does not have RUNE OF THREE FINGERS, or if the player has MIQUELLAS CLEANSING:
- the player may choose the ending by using one rune:

POUZI RUNE OF GODRICK
POUZI RUNE OF RENNALA
POUZI RUNE OF RADAHN
POUZI RUNE OF MORGOTT
POUZI RUNE OF RANNI
POUZI RUNE OF MOHG
POUZI RUNE OF RYKARD
POUZI RUNE OF FIA
POUZI RUNE OF GOLDMASK
POUZI RUNE OF MALENIA
POUZI RUNE OF DUNG EATER

14. Endings
-----------
14.1 Standard TUKE Lord ending
Triggered by: RUNE OF GODRICK, RUNE OF RENNALA, RUNE OF RADAHN, RUNE OF MORGOTT
Ending text: You became the TUKE Lord, ruler of the Lands Between and servant of the Greater Will.

14.2 Ranni ending
Triggered by: RUNE OF RANNI
Ending text: You became Ranni's consort. The Age of Stars begins, cold and distant, beyond the reach of the Greater Will.

14.3 Mohg ending
Triggered by: RUNE OF MOHG
Ending text: You became the consort of Mohg. The Bloody Dynasty rises, and the Lands Between drown beneath a crimson oath.

14.4 Rykard ending
Triggered by: RUNE OF RYKARD
Ending text: The world serpent awakens. It devours you, the Erdtree and the Lands Between. All becomes one inside the endless hunger.

14.5 Fia ending
Triggered by: RUNE OF FIA
Ending text: You became the lord of those who live in death. The dead are no longer rejected, and the world learns to breathe beside them.

14.6 Goldmask ending
Triggered by: RUNE OF GOLDMASK
Ending text: You restored the Golden Order and forged a colder, perfect law. No god, no passion, no contradiction may bend it again.

14.7 Malenia / Miquella ending
Triggered by: RUNE OF MALENIA
Ending text: You became the consort of Miquella. A world without suffering begins - a world of eternal deception.

14.8 Dung Eater ending
Triggered by: RUNE OF DUNG EATER
Ending text: You became the lord of a cursed world. No soul will be born clean again.

14.9 Frenzied Flame ending
Triggered by: RUNE OF THREE FINGERS and no MIQUELLAS CLEANSING
Ending text: The Frenzied Flame awakens before the Erdtree Forge. The Erdtree and the Lands Between burn to ash. The daughter of the Dark Moon will hunt you beyond the edge of the world. You became chaos itself - a flame that destroys all, hoping to melt the world into something new.

15. Implementation Plan
-----------------------
Do not touch these stable modules unless necessary:
- item.c
- command.c
- container.c
- room.c
- backpack.c
- parser.c
- main.c

Change only:

1. world.c
   - Replace current 15-room world with 17-room Elden Ring TUKE Edition world.
   - Add all runes, key items, stationary objects and lore items.

2. game.c
   - Add movement locks.
   - Add rule for empty inventory when entering FRENZIED FLAME PROSCRIPTION.
   - Add rule that RUNE OF THREE FINGERS cannot be dropped.
   - Add Miquellas Needle cleansing logic in PLACIDUSAX ARENA.
   - Add final ending logic in HEART OF THE ERDTREE.

3. scenario.txt
   - Write successful scenario with at least 25 commands.
   - It should collect enough runes and trigger one ending.

16. Source Note
---------------
The lore descriptions are paraphrased and condensed from Elden Ring wiki material, including pages about Finger Maidens, Godwyn, Deathroot, Ranni and the Night of the Black Knives, Black Knife assassins, Goldmask, Three Fingers, Crucible Knights, Empyreans, Maliketh, Placidusax, Godfrey, Volcano Manor, the astrologers, Miquella, Malenia, and the Haligtree.

The text is adapted for an educational C programming project and is not official Elden Ring writing.
