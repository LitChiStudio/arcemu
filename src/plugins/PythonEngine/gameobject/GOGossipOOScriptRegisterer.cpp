/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2008-2024 <http://www.ArcEmu.org/>
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

#include "StdAfx.h"

#include "GOGossipOOScriptRegisterer.hpp"

#include "Python.h"

#include "gossip/PythonGossipOOScript.hpp"

void GOGossipOOScriptRegisterer::visit( uint32 goId, void *script )
{
	PyObject *p = (PyObject*)script;

	Arcemu::Gossip::Script *gossip = mgr->get_go_gossip( goId );
	if( gossip != NULL )
	{
		PythonGossipOOScript *pythonGossipScript = dynamic_cast< PythonGossipOOScript* >( gossip );
		if( pythonGossipScript != NULL )
		{
			pythonGossipScript->setObject( p );
		}
	}
	else
	{
		mgr->register_go_gossip( goId, new PythonGossipOOScript( p ) );
	}
}
