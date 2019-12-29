/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2008-2019 <http://www.ArcEmu.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _MESSENGER_H
#define _MESSENGER_H

class Object;

class Messenger
{
public:
	/// Log miss, block, etc for spell based attacks in the client
	static void SendSpellLog( Object* Caster, Object* Target, uint32 Ability, uint8 SpellLogType );

	/// Log spell damage in the client
	static void SendSpellNonMeleeDamageLog( Object* Caster, Object* Target, uint32 SpellID, uint32 Damage, uint8 School, uint32 AbsorbedDamage, uint32 ResistedDamage, bool PhysicalDamage, uint32 BlockedDamage, bool CriticalHit, bool bToSet );

	/// Log melee damage in the client
	static void SendAttackerStateUpdate( Object* Caster, Object* Target, dealdamage* Dmg, uint32 Damage, uint32 Abs, uint32 BlockedDamage, uint32 HitStatus, uint32 VState );

	/// Plays a sound effect to the players around the object
	static void PlaySoundToSet( Object* object, uint32 sound_entry );

	/// Send AI reaction to client ("aggro sound" like growling)
	static void SendAIReaction( Object* object, uint32 reaction = 2 );

	/// Destroys this Object for the players' clients that are nearby ( client removes object from the screen )
	static void SendDestroyObjectToSet( Object* object );

	/// Sends a gameobject animation to the player
	static void SendGameObjectCustomAnim( GameObject* go, uint32 anim, Player* player );

	/// Sends the gameobject despawn animation. Removes gameobject from client screen.
	static void SendGameObjectDespawnAnim( GameObject *go );

	/// Destructible building damage. Notifies the surrounding clients about the GameObject taking damage.
	static void SendBuildingDamageToSet( GameObject* go, uint32 damage, uint64 AttackerGUID, uint64 ControllerGUID, uint32 SpellID );
};

#endif
