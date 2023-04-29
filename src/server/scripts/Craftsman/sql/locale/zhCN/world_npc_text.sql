DELETE FROM `npc_text_locale` WHERE `Locale`='zhCN' AND `ID` BETWEEN 76000 AND 76999;

INSERT INTO `npc_text_locale` (`ID`, `Locale`, `Text0_0`, `Text0_1`, `Text1_0`, `Text1_1`, `Text2_0`, `Text2_1`, `Text3_0`, `Text3_1`, `Text4_0`, `Text4_1`, `Text5_0`, `Text5_1`, `Text6_0`, `Text6_1`, `Text7_0`, `Text7_1`)
VALUES
	(76000, 'zhCN', '需要我帮你做什么，$R？', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
	(76001, 'zhCN', '抱歉，我现在正忙，请稍等一会儿。', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
	(76002, 'zhCN', '有什么好东西要给我吗？', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
	(76003, 'zhCN', '谢谢！不过我已经学习过这个配方了。', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
	(76004, 'zhCN', '谢谢你！$N！', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
