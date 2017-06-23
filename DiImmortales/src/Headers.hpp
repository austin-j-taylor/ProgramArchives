#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <string>
#include <algorithm>
#include <windows.h>

#define windowWidth 100

enum Styles { Slash, Stab, Crush, Bash, Block, Parry, Hurl };
enum Usages { Use, Eat, Equip, Unequip, Examine };
enum Stats { None, Hp, HpMod, MaxHp, Str, StrMod, Def, DefMod, Dex, DexMod, Agil, AgilMod };

#include "text.hpp"

#include "Item\Effect\Effect.hpp"
#include "Item\Effect\ActiveEffects.hpp"
#include "Item\Effect\Stunned.hpp"
#include "Item\Effect\Dazed.hpp"
#include "Item\Effect\Bleeding.hpp"
#include "Item\Effect\Poisoned.hpp"

#include "Item\Style\Style.hpp"

#include "Item\Usage\Usage.hpp"

#include "Item\Material\Material.hpp"
#include "Item\Material\Basic.hpp"
#include "Item\Material\Wooden.hpp"
#include "Item\Material\Bronze.hpp"
#include "Item\Material\Steel.hpp"

#include "Item\Item.hpp"
#include "Item\Bag.hpp"

#include "Item\Consumable\Consumable.hpp"
#include "Item\Consumable\Apple.hpp"

#include "Item\Weapon\Weapon.hpp"
#include "Item\Weapon\Melee\Dagger.hpp"
#include "Item\Weapon\Melee\HumanFist.hpp"
#include "Item\Weapon\Melee\Longsword.hpp"
#include "Item\Shield\Shield.hpp"
#include "Item\Shield\Buckler\Buckler.hpp"
#include "Item\Item\Rock.hpp"

#include "Character\Character.hpp"

#include "Story\Screen\GameOver.hpp"
#include "Story\Screen\Menu.hpp"

#include "Story\Scene.hpp"
#include "Story\Scenes\Intro.hpp"

#include "Character\Human.hpp"
#include "Character\Player.hpp"
#include "Character\Bourgeoisie.hpp"


#include "Field\Field.hpp"
#include "Field\CombatField.hpp"

