DELETE FROM `craftsman_text_locale` WHERE `Locale`='zhCN';

INSERT INTO `craftsman_text_locale` (`id`, `locale`, `text`)
VALUES
	(1000, 'zhCN', '裁缝服务'),
	(1100, 'zhCN', '关键词：{0}'),
	(1101, 'zhCN', '<点击输入关键词搜索>'),
	(1102, 'zhCN', '制作{0}需要{1}。'),
	(1103, 'zhCN', '你的背包满了！'),
	(1104, 'zhCN', '{0}很快就好，请稍等一会儿。'),
	(1105, 'zhCN', '我有一个配方要给你。'),
	(1106, 'zhCN', '<返回>'),
	(1107, 'zhCN', '你没有这件物品。'),
	(1108, 'zhCN', '我学会了，谢谢你！'),
	(1109, 'zhCN', '好的！'),
	(1110, 'zhCN', '不用谢！');
