/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// This is where scripts' loading functions should be declared:
void AddSC_craftsman_text_manager();
void AddSC_craftsman_recipe_loader();

void AddSC_npc_craftsman_tailor();
void AddSC_npc_craftsman_miner();
void AddSC_npc_craftsman_blacksmith();

// The name of this function should match:
// void Add${NameOfDirectory}Scripts()
void AddCraftsmanScripts()
{
    AddSC_craftsman_text_manager();
    AddSC_craftsman_recipe_loader();

    AddSC_npc_craftsman_tailor();
    AddSC_npc_craftsman_miner();
    AddSC_npc_craftsman_blacksmith();
}
