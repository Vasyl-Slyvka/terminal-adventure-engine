#include <stdlib.h>

#include "world.h"
#include "item.h"

static int add_room_checked(struct container** world, struct room* room){
    if(world == NULL || room == NULL){
        return 0;
    }

    struct container* created_container = add_room_to_world(*world, room);

    if(created_container == NULL){
        return 0;
    }

    if(*world == NULL){
        *world = created_container;
    }

    return 1;
}

static void add_item_checked(struct room* room, struct item* item){
    if(room == NULL || item == NULL){
        if(item != NULL){
            destroy_item(item);
        }

        return;
    }

    if(add_item_to_room(room, item) == false){
        (void)destroy_item(item);
    }
}

struct container* add_room_to_world(struct container* world, struct room* room){
    if(room == NULL){
        return NULL;
    }

    if(world != NULL && get_room(world, room->name) != NULL){
        return NULL;
    }

    return create_container(world, ROOM, room);
}

struct room* get_room(struct container* world, const char* name){
    if(world == NULL || name == NULL){
        return NULL;
    }

    return get_from_container_by_name(world, name);
}

struct container* create_world(void){
    struct container* world = NULL;

    struct room* stranded_graveyard = create_room(
        "STRANDED GRAVEYARD",
        "You awaken in the Stranded Graveyard. The air is cold, the stone is wet, and the call of grace is almost silent here."
    );

    struct room* stormveil_castle = create_room(
        "STORMVEIL CASTLE",
        "Stormveil Castle rises above the cliffs, broken by war and pride. The first shardbearer waits among the old stones."
    );

    struct room* academy = create_room(
        "ACADEMY OF RAYA LUCARIA",
        "The Academy of Raya Lucaria stands over the lake, filled with old glintstone knowledge and cold ambition."
    );

    struct room* radahn_arena = create_room(
        "RADAHN ARENA",
        "A red battlefield stretches beneath a dying sky. The sand still remembers Radahn's festival."
    );

    struct room* nokstella = create_room(
        "NOKSTELLA ETERNAL CITY",
        "Nokstella sleeps under false stars. Silver tears, old knives, and forgotten lunar oaths haunt the city."
    );

    struct room* volcano_manor = create_room(
        "VOLCANO MANOR",
        "Volcano Manor rejects the Erdtree. Its walls are warm with blasphemy, rebellion, and the hunger of a serpent."
    );

    struct room* leyndell = create_room(
        "LEYNDELL ROYAL CAPITAL",
        "Leyndell, the Royal Capital, still shines beneath the Erdtree, but its golden order is cracked from within."
    );

    struct room* deeproot = create_room(
        "DEEPROOT DEPTHS",
        "Deeproot Depths lie beneath the Erdtree, where deathroot twists around the corpse of a murdered demigod."
    );

    struct room* mountaintops = create_room(
        "MOUNTAINTOPS OF THE GIANTS",
        "The frozen mountaintops hold the memory of giants, fire, and the last war against the flame."
    );

    struct room* farum_azula = create_room(
        "CRUMBLING FARUM AZULA",
        "Crumbling Farum Azula floats outside ordinary time. Beasts, dragons, and broken storms remain here."
    );

    struct room* placidusax_arena = create_room(
        "PLACIDUSAX ARENA",
        "The heart of the storm bends around the ancient dragonlord. Time itself seems wounded in this arena."
    );

    struct room* mohgwyn_palace = create_room(
        "MOHGWYN PALACE",
        "Mohgwyn Palace is drowned in blood-red devotion. A stolen cocoon rests at the center of a dynasty yet unborn."
    );

    struct room* snowfield = create_room(
        "CONSECRATED SNOWFIELD",
        "The Consecrated Snowfield is white, silent, and almost unreal. Hidden paths lead toward the Haligtree."
    );

    struct room* haligtree = create_room(
        "HALIGTREE",
        "The Haligtree is a wounded sanctuary. It promises mercy, but its roots drink rot, devotion, and deception."
    );

    struct room* frenzied_proscription = create_room(
        "FRENZIED FLAME PROSCRIPTION",
        "Far below Leyndell, the Frenzied Flame whispers from a sealed tomb. To enter, one must abandon everything."
    );

    struct room* ashen_capital = create_room(
        "LEYNDELL ASHEN CAPITAL",
        "Leyndell is now an Ashen Capital. Gold is buried under grey dust, and the road to the Erdtree is open."
    );

    struct room* heart_erdtree = create_room(
        "HEART OF THE ERDTREE",
        "You stand inside the Heart of the Erdtree. The Erdtree Forge waits for one final rune and one final choice."
    );

    if(stranded_graveyard == NULL || stormveil_castle == NULL || academy == NULL ||
       radahn_arena == NULL || nokstella == NULL || volcano_manor == NULL ||
       leyndell == NULL || deeproot == NULL || mountaintops == NULL ||
       farum_azula == NULL || placidusax_arena == NULL || mohgwyn_palace == NULL ||
       snowfield == NULL || haligtree == NULL || frenzied_proscription == NULL ||
       ashen_capital == NULL || heart_erdtree == NULL){
        stranded_graveyard = destroy_room(stranded_graveyard);
        stormveil_castle = destroy_room(stormveil_castle);
        academy = destroy_room(academy);
        radahn_arena = destroy_room(radahn_arena);
        nokstella = destroy_room(nokstella);
        volcano_manor = destroy_room(volcano_manor);
        leyndell = destroy_room(leyndell);
        deeproot = destroy_room(deeproot);
        mountaintops = destroy_room(mountaintops);
        farum_azula = destroy_room(farum_azula);
        placidusax_arena = destroy_room(placidusax_arena);
        mohgwyn_palace = destroy_room(mohgwyn_palace);
        snowfield = destroy_room(snowfield);
        haligtree = destroy_room(haligtree);
        frenzied_proscription = destroy_room(frenzied_proscription);
        ashen_capital = destroy_room(ashen_capital);
        heart_erdtree = destroy_room(heart_erdtree);

        return NULL;
    }

    if(add_room_checked(&world, stranded_graveyard) == 0 ||
       add_room_checked(&world, stormveil_castle) == 0 ||
       add_room_checked(&world, academy) == 0 ||
       add_room_checked(&world, radahn_arena) == 0 ||
       add_room_checked(&world, nokstella) == 0 ||
       add_room_checked(&world, volcano_manor) == 0 ||
       add_room_checked(&world, leyndell) == 0 ||
       add_room_checked(&world, deeproot) == 0 ||
       add_room_checked(&world, mountaintops) == 0 ||
       add_room_checked(&world, farum_azula) == 0 ||
       add_room_checked(&world, placidusax_arena) == 0 ||
       add_room_checked(&world, mohgwyn_palace) == 0 ||
       add_room_checked(&world, snowfield) == 0 ||
       add_room_checked(&world, haligtree) == 0 ||
       add_room_checked(&world, frenzied_proscription) == 0 ||
       add_room_checked(&world, ashen_capital) == 0 ||
       add_room_checked(&world, heart_erdtree) == 0){
        world = destroy_world(world);
        return NULL;
    }

    set_exits_from_room(stranded_graveyard, stormveil_castle, NULL, NULL, NULL);

    set_exits_from_room(stormveil_castle, academy, stranded_graveyard, radahn_arena, NULL);
    set_exits_from_room(academy, leyndell, stormveil_castle, NULL, nokstella);
    set_exits_from_room(radahn_arena, NULL, NULL, NULL, stormveil_castle);

    set_exits_from_room(nokstella, NULL, volcano_manor, academy, NULL);
    set_exits_from_room(volcano_manor, nokstella, NULL, NULL, NULL);

    set_exits_from_room(leyndell, mountaintops, academy, deeproot, frenzied_proscription);
    set_exits_from_room(deeproot, NULL, NULL, NULL, leyndell);

    set_exits_from_room(mountaintops, snowfield, leyndell, farum_azula, NULL);
    set_exits_from_room(farum_azula, NULL, NULL, placidusax_arena, mountaintops);
    set_exits_from_room(placidusax_arena, NULL, mohgwyn_palace, NULL, farum_azula);
    set_exits_from_room(mohgwyn_palace, placidusax_arena, NULL, NULL, NULL);

    set_exits_from_room(snowfield, haligtree, mountaintops, NULL, NULL);
    set_exits_from_room(haligtree, ashen_capital, snowfield, NULL, NULL);

    set_exits_from_room(frenzied_proscription, NULL, NULL, leyndell, NULL);

    set_exits_from_room(ashen_capital, heart_erdtree, haligtree, NULL, NULL);
    set_exits_from_room(heart_erdtree, NULL, ashen_capital, NULL, NULL);

    add_item_checked(stranded_graveyard, create_item(
        "TARNISHED SWORD",
        "A simple sword left for a nameless Tarnished. Without it, the road beyond the graveyard is almost impossible.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(stranded_graveyard, create_item(
        "VETERANS NOTES",
        "The notes say: Take the Tarnished Sword. Collect at least three Great Runes. Some roads need special items. To enter the Frenzied Flame Proscription, your inventory must be empty. The Rune of Three Fingers cannot be dropped. Miquellas Needle can cleanse the flame only in Placidusax Arena. In the Heart of the Erdtree, use one rune to choose your ending.",
        MOVABLE | EXAMINABLE
    ));

    add_item_checked(stranded_graveyard, create_item(
        "MAIDENS CORPSE",
        "A dead maiden lies near the first grace. Finger Maidens were meant to guide the Tarnished, read the will of the Two Fingers, and turn runes into strength. This one never reached her champion.",
        EXAMINABLE
    ));

    add_item_checked(stormveil_castle, create_item(
        "RUNE OF GODRICK",
        "A Great Rune held by Godrick the Grafted. It is weak compared to the oldest powers, but it is still a shard of the Elden Ring.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(stormveil_castle, create_item(
        "GODWYNS CORPSE",
        "The corpse reminds you of Godwyn the Golden, the first demigod to die in soul during the Night of the Black Knives. From that death, deathroot began to spread through the Lands Between.",
        EXAMINABLE
    ));

    add_item_checked(academy, create_item(
        "RUNE OF RENNALA",
        "A Great Rune tied to Rennala and the mystery of rebirth. It smells faintly of moonlight and old glintstone.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(academy, create_item(
        "MEDALLION",
        "A medallion marked with the road to Leyndell. It can open the way toward the Royal Capital.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(academy, create_item(
        "ACADEMY NOTES",
        "These notes describe astrologers who looked into the night sky before the age of the Erdtree. Their study of stars became glintstone sorcery and later the pride of Raya Lucaria.",
        MOVABLE | EXAMINABLE
    ));

    add_item_checked(radahn_arena, create_item(
        "RUNE OF RADAHN",
        "A Great Rune of Radahn, the starscourge. Its power still feels heavy, like gravity itself is chained to it.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(radahn_arena, create_item(
        "DEATHROOT",
        "A twisted root of death. It recalls Tibia Mariners, the spread of Those Who Live in Death, Maliketh's stolen Rune of Death, and Fia's dream of a place for the dead.",
        MOVABLE | EXAMINABLE
    ));

    add_item_checked(nokstella, create_item(
        "RUNE OF RANNI",
        "A cold lunar rune. It points away from the Greater Will and toward the distant Age of Stars.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(nokstella, create_item(
        "RANNIS CORPSE",
        "This empty body recalls the Night of the Black Knives. Ranni cast away her flesh to escape the fate imposed on Empyreans, leaving only a dead shell behind.",
        EXAMINABLE
    ));

    add_item_checked(volcano_manor, create_item(
        "RUNE OF RYKARD",
        "A blasphemous rune of Rykard. It pulses like something swallowed but not yet digested.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(volcano_manor, create_item(
        "TANITHS MASK",
        "The mask remembers Tanith and Volcano Manor, where rebellion against the Erdtree turned into worship of the serpent and the will to devour the gods themselves.",
        MOVABLE | EXAMINABLE
    ));

    add_item_checked(leyndell, create_item(
        "RUNE OF MORGOTT",
        "A Great Rune of Morgott, the last king of Leyndell. It carries loyalty, shame, and a desperate love for the order that rejected him.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(leyndell, create_item(
        "MARIKA STATUE",
        "A broken statue of Marika stands in silence. A hidden truth is carved behind it: Radagon is Marika.",
        EXAMINABLE
    ));

    add_item_checked(deeproot, create_item(
        "RUNE OF FIA",
        "A rune of deathly embrace. It offers a future where Those Who Live in Death are no longer rejected by the order of the world.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(deeproot, create_item(
        "CRUCIBLE ROOT",
        "This ancient root speaks of the Crucible, the primordial form of life before the Erdtree. Crucible Knights still bear that older, wilder sacred power.",
        EXAMINABLE
    ));

    add_item_checked(mountaintops, create_item(
        "FLAME OF THE GIANTS",
        "A fire that survived the war of the giants. It can burn a path toward Farum Azula.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(mountaintops, create_item(
        "GIANTS EYE",
        "A giant eye rests frozen in the snow. It remembers Godfrey's war against the giants and the fear that their flame could burn the Erdtree.",
        MOVABLE | EXAMINABLE
    ));

    add_item_checked(farum_azula, create_item(
        "RUNE OF DEATH",
        "A fragment of destined death. Without it, the Ashen Capital remains unreachable.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(farum_azula, create_item(
        "WOLF AND CHILD STATUE",
        "The statue shows a child beside a shadow-beast. Empyreans were given shadows by the Two Fingers, protectors that could also become prisons.",
        EXAMINABLE
    ));

    add_item_checked(placidusax_arena, create_item(
        "PLACIDUSAX RING",
        "A ring of ancient stone in the storm. Miquellas Needle can be used here to silence the Frenzied Flame.",
        EXAMINABLE
    ));

    add_item_checked(placidusax_arena, create_item(
        "PLACIDUSAX CLAW",
        "The claw belongs to the ancient Dragonlord Placidusax, who once served a god before the age of the Erdtree and waited beyond time for its return.",
        MOVABLE | EXAMINABLE
    ));

    add_item_checked(mohgwyn_palace, create_item(
        "RUNE OF MOHG",
        "A blood-soaked rune of Mohg. It promises a dynasty born from obsession, blood, and stolen divinity.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(mohgwyn_palace, create_item(
        "MIQUELLAS COCOON",
        "The cocoon of Miquella rests in the palace. Mohg stole the sleeping Empyrean, hoping to become his consort and raise a bloody dynasty.",
        EXAMINABLE
    ));

    add_item_checked(snowfield, create_item(
        "INVERTED MEDALLION",
        "A secret medallion leading through hidden snow toward the Haligtree.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(snowfield, create_item(
        "BLACK KNIFE ARMOR",
        "The armor belonged to the Black Knife assassins. Their blades killed Godwyn's soul, and many of them were said to be Numen women close to Marika's people.",
        MOVABLE | EXAMINABLE
    ));

    add_item_checked(haligtree, create_item(
        "RUNE OF MALENIA",
        "A rune of Malenia, marked by rot and undefeated pride. It carries both devotion and decay.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(haligtree, create_item(
        "MIQUELLAS NEEDLE",
        "A delicate needle of unalloyed gold. In the right place, it can resist the influence of an outer god and cleanse the Frenzied Flame.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(haligtree, create_item(
        "MALENIAS FLOWER",
        "A scarlet flower blooms in the Haligtree. It tells of Malenia, the Blade of Miquella, and the rot that made her both saint and catastrophe.",
        EXAMINABLE
    ));

    add_item_checked(frenzied_proscription, create_item(
        "RUNE OF THREE FINGERS",
        "A burning rune of the Three Fingers. Once taken, it cannot be dropped. It opens locked roads, but it forces the path of chaos unless cleansed.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(frenzied_proscription, create_item(
        "THREE FINGERS STATUE",
        "The statue radiates madness. It speaks of Shabriri, the Three Fingers, and the Frenzied Flame that wants to melt all suffering, all order, and all life into one fire.",
        EXAMINABLE
    ));

    add_item_checked(ashen_capital, create_item(
        "RUNE OF GOLDMASK",
        "A rune of perfect order. It seeks law beyond emotion, weakness, and contradiction.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(ashen_capital, create_item(
        "RUNE OF DUNG EATER",
        "A cursed rune of the Dung Eater. It promises a world where every soul is born defiled.",
        MOVABLE | USABLE | EXAMINABLE
    ));

    add_item_checked(ashen_capital, create_item(
        "GODFREYS CROWN",
        "The crown recalls Godfrey, first Elden Lord, whose conquests built the age of the Erdtree before grace was taken from him.",
        MOVABLE | EXAMINABLE
    ));

    add_item_checked(ashen_capital, create_item(
        "GOLDMASKS CORPSE",
        "Goldmask's silent corpse points toward the broken order. On the ash-covered wall is written: Ordo non nascitur ex voluntate deorum, sed ex lege pura, frigida et incorrupta. Ubi passio tacet, ibi veritas regnat. Order is not born from the will of gods, but from pure, cold and incorruptible law. Where passion is silent, truth reigns.",
        EXAMINABLE
    ));

    add_item_checked(heart_erdtree, create_item(
        "ERDTREE FORGE",
        "The Erdtree Forge waits for the chosen rune. Here the Tarnished may decide the final shape of the world.",
        EXAMINABLE
    ));

    add_item_checked(heart_erdtree, create_item(
        "MARIKAS BODY",
        "Marika's broken body hangs at the center of the order she shattered. Her silence is heavier than any command of the Greater Will.",
        EXAMINABLE
    ));

    return world;
}

struct container* destroy_world(struct container* world){
    return destroy_containers(world);
}
