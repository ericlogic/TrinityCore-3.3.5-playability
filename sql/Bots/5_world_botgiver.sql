DELETE FROM `creature_template` WHERE `entry` = 70000;
INSERT INTO `creature_template`
(`entry`,`difficulty_entry_1`,`difficulty_entry_2`,`difficulty_entry_3`,`KillCredit1`,`KillCredit2`,
`modelid1`,`modelid2`,`modelid3`,`modelid4`,`name`,`subname`,`IconName`,`gossip_menu_id`,`minlevel`,`maxlevel`,`exp`,
`faction`,`npcflag`,`speed_walk`,`speed_run`,`scale`,`rank`,`dmgschool`,`BaseAttackTime`,`RangeAttackTime`,
`BaseVariance`,`RangeVariance`,`unit_class`,`unit_flags`,`unit_flags2`,`dynamicflags`,`family`,`type`,`type_flags`,`lootid`,
`pickpocketloot`,`skinloot`,`PetSpellDataId`,`VehicleId`,`mingold`,`maxgold`,`AIName`,`MovementType`,
`HoverHeight`,`HealthModifier`,`ManaModifier`,`ArmorModifier`,`DamageModifier`,`ExperienceModifier`,`RacialLeader`,`movementId`,`RegenHealth`,
`mechanic_immune_mask`,`spell_school_immune_mask`,`flags_extra`,`ScriptName`,`VerifiedBuild`)
VALUES
('70000','0','0','0','0','0','27541','0','0','0','Lagretta','Bots for hire','','0','83','83','2','35','1','1.4','1.14286','0.7','4','0','0','0','1','1','1','33088','2048','0','0','0','0','0','0','0','0','0','0','0','','0','1','4.8','1','1','1','1','0','0','1','0','0','0','script_bot_giver','-1');

DELETE FROM `npc_text` WHERE `ID` BETWEEN 70201 AND 70204;
INSERT INTO `npc_text` (`ID`,`text0_0`,`VerifiedBuild`) VALUES
('70201','There are always dudes ready to kill for money.','-1'),
('70202','Mercenaries are always in demand. Here is what available right now.','-1'),
('70203','Mercenaries are always in demand. Here is what available right now.','-1'),
('70204','Seems like there is nobody available right now, check again later.','-1');

-- Custom bot givers
DELETE FROM `creature_template` WHERE `entry` between 70700 AND 70799;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `spell_school_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`)
VALUES
(70701, 0, 0, 0, 0, 0, 3289, 0, 0, 0, 'Faithe', 'Bots for hire', '', 0, 30, 30, 2, 35, 1, 1.4, 1.14286, 1, 4, 0, 0, 0, 1, 1, 1, 33088, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 4.8, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 'script_bot_giver', -1),
(70702, 0, 0, 0, 0, 0, 3100, 0, 0, 0, 'Mandel', 'Bots for hire', '', 0, 30, 30, 2, 35, 1, 1.4, 1.14286, 1, 4, 0, 0, 0, 1, 1, 1, 33088, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 4.8, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 'script_bot_giver', -1),
(70703, 0, 0, 0, 0, 0, 2252, 0, 0, 0, 'Dean', 'Bots for hire', '', 0, 30, 30, 2, 35, 1, 1.4, 1.14286, 1, 4, 0, 0, 0, 1, 1, 1, 33088, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 4.8, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 'script_bot_giver', -1),
(70704, 0, 0, 0, 0, 0, 16726, 0, 0, 0, 'Laurel', 'Bots for hire', '', 0, 30, 30, 2, 35, 1, 1.4, 1.14286, 1, 4, 0, 0, 0, 1, 1, 1, 33088, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 4.8, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 'script_bot_giver', -1),
(70705, 0, 0, 0, 0, 0, 2658, 0, 0, 0, 'Zara', 'Bots for hire', '', 0, 30, 30, 2, 35, 1, 1.4, 1.14286, 1, 4, 0, 0, 0, 1, 1, 1, 33088, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 4.8, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 'script_bot_giver', -1),
(70706, 0, 0, 0, 0, 0, 1328, 0, 0, 0, 'Zachary', 'Bots for hire', '', 0, 30, 30, 2, 35, 1, 1.4, 1.14286, 1, 4, 0, 0, 0, 1, 1, 1, 33088, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 4.8, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 'script_bot_giver', -1),
(70707, 0, 0, 0, 0, 0, 2096, 0, 0, 0, 'Moore', 'Bots for hire', '', 0, 30, 30, 2, 35, 1, 1.4, 1.14286, 1, 4, 0, 0, 0, 1, 1, 1, 33088, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 4.8, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 'script_bot_giver', -1),
(70708, 0, 0, 0, 0, 0, 16798, 0, 0, 0, 'Jocelyn', 'Bots for hire', '', 0, 30, 30, 2, 35, 1, 1.4, 1.14286, 1, 4, 0, 0, 0, 1, 1, 1, 33088, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 4.8, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 'script_bot_giver', -1);
