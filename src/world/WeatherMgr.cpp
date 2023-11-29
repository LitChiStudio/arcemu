/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2008-2012 <http://www.ArcEmu.org/>
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

initialiseSingleton(WeatherMgr);

WeatherMgr::WeatherMgr()
{
}

WeatherMgr::~WeatherMgr()
{
	std::map<uint32, WeatherInfo*>::iterator itr;
	for(itr = m_zoneWeathers.begin(); itr != m_zoneWeathers.end(); itr++)
	{
		delete itr->second;
	}

	m_zoneWeathers.clear();
}

void WeatherMgr::LoadFromDB()
{
	//sLog.outString("  Loading Weather..."); // weather type 0= sunny / 1= fog / 2 = light_rain / 4 = rain / 8 = snow / ?? = sandstorm
	QueryResult* result = WorldDatabase.Query("SELECT zoneId,high_chance,high_type,med_chance,med_type,low_chance,low_type FROM weather");

	if(!result)
		return;

	do
	{
		Field* fields = result->Fetch();
		WeatherInfo* wi = new WeatherInfo;
		wi->m_zoneId = fields[0].GetUInt32();
		wi->m_effectValues[0] = fields[1].GetUInt32();  // high_chance
		wi->m_effectValues[1] = fields[2].GetUInt32();  // high_type
		wi->m_effectValues[2] = fields[3].GetUInt32();  // med_chance
		wi->m_effectValues[3] = fields[4].GetUInt32();  // med_type
		wi->m_effectValues[4] = fields[5].GetUInt32();  // low_chance
		wi->m_effectValues[5] = fields[6].GetUInt32();  // low_type
		m_zoneWeathers[wi->m_zoneId] = wi;

		wi->_GenerateWeather();
	}
	while(result->NextRow());
	Log.Notice("WeatherMgr", "Loaded weather information for %u zones.", result->GetRowCount());

	delete result;
}

void WeatherMgr::SendWeather(Player* plr)  //Update weather when player has changed zone (WorldSession::HandleZoneUpdateOpcode)
{
	std::map<uint32, WeatherInfo*>::iterator itr;
	itr = m_zoneWeathers.find(plr->GetZoneId());

	if(itr == m_zoneWeathers.end())
	{
		WorldPacket data(SMSG_WEATHER, 9);
		WeatherPacketBuilder builder( 0, 0 );
		builder.buildPacket( data );
		plr->GetSession()->SendPacket(&data);
		plr->m_lastSeenWeather = 0;

		return;
	}
	else
	{
		itr->second->SendUpdate(plr);
	}
}
