--
SET @OGUID := 55259; -- Need 46
SET @EVENT := 24;

DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+45;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(@OGUID+0, 195256, 571, 3711, 4284, 1, 1, 5575.6259765625, 5710.97119140625, -76.6946334838867187, 5.35816192626953125, 0, 0, -0.446197509765625, 0.894934535026550292, 120, 255, 1, 0), -- Standing, Exterior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+1, 195266, 571, 3711, 4284, 1, 1, 5550.9208984375, 5732.02978515625, -72.8947296142578125, 5.742135047912597656, 0, 0, -0.26723766326904296, 0.96363067626953125, 120, 255, 1, 0), -- Hanging, Streamer - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+2, 195266, 571, 3711, 4284, 1, 1, 5544.88623046875, 5730.65380859375, -72.8956222534179687, 4.1538848876953125, 0, 0, -0.8746194839477539, 0.484810054302215576, 120, 255, 1, 0), -- Hanging, Streamer - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+3, 195256, 571, 3711, 4284, 1, 1, 5547.86279296875, 5726.3916015625, -76.0391387939453125, 4.502951622009277343, 0, 0, -0.7771453857421875, 0.629321098327636718, 120, 255, 1, 0), -- Standing, Exterior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+4, 195266, 571, 3711, 4284, 1, 1, 5549.515625, 5738.0556640625, -72.9350662231445312, 0.994837164878845214, 0, 0, 0.477158546447753906, 0.878817260265350341, 120, 255, 1, 0), -- Hanging, Streamer - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+5, 195264, 571, 3711, 4284, 1, 1, 5543.533203125, 5732.81884765625, -75.006072998046875, 4.45059061050415039, 0, 0, -0.79335308074951171, 0.608761727809906005, 120, 255, 1, 0), -- Standing, Interior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+6, 195266, 571, 3711, 4284, 1, 1, 5543.41943359375, 5736.71630859375, -72.8888320922851562, 2.583080768585205078, 0, 0, 0.961260795593261718, 0.275640487670898437, 120, 255, 1, 0), -- Hanging, Streamer - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+7, 195256, 571, 3711, 4284, 1, 1, 5538.6083984375, 5734.04248046875, -76.7061233520507812, 3.316144466400146484, 0, 0, -0.99619388580322265, 0.087165042757987976, 120, 255, 1, 0), -- Standing, Exterior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+8, 195256, 571, 3711, 4284, 1, 1, 5594.93408203125, 5715.6484375, -72.77392578125, 4.084071159362792968, 0, 0, -0.8910064697265625, 0.453990638256072998, 120, 255, 1, 0), -- Standing, Exterior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+9, 195266, 571, 3711, 4284, 1, 1, 5584.953125, 5748.9140625, -68.31658935546875, 3.281238555908203125, 0, 0, -0.99756336212158203, 0.069766148924827575, 120, 255, 1, 0), -- Hanging, Streamer - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+10, 195256, 571, 3711, 4284, 1, 1, 5565.49072265625, 5758.58251953125, -75.2259063720703125, 5.794494152069091796, 0, 0, -0.24192142486572265, 0.970295846462249755, 120, 255, 1, 0), -- Standing, Exterior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+11, 195264, 571, 3711, 4284, 1, 1, 5558.14453125, 5760.76123046875, -76.66796875, 2.286378860473632812, 0, 0, 0.909960746765136718, 0.414694398641586303, 120, 255, 1, 0), -- Standing, Interior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+12, 195260, 571, 3711, 4284, 1, 1, 5547.07373046875, 5741.958984375, -75.4053497314453125, 0.820303261280059814, 0, 0, 0.398748397827148437, 0.917060375213623046, 120, 255, 1, 0), -- Standing, Interior, Small - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+13, 195264, 571, 3711, 4284, 1, 1, 5546.4443359375, 5741.97412109375, -75.4053497314453125, 3.560472726821899414, 0, 0, -0.97814750671386718, 0.207912087440490722, 120, 255, 1, 0), -- Standing, Interior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+14, 195264, 571, 3711, 4284, 1, 1, 5564.951171875, 5763.7421875, -74.1049652099609375, 4.293513298034667968, 0, 0, -0.8386697769165039, 0.544640243053436279, 120, 255, 1, 0), -- Standing, Interior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+15, 195266, 571, 3711, 4284, 1, 1, 5569.91650390625, 5759.85791015625, -69.3228530883789062, 4.677483558654785156, 0, 0, -0.71933937072753906, 0.694658815860748291, 120, 255, 1, 0), -- Hanging, Streamer - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+16, 195256, 571, 3711, 4284, 1, 1, 5581.7734375, 5765.79248046875, -74.648590087890625, 5.061456203460693359, 0, 0, -0.57357597351074218, 0.819152355194091796, 120, 255, 1, 0), -- Standing, Exterior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+17, 195256, 571, 3711, 4284, 1, 1, 5584.72509765625, 5752.109375, -72.0627365112304687, 3.612837791442871093, 0, 0, -0.97236919403076171, 0.233448356389999389, 120, 255, 1, 0), -- Standing, Exterior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+19, 195264, 571, 3711, 4284, 1, 1, 5592.455078125, 5748.15673828125, -70.1986236572265625, 0.453785061836242675, 0, 0, 0.224950790405273437, 0.974370121955871582, 120, 255, 1, 0), -- Standing, Interior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+20, 195260, 571, 3711, 4284, 1, 1, 5591.068359375, 5747.46630859375, -70.5360488891601562, 2.059488296508789062, 0, 0, 0.857167243957519531, 0.515038192272186279, 120, 255, 1, 0), -- Standing, Interior, Small - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+21, 195264, 571, 3711, 4284, 1, 1, 5565.40087890625, 5770.0302734375, -74.0870285034179687, 5.6897735595703125, 0, 0, -0.29237174987792968, 0.956304728984832763, 120, 255, 1, 0), -- Standing, Interior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+22, 195266, 571, 3711, 4284, 1, 1, 5562.83837890625, 5767.767578125, -69.3107070922851562, 3.036838293075561523, 0, 0, 0.998628616333007812, 0.052353221923112869, 120, 255, 1, 0), -- Hanging, Streamer - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+23, 195260, 571, 3711, 4284, 1, 1, 5555.88525390625, 5763.05224609375, -76.6834869384765625, 3.90954136848449707, 0, 0, -0.92718315124511718, 0.37460830807685852, 120, 255, 1, 0), -- Standing, Interior, Small - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+24, 195266, 571, 3711, 4284, 1, 1, 5577.76123046875, 5766.7099609375, -69.3400802612304687, 6.230826377868652343, 0, 0, -0.02617645263671875, 0.999657332897186279, 120, 255, 1, 0), -- Hanging, Streamer - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+25, 195260, 571, 3711, 4284, 1, 1, 5564.96337890625, 5765.20947265625, -74.1218185424804687, 6.265733242034912109, 0, 0, -0.00872611999511718, 0.999961912631988525, 120, 255, 1, 0), -- Standing, Interior, Small - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+26, 195266, 571, 3711, 4284, 1, 1, 5570.90087890625, 5774.63525390625, -69.3967971801757812, 1.448621988296508789, 0, 0, 0.662619590759277343, 0.748956084251403808, 120, 255, 1, 0), -- Hanging, Streamer - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+27, 195256, 571, 3711, 4284, 1, 1, 5623.017578125, 5797.69189453125, -71.1530685424804687, 1.605701684951782226, 0, 0, 0.719339370727539062, 0.694658815860748291, 120, 255, 1, 0), -- Standing, Exterior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+28, 195256, 571, 3711, 4284, 1, 1, 5590.330078125, 5779.95458984375, -71.8887252807617187, 5.672322273254394531, 0, 0, -0.3007049560546875, 0.953717231750488281, 120, 255, 1, 0), -- Standing, Exterior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+29, 195256, 571, 3711, 4284, 1, 1, 5533.6171875, 5764.57275390625, -78.6415481567382812, 0.802850961685180664, 0, 0, 0.390730857849121093, 0.920504987239837646, 120, 255, 1, 0), -- Standing, Exterior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+30, 195256, 571, 3711, 4284, 1, 1, 5591.7470703125, 5812.30810546875, -69.8521499633789062, 1.570795774459838867, 0, 0, 0.707106590270996093, 0.707106947898864746, 120, 255, 1, 0), -- Standing, Exterior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+31, 195256, 571, 3711, 4284, 1, 1, 5609.3271484375, 5807.85888671875, -70.49896240234375, 0.645771682262420654, 0, 0, 0.317304611206054687, 0.948323667049407958, 120, 255, 1, 0), -- Standing, Exterior, Medium - Brewfest (Area: Nesingwary Base Camp - Difficulty: 0) CreateObject1
(@OGUID+32, 195260, 571, 3711, 4383, 1, 1, 5479.8720703125, 4726.02978515625, -194.349822998046875, 4.049167633056640625, 0, 0, -0.89879322052001953, 0.438372820615768432, 120, 255, 1, 0), -- Standing, Interior, Small - Brewfest (Area: Lakeside Landing - Difficulty: 0) CreateObject1
(@OGUID+33, 195256, 571, 3711, 4383, 1, 1, 5478.01904296875, 4730.70654296875, -195.108367919921875, 0.785396754741668701, 0, 0, 0.38268280029296875, 0.923879802227020263, 120, 255, 1, 0), -- Standing, Exterior, Medium - Brewfest (Area: Lakeside Landing - Difficulty: 0) CreateObject1
(@OGUID+34, 195256, 571, 3711, 4383, 1, 1, 5480.52197265625, 4749.84375, -197.169540405273437, 5.654868602752685546, 0, 0, -0.30901622772216796, 0.95105677843093872, 120, 255, 1, 0), -- Standing, Exterior, Medium - Brewfest (Area: Lakeside Landing - Difficulty: 0) CreateObject1
(@OGUID+35, 195259, 571, 3711, 4383, 1, 1, 5482.611328125, 4728.69482421875, -191.631149291992187, 1.221729278564453125, 0, 0, 0.573575973510742187, 0.819152355194091796, 120, 255, 1, 0), -- Hanging, Square, Small - Brewfest (Area: Lakeside Landing - Difficulty: 0) CreateObject1
(@OGUID+36, 195260, 571, 3711, 4383, 1, 1, 5509.4775390625, 4741.9794921875, -194.433822631835937, 2.111847877502441406, 0, 0, 0.870355606079101562, 0.492423713207244873, 120, 255, 1, 0), -- Standing, Interior, Small - Brewfest (Area: Lakeside Landing - Difficulty: 0) CreateObject1
(@OGUID+37, 195260, 571, 3711, 4383, 1, 1, 5510.404296875, 4753.5478515625, -194.433822631835937, 3.804818391799926757, 0, 0, -0.94551849365234375, 0.325568377971649169, 120, 255, 1, 0), -- Standing, Interior, Small - Brewfest (Area: Lakeside Landing - Difficulty: 0) CreateObject1
(@OGUID+38, 195256, 571, 3711, 4383, 1, 1, 5489.2490234375, 4730.6259765625, -194.757522583007812, 1.186823248863220214, 0, 0, 0.559192657470703125, 0.829037725925445556, 120, 255, 1, 0), -- Standing, Exterior, Medium - Brewfest (Area: Lakeside Landing - Difficulty: 0) CreateObject1
(@OGUID+39, 195260, 571, 3711, 4383, 1, 1, 5502.95654296875, 4741.2734375, -194.433822631835937, 1.32644820213317871, 0, 0, 0.615660667419433593, 0.788011372089385986, 120, 255, 1, 0), -- Standing, Interior, Small - Brewfest (Area: Lakeside Landing - Difficulty: 0) CreateObject1
(@OGUID+40, 195256, 571, 3711, 4383, 1, 1, 5480.35498046875, 4744.158203125, -196.428298950195312, 0.087265998125076293, 0, 0, 0.043619155883789062, 0.999048233032226562, 120, 255, 1, 0), -- Standing, Exterior, Medium - Brewfest (Area: Lakeside Landing - Difficulty: 0) CreateObject1
(@OGUID+41, 195260, 571, 3711, 4383, 1, 1, 5503.82666015625, 4755.5263671875, -194.433822631835937, 4.904376029968261718, 0, 0, -0.636077880859375, 0.771624863147735595, 120, 255, 1, 0), -- Standing, Interior, Small - Brewfest (Area: Lakeside Landing - Difficulty: 0) CreateObject1
(@OGUID+42, 195260, 571, 3711, 4383, 1, 1, 5498.5927734375, 4745.71630859375, -194.433822631835937, 0.523597896099090576, 0, 0, 0.258818626403808593, 0.965925931930541992, 120, 255, 1, 0), -- Standing, Interior, Small - Brewfest (Area: Lakeside Landing - Difficulty: 0) CreateObject1
(@OGUID+43, 195260, 571, 3711, 4383, 1, 1, 5498.83642578125, 4751.91796875, -194.433822631835937, 5.89921426773071289, 0, 0, -0.19080829620361328, 0.981627285480499267, 120, 255, 1, 0), -- Standing, Interior, Small - Brewfest (Area: Lakeside Landing - Difficulty: 0) CreateObject1
(@OGUID+44, 195256, 571, 3711, 4383, 1, 1, 5499.65478515625, 4733.095703125, -194.544998168945312, 2.460912704467773437, 0, 0, 0.942641258239746093, 0.333807557821273803, 120, 255, 1, 0), -- Standing, Exterior, Medium - Brewfest (Area: Lakeside Landing - Difficulty: 0) CreateObject1
(@OGUID+45, 195260, 571, 3711, 4383, 1, 1, 5513.060546875, 4747.65869140625, -194.433822631835937, 2.932138919830322265, 0, 0, 0.994521141052246093, 0.104535527527332305, 120, 255, 1, 0); -- Standing, Interior, Small - Brewfest (Area: Lakeside Landing - Difficulty: 0) CreateObject1

DELETE FROM `game_event_gameobject` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+45 AND `eventEntry`=@EVENT;
INSERT INTO `game_event_gameobject` SELECT @EVENT, gameobject.guid FROM `gameobject` WHERE gameobject.guid BETWEEN @OGUID+0 AND @OGUID+45;